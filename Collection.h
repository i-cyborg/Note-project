//
// Created by volta on 05/11/2024.
//

#ifndef COLLECTION_H
#define COLLECTION_H
#include <string>
#include <vector>
#include <memory>
#include "Note.h"
#include "Observer.h"


class Collection {
public:
    explicit Collection(const std::string& n);

    void addNote(const std::shared_ptr<Note>& note);
    bool removeNote(const std::string& title);

    std::string getName() const;

    //restituisce l' i-esimo elemento del vettore notes
    std::shared_ptr<Note> getNotes(int i);

    void registerObserver(const std::shared_ptr<Observer>& observer);
    void removeObserver(const std::shared_ptr<Observer>& observer);
    void notifyObservers(int noteNumChange);
private:
    std::string name;
    std::vector <std::shared_ptr<Note>> notes;
    std::vector <std::shared_ptr<Observer>> observers;

};



#endif //COLLECTION_H
