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

class Control {
        protected:

        raii::String jsName;

        raii::String id;
        raii::Map<raii::String,raii::String> option;        
	public:

        static raii::String jsEscape(const raii::String& str) {
                
                raii::String tmp;
                
                for ( raii::String::const_iterator it=str.begin() ;
                      it != str.end() ;
                      ++it ) {
                       if ( *it == '\'' )
                               tmp+="\\'";
			else if ( *it == '\n' )
				tmp+="\\n";
                       else
                               tmp+=*it;
                }
                return raii::String("'") + tmp + "'";
        }
        protected:
        Control(const raii::String name) : jsName(name), id(""), option() {}
        
	virtual ~Control() {}

        virtual raii::String getRequiredOptions()=0;
        virtual raii::String getPrefix() {
                return "";
        }
        virtual raii::String getPostfix() {
                return "";
        }
        raii::String getOptions() {
                
                raii::String options="";
                
                for ( raii::Map<raii::String,raii::String>::const_iterator it=option.begin();
                      it != option.end() ;
                      /*nop*/ ) {
		        if ( it->second.empty() ) 
				options += it->first + ": 'boggus value'";
			else
        	                options += it->first + ": " + it->second ;
                        if ( ++it != option.end() )
                                options += ", ";
                }
                return options;
        }


        raii::String tostring() {
                raii::String prefix=getPrefix();
                raii::String postfix=getPostfix();
                raii::String options=getOptions();
                raii::String requiredOptions=getRequiredOptions();               
                 return prefix + "<script type=\"text/javascript\">\n"
			        "//<![CDATA[\n"
                         + jsName + "('" + id  +"'"
                         + ( requiredOptions.empty()?"": ( raii::String(", ") + requiredOptions ) )
                         + ( options.empty()?"": ( raii::String(", {") + options + "}" ) )
                         +");\n"
                          "//]]>\n"
			   "</script>\n" + postfix;
        }


        public:

        void setId(const raii::String& str) { id=str; }

        void doStart(raii::HttpServletRequest& request, raii::HttpServletResponse& response) {

                response << tostring();
        }
};



