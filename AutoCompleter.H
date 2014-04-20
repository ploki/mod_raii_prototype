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

<input class="%CLASS|autocomplete" type="text" id="%ID%" name="%ID%_parameter"/>
<span id="%ID%_indicator" style="display: none"><img src="%WORKINGIMAGE%" alt="%WORKINGTXT%" /></span>
<div id="%ID%_choices" class="%CLASS%|autocomplete"></div>
new Ajax.Autocompleter("%ID%",
                       "%ID%_choices",
                       "/url/on/server",
                       { paramName: "value",
                         minChars: 2,
                         updateElement: addItemToList,
                         indicator: '%ID%_indicator'});

http://wiki.script.aculo.us/scriptaculous/show/Ajax.Autocompleter

*/


class AutoCompleter : public Control {

        protected:

        raii::String getRequiredOptions() {
                return raii::String("'")+id+"_choices', '"+url+"'";
        }
        raii::String getPrefix() {
                option["paramName"] = jsEscape(name);
                option["indicator"] = jsEscape(id+"_indicator");
                return raii::String("<input class=\"")+class_.escapeAttribute()+"\" type=\"text\" id=\""+id.escapeAttribute()+"\" name=\""+name.escapeAttribute()+"\" value=\""+value.escapeAttribute()+"\" "+(onChange.empty()?raii::String(""):raii::String("onchange=\"")+onChange+raii::String("\""))+"/>\n"
                  + "<span class=\""+class_.escapeAttribute()+"_indicator\" id=\""+id.escapeAttribute()+"_indicator\" style=\"display: none\"><img src=\""+workingImage.escapeAttribute()+"\" alt=\""+workingText.escapeAttribute()+"\" /></span>\n"
                  + "<div id=\""+id.escapeAttribute()+"_choices\" class=\""+class_.escapeAttribute()+"_choices\"></div>\n";
                  
        }
        
        public:

        raii::String url;
        raii::String class_;
        raii::String workingImage, workingText;
	raii::String value;
	raii::String name;
        raii::String onChange;
        
        AutoCompleter() : Control("new Ajax.Autocompleter") { }


        void setWorkingImage(const raii::String& str) { workingImage=str; }
        void setWorkingText(const raii::String& str) { workingText=str; }
        void setUrl(const raii::String& str) { url=str; }
        void setClass(const raii::String& str) { class_=str; }
        //void setParamName(const raii::String& str) { option["paramName"] = jsEscape(str); }
        void setTokens(const raii::String& str) { option["tokens"] = str; }
        void setFrequency(const raii::String& str) { option["frequency"] = str; }
        void setMinChars(int i) { option["minChars"] = raii::itostring(i); }
        //void setIndicator(const raii::String& str) { option["indicator"] = jsEscape(str); }
        void setUpdateElement(const raii::String& str) { option["updateElement"] = jsEscape(str); }
        void setAfterUpdateElement(const raii::String& str) { option["afterUpdateElement"] = str; }
        void setValue(const raii::String& str) { value=str; }
	void setName(const raii::String& str) { name=str; }
        void setOnChange(const raii::String& str) { onChange=str; }
      
};
