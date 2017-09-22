//
// Created by Jonathan Gescheit on 9/22/17.
//

#include "ChessWidget.h"

void destroyWidget(ChessWidget* src) {//Making NULL Safe Destroy
    if (src == NULL ) {
        return;
    }
    src->destroyWidget(src);
}