#include "all.H"

using namespace raii;
namespace prototype {

        import::operator raii::String() {
         
                return raii::String("<script src=\"") + path.escapeAttribute() + "/prototype.js\" type=\"text/javascript\"></script>\n";
        }
        

        void import::doStart(HttpServletRequest& request, HttpServletResponse& response) {
                
                response << *this;
        }
        
        
        void import::setPath(const raii::String& thePath) {
                
                path=thePath;
        }
}
