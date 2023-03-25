#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../components/aquarium/aquarium.h"

/**
 * @brief test function view aquarium 
 * @note if you want to test in the tes directory, you need to change path of 
 * the aquarium.load file because it a relative path
 * @note the best way it to test from the controller directory
 */
void test_function_view_aquarium(){
    printf("test_add_view_aquarium\n");
    struct aquarium *aquarium = create_aquarium();
    load_aquarium(aquarium);
    show_aquarium(aquarium);
    struct view *view = malloc(sizeof(struct view));
    view->id=5;
    view->d.height=400;
    view->d.width=200;
    view->p.x=400;
    view->p.y=400;
    add_view_aquarium(aquarium,view);
    save_aquarium(aquarium);
    show_aquarium(aquarium);
    del_view_aquarium(aquarium,2);
    show_aquarium(aquarium);
    free_aquarium(aquarium);
}

int main(){
    test_function_view_aquarium();
}


