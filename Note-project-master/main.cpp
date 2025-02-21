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
                std::getline(std::cin >> std::ws, nome);
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
                try{
                    collections[sceltaCollezione]->addNote();
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
                if(collections[sceltaCollezione]->getNoteCount() == 0) {
                    std::cout << "Non sono presenti note da modificare" << std::endl;
                    break;
                }
                try {
                    collections[sceltaCollezione]->updateNote();
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

                if(collections[sceltaCollezione]->getNoteCount() == 0) {
                    std::cout << "Non sono presenti note da eliminare" << std::endl;
                    break;
                }
                collections[sceltaCollezione]->removeNote();
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
                if(collections[sceltaCollezione]->getNoteCount() == 0) {
                    std::cout << "Non sono presenti note" << std::endl;
                    break;
                }
                collections[sceltaCollezione]->printNotes();
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
                }else{
                    std::cout << "Inserisci il testo della nota da cercare: ";
                    std::string testo;
                    std::getline(std::cin >> std::ws, testo);
                    for (int i = 0; i < collections.size(); i++) {
                        collections[i]->searchByText(testo);
                    }
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