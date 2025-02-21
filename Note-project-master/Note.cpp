//
// Created by volta on 05/11/2024.
//

#include "Note.h"
#include <stdexcept>
#include <string>


Note::Note(const std::string& t, const std::string& b, bool l, bool i) : title(t), body(b), isLocked(l), important(i) {
    if(title.empty() || body.empty()) {
        throw std::invalid_argument("Titolo e testo della nota non possono essere vuoti");
    }
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

void Note::setImportant(bool i) {
    important = i;
}

bool Note::getImportant() const {
    return important;
}


