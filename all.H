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
