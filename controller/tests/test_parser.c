#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../parser/parser.h"
#include "../utilities/tools.h"
#include "../components/aquarium/aquarium.h"

void test_parser_load_aquarium() {
    printf("test_parser_load_aquarium  ");

    struct aquarium *aquarium = malloc(sizeof(struct aquarium));
    aquarium->num_aquarium_views=0;
    for (int i = 0; i < MAX_VIEWS; i++) {
        aquarium->aquarium_views[i] = malloc(sizeof(struct view));
    }
    parser_load_aquarium("./tests/aquarium.load.test",aquarium);
    assert(aquarium->num_aquarium_views==4);
    assert(aquarium->dimension.width==1000);
    assert(aquarium->dimension.height==1000);
    
    // view N1
    assert(aquarium->aquarium_views[0]->id==1);
    assert(aquarium->aquarium_views[0]->p.x==0);
    assert(aquarium->aquarium_views[0]->p.y==0);
    assert(aquarium->aquarium_views[0]->d.width==500);
    assert(aquarium->aquarium_views[0]->d.height==500);

    // view N2
    assert(aquarium->aquarium_views[1]->id==2);
    assert(aquarium->aquarium_views[1]->p.x==500);
    assert(aquarium->aquarium_views[1]->p.y==0);
    assert(aquarium->aquarium_views[1]->d.width==500);
    assert(aquarium->aquarium_views[1]->d.height==500);

    // view N3
    assert(aquarium->aquarium_views[2]->id==3);
    assert(aquarium->aquarium_views[2]->p.x==0);
    assert(aquarium->aquarium_views[2]->p.y==500);
    assert(aquarium->aquarium_views[2]->d.width==500);
    assert(aquarium->aquarium_views[2]->d.height==500);

    // view N4
    assert(aquarium->aquarium_views[3]->id==4);
    assert(aquarium->aquarium_views[3]->p.x==500);
    assert(aquarium->aquarium_views[3]->p.y==500);
    assert(aquarium->aquarium_views[3]->d.width==500);
    assert(aquarium->aquarium_views[3]->d.height==500);

    for (int i = 0; i < MAX_VIEWS; i++) {
        free(aquarium->aquarium_views[i]);
    }
    free(aquarium);
    printf("OK\n");
}

int main(){
    test_parser_load_aquarium();
    return 0;
}