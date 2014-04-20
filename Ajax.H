/* 
 * Copyright (c) 2006-2011, Guillaume Gimenez <guillaume@blackmilk.fr>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of G.Gimenez nor the names of its contributors may
 *       be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL G.Gimenez SA BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors:
 *     * Guillaume Gimenez <guillaume@blackmilk.fr>
 *
 */
/*
  < % : Ajax 

          //preparation de l'appel ( javascript)
          confirm="chaine";
          condition="condition javascript";
          before="expression javascript";
          after="expression javascript";


          
          //appel ajax
          url="/chaine/de/caractÃšre/sans/le/contextPath";
          update="success_id"[,"failure_id"];
          [cb["403|500|...|uninitialized|loading|loaded|interactive|complete"]="expression javascript";...]
          asynchronous=true|false;
          method="get"|"post";
          submit="form_id|this";
          [with["name"]="value";...] nom et valeurs url_encodÃ©s
          with|withTail="expression javascript : '&value='+value par exemple"
          evalScripts=true|false;
	  stopEvent=true|false

         % >  
*/
class Ajax {
        raii::String confirm,condition,before,after;
        
        raii::String url;
        raii::String failure,update;
        mutable raii::Map<raii::String,raii::String> callback;
        mutable raii::Map<raii::String,raii::String> with;
        raii::String withTail;
        mutable raii::Map<raii::String,raii::String> ajaxParameter;

        raii::String method;
        enum WhichMap{ Callback, With };
        bool asynchronous;
        bool evalScripts;
        raii::String submit;
	bool stopEvent;

        
        raii::String currentKey;
        WhichMap whichMap;
        
        
        
        public:
        class Setter {
                Ajax& ajax;
                WhichMap curmap;
                public:
                Setter(Ajax& a,WhichMap map) : ajax(a),curmap(map) {};
                Ajax& operator[] (const raii::String& key) {
                        ajax.setWhichMap(curmap);
                        ajax.setCurrentKey(key);
                        return ajax;
                }
                void operator() (const raii::String& s) {
                  ajax.setWithTail(s);
                }
        };

        Setter setCb;
        Setter setWith;

        Ajax& setConfirm(const raii::String& s) { confirm=s; return *this;}
        Ajax& setCondition(const raii::String& s) { condition=s; return *this;}
        Ajax& setBefore(const raii::String& s) { before=s; return *this;}
        Ajax& setAfter(const raii::String& s) { after=s; return *this;}
        Ajax& setWithTail(const raii::String& s) { withTail=s; return *this; }
        Ajax& setUrl(const raii::String& s) {
          raii::RaiiConfig* cfg=raii::get_dconfig(raii::apacheRequest);
          url=raii::String(cfg->contextpath) + s;
          return *this;
        }
        Ajax& setUpdate(const raii::String& u,const raii::String& f="") { update=u; failure=f; return *this; }
        Ajax& setSubmit(const raii::String& s) { submit=s; return *this; }
	Ajax& setStopEvent(bool b) { stopEvent=b; return *this; }
        Ajax& setMethod(const raii::String& m) { method=m; return *this; }
        Ajax& setAsynchronous(bool b) { asynchronous=b; return *this; }
        Ajax& setEvalScripts(bool b) { evalScripts=b; return *this; }

        ~Ajax() {
        }
        Ajax() :
          confirm(""),
          condition(""),
          before(""),
          after(""),
          url(""),
          failure(""),
          update(""),
          callback(),
          with(),
          withTail(""),
          ajaxParameter(),
          method("get"),
          asynchronous(true),
          evalScripts(false),
          submit(""),
	  stopEvent(true),
          currentKey(""),
          whichMap(Callback),
          setCb(*this,Callback),
          setWith(*this,With) {}

          
        void setCurrentKey(const raii::String& k) { currentKey=k; }
        void setWhichMap(WhichMap m) { whichMap=m; }
        
        Ajax& operator() (const raii::String& value) {
                switch (whichMap) {
                        case Callback:
                                callback[currentKey]=value;
                                break;
                        case With:
                                with[currentKey]=value;
                                break;
                        default:
                                throw "Unknown map!";
                }
                return *this;
        }

/*
        operator String() const{
                return this->toString();
        }
  */      
        raii::String toString() const {

                raii::StringStream ss_update;
                if ( !update.empty() && !failure.empty() ) {
                        ss_update << "{ "
                                  << " success: '" << update << "',"
                                  << " failure: '" << failure << "' }";
                } else if ( !update.empty() ) {
                        ss_update << "'" << update << "'";
                }

                raii::StringStream ss_function;
                ss_function << ( ss_update.str().empty() ?
                        ( raii::String("new Ajax.Request(") ) :
                        ( raii::String("new Ajax.Updater(")  + ss_update.str() + ", " ) )

                        << "'" << url << "', {";

                for ( raii::Map<raii::String, raii::String>::const_iterator it=callback.begin() ;
                      it != callback.end() ;
                      ++it ) {
                        ajaxParameter[raii::String("on") + (char)toupper(it->first[0]) + it->first.substr(1)]
                          = raii::String("function(transport) {") + it->second + "}";
                }
                ajaxParameter["asynchronous"] = asynchronous ? "true" : "false";
                ajaxParameter["method"] = method == "get" ? "'get'" : "'post'";
                
                if ( ! submit.empty() ) {
                        if ( submit == "this" )
                                ajaxParameter["parameters"] = "Form.serialize(this)";
                        else
                                ajaxParameter["parameters"] = raii::String("Form.serialize('")+submit+"')";
                }
                if ( ! with.empty() ) {
                        raii::String qs;
                        for ( raii::Map<raii::String,raii::String>::const_iterator it=with.begin();
                              it != with.end() ;
                              /*nop*/ ) {
                                qs += raii::url_encode( it->first ) + "=" + raii::url_encode( it->second );
                                if ( ++it != with.end() )
                                  qs += "&";
                        }
                        ajaxParameter["parameters"] =
                                raii::String( ajaxParameter["parameters"].empty()
                                  ? raii::String("'") 
                                  : ( ajaxParameter["parameters"] + "+'&")  )
                                + qs + "'";
                }
                if ( ! withTail.empty() ) {
                  ajaxParameter["parameters"] =
                    raii::String( ajaxParameter["parameters"].empty()
                      ? raii::String("")
                       : ( ajaxParameter["parameters"] + " + ")  )
                       + withTail ;
                }
                
                ajaxParameter["evalScripts"]= evalScripts?"true":"false";
                
                
                for ( raii::Map<raii::String,raii::String>::const_iterator it=ajaxParameter.begin();
                        it != ajaxParameter.end() ;
                        /*nop*/ ) {
                        ss_function << it->first << ": " << it->second;
                        if ( ++it != ajaxParameter.end() )
                                ss_function << ", ";
                }
                
                ss_function << "} )";
                raii::String function=ss_function.str();

                if ( ! before.empty() ) {
                        function = before + "; " + function;
                }
                if ( ! after.empty() ) {
                        function = function + "; " + after;
                }
                if ( ! condition.empty() ) {
                        function = raii::String("if ( ")+condition+" ) { "+function+"; }";
                }
                if ( ! confirm.empty() ) {
                        function = raii::String("if (confirm('")+confirm+"')) { "+function+"; }";
                }

                return function + ";" + (stopEvent?" return false;":"");
        }
        void doStart(raii::HttpServletRequest& request, raii::HttpServletResponse& response) {
                response << toString();
        }
};




