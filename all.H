#include <raii.H>

namespace prototype {

        
        /*
        
        <%:prototype::import [path="/chemin";]%> 
        
        */
class Import {
        raii::String path;
        public:
        Import() : path("/prototype") {}
        void setPath(const raii::String& thePath) {
                
                path=thePath;
        }
        operator raii::String(){
         
                return raii::String("<script src=\"") + path + "/prototype.js\" type=\"text/javascript\"></script>\n" +
                       raii::String("<script src=\"") + path + "/scriptaculous.js\" type=\"text/javascript\"></script>\n";
        }
        void doStart(raii::HttpServletRequest& request, raii::HttpServletResponse& response) {
                
                response << *this;
        }
        
};

class Include {
        raii::String page;
        public:
        void setPage(const raii::String& str) { page=str; }
        void doStart(raii::HttpServletRequest& request, raii::HttpServletResponse& response) {
          raii::RequestDispatcher rd=request.getRequestDispatcher(page);
          rd.include(request,response);
        }
};
#include "Ajax.H"
#include "Effect.H"
#include "Control.H"
#include "DragAndDrop.H"
#include "InPlace.H"
#include "AutoCompleter.H"
}
