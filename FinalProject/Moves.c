//
// Created by Dror on 2017-08-25.
//

#include "Moves.h"




MoveList* MoveListCreate(){
    MoveList* list = malloc(sizeof(MoveList));
    if(list == NULL){
        // ERROR
    }
    list -> first = NULL;
    return list;
}

void MovePush(MoveList* list, char y1, char x1, char y2, char x2){
    LinkedMove* move = malloc(sizeof(LinkedMove));
    if(move == NULL){
        // ERROR
    }

    move -> y1 = y1;
    move -> x1 = x1;
    move -> y2 = y2;
    move -> x2 = x2;
    move -> next = list -> first;
    list -> first = move;
}

LinkedMove* MovePop(MoveList* list){
    LinkedMove* move = list -> first;
    if(move != NULL){
        list -> first = move -> next;
    }
    return move;
}

void MoveListDestroy(MoveList* list){
    if(list == NULL) return;
    LinkedMove* temp = list -> first;
    while(temp != NULL){
        list -> first = temp -> next;
        free(temp);
        temp = list -> first;
    }
}



////////


ScoredMove* ScoredMoveCreate(char y1, char x1, char y2, char x2, int score){
    ScoredMove* move = malloc(sizeof(ScoredMove));
    if(move == NULL){
        /// ERROR
    }
    move -> y1 = y1;
    move -> x1 = x1;
    move -> y2 = y2;
    move -> x2 = x2;
    move -> score = score;
    return move;
}

void ScoredMoveDestroy(ScoredMove* move){
    free(move);
}