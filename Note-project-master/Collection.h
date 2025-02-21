//
// Created by volta on 05/11/2024.
//

#ifndef COLLECTION_H
#define COLLECTION_H
#include <string>
#include <vector>
#include <memory>
#include <list>
#include "Note.h"
#include "ConcreteObserver.h"
#include "Subject.h"


class Collection: public Subject {
public:
    explicit Collection(const std::string& n);

    void addNote();
    void addNote(const std::shared_ptr<Note>& note);
    bool removeNote();
    bool removeNote(const std::shared_ptr<Note>& note);

    std::string getName() const;
    //restituisce l' i-esimo elemento del vettore notes
    std::shared_ptr<Note> getNotes(int i);
    std::list<Observer*> getObservers();
    int getNoteCount();
    bool updateNote();
    void printNotes() const;
    std::shared_ptr<Note> searchByTitle(const std::string& title);
    std::shared_ptr<Note> searchByText(const std::string& text);

    virtual void registerObserver(Observer* observer) override;
    virtual void removeObserver(Observer* observer) override;
    virtual void notifyObservers() override;
private:
    std::string name;
    std::list <std::shared_ptr<Note>> notes;
    std::list<std::shared_ptr<Note>> importantNotes;
    std::list<Observer*> observers;

};



#endif //COLLECTION_H
