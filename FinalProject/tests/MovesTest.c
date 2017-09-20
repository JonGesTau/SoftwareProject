//
// Created by Dror on 2017-09-17.
//

#include "MovesTest.h"

void MovesTestPrintMoves(MoveList* list){
    LinkedMove* lmove = MovePop(list);
    if(lmove == NULL) return;
    Move* move;

    while(lmove != NULL){
        move = lmove->move;
        printf("next move is: (%d, %d) -> (%d, %d)\n", move->y1, move->x1, move->y2, move->x2);
        LinkedMoveDestroy(lmove);
        lmove = MovePop(list);
    }
}

int MovesTestLinked(){
    MoveList* list = MoveListCreate();
    if(list == NULL){
        printf("list problem\n");
        return -1;
    }

    MovePush(list, 1, 1, 3, 1);
    MovePush(list, 3, 5, 2, 5);
    MovePush(list, 2, 5, 2, 3);

    MovesTestPrintMoves(list);
    return 1;
}


int MovesTestScore(){

}
