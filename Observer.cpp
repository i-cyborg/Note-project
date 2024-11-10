//
// Created by volta on 08/11/2024.
//

#include "Observer.h"

//1 = add note, 0 = remove note
void Observer::update(const int noteNumChange) {
    if(noteNumChange == 1)
        noteCount++;
    else
        noteCount--;
}

int Observer::getNoteCount() const {
    return noteCount;
}
