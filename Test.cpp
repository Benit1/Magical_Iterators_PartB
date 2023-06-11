//
// Created by beni on 5/28/23.
//
#include "doctest.h"
#include "sources/MagicalContainer.hpp"

TEST_SUITE("MagicalContainer initialization") {

    TEST_CASE("AscendingIterator") {
        ariel::MagicalContainer container;
        CHECK_EQ(container.size(), 0);
        ariel::MagicalContainer::AscendingIterator ascIt(container);

        CHECK(ascIt.begin() == ascIt.end());
        CHECK_FALSE(ascIt.begin() != ascIt.end());
    }

    TEST_CASE("SideCrossIterator") {
        ariel::MagicalContainer container;
        CHECK_EQ(container.size(), 0);
        ariel::MagicalContainer::SideCrossIterator sideIt(container);

        CHECK(sideIt.begin() == sideIt.end());
        CHECK_FALSE(sideIt.begin() != sideIt.end());
    }

    TEST_CASE("PrimeIterator") {
        ariel::MagicalContainer container;
        CHECK_EQ(container.size(), 0);
        ariel::MagicalContainer::PrimeIterator primeIt(container);

        CHECK(primeIt.begin() == primeIt.end());
        CHECK_FALSE(primeIt.begin() != primeIt.end());
    }

}

TEST_SUITE("Add and Remove elements from Magical Container") {
    TEST_CASE("Add and Remove function work correctly") {
        ariel::MagicalContainer container;
        container.addElement(10);
        CHECK_EQ(container.size(), 1);
        container.addElement(5);
        CHECK_EQ(container.size(), 2);
        container.addElement(20);
        CHECK_EQ(container.size(), 3);
        container.addElement(15);
        CHECK_EQ(container.size(), 4);

        container.removeElement(5);
        CHECK_EQ(container.size(), 3);
        container.removeElement(20);
        CHECK_EQ(container.size(), 2);

    }

    TEST_CASE("Removing non existing element throws an exception") {
        ariel::MagicalContainer container;
        container.addElement(10);
        container.addElement(5);
        CHECK_THROWS(container.removeElement(11));
        CHECK_THROWS(container.removeElement(12));
    }

    TEST_CASE("Adding and Removing large number of elements") {
        ariel::MagicalContainer container;
        const int numElements = 1000;

        // Add elements
        for (int i = 0; i < numElements; ++i) {
            container.addElement(i);
        }
        CHECK_EQ(container.size(), numElements);

        // Remove elements
        for (int i = 0; i < numElements; ++i) {
            container.removeElement(i);
        }
        CHECK_EQ(container.size(), 0);
    }

    TEST_CASE("Adding the same two elements does not affect the size") {
        ariel::MagicalContainer container;
        container.addElement(10);
        CHECK_EQ(container.size(), 1);
        container.addElement(10);
        CHECK_EQ(container.size(), 1);
    }

}
TEST_SUITE("Test each iterator separately") {
    TEST_CASE("AscendingIterator") {
        ariel::MagicalContainer container;
        container.addElement(4);
        container.addElement(3);
        container.addElement(2);
        container.addElement(1);
        ariel::MagicalContainer::AscendingIterator ascIt(container);
        CHECK_EQ(*ascIt.begin(), 1);
        CHECK_EQ((*(++ascIt)), 2);
        CHECK_EQ((*(++ascIt)), 3);
        CHECK_EQ((*(++ascIt)), 4);
        CHECK_EQ((*(++ascIt)), *ascIt.end());
    }

    TEST_CASE("SideCrossIterator") {
        ariel::MagicalContainer container;
        container.addElement(1);
        container.addElement(2);
        container.addElement(3);
        container.addElement(4);
        ariel::MagicalContainer::SideCrossIterator sidIt(container);
        CHECK_EQ(*sidIt.begin(), 1);
        CHECK_EQ((*(++sidIt)), 4);
        CHECK_EQ((*(++sidIt)), 2);
        CHECK_EQ((*(++sidIt)), 3);
        CHECK_EQ((*(++sidIt)), *sidIt.end());
    }

    TEST_CASE("PrimeIterator") {
        ariel::MagicalContainer container;
        container.addElement(11);
        container.addElement(2);
        container.addElement(7);
        container.addElement(4);
        ariel::MagicalContainer::PrimeIterator primeIt(container);
        CHECK_EQ(*primeIt.begin(), 2);
        CHECK_EQ((*(++primeIt)), 7);
        CHECK_EQ((*(++primeIt)), 11);
        CHECK_EQ((*(++primeIt)), *primeIt.end());
    }
}
