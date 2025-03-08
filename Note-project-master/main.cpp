#include <iostream>
#include <limits>

#include "Collection.h"
#include "Note.h"
#include <vector>
#include <memory>
#include <algorithm>

int main() {
    std::vector<std::shared_ptr<Collection>> collections;
    std::vector<std::shared_ptr<Note>> notes;
    std::vector<ConcreteObserver*> observers;


    while(true) {
        std::cout << "1. Crea nuova collezione" << std::endl;
        std::cout << "2. Crea nuova nota" << std::endl;
        std::cout << "3. Modifica nota"  << std::endl;
        std::cout << "4. Rimuovi nota" << std::endl;
        std::cout << "5. Visualizza collezioni e note" << std::endl;
        std::cout << "6. Cerca nota" << std::endl;
        std::cout << "7. Esci" << std::endl;

        int scelta;
        std::cin >> scelta;

        switch (scelta) {
            case 1: {
                std::cout << "Nome della collezione: ";
                std::string nome;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, nome);
                try {
                    std::shared_ptr<Collection> newCollection = std::make_shared<Collection>(nome);
                    collections.push_back(newCollection);
                    ConcreteObserver* newObserver = new ConcreteObserver(newCollection.get());
                    std::cout << "Collezione creata con successo" << std::endl;
                } catch (std::invalid_argument& e) {
                    std::cout << "Errore: " << e.what() << std::endl;
                }
                break;
            }
            case 2: {
                if(collections.empty()) {
                    std::cout << "Non sono presenti collezioni" << std::endl;
                    break;
                }
                std::cout << "A quale collezione vuoi aggiungere la nota?" << std::endl;
                for (int i = 0; i < collections.size(); i++) {
                    std::cout << i << ". " << collections[i]->getName() << std::endl;
                }
                int sceltaCollezione;
                std::cin >> sceltaCollezione;
                if (sceltaCollezione < 0 || sceltaCollezione >= collections.size()) {
                    std::cout << "Collezione non valida!" << std::endl;
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Nome della nota:";
                std::string titolo;
                std::getline(std::cin, titolo);
                std::cout << "Testo della nota:";
                std::string testo;
                std::getline(std::cin, testo);
                std::cout << "Vuoi bloccare la nota? 1. Si 0. No" << std::endl;
                bool sceltaBlocco;
                std::cin >> sceltaBlocco;
                if(sceltaBlocco != 1 && sceltaBlocco != 0) {
                    std::cout << "Scelta non valida" << std::endl;
                    break;
                }
                std::cout << "Nota importante? 1. Si 0. No" << std::endl;
                bool sceltaImportante;
                std::cin >> sceltaImportante;
                if(sceltaImportante != 1 && sceltaImportante != 0) {
                    std::cout << "Scelta non valida" << std::endl;
                    break;
                }
                try{
                    collections[sceltaCollezione]->addNote(titolo, testo, sceltaBlocco, sceltaImportante);
                } catch (std::invalid_argument& e) {
                    std::cout << "Errore: " << e.what() << std::endl;
                }
                break;
            }

            case 3: {
                std::cout << "Seleziona la collezione: " << std::endl;
                for (int i = 0; i < collections.size(); i++) {
                    std::cout << i << ". " << collections[i]->getName() << std::endl;
                }
                int sceltaCollezione;
                std::cin >> sceltaCollezione;

                if (sceltaCollezione < 0 || sceltaCollezione >= collections.size()) {
                    std::cout << "Collezione non valida!" << std::endl;
                    break;
                }
                if(collections[sceltaCollezione]->getNoteCount() + collections[sceltaCollezione]->getImportantNoteCount() == 0) {
                    std::cout << "Non sono presenti note da modificare" << std::endl;
                    break;
                }
                std::cout << "Seleziona la nota da modificare" << std::endl;
                std::cout << "Note importanti:" << std::endl;
                for (int i = 0; i < collections[sceltaCollezione]->getImportantNoteCount(); i++) {
                    std::cout << i << ". " << collections[sceltaCollezione]->getImportantNotes(i)->getTitle() << std::endl;
                }
                std::cout << "Note:" << std::endl;
                for (int i = 0; i < collections[sceltaCollezione]->getNoteCount(); i++) {
                    std::cout << i + collections[sceltaCollezione]->getImportantNoteCount() << ". " << collections[sceltaCollezione]->getNotes(i)->getTitle() << std::endl;
                }
                int sceltaNota;
                std::cin >> sceltaNota;
                bool important = false;
                important = (sceltaNota < collections[sceltaCollezione]->getImportantNoteCount());
                std::shared_ptr<Note> it;
                if(important) {
                    it = collections[sceltaCollezione]->getImportantNotes(sceltaNota);
                } else {
                    it = collections[sceltaCollezione]->getNotes(sceltaNota);
                }
                std::cout << "1. Modifica titolo" << " 2. Modifica testo"<< " 3. Modifica importante" << " 4. Esci"<< std::endl;
                int scelta;
                std::cin >> scelta;
                if(scelta < 1 || scelta > 4) {
                    std::cout << "Scelta non valida" << std::endl;
                    break;
                }
                try {
                    switch(scelta) {
                        case 1: {
                            std::cout << "Vecchio titolo: " << (it)->getTitle() << std::endl;
                            std::cout << "Inserisci il nuovo titolo: ";
                            std::string nuovoTitolo;
                            std::getline(std::cin >> std::ws, nuovoTitolo);
                            collections[sceltaCollezione]->updateNoteTitle(sceltaNota, important, nuovoTitolo);
                            break;
                        }
                        case 2: {
                            std::cout << "Vecchio testo: " << (it)->getBody() << std::endl;
                            std::cout << "Inserisci il nuovo testo: ";
                            std::string nuovoTesto;
                            std::getline(std::cin >> std::ws, nuovoTesto);
                            collections[sceltaCollezione]->updateNoteText(sceltaNota, important, nuovoTesto);
                            break;
                        }
                        case 3: {
                            std::cout << "Nota importante? 1. Si 0. No" << std::endl;
                            bool nuovoImportante;
                            std::cin >> nuovoImportante;
                            if(nuovoImportante != 1 && nuovoImportante != 0) {
                                std::cout << "Scelta non valida" << std::endl;
                                break;
                            }
                            collections[sceltaCollezione]->updateNoteImportant(sceltaNota, important, nuovoImportante);
                            break;
                        }
                        case 4: {
                            break;
                        }
                        default: {
                            std::cout << "Scelta non valida" << std::endl;
                            break;
                        }
                    }
                } catch (std::invalid_argument& e) {
                    std::cout << "Errore: " << e.what() << std::endl;
                }
                break;
            }
            case 4: {
                std::cout << "Seleziona la collezione: " << std::endl;
                for (int i = 0; i < collections.size(); i++) {
                    std::cout << i << ". " << collections[i]->getName() << std::endl;
                }
                int sceltaCollezione;
                std::cin >> sceltaCollezione;

                if (sceltaCollezione < 0 || sceltaCollezione >= collections.size()) {
                    std::cout << "Collezione non valida!" << std::endl;
                    break;
                }

                if(collections[sceltaCollezione]->getNoteCount() + collections[sceltaCollezione]->getImportantNoteCount() == 0) {
                    std::cout << "Non sono presenti note da eliminare" << std::endl;
                    break;
                }
                std::cout << "Seleziona la nota da rimuovere" << std::endl;
                std::cout << "Note importanti:" << std::endl;
                for (int i = 0; i < collections[sceltaCollezione]->getImportantNoteCount(); i++) {
                    std::cout << i << ". " << collections[sceltaCollezione]->getImportantNotes(i)->getTitle() << std::endl;
                }
                std::cout << "Note:" << std::endl;
                for (int i = 0; i < collections[sceltaCollezione]->getNoteCount(); i++) {
                    std::cout << i + collections[sceltaCollezione]->getImportantNoteCount() << ". " << collections[sceltaCollezione]->getNotes(i)->getTitle() << std::endl;
                }
                int sceltaNota;
                std::cin >> sceltaNota;
                bool important = false;
                important = (sceltaNota < collections[sceltaCollezione]->getImportantNoteCount());
                collections[sceltaCollezione]->removeNote(sceltaNota, important);
                break;
            }
            case 5: {
                std::cout << "Collezioni:" << std::endl;
                for (int i = 0; i < collections.size(); i++) {
                    std::cout << i << ". " << collections[i]->getName() << std::endl;
                }
                std::cout << "Seleziona collezione: " << std::endl;
                int sceltaCollezione;
                std::cin >> sceltaCollezione;
                if (sceltaCollezione < 0 || sceltaCollezione >= collections.size()) {
                    std::cout << "Collezione non valida!" << std::endl;
                    break;
                }
                if(collections[sceltaCollezione]->getNoteCount()+ collections[sceltaCollezione]->getImportantNoteCount() == 0) {
                    std::cout << "Non sono presenti note" << std::endl;
                    break;
                }
                std::cout << "Note" << std::endl;
                break;
            }
            case 6: {
                std::cout << "Vuoi cercare una nota per titolo o per testo? 1. Titolo 2. Testo" << std::endl;
                int scelta;
                std::cin >> scelta;
                if(scelta < 1 || scelta > 2) {
                    std::cout << "Scelta non valida" << std::endl;
                    break;
                }
                if(scelta == 1) {
                    std::cout << "Inserisci il titolo della nota da cercare: ";
                    std::string titolo;
                    std::getline(std::cin >> std::ws, titolo);
                    for (int i = 0; i < collections.size(); i++) {
                            collections[i]->searchByTitle(titolo);
                    }
                    break;
                }else{
                    std::cout << "Inserisci il testo della nota da cercare: ";
                    std::string testo;
                    std::getline(std::cin >> std::ws, testo);
                    for (int i = 0; i < collections.size(); i++) {
                        std::list<std::shared_ptr<Note>> results = collections[i]->searchByText(testo);

                        if (!results.empty()) {
                            std::cout << "Note trovate nella collezione: " << collections[i]->getName() << std::endl;

                            for (const auto& note : results) {
                                std::cout << " - Titolo: " << note->getTitle() << std::endl;
                                std::cout << " - Testo: " << note->getBody() << std::endl;
                                std::cout << "---------------------------" << std::endl;
                            }
                        }
                    }
                    break;

                }
            }
            case 7: {
                return 0;
            }
            default: {
                std::cout << "Scelta non valida" << std::endl;
                break;
            }
        }
    }

}