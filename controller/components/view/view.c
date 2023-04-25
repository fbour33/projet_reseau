#include <stdlib.h>

#include "view.h"
#include "../../utilities/tools.h"

struct view *create_view(int id, int x, int y, int width, int height){
    struct view * view = malloc(sizeof(struct view));

    view->id = id;
    view->p = _position(x,y);
    view->d.width = width;
    view->d.height = height;
    view->free = 1; //1 if free 0 if not
    return view;
}