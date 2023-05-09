#include "test.h"

/**
 * @brief test function view aquarium 
 * @note if you want to test in the tes directory, you need to change path of 
 * the aquarium.load file because it a relative path
 * @note the best way it to test from the controller directory
 */
void test_function_view_aquarium(){
    printf("test_add_view_aquarium :");
    struct aquarium *aquarium = create_aquarium();
    load_aquarium(aquarium);
    show_aquarium(aquarium);

    struct view* view = create_view(5, 400, 200, 400, 400);
    
    add_view_aquarium(aquarium,view);
    save_aquarium(aquarium);
    show_aquarium(aquarium);
    del_view_aquarium(aquarium,2);
    show_aquarium(aquarium);
    free_aquarium(aquarium);
    printf("test_add_view_aquarium :\tOK\n");
}

int main(){
    //initialise le fichier log ou pas
	char log_dir[MSG_LEN] = LOG_DIR;
	log_f = init_log_f(log_dir);

    test_function_view_aquarium();
}