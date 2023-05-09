#include "test.h"


void test_create_view() {
    printf("test_create_view:\tOK\n");
    struct view* v1 = create_view(0, 1, 2, 3, 4);
    free_view(v1);
}

void test_add_fish_in_view() {
    printf("test_add_fish_in_view:\t");
    struct view* v1 = create_view(0, 0, 0, 600, 400);
    struct fish* f1 = create_fish("Alex", REDFISH, HORIZONTAL, 100, 100, 600, 400);
    struct fish* f2 = create_fish("Flo", CLOWNFISH, VERTICAL, 200, 200, 600, 400);
    assert(delete_fish(v1, "blablabla") == -1);

    assert(add_fish(v1, f1) == 0);
    assert(add_fish(v1, f2) == 0);

    assert(delete_fish(v1, "Alex") == 0);
    assert(delete_fish(v1, "Alec") == -1);

    free_view(v1);
    printf("OK\n");
}

void test_get_status_fish() {
    char msg[1024];
    char resp[1024];
    printf("test_get_status_fish:\n");
    struct view* v1 = create_view(0, 0, 0, 600, 400);
    struct fish* f1 = create_fish("Alex", REDFISH, HORIZONTAL, 100, 100, 600, 400);
    struct fish* f2 = create_fish("Flo", CLOWNFISH, VERTICAL, 200, 200, 600, 400);
    assert(delete_fish(v1, "blablabla") == -1);

    assert(add_fish(v1, f1) == 0);
    assert(add_fish(v1, f2) == 0);

    get_fishes(v1, msg,0);
    printf("%s", msg);
    status(v1, resp);
    printf("%s\n", resp);

    assert(delete_fish(v1, "Alex") == 0);

    get_fishes(v1, msg, 0);
    printf("%s", msg);
    status(v1, resp);
    printf("%s", resp);
    
    free_view(v1);
    printf("test_get_status_fish:\tOK\n");
}

int main()
{
    //initialise le fichier log ou pas
	char log_dir[MSG_LEN] = LOG_DIR;
	log_f = init_log_f(log_dir);

    test_create_view();
    test_add_fish_in_view();
    test_get_status_fish();
}