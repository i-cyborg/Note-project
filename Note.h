//
// Created by volta on 05/11/2024.
//

#ifndef NOTE_H
#define NOTE_H
#include <string>



class Note {
public:
    Note(std::string& t, std::string& b, bool l = false);

    void setTitle(const std::string& newTitle);
    std::string getTitle();
    void setBody(const std::string& newBody);
    std::string getBody();

    void lock();
    void unlock();
    bool getLock() const;

private:
    std::string title;
    std::string body;
    bool isLocked = false;

};



#endif //NOTE_H
