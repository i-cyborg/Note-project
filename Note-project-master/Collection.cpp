//
// Created by volta on 05/11/2024.
//

#include "Collection.h"
#include "Note.h"
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>
#include <limits>

Collection::Collection(const std::string& n) : name(n){
    if(name.empty()) {
        throw std::invalid_argument("Il nome della collezione non può essere vuoto");
    }
}

bool Collection::addNote(const std::string& titolo, const std::string& testo, bool blocco, bool importante) {
    if(titolo.empty() || testo.empty()) {
        std::cout << "Titolo e testo della nota non possono essere vuoti" << std::endl;
        return false;
    }
    for(const auto& note : notes) {
        if(note->getTitle() == titolo) {
            std::cout << "Nota con lo stesso titolo già presente" << std::endl;
            return false;
        }
    }
    for(const auto& note : importantNotes) {
        if(note->getTitle() == titolo) {
            std::cout << "Nota con lo stesso titolo già presente" << std::endl;
            return false;
        }
    }
    std::shared_ptr<Note> n = std::make_shared<Note>(titolo, testo, blocco, importante);
    std::cout << "Nota creata con successo" << std::endl;
    if(importante) {
        importantNotes.push_back(n);
    }   else {
        notes.push_back(n);
    }
    notifyObservers();
    return true;
}

bool Collection::removeNote(int index, bool important) {
    if (important) {
        if (index < 0 || index >= importantNotes.size()) {
            std::cout << "Nota non valida" << std::endl;
            return false;
        }
        auto it = std::next(importantNotes.begin(), index);
        if ((*it)->getLock()) {
            std::cout << "Nota bloccata, impossibile rimuovere" << std::endl;
            return false;
        }

        importantNotes.remove(*it);

        std::cout << "Nota rimossa con successo" << std::endl;
        notifyObservers();
        return true;
    } else {
        if (index < 0 || index >= notes.size()) {
            std::cout << "Nota non valida" << std::endl;
            return false;
        }
        auto it = std::next(notes.begin(), index);
        if ((*it)->getLock()) {
            std::cout << "Nota bloccata, impossibile rimuovere" << std::endl;
            return false;
        }

        notes.remove(*it);

        std::cout << "Nota rimossa con successo" << std::endl;
        notifyObservers();
        return true;
    }
}

std::string Collection::getName() const {
    return name;
}

std::shared_ptr<Note> Collection::getNotes(const int i) const {
    if (i < 0 || i >= notes.size()) {
        return nullptr;
    }

    auto it = notes.begin();
    std::advance(it, i);
    return *it;
}

void Collection::registerObserver(Observer* observer) {
    observers.push_back(observer);
}

void Collection::removeObserver(Observer* observer) {
    observers.remove(observer);
}

void Collection::notifyObservers() {
    for(auto& observer : observers) {
        observer->update();
    }
}

int Collection::getNoteCount() const {
    return notes.size();
}

std::shared_ptr<Note> Collection::searchByTitle(const std::string &title) const {
    for(const auto& note : notes) {
        if(note->getTitle() == title) {
            std::cout << "Nota trovata" << std::endl;
            std::cout << "Titolo: " << note->getTitle() << std::endl;
            std::cout << "Testo: " << note->getBody() << std::endl;
            return note;
        }
    }
    for(const auto& note : importantNotes) {
        if(note->getTitle() == title) {
            std::cout << "Nota trovata" << std::endl;
            std::cout << "Titolo: " << note->getTitle() << std::endl;
            std::cout << "Testo: " << note->getBody() << std::endl;
            return note;
        }
    }
    std::cout << "Nota non trovata" << std::endl;
    return nullptr;
}

std::list<std::shared_ptr<Note>> Collection::searchByText(const std::string &text) const {
    std::list<std::shared_ptr<Note>> results;
    for (const auto& note : notes) {
        if (note->getBody() == text) {
            results.push_back(note);
        }
    }
    for (const auto& note : importantNotes) {
        if (note->getBody() == text) {
            results.push_back(note);
        }
    }
    return results;
}

std::list<Observer *> Collection::getObservers() const {
    return observers;
}

int Collection::getImportantNoteCount() const {
    return importantNotes.size();
}

std::shared_ptr<Note> Collection::getImportantNotes(int i) const {
    if (i < 0 || i >= importantNotes.size()) {
        return nullptr;
    }

    auto it = importantNotes.begin();
    std::advance(it, i);
    return *it;
}

bool Collection::updateNoteTitle(int index, bool important, const std::string &newTitle) {
    if(newTitle.empty()) {
        throw std::invalid_argument("Il nuovo titolo non può essere vuoto");
    }
    for(const auto& note : notes) {
        if(note->getTitle() == newTitle) {
            std::cout << "Nota con lo stesso titolo già presente" << std::endl;
            return false;
        }
    }
    for(const auto& note : importantNotes) {
        if(note->getTitle() == newTitle) {
            std::cout << "Nota con lo stesso titolo già presente" << std::endl;
            return false;
        }
    }
    if (important) {
        if (index < 0 || index > importantNotes.size()) {
            std::cout << "Nota non valida" << std::endl;
            return false;
        }
        auto it = std::next(importantNotes.begin(), index);
        if ((*it)->getLock()) {
            std::cout << "Nota bloccata, impossibile modificare" << std::endl;
            return false;
        }

        (*it)->setTitle(newTitle);
        std::cout << "Titolo nota modificato con successo" << std::endl;
        return true;
    } else {
        if (index < 0 || index >= notes.size()) {
            std::cout << "Nota non valida" << std::endl;
            return false;
        }
        auto it = std::next(notes.begin(), index);
        if ((*it)->getLock()) {
            std::cout << "Nota bloccata, impossibile modificare" << std::endl;
            return false;
        }

        (*it)->setTitle(newTitle);
        std::cout << "Titolo nota modificato con successo" << std::endl;
        return true;
    }
}

bool Collection::updateNoteText(int index, bool important, const std::string &newText) {
    if(newText.empty()) {
        throw std::invalid_argument("Il nuovo testo non può essere vuoto");
    }
    if (important) {
        if (index < 0 || index > importantNotes.size()) {
            std::cout << "Nota non valida" << std::endl;
            return false;
        }
        auto it = std::next(importantNotes.begin(), index);
        if ((*it)->getLock()) {
            std::cout << "Nota bloccata, impossibile modificare" << std::endl;
            return false;
        }

        (*it)->setBody(newText);
        std::cout << "Testo nota modificato con successo" << std::endl;
        return true;

    } else {
        if (index < 0 || index >= notes.size()) {
            std::cout << "Nota non valida" << std::endl;
            return false;
        }
        auto it = std::next(notes.begin(), index);
        if ((*it)->getLock()) {
            std::cout << "Nota bloccata, impossibile modificare" << std::endl;
            return false;
        }

        (*it)->setBody(newText);
        std::cout << "Testo nota modificato con successo" << std::endl;
        return true;
    }
}

bool Collection::updateNoteImportant(int index, bool important, bool newImportant) {
    if (important && !newImportant) {
        if (index < 0 || index > importantNotes.size()) {
            std::cout << "Nota non valida" << std::endl;
            return false;
        }
        auto it = std::next(importantNotes.begin(), index);
        if ((*it)->getLock()) {
            std::cout << "Nota bloccata, impossibile modificare" << std::endl;
            return false;
        }
        getImportantNotes(index)->setImportant(newImportant);
        notes.push_back(std::move(*it));
        importantNotes.erase(it);
        std::cout << "Attributo importante della nota modificato con successo" << std::endl;
        return true;

    } else if (!important && newImportant) {
        if (index < 0 || index >= notes.size()) {
            std::cout << "Nota non valida" << std::endl;
            return false;
        }
        auto it = std::next(notes.begin(), index);
        if ((*it)->getLock()) {
            std::cout << "Nota bloccata, impossibile modificare" << std::endl;
            return false;
        }
        getNotes(index)->setImportant(newImportant);
        importantNotes.push_back(std::move(*it));
        notes.erase(it);
        std::cout << "Attributo importante della nota modificato con successo" << std::endl;
        return true;
    }
    return false;
}
