//
// Created by volta on 29/11/2024.
//
#pragma once

class Observer {
public:
    virtual ~Observer() {}
    virtual void update() = 0;

    virtual void attach() = 0;
    virtual void detach() = 0;
};