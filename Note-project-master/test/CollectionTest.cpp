//
// Created by volta on 21/11/2024.
//

#include "gtest/gtest.h"
#include "../Collection.h"
#include "../Note.h"

class CollectionTest : public ::testing::Test {
protected:
    void SetUp() override {
        collection = std::make_shared<Collection>("Collezione di prova");
        o1 = std::make_shared<ConcreteObserver>(collection.get());
    }

    std::shared_ptr<Collection> collection;
    std::shared_ptr<Note> n1;
    std::shared_ptr<ConcreteObserver> o1;
};

TEST_F(CollectionTest, TestAddEmptyNote) {
    EXPECT_FALSE(collection->addNote("", "testo di prova", false, false));
    EXPECT_FALSE(collection->addNote("Titolo di prova", "", false, false));
    EXPECT_FALSE(collection->addNote("", "", false, false));
    EXPECT_TRUE(collection->addNote("Titolo di prova", "testo di prova", false, false));
}

TEST_F(CollectionTest, TestAddSameTitleNote) {
    EXPECT_TRUE(collection->addNote("Titolo di prova", "testo di prova", false, false));
    EXPECT_FALSE(collection->addNote("Titolo di prova", "testo di prova", false, false));
}

TEST_F(CollectionTest, TestAddNote) {
    EXPECT_TRUE(collection->addNote("Titolo di prova", "testo di prova", false, false));
    EXPECT_EQ(collection->getNoteCount(), 1);
    EXPECT_EQ(collection->getImportantNoteCount(), 0);
}

TEST_F(CollectionTest, TestAddImportantNote) {
    EXPECT_TRUE(collection->addNote("Titolo di prova", "testo di prova", false, true));
    EXPECT_EQ(collection->getNoteCount(), 0);
    EXPECT_EQ(collection->getImportantNoteCount(), 1);
}

TEST_F(CollectionTest, TestRemoveNote) {
    collection->addNote("Titolo di prova", "testo di prova", false, false);
    EXPECT_EQ(collection->getNoteCount(), 1);
    EXPECT_TRUE(collection->removeNote(0, false));
    EXPECT_EQ(collection->getNoteCount(), 0);
    EXPECT_FALSE(collection->removeNote(0, false));
}

TEST_F(CollectionTest, TestRemoveImportantNote) {
    collection->addNote("Titolo di prova", "testo di prova", false, true);
    EXPECT_EQ(collection->getImportantNoteCount(), 1);
    EXPECT_TRUE(collection->removeNote(0, true));
    EXPECT_EQ(collection->getImportantNoteCount(), 0);
    EXPECT_FALSE(collection->removeNote(0, true));
}

TEST_F(CollectionTest, TestRemoveLockedNote) {
    collection->addNote("Titolo di prova", "testo di prova", true, false);
    auto note = collection->getNotes(0);
    EXPECT_TRUE(note->getLock());
    EXPECT_FALSE(collection->removeNote(0, false));
    EXPECT_EQ(collection->getNoteCount(), 1);
    note->unlock();
    EXPECT_TRUE(collection->removeNote(0, false));
    EXPECT_EQ(collection->getNoteCount(), 0);
}

TEST_F(CollectionTest, TestGetName) {
    EXPECT_EQ(collection->getName(), "Collezione di prova");
}

TEST_F(CollectionTest, TestGetNotes) {
    collection->addNote("Titolo 1", "Testo 1", false, false);
    collection->addNote("Titolo 2", "Testo 2", false, false);
    collection->addNote("Titolo 3", "Testo 3", false, false);

    std::shared_ptr<Note> note = collection->getNotes(1);
    EXPECT_EQ(note->getTitle(), "Titolo 2");
    EXPECT_EQ(note->getBody(), "Testo 2");
    note = collection->getNotes(-10);
    EXPECT_EQ(note, nullptr);
    note = collection->getNotes(100000);
    EXPECT_EQ(note, nullptr);
}

TEST_F(CollectionTest, TestGetImportantNotes) {
    collection->addNote("Titolo 1", "Testo 1", false, true);
    collection->addNote("Titolo 2", "Testo 2", false, true);
    collection->addNote("Titolo 3", "Testo 3", false, true);

    std::shared_ptr<Note> note = collection->getImportantNotes(1);
    EXPECT_EQ(note->getTitle(), "Titolo 2");
    EXPECT_EQ(note->getBody(), "Testo 2");
    note = collection->getImportantNotes(-12);
    EXPECT_EQ(note, nullptr);
    note = collection->getImportantNotes(100000);
    EXPECT_EQ(note, nullptr);
}

TEST_F(CollectionTest, TestGetNoteCount) {
    collection->addNote("Titolo di prova", "Testo di prova", false, false);
    EXPECT_EQ(collection->getNoteCount(), 1);
    collection->removeNote(0, false);
    EXPECT_EQ(collection->getNoteCount(), 0);
}

TEST_F(CollectionTest, TestGetImportantNoteCount) {
    collection->addNote("Titolo di prova", "Testo di prova", false, true);
    EXPECT_EQ(collection->getImportantNoteCount(), 1);
    collection->removeNote(0, true);
    EXPECT_EQ(collection->getImportantNoteCount(), 0);
}

TEST_F(CollectionTest, TestUpdateNoteTitle) {
    //testo modifica titolo di nota normale
    collection->addNote("Titolo di prova", "Testo di prova", false, false);
    EXPECT_TRUE(collection->updateNoteTitle(0, false, "Nuovo Titolo"));
    EXPECT_EQ(collection->getNotes(0)->getTitle(), "Nuovo Titolo");
    //testo modifica titolo di nota importante
    collection->addNote("Titolo di prova", "Testo di prova", false, true);
    EXPECT_TRUE(collection->updateNoteTitle(0, true, "Nuovo Titolo 2"));
    //testo che nuovo titolo non corrisponda ad uno già presente nella collezione
    EXPECT_FALSE(collection->updateNoteTitle(0, true, "Nuovo Titolo"));
}

TEST_F(CollectionTest, TestUpdateNoteTitleEmpty) {
    collection->addNote("Titolo di prova", "Testo di prova", false, false);
    EXPECT_THROW(collection->updateNoteTitle(0, false, ""), std::invalid_argument);
}

TEST_F(CollectionTest, TestUpdateLockedNoteTitle) {
    collection->addNote("Titolo di prova", "Testo di prova", true, false);
    EXPECT_FALSE(collection->updateNoteTitle(0, false, "Nuovo Titolo"));
    auto note = collection->getNotes(0);
    note->unlock();
    EXPECT_TRUE(collection->updateNoteTitle(0, false, "Nuovo Titolo"));
}

TEST_F(CollectionTest, TestUpdateNoteText) {
    //testo modifica testo di nota normale
    collection->addNote("Titolo di prova", "Testo di prova", false, false);
    EXPECT_TRUE(collection->updateNoteText(0, false, "Nuovo Testo"));
    EXPECT_EQ(collection->getNotes(0)->getBody(), "Nuovo Testo");
    //testo modifica testo di nota importante
    collection->addNote("Titolo di prova 2", "Testo di prova", false, true);
    EXPECT_TRUE(collection->updateNoteText(0, true, "Nuovo Testo 2"));
}

TEST_F(CollectionTest, TestUpdateNoteTextEmpty) {
    collection->addNote("Titolo di prova", "Testo di prova", false, false);
    EXPECT_THROW(collection->updateNoteText(0, false, ""), std::invalid_argument);
}

TEST_F(CollectionTest, TestUpdateLockedNoteText) {
    collection->addNote("Titolo di prova", "Testo di prova", true, false);
    EXPECT_FALSE(collection->updateNoteText(0, false, "Nuovo Testo"));
    auto note = collection->getNotes(0);
    note->unlock();
    EXPECT_TRUE(collection->updateNoteText(0, false, "Nuovo Testo"));
}

TEST_F(CollectionTest, TestUpdateNoteImportantAttribute) {
    collection->addNote("Titolo di prova", "Testo di prova", false, true);
    EXPECT_TRUE(collection->updateNoteImportant(0, true, false));
    EXPECT_FALSE(collection->getNotes(0)->getImportant());
    EXPECT_EQ(collection->getImportantNoteCount(), 0);
    EXPECT_EQ(collection->getNoteCount(), 1);
    collection->removeNote(0, false);

    collection->addNote("Titolo di prova 2", "Testo di prova", false, false);
    EXPECT_TRUE(collection->updateNoteImportant(0, false, true));
    EXPECT_TRUE(collection->getImportantNotes(0)->getImportant());
    EXPECT_EQ(collection->getImportantNoteCount(), 1);
    EXPECT_EQ(collection->getNoteCount(), 0);
}

TEST_F(CollectionTest, TestUpdateLockedNoteImportantAttribute) {
    collection->addNote("Titolo di prova", "Testo di prova", true, false);
    EXPECT_FALSE(collection->updateNoteImportant(0, false, true));
}

TEST_F(CollectionTest, SearchByTitle) {
    collection->addNote("Titolo di prova", "Testo di prova", false, false);
    auto foundNote = collection->searchByTitle("Titolo di prova");
    EXPECT_EQ(foundNote->getTitle(), "Titolo di prova");
    auto notFoundNote = collection->searchByTitle("Titolo sbagliato");
    EXPECT_EQ(notFoundNote, nullptr);
}

TEST_F(CollectionTest, TestSearchByText) {
    collection->addNote("Titolo 1", "Testo 1", false, false);
    collection->addNote("Titolo 2", "Testo di prova", false, false);
    collection->addNote("Titolo 3", "Testo di prova", true, true);
    collection->addNote("Titolo 4", "Testo diverso", false, false);

    std::list<std::shared_ptr<Note>> results = collection->searchByText("Testo di prova");
    EXPECT_EQ(results.size(), 2);

    results = collection->searchByText("Testo non presente");
    EXPECT_EQ(results.size(), 0);


    results = collection->searchByText("Testo diverso");
    EXPECT_EQ(results.size(), 1);
}

