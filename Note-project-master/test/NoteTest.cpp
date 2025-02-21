//
// Created by volta on 21/11/2024.
//
#include "gtest/gtest.h"
#include "../Note.h"

class NoteTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::string titolo = "Titolo di prova";
        std::string testo = "Testo di prova";
        n = std::make_shared<Note>(titolo, testo, false);
    }

    std::shared_ptr<Note> n;
};

TEST_F(NoteTest, TestSetTitle) {
    n->setTitle("Nuovo titolo");
    ASSERT_EQ(n->getTitle(), "Nuovo titolo");
}

TEST_F(NoteTest, TestSetBody) {
    n->setBody("Nuovo testo");
    ASSERT_EQ(n->getBody(), "Nuovo testo");
}

TEST_F(NoteTest, TestLock) {
    n->lock();
    ASSERT_TRUE(n->getLock());

    n->unlock();
    ASSERT_FALSE(n->getLock());
}
//testa i setter quando la nota è bloccata
TEST_F(NoteTest, TestLockSetters) {
    n->lock();
    n->setTitle("Nuovo titolo");
    n->setBody("Nuovo testo");
    ASSERT_EQ(n->getTitle(), "Titolo di prova");
    ASSERT_EQ(n->getBody(), "Testo di prova");
}

TEST_F(NoteTest, TestSetImportant) {
    n->setImportant(true);
    ASSERT_TRUE(n->getImportant());

    n->setImportant(false);
    ASSERT_FALSE(n->getImportant());
}