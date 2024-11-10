//
// Created by volta on 05/11/2024.
//

#include "Note.h"
#include <string>


Note::Note(std::string& t, std::string& b, bool l) : title(t), body(b), isLocked(l) {
}

void Note::setTitle(const std::string& newTitle) {
    if(!isLocked) {
        title = newTitle;
    }
}

std::string Note::getTitle() {
    return title;
}

void Note::setBody(const std::string &newBody) {
    if(!isLocked)
        body = newBody;
}

std::string Note::getBody() {
    return body;
}

void Note::lock() {
    isLocked = true;
}

void Note::unlock() {
    isLocked = false;
}

bool Note::getLock() const {
    return isLocked;
}


