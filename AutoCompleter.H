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
