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
    free(lmove);
}


MoveList* MoveListCreate(){
    MoveList* list = malloc(sizeof(MoveList));
    if(list == NULL){
        // ERROR
        return NULL;
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

LinkedMove* MovePop(MoveList* list){
    LinkedMove* lmove = list -> first;
    if(lmove != NULL){
        list -> first = lmove -> next;
    }
    return lmove;
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


bool isMoveListEmpty(MoveList* list){
    if(list == NULL){ return true; } // maybe should be false?
    return list->first == NULL;
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
        free(smove);
        return NULL;
    }
    smove -> move = move;
    smove -> score = score;
    return smove;
}

void ScoredMoveDestroy(ScoredMove* smove){
    if(smove != NULL){
        MoveDestroy(smove -> move);
    }
    free(smove);
}


/////////////////////

HistoryMove* HistoryMoveCreate(char y1, char x1, char y2, char x2, char original){
    HistoryMove* hist = malloc(sizeof(HistoryMove));
    if(hist == NULL){
        // ERROR
        return NULL;
    }
    hist->move = MoveCreate(y1, x1, y2, x2);
    if(hist -> move == NULL){
        free(hist);
        return NULL;
        // error
    }
    hist->original = original;
    return hist;
}

void HistoryMoveDestroy(HistoryMove* hist){
    if(hist != NULL) free(hist->move);
    free(hist);
}