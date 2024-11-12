#include <iostream>
#include <limits>

#include "Collection.h"
#include "Note.h"
#include <vector>
#include <memory>
#include <algorithm>

int getValidInput() {
    std::string input;
    int scelta;

    while (true) {
        std::getline(std::cin, input);

        bool isValid = !input.empty() && std::all_of(input.begin(), input.end(), ::isdigit);

        if (isValid) {
            scelta = std::stoi(input);
            break;
        } else {
            std::cout << "Input non valido. Per favore inserisci un numero intero: ";
        }
    }

    return scelta;
}

int main() {
    std::vector<std::shared_ptr<Collection>> collections;
    std::vector<std::shared_ptr<Note>> notes;
    std::vector<std::shared_ptr<Observer>> observers;

    collections.push_back(std::make_shared<Collection>("Collezione note importanti"));
    const std::shared_ptr<Observer> o = std::make_shared<Observer>();
    collections[0]->registerObserver(o);
    observers.push_back(o);

    while(true) {
        std::cout << "1. Crea nuova collezione" << std::endl;
        std::cout << "2. Crea nuova nota" << std::endl;
        std::cout << "3. Modifica nota"  << std::endl;
        std::cout << "4. Rimuovi nota" << std::endl;
        std::cout << "5. Visualizza collezioni e note" << std::endl;
        std::cout << "6. Esci" << std::endl;

        int scelta = getValidInput();

        switch (scelta) {
            case 1: {
                std::cout << "Nome della collezione: ";
                std::string nome;
                std::getline(std::cin >> std::ws, nome);  // Use std::ws to ignore leading whitespace
                std::shared_ptr<Collection> newCollection = std::make_shared<Collection>(nome);
                collections.push_back(newCollection);

                std::shared_ptr<Observer> newObserver = std::make_shared<Observer>();
                newCollection->registerObserver(newObserver);
                observers.push_back(newObserver);
                std::cout << "Collezione creata con successo" << std::endl;
                break;
            }
            case 2: {
                std::cout << "Nome della nota:";
                std::string titolo;
                std::getline(std::cin >> std::ws, titolo);  // Use std::ws to ignore leading whitespace
                std::cout << "Testo della nota:";
                std::string testo;
                std::getline(std::cin >> std::ws, testo);  // Use std::ws to ignore leading whitespace
                std::cout << "A quale collezione vuoi aggiungere la nota?" << std::endl;
                for (int i = 0; i < collections.size(); i++) {
                    std::cout << i << ". " << collections[i]->getName() << std::endl;
                }
                int sceltaCollezione = getValidInput();
                if (sceltaCollezione < 0 || sceltaCollezione >= collections.size()) {
                    std::cout << "Collezione non valida!" << std::endl;
                    break;
                }
                std::cout << "Vuoi bloccare la nota? 1. Si 2. No" << std::endl;
                int sceltaBlocco = getValidInput();
                if(sceltaBlocco != 1 && sceltaBlocco != 2) {
                    std::cout << "Scelta non valida" << std::endl;
                    break;
                }
                bool blocco = false;
                if (sceltaBlocco == 1) {
                    blocco = true;
                }
                std::shared_ptr<Note> n = std::make_shared<Note>(titolo, testo, blocco);
                collections[sceltaCollezione]->addNote(n);
                std::cout << "Nota creata con successo" << std::endl;
                break;
            }

            case 3: {
                std::cout << "Seleziona la collezione: " << std::endl;
                for (int i = 0; i < collections.size(); i++) {
                    std::cout << i << ". " << collections[i]->getName() << std::endl;
                }
                int sceltaCollezione = getValidInput();

                if (sceltaCollezione < 0 || sceltaCollezione >= collections.size()) {
                    std::cout << "Collezione non valida!" << std::endl;
                    break;
                }
                if(observers[sceltaCollezione]->getNoteCount() == 0) {
                    std::cout << "Non sono presenti note da modificare" << std::endl;
                    break;
                }
                std::cout << "Seleziona la nota da modificare" << std::endl;
                const int noteCount = observers[sceltaCollezione]->getNoteCount();
                for (int i = 0; i < noteCount; i++) {
                    std::cout << i << ". " << collections[sceltaCollezione]->getNotes(i)->getTitle() << std::endl;
                }
                int sceltaNota = getValidInput();
                if (sceltaNota < 0 || sceltaNota >= noteCount) {
                    std::cout << "Nota non valida!" << std::endl;
                    break;
                }
                if(collections[sceltaCollezione]->getNotes(sceltaNota)->getLock()) {
                    std::cout << "Nota bloccata, impossibile modificare" << std::endl;
                    break;
                }
                std::cout << "1. Modifica titolo" << " 2. Modifica testo"<<" 3. Modifica collezione"<<" 4. Esci"<<std::endl;
                int sceltaModifica = getValidInput();
                switch (sceltaModifica) {
                    case 1: {
                        std::cout << "Vecchio titolo: " << collections[sceltaCollezione]->getNotes(sceltaNota)->getTitle() << std::endl;
                        std::cout << "Inserisci il nuovo titolo: ";
                        std::string nuovoTitolo;
                        std::getline(std::cin, nuovoTitolo);
                        collections[sceltaCollezione]->getNotes(sceltaNota)->setTitle(nuovoTitolo);
                        std::cout << "Titolo modificato con successo" << std::endl;
                        break;
                    }
                    case 2: {
                        std::cout << "Vecchio testo: " << collections[sceltaCollezione]->getNotes(sceltaNota)->getBody() << std::endl;
                        std::cout << "Inserisci il nuovo testo: ";
                        std::string nuovoTesto;
                        std::getline(std::cin, nuovoTesto);
                        collections[sceltaCollezione]->getNotes(sceltaNota)->setBody(nuovoTesto);
                        std::cout << "Testo modificato con successo" << std::endl;
                        break;
                    }
                    case 3: {
                        std::cout << "A che collezione vuoi aggiugere la nota?" << std::endl;
                        for (int i = 0; i < collections.size(); i++) {
                            std::cout << i << ". " << collections[i]->getName() << std::endl;
                        }
                        int modificaCollezione = getValidInput();
                        if (modificaCollezione < 0 || modificaCollezione >= collections.size()) {
                            std::cout << "Collezione non valida!" << std::endl;
                            break;
                        }
                        if(collections[modificaCollezione]->getNotes(sceltaNota) == nullptr && collections[modificaCollezione]->getNotes(sceltaNota)->getTitle() != collections[sceltaCollezione]->getNotes(sceltaNota)->getTitle()) {
                            collections[modificaCollezione]->addNote(collections[sceltaCollezione]->getNotes(sceltaNota));
                            std::cout << "Nota aggiunta a collezione: " << collections[modificaCollezione]->getName() << std::endl;
                            break;
                        } else {
                            std::cout << "Nota già presente nella collezione" << std::endl;
                            break;
                        }
                    }
                    case 4: {
                        break;
                    }
                    default: {
                        std::cout << "Scelta non valida" << std::endl;
                        break;
                    }
                }
                break;
            }
            case 4: {
                std::cout << "Seleziona la collezione: " << std::endl;
                for (int i = 0; i < collections.size(); i++) {
                    std::cout << i << ". " << collections[i]->getName() << std::endl;
                }
                int sceltaCollezione = getValidInput();

                if (sceltaCollezione < 0 || sceltaCollezione >= collections.size()) {
                    std::cout << "Collezione non valida!" << std::endl;
                    break;
                }

                if(observers[sceltaCollezione]->getNoteCount() == 0) {
                    std::cout << "Non sono presenti note da eliminare" << std::endl;
                    break;
                }
                std::cout << "Seleziona la nota da rimuovere" << std::endl;
                std::shared_ptr<Note> n = collections[sceltaCollezione] -> getNotes(0);
                const int noteCount = observers[sceltaCollezione]->getNoteCount();
                for (int i = 0; i < noteCount; i++) {
                    std::cout << i << ". " << collections[sceltaCollezione]->getNotes(i)->getTitle() << std::endl;
                }
                int sceltaNota = getValidInput();
                if (sceltaNota < 0 || sceltaNota >= noteCount) {
                    std::cout << "Nota non valida!" << std::endl;
                    break;
                }
                if(collections[sceltaCollezione]->getNotes(sceltaNota)->getLock()) {
                    std::cout << "Nota bloccata, impossibile rimuovere" << std::endl;
                    break;
                }
                collections[sceltaCollezione]->removeNote(collections[sceltaCollezione]->getNotes(sceltaNota)->getTitle());
                std::cout << "Nota rimossa con successo" << std::endl;
                break;
            }
            case 5: {
                std::cout << "Collezioni:" << std::endl;
                for (int i = 0; i < collections.size(); i++) {
                    std::cout << i << ". " << collections[i]->getName() << std::endl;
                }
                std::cout << "Seleziona collezione: " << std::endl;
                int sceltaCollezione = getValidInput();
                if (sceltaCollezione < 0 || sceltaCollezione >= collections.size()) {
                    std::cout << "Collezione non valida!" << std::endl;
                    break;
                }
                if(observers[sceltaCollezione]->getNoteCount() == 0) {
                    std::cout << "Non sono presenti note" << std::endl;
                    break;
                }
                std::cout << "Note:" << std::endl;
                const int noteCount = observers[sceltaCollezione]->getNoteCount();
                for (int i = 0; i < noteCount; ++i) {
                    std::cout << i << ". " << collections[sceltaCollezione]->getNotes(i)->getTitle() << std::endl;
                }
                std::cout << "Numero di note: " << noteCount << std::endl;
                std::cout << "Seleziona nota: " << std::endl;
                int sceltaNota = getValidInput();
                if (sceltaNota < 0 || sceltaNota >= noteCount) {
                    std::cout << "Nota non valida!" << std::endl;
                    break;
                }
                std::cout << "Titolo: " << collections[sceltaCollezione]->getNotes(sceltaNota)->getTitle() << std::endl;
                std::cout << "Testo: " << collections[sceltaCollezione]->getNotes(sceltaNota)->getBody() << std::endl;
                break;
            }
            case 6: {
                return 0;
            }
            default: {
                std::cout << "Scelta non valida" << std::endl;
                break;
            }
        }
    }

}
