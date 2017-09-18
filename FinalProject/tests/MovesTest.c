//
// Created by Dror on 2017-09-17.
//

#include "MovesTest.h"



int MovesTestLinked(){
    MoveList* list = MoveListCreate();
    if(list == NULL){
        printf("list problem\n");
        return -1;
    }

    MovePush(list, 1, 1, 3, 1);
    MovePush(list, 3, 5, 2, 5);
    MovePush(list, 2, 5, 2, 3);

    Move* move = MovePop(list);

    while(move != NULL){
        printf("next move is: (%d, %d) -> (%d, %d)\n", move->y1, move->x1, move->y2, move->x2);
        MoveDestroy(move);
        move = MovePop(list);
    }

    MoveListDestroy(list);
    return 1;
}


int MovesTestScore(){

}
