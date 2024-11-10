//
// Created by volta on 08/11/2024.
//

#ifndef OBSERVER_H
#define OBSERVER_H



class Observer {
public:
    void update(int noteNumChange);
    int getNoteCount() const;

private:
    int noteCount = 0;
};



#endif //OBSERVER_H
