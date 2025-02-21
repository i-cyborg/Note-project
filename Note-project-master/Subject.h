//
// Created by volta on 29/11/2024.
//

#include <memory>
#include "Observer.h"


class Subject {
public:
    virtual void registerObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;

    virtual ~Subject() {}
};