//
// Created by volta on 20/03/2025.
//
#include "gtest/gtest.h"
#include "../Collection.h"
#include "../ConcreteObserver.h"

class ObserverTest : public ::testing::Test {
protected:
    void SetUp() override {
        collection = std::make_shared<Collection>("Collezione di prova");
        o1 = std::make_shared<ConcreteObserver>(collection.get());
    }

    std::shared_ptr<Collection> collection;
    std::shared_ptr<Note> n1;
    std::shared_ptr<ConcreteObserver> o1;
};

TEST_F(ObserverTest, ObserverUpdate) {
    EXPECT_EQ(o1->update(), 0);
    collection->addNote("Titolo di prova", "Testo di prova", false, false);
    EXPECT_EQ(o1->update(), 1);
    collection->removeNote(0, false);
    EXPECT_EQ(o1->update(), 0);
}

TEST_F(ObserverTest, DetachObserver) {
    EXPECT_FALSE(collection->getObservers().empty());
    o1->detach();
    EXPECT_TRUE(collection->getObservers().empty());
}

TEST_F(ObserverTest, AttachObserver) {
    EXPECT_FALSE(collection->getObservers().empty());
    o1->detach();
    EXPECT_TRUE(collection->getObservers().empty());
    o1->attach();
    EXPECT_FALSE(collection->getObservers().empty());
}