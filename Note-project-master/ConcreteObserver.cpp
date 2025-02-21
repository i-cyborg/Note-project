//
// Created by volta on 08/11/2024.
//

#include "ConcreteObserver.h"
#include <iostream>


ConcreteObserver::ConcreteObserver(Collection* c) : subject(c) {
    attach();
}

ConcreteObserver::~ConcreteObserver() {
    detach();
}

int ConcreteObserver::update() {
    if (subject) {
        noteCount = subject->getNoteCount();
        showNoteCount();
        return noteCount;
    }
}

void ConcreteObserver::attach() {
    if (subject) {
        subject->registerObserver(this);
    }
}

void ConcreteObserver::detach() {
    if (subject) {
        subject->removeObserver(this);
    }
}

void ConcreteObserver::showNoteCount() const {
    std::cout << "Numero di note nella collezione: " << noteCount << std::endl;
}
