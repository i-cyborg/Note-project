//
// Created by volta on 20/03/2025.
//
#include "gtest/gtest.h"
#include "../Collection.h"
#include "../ConcreteObserver.h"

class TestObserver : public ConcreteObserver {
public:
    explicit TestObserver(Collection* c) : ConcreteObserver(c) {}
    virtual ~TestObserver() {}

    int updateCount = 0;

    //tiene traccia di quando update() viene chiamato
    void update() override {
        updateCount++;
    }

    int getUpdateCount() const {
        return updateCount;
    }
};


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

//Testa con un observer di test che update() venga effettivamente chiamato e controlla che il conteggio sia corretto
TEST_F(ObserverTest, ObserverUpdateTest) {
    std::shared_ptr<TestObserver> testObserver = std::make_shared<TestObserver>(collection.get());

    EXPECT_EQ(testObserver->getUpdateCount(), 0);
    EXPECT_EQ(o1->getNoteCount(), 0);
    collection->addNote("Titolo di prova", "Testo di prova", false, false);
    EXPECT_EQ(testObserver->getUpdateCount(), 1);
    EXPECT_EQ(o1->getNoteCount(), 1);
    collection->removeNote(0, false);
    EXPECT_EQ(testObserver->getUpdateCount(), 2);
    EXPECT_EQ(o1->getNoteCount(), 0);
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