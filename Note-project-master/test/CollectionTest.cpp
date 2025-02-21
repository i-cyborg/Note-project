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
        n1 = std::make_shared<Note>(titolo_nota, testo_nota, false, false);
        o1 = std::make_shared<ConcreteObserver>(collection.get());

    }

    std::shared_ptr<Collection> collection;
    std::shared_ptr<Note> n1;
    std::shared_ptr<ConcreteObserver> o1;
};

TEST_F(CollectionTest, TestAddNote) {
    collection->addNote(n1);
    ASSERT_EQ(collection->getNotes(0)->getTitle(), "Nota di testing");
}

TEST_F(CollectionTest, TestRemoveNote) {
    collection->addNote(n1);
    ASSERT_TRUE(collection->removeNote(n1));
    ASSERT_EQ(collection->getNotes(0), nullptr);
    ASSERT_FALSE(collection->removeNote(n1));
}

TEST_F(CollectionTest, TestRemoveLockedNote) {
    n1->lock();
    collection->addNote(n1);
    ASSERT_FALSE(collection->removeNote(n1));
    n1->unlock();
    ASSERT_TRUE(collection->removeNote(n1));
}

TEST_F(CollectionTest, TestGetName) {
    ASSERT_EQ(collection->getName(), "Collezione di testing");
}

TEST_F(CollectionTest, SearchByTitle) {
    collection->addNote(n1);
    auto foundNote = collection->searchByTitle("Nota di testing");
    ASSERT_EQ(foundNote->getTitle(), "Nota di testing");
    auto notFoundNote = collection->searchByTitle("Titolo sbagliato");
    ASSERT_EQ(notFoundNote, nullptr);
}

TEST_F(CollectionTest, SearchByText) {
    collection->addNote(n1);
    auto foundNote = collection->searchByText("Testo di prova");
    ASSERT_EQ(foundNote->getBody(), "Testo di prova");
    auto notFoundNote = collection->searchByText("Testo sbagliato");
    ASSERT_EQ(notFoundNote, nullptr);
}

TEST_F(CollectionTest, UpdateNoteTitle) {
    collection->addNote(n1);

    std::string input = "0\n1\nNuovo Titolo\n";
    std::istringstream simulatedInput(input);
    std::cin.rdbuf(simulatedInput.rdbuf());
    std::ostringstream output;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    bool result = collection->updateNote();

    std::cin.rdbuf(std::cin.rdbuf());
    std::cout.rdbuf(originalCoutBuffer);

    ASSERT_TRUE(result);
    ASSERT_EQ(collection->getNotes(0)->getTitle(), "Nuovo Titolo");
    ASSERT_NE(collection->getNotes(0)->getTitle(), "Nota di testing");
}

TEST_F(CollectionTest, UpdateNoteBody) {
    collection->addNote(n1);

    std::string input = "0\n2\nNuovo Testo\n";
    std::istringstream simulatedInput(input);
    std::cin.rdbuf(simulatedInput.rdbuf());
    std::ostringstream output;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    bool result = collection->updateNote();

    std::cin.rdbuf(std::cin.rdbuf());
    std::cout.rdbuf(originalCoutBuffer);

    ASSERT_TRUE(result);
    ASSERT_EQ(collection->getNotes(0)->getBody(), "Nuovo Testo");
    ASSERT_NE(collection->getNotes(0)->getBody(), "Testo di prova");
}

TEST_F(CollectionTest, UpdateLockedNote) {
    n1->lock();
    collection->addNote(n1);
    std::string input = "0\n1\nNuovo Titolo\n";
    std::istringstream simulatedInput(input);
    std::cin.rdbuf(simulatedInput.rdbuf());
    std::ostringstream output;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    bool result = collection->updateNote();

    std::cin.rdbuf(std::cin.rdbuf());
    std::cout.rdbuf(originalCoutBuffer);

    ASSERT_FALSE(result);
    ASSERT_NE(collection->getNotes(0)->getTitle(), "Nuovo Titolo");
}

TEST_F(CollectionTest, GetNoteCount) {
    collection->addNote(n1);
    ASSERT_EQ(collection->getNoteCount(), 1);
    collection->removeNote(n1);
    ASSERT_EQ(collection->getNoteCount(), 0);
}

TEST_F(CollectionTest, ObserverUpdate) {
    ASSERT_EQ(o1->update(), 0);
    collection->addNote(n1);
    ASSERT_EQ(o1->update(), 1);
    collection->removeNote(n1);
    ASSERT_EQ(o1->update(), 0);
}

TEST_F(CollectionTest, DetachObserver) {
    ASSERT_FALSE(collection->getObservers().empty());
    o1->detach();
    ASSERT_TRUE(collection->getObservers().empty());
}

TEST_F(CollectionTest, AttachObserver) {
    ASSERT_FALSE(collection->getObservers().empty());
    o1->detach();
    ASSERT_TRUE(collection->getObservers().empty());
    o1->attach();
    ASSERT_FALSE(collection->getObservers().empty());
}
