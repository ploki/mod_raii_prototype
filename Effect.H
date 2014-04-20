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
namespace Effect {


class Base {
        raii::String effectName;
        raii::String for_;
        bool return_;
        raii::String currentKey;
        raii::String lowlevelEffect;
        raii::Map<raii::String,raii::String> js_options;
        public:
        class Setter {
                Base& base;
                public:
                Setter(Base& b) : base(b) {};
                Base& operator[] (const char * key) {
                        base.setCurrentKey(key);
                        return base;
                }
        };

        Setter set;

        void setCurrentKey(const raii::String& str) { currentKey=str; }


        void operator() (const raii::String& str) { js_options[currentKey] = str; }


        Base(const raii::String& name) : effectName(name), for_("this"), return_(false), currentKey(""), lowlevelEffect(""), js_options(), set(*this) {}
        virtual ~Base() {}
        

        void setFor(const raii::String& str) { for_=str; }
        void setReturn(bool b) { return_=b; }
        void setEffect(const raii::String& str) { lowlevelEffect=str; }
        
        raii::String tostring() {
                raii::StringStream ss;
                ss << "Effect." << effectName << "(";
                if ( for_ == "this" )
                        ss << "this";
                else
                        ss << "'" << for_ << "'";
                if ( ! lowlevelEffect.empty() ) {
                        ss << ", '" << lowlevelEffect << "'";
                }
                if ( ! js_options.empty() ) {
                        ss << ", {";
                        for ( raii::Map<raii::String,raii::String>::const_iterator it=js_options.begin();
                              it != js_options.end() ;
                              /*nop*/ ) {
                                ss << it->first << ": " << it->second;
                                if ( ++it != js_options.end() )
                                        ss << ", ";
                        }
                        ss << "}";
                }
                ss << "); return " << ( return_?"true":"false" ) << ";";
                return ss.str();
        }
        
        void doStart(raii::HttpServletRequest& request, raii::HttpServletResponse& response) {
                response << tostring();
        }
};

#define new_effect(name)    \
class name : public Base {  \
  public:                   \
  name() : Base( #name ) {} \
}

/*
  <%:Effect::Appear for="id|this";
                    ["duration"]="3.0"; //durÃ©e
                    ["from"]="_0.0_ to 1.0"; //opacitÃ©
                    ["to"]="0.0 to _1.0_";   //opacitÃ©
                    %>
*/
new_effect(Appear);

/*
  <%:Effect::Fade for="id|this";
                  ["duration"]="3.0"; //durÃ©e
                  ["from"]="_0.0_ to 1.0"; //opacitÃ©
                  ["to"]="0.0 to _1.0_";   //opacitÃ©
                  ["transition"]="Effect.Transitions.wobble";
                    %>
*/
new_effect(Fade);


/* comme Appear */
new_effect(Puff);

/* sans options */
new_effect(DropOut);

/* sans options */
new_effect(Shake);

/*
  <%:Effect::Highlight for="id|this";
                       ["startcolor"]="#ffff99";
                       ["endcolor"]="#ffffff";
                       ["restorecolor"]="#......"; // si la couleur n'a pas Ã©tÃ© donnÃ©es par rgb(,,) dans le style de l'Ã©lÃ©m
*/
new_effect(Highlight);


/* sans options */
new_effect(SwitchOff);

/*
 <%:Effect::Blind[Down|Up] for="id|this";
                           ["scaleX"]="true|_false_";
                           ["scaleY"]="_true_|false";
                           ["scaleContent"]="_true_|false";
                           ["scaleFromCenter"]="true|_false_";
                           ["scaleMode"]="'box'|'contents'";
                           ["scaleFrom"]="100.0"; // de 0% Ã  100%
                           ["scaleTo"]="0";
                           ["duration"]="1";
 %>
*/
new_effect(BlindDown);
new_effect(BlindUp);


/* comme Blind[Down|Up] */
new_effect(SlideDown);
new_effect(SlideUp);

/* sans options */
new_effect(Pulsate);
new_effect(Squish);
new_effect(Fold);

/*
  <%:Effect::Grow for="id|this";
                  ["direction"]="'top-left'|'top-right'|'bottom-left'|'bottom-right'|'center'";
  %>
*/
new_effect(Grow);

/*sans options */
new_effect(Shrink);


/*
  <%:Effect::toggle for="id|this";
                    effect="appear|slide|blind";
                    options...
  %>
*/
new_effect(toggle);

}
