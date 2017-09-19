//
// Created by Dror on 2017-08-25.
//

#include "Moves.h"



Move* MoveCreate(char y1, char x1, char y2, char x2){
    Move* move = malloc(sizeof(Move));
    if(move == NULL)
        return NULL;
    move -> y1 = y1;
    move -> x1 = x1;
    move -> y2 = y2;
    move -> x2 = x2;
    return move;
}

void MoveDestroy(Move* move){
    free(move);
}


LinkedMove* LinkedMoveCreate(char y1, char x1, char y2, char x2){
    LinkedMove* lmove = malloc(sizeof(LinkedMove));
    if(lmove == NULL){
        // ERROR
        return NULL;
    }
    lmove -> move = MoveCreate(y1, x1, y2, x2);
    if(lmove -> move == NULL){
        free(lmove);
        return NULL;
        // ERROR
    }
    return lmove;
}
void LinkedMoveDestroy(LinkedMove* lmove){
    if(lmove -> move != NULL){
        MoveDestroy(lmove -> move);
    }
    if(lmove != NULL)
        free(lmove);
}


MoveList* MoveListCreate(){
    MoveList* list = malloc(sizeof(MoveList));
    if(list == NULL){
        // ERROR
    }
    list -> first = NULL;
    return list;
}

void MovePush(MoveList* list, char y1, char x1, char y2, char x2){
    LinkedMove* lmove = LinkedMoveCreate(y1, x1, y2, x2);
    if(lmove == NULL){
        // ERROR
        return;
    }

    lmove -> next = list -> first;
    list -> first = lmove;
}

Move* MovePop(MoveList* list){
    LinkedMove* lmove = list -> first;
    if(lmove != NULL){
        list -> first = lmove -> next;
    }
    return lmove -> move;
}

void MoveListDestroy(MoveList* list){
    if(list == NULL) return;
    LinkedMove* temp = list -> first;
    while(temp != NULL){
        list -> first = temp -> next;
        LinkedMoveDestroy(temp);
        temp = list -> first;
    }
}



////////


ScoredMove* ScoredMoveCreate(char y1, char x1, char y2, char x2, int score){
    ScoredMove* smove = malloc(sizeof(ScoredMove));
    if(smove == NULL){
        /// ERROR
        return NULL;
    }

    Move* move = MoveCreate(y1, x1, y2, x2);
    if(move == NULL){
        // ERROR
        return NULL;
    }

    move -> y1 = y1;
    move -> x1 = x1;
    move -> y2 = y2;
    move -> x2 = x2;
    smove -> score = score;
    return smove;
}

void ScoredMoveDestroy(ScoredMove* move){
    free(move);
}