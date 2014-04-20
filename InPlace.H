


// http://wiki.script.aculo.us/scriptaculous/show/Ajax.InPlaceEditor


class InPlaceEditor : public Control {
        protected:
        raii::String getRequiredOptions() {
                return raii::String("'")+url+"'";
        }
        
        public:
        
        InPlaceEditor(const raii::String name="new Ajax.InPlaceEditor") : Control(name) {
                //french l10n
                option["okText"]=jsEscape("Envoyer");
                option["cancelText"]=jsEscape("Annuler");
                option["savingText"]=jsEscape("Envoi...");
                option["clickToEditText"]=jsEscape("Cliquez pour éditer ce champ");
                option["loadingText"]=jsEscape("Chargement...");
        }
        
        raii::String url;
        void setUrl(raii::String str) { url=str; };
        
        void setOkButton(bool b) { option["okButton"] = b?"true":"false"; }
        void setOkText(raii::String str) { option["okText"] = jsEscape(str); }
        void setCancelLink(bool b) { option["cancelLink"] = b?"true":"false"; }
        void setCancelText(raii::String str) { option["cancelText"] = jsEscape(str); }
        void setSavingText(raii::String str) { option["savingText"] = jsEscape(str); }
        void setClickToEdit(raii::String str) { option["clickToEditText"] = jsEscape(str); }
        void setFormId(raii::String str) { option["formId"] = jsEscape(str); }
        void setExternalControl(raii::String str) { option["externalControl"] = jsEscape(str); }
        void setRows(int i) { option["rows"] = raii::itostring(i); }
        void setOnComplete(raii::String str) { option["onComplete"] = jsEscape(str); }
        void setOnFailure(raii::String str) { option["onFailure"] = jsEscape(str); }
        void setCols(int i) { option["cols"] = raii::itostring(i); }
        void setSize(int i) { option["size"] = raii::itostring(i); }
        void setHighlightColor(raii::String str) { option["highlightcolor"] = jsEscape(str); }
        void setHighlightEndColor(raii::String str) { option["highlightendcolor"] = jsEscape(str); }
        void setSavingClassName(raii::String str) { option["savingClassName"] = jsEscape(str); }
        void setFormClassName(raii::String str) { option["formClassName"] = jsEscape(str); }
        void setHoverClass(raii::String str) { option["hoverClass"] = jsEscape(str); }
        void setName(raii::String str) { option["Name"] = jsEscape(str); }
        void setLoadTextURL(raii::String str) { option["loadTextURL"] = jsEscape(str); }
        void setLoadingText(raii::String str) { option["loadingText"] = jsEscape(str); }
        void setCallback(raii::String str) { option["callback"] = jsEscape(str); }
        void setSubmitOnBlur(bool b) { option["submitOnBlur"] = b?"true":"false"; }
        void setAjaxOptions(raii::String str) { option["ajaxOptions"] = jsEscape(str); }
        
        
};


// http://wiki.script.aculo.us/scriptaculous/show/Ajax.In+Place+Collection+Editor

class InPlaceCollectionEditor : public InPlaceEditor {

        protected:

        raii::Map<raii::String, raii::String> collection;
        const char * currentKey;
        
        raii::String getRequiredOptions() {
                raii::String col="";
                for ( raii::Map<raii::String,raii::String>::const_iterator it = collection.begin();
                      it != collection.end() ;
                      /* nop */ ) {
                        col = col + "['"+ jsEscape(it->first) +"','"+ jsEscape(it->second) +"']";
                        if ( ++ it != collection.end() )
                                col += ", ";
                }
                if ( ! col.empty() ) {
                        col = raii::String("[") + col + "]";
                        option["collection"] = col;
                }
                
                return raii::String("'")+url+"'";
        }

        public:
        
        class Setter {
                InPlaceCollectionEditor& editor;
                public:
                Setter(InPlaceCollectionEditor& e) : editor(e) {}
                InPlaceCollectionEditor& operator[] (const char *key) {
                        editor.setCurrentKey(key);
                        return editor;
                }
        };
        
        Setter set;
        void setCurrentKey(const char* k) {
                currentKey=k;
        }
        void operator() (const char *value) {
                collection[currentKey]=value;
        }

        InPlaceCollectionEditor() 
                : InPlaceEditor("new Ajax.InPlaceCollectionEditor"),
                  collection(),
                  currentKey(NULL),
                  set(*this) {}



};

