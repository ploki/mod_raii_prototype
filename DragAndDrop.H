

/*
<%:Draggable id="elem_id";     // element sur lequel s'applique l'effet
             handle="elem_id"; // id de la poignée ou class ( premier trouvé )
             revert="false|true|fonction"; // revient à sa position originale
             snap="false|fonction";
             zIndex=int;                //css zindex
             constraint="horizontal|vertical";
             ghosting="false|true"; //clone elem et drag le clone
             startEffect="Opacity";
             revertEffect="Move";
             endEffect="Opacity";
             change="function(id) {}"; //appelé quand le drag est déplacé

%>

*/

class Draggable : public Control {

        protected:
        
        raii::String getRequiredOptions() {
                return "";
        }
        
        public:
        
        Draggable() : Control("new Draggable") {}
        
        void setHandle(const raii::String& str)     { option["handle"]    =jsEscape(str); }
        void setRevert(const raii::String& str)     { option["revert"]    =jsEscape(str); }
        void setSnap(const raii::String& str)       { option["snap"]      =jsEscape(str); }
        void setZIndex(int i)                      { option["zindex"]    =raii::itostring(i);   }
        void setConstraint(const raii::String& str) { option["constraint"]=jsEscape(str); }
        void setGhosting(bool b)                    { option["ghosting"]   = (b?"true":"false"); }
        void setStartEffect(const raii::String& str) { option["stareffect"] =jsEscape(str); }
        void setRevertEffect(const raii::String& str){ option["reverteffect"] =jsEscape(str); }
        void setEndEffect(const raii::String& str )  { option["endeffect"]    =jsEscape(str); }
        void setChange(const raii::String& str )     { option["change"] =jsEscape(str); }

};


/*

<script>
callback= function (draggable,droppable) {
        <%:Ajax update="droppable"...draggable... %>
}
</script>


<div id="product_1" class="product"></div>
<div id="product_2" class="product"></div>
<div id="product_3" class="product"></div>
<div id="depot"></div>

<%:Droppable for="depot";
             accept="product"; //quel class de draggable est accepté
             containment=""; //quels id de draggable est accepté un seul ou un tableau
             hoverclass=""; //class css additionnelle lors qu'un "accepté" est au dessus
             overlap="horizontal|vertical";
             greedy="true|false"; // ne va pas chercher les autres droppables si ils chevauchent celui ci
             onDrop="callback";
             onHover="autrecallback";
             
             %>


*/



class Droppable : public Control {
        protected:
        
        raii::String getRequiredOptions() {
                return "";
        }
        
        public:
        
        Droppable() : Control("Droppables.add") {}
        
        void setAccept(const raii::String& str)      { option["accept"]     =jsEscape(str); }
        void setContainment(const raii::String& str) { option["containment"]=jsEscape(str); }
        void setHoverClass(const raii::String& str)  { option["hoverclass"] =jsEscape(str); }
        void setHover(const raii::String& str)       { option["hoverclass"] =jsEscape(str); }
        void setGreedy(const raii::String& str)      { option["greedy"]     =jsEscape(str); }
        void setOnHover(const raii::String& str)     { option["onHover"]    =jsEscape(str); }
        void setOnDrop(const raii::String& str)      { option["onDrop"]     =jsEscape(str); }
};
