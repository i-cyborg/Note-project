//
// Created by volta on 21/11/2024.
//

#include "gtest/gtest.h"
#include "../Collection.h"
#include "../Note.h"

class CollectionTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::string titolo_collezione = "Collezione di testing";
        std::string titolo_nota = "Nota di testing";
        std::string testo_nota = "Testo di prova";
        collection = std::make_shared<Collection>(titolo_collezione);
        n1 = std::make_shared<Note>(titolo_nota, testo_nota, false);
    }

    std::shared_ptr<Collection> collection;
    std::shared_ptr<Note> n1;
};

TEST_F(CollectionTest, TestAddNote) {
    collection->addNote(n1);
    ASSERT_EQ(collection->getNotes(0)->getTitle(), "Nota di testing");
}

TEST_F(CollectionTest, TestRemoveNote) {
    collection->addNote(n1);
    ASSERT_TRUE(collection->removeNote("Nota di testing"));
    ASSERT_EQ(collection->getNotes(0), nullptr);
}

TEST_F(CollectionTest, TestRemoveLockedNote) {
    n1->lock();
    collection->addNote(n1);
    ASSERT_FALSE(collection->removeNote("Nota di testing"));
}

TEST_F(CollectionTest, TestGetName) {
    ASSERT_EQ(collection->getName(), "Collezione di testing");
}


