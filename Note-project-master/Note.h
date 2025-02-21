//
// Created by volta on 05/11/2024.
//

#ifndef NOTE_H
#define NOTE_H
#include <string>



class Note {
public:
    Note(const std::string& t, const std::string& b, bool l = false, bool i = false);

    void setTitle(const std::string& newTitle);
    std::string getTitle();
    void setBody(const std::string& newBody);
    std::string getBody();

    void lock();
    void unlock();
    bool getLock() const;

    void setImportant(bool i);
    bool getImportant() const;

private:
    std::string title;
    std::string body;
    bool isLocked = false;
    bool important = false;

};



#endif //NOTE_H
