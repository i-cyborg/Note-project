//
// Created by volta on 05/11/2024.
//

#include "Collection.h"
#include "Note.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

Collection::Collection(const std::string &n) : name(n){
}

void Collection::addNote(const std::shared_ptr<Note>& note) {
    notes.push_back(note);
    notifyObservers(1);
}

bool Collection::removeNote(const std::string &title) {
    for(auto t = notes.begin(); t != notes.end(); ++t ) {
        if ((*t)->getTitle() == title) {
            if((*t)->getLock()) {
                std::cout << "Impossibile rimuovere la nota perché è bloccata" << std::endl;
                return false;
            } else {
                notes.erase(t);
                notifyObservers(0);
                return true;
            }
        }
    }

    std::cout << "Nota non trovata" << std::endl;
    return false;
}

std::string Collection::getName() const {
    return name;
}

std::shared_ptr<Note> Collection::getNotes(const int i) {
    if (i >= 0 && i < notes.size()) {
        return notes[i];
    }
    return nullptr;
}

void Collection::registerObserver(const std::shared_ptr<Observer>& observer) {
    observers.push_back(observer);
}

void Collection::removeObserver(const std::shared_ptr<Observer>& observer) {
    std::erase(observers, observer);
}

void Collection::notifyObservers(const int noteNumChange) {
    if(noteNumChange){
        for (const auto & observer : observers) {
            observer->update(1);
        }
    } else {
        for (const auto & observer : observers) {
            observer->update(0);
        }
    }
}
