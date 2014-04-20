
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



