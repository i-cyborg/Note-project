//
// Created by volta on 05/11/2024.
//

#include "Collection.h"
#include "Note.h"
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

Collection::Collection(const std::string& n) : name(n){
    if(name.empty()) {
        throw std::invalid_argument("Il nome della collezione non può essere vuoto");
    }
}

void Collection::addNote() {
    std::cout << "Nome della nota:";
    std::string titolo;
    std::getline(std::cin >> std::ws, titolo);
    std::cout << "Testo della nota:";
    std::string testo;
    std::getline(std::cin >> std::ws, testo);
    std::cout << "Vuoi bloccare la nota? 1. Si 0. No" << std::endl;
    bool sceltaBlocco;
    std::cin >> sceltaBlocco;
    if(sceltaBlocco != 1 && sceltaBlocco != 0) {
        std::cout << "Scelta non valida" << std::endl;
        return;
    }
    std::cout << "Nota importante? 1. Si 0. No" << std::endl;
    bool sceltaImportante;
    std::cin >> sceltaImportante;
    if(sceltaImportante != 1 && sceltaImportante != 0) {
        std::cout << "Scelta non valida" << std::endl;
        return;
    }

    std::shared_ptr<Note> n = std::make_shared<Note>(titolo, testo, sceltaBlocco, sceltaImportante);
    std::cout << "Nota creata con successo" << std::endl;
    if(sceltaImportante) {
        importantNotes.push_back(n);
    }
    notes.push_back(n);
    notifyObservers();
}

bool Collection::removeNote() {
    std::cout << "Seleziona la nota da rimuovere" << std::endl;
    int index = 0;
    for (const auto& note : notes) {
        std::cout << index++ << ". " << note->getTitle() << std::endl;
    }
    int sceltaNota;
    std::cin >> sceltaNota;
    if(sceltaNota < 0 || sceltaNota >= notes.size()) {
        std::cout << "Nota non valida" << std::endl;
        return false;
    }
    auto it = std::next(notes.begin(), sceltaNota);
    if ((*it)->getLock()) {
        std::cout << "Nota bloccata, impossibile rimuovere" << std::endl;
        return false;
    }

    importantNotes.remove(*it);
    notes.erase(it);

    std::cout << "Nota rimossa con successo" << std::endl;
    notifyObservers();
    return true;
}

std::string Collection::getName() const {
    return name;
}

std::shared_ptr<Note> Collection::getNotes(const int i) {
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

int Collection::getNoteCount() {
    return notes.size();
}

bool Collection::updateNote() {
    std::cout << "Seleziona la nota da modificare" << std::endl;
    int i = 0;
    for (auto it = notes.begin(); it != notes.end(); ++it, ++i) {
        std::cout << i << ". " << (*it)->getTitle() << std::endl;
    }
    int sceltaNota;
    std::cin >> sceltaNota;
    if(sceltaNota < 0 || sceltaNota >= notes.size()) {
        std::cout << "Nota non valida" << std::endl;
        return false;
    }
    auto it = notes.begin();
    std::advance(it, sceltaNota);

    if((*it)->getLock()) {
        std::cout << "Nota bloccata, impossibile modificare" << std::endl;
        return false;
    }
    std::cout << "1. Modifica titolo" << " 2. Modifica testo"<< " 3. Esci"<<std::endl;
    int scelta;
    std::cin >> scelta;
    if(scelta < 1 || scelta > 3) {
        std::cout << "Scelta non valida" << std::endl;
        return false;
    }
    switch(scelta) {
        case 1: {
            std::cout << "Vecchio titolo: " << (*it)->getTitle() << std::endl;
            std::cout << "Inserisci il nuovo titolo: ";
            std::string nuovoTitolo;
            std::getline(std::cin >> std::ws, nuovoTitolo);
            if(nuovoTitolo.empty()) {
                throw std::invalid_argument("Il nuovo titolo non può essere vuoto");
            }
            (*it)->setTitle(nuovoTitolo);
            std::cout << "Titolo modificato con successo" << std::endl;
            return true;
        }
        case 2: {
            std::cout << "Vecchio testo: " << (*it)->getBody() << std::endl;
            std::cout << "Inserisci il nuovo testo: ";
            std::string nuovoTesto;
            std::getline(std::cin >> std::ws, nuovoTesto);
            if(nuovoTesto.empty()) {
                throw std::invalid_argument("Il nuovo testo non può essere vuoto");
            }
            (*it)->setBody(nuovoTesto);
            std::cout << "Testo modificato con successo" << std::endl;
            return true;
        }
        case 3: {
            return false;
        }
        default: {
            std::cout << "Scelta non valida" << std::endl;
            return false;
        }
    }

}

void Collection::printNotes() const {
    std::cout << "Note importanti:" << std::endl;
    int i = 1;
    for (const auto& note : importantNotes) {
        std::cout << "Nota " << i++ << ":" << std::endl;
        std::cout << "Titolo: " << note->getTitle() << std::endl;
        std::cout << "Testo: " << note->getBody() << std::endl << std::endl;
    }
    std::cout << "Note:" << std::endl;
    i = 1;
    for (const auto& note : notes) {
        std::cout << "Nota " << i++ << ":" << std::endl;
        std::cout << "Titolo: " << note->getTitle() << std::endl;
        std::cout << "Testo: " << note->getBody() << std::endl << std::endl;
    }

}

std::shared_ptr<Note> Collection::searchByTitle(const std::string &title) {
    for(const auto& note : notes) {
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

std::shared_ptr<Note> Collection::searchByText(const std::string &text) {
    for(const auto& note : notes) {
        if(note->getBody() == text) {
            std::cout << "Nota trovata nella collezione: " << name << std::endl;
            std::cout << "Titolo: " << note->getTitle() << std::endl;
            std::cout << "Testo: " << note->getBody() << std::endl;
            return note;
        }
    }
    std::cout << "Nota non trovata" << std::endl;
    return nullptr;
}

void Collection::addNote(const std::shared_ptr<Note> &note) {
    if(note->getImportant()) {
        importantNotes.push_back(note);
    }
    notes.push_back(note);
    notifyObservers();
}

bool Collection::removeNote(const std::shared_ptr<Note>& note) {
    if (note->getLock()) {
        std::cout << "Nota bloccata, impossibile rimuovere" << std::endl;
        return false;
    }

    auto it = std::find(notes.begin(), notes.end(), note);
    if (it != notes.end()) {
        notes.erase(it);

        // Rimuove anche dalla lista delle note importanti, se presente
        importantNotes.remove(note);

        notifyObservers();
        std::cout << "Nota rimossa con successo" << std::endl;
        return true;
    }

    std::cout << "Nota non trovata" << std::endl;
    return false;
}

std::list<Observer *> Collection::getObservers() {
    return observers;
}
