//
// Created by volta on 08/11/2024.
//

#ifndef OBSERVER_H
#define OBSERVER_H
#include "Observer.h"
#include "Collection.h"

class Collection;

class ConcreteObserver: public Observer {
public:
    explicit ConcreteObserver(Collection* c);
    virtual ~ConcreteObserver();

    virtual int update() override;
    virtual void attach() override;
    virtual void detach() override;
//mostra a schermo il numero di note
    void showNoteCount() const;

private:
    int noteCount = 0;
    Collection* subject;
};



#endif //OBSERVER_H
