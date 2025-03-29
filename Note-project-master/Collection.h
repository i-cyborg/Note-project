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

    bool addNote(const std::string& titolo, const std::string& testo, bool blocco, bool importante);
    bool removeNote(int index, bool important);

    std::string getName() const;
    //restituisce l' i-esimo elemento della lista notes
    std::shared_ptr<Note> getNotes(int i) const;
    std::shared_ptr<Note> getImportantNotes(int i) const;
    std::list<Observer*> getObservers() const;
    int getNoteCount() const;
    int getImportantNoteCount() const;

    bool updateNoteTitle(int index, bool important, const std::string& newTitle);
    bool updateNoteText(int index, bool important, const std::string& newText);
    bool updateNoteImportant(int index, bool important, bool newImportant);

    std::shared_ptr<Note> searchByTitle(const std::string& title) const;
    std::list<std::shared_ptr<Note>> searchByText(const std::string& text) const;

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
