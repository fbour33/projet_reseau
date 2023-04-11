#include <stdio.h>
#include <assert.h>
#include "../components/view/view.h"


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

int main(int argc, char* argv[])
{
    test_create_view();
    test_add_fish_in_view();
}