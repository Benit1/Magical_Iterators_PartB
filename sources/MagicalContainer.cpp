//
// Created by beni on 5/28/23.
//
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <valarray>
#include <iostream>
#include "MagicalContainer.hpp"

using namespace ariel;

void MagicalContainer::addElement(int element) {
    if (!is_exist(element)) {
        //returns an iterator to the first element in the sorted range that is not less than element
        //If all the elements in the range are less than element, the function returns end
        auto iter = lower_bound(this->elementsContainer.begin(), this->elementsContainer.end(), element);
        //inserts the element
        this->elementsContainer.insert(iter, element);
        // If the element is prime
        if (is_Prime(element)) {
            // Allocate memory for the prime element
            int *prime_element = new int(element);
            // insert into pointerPrime at the right position and keep it sorted
            auto it_prime = findInsertionPoint(this->pointerPrime, prime_element);
            this->pointerPrime.insert(it_prime, prime_element);
        }
    }
}

std::vector<int *>::iterator MagicalContainer::findInsertionPoint(std::vector<int *> &vec, int *element) {
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (sortPointers(element, *it)) {
            return it;
        }
    }
    return vec.end();
}

void MagicalContainer::removeElement(int element) {
    {
        auto it = std::find(elementsContainer.begin(), elementsContainer.end(), element);

        if (it != elementsContainer.end()) {
            elementsContainer.erase(it);
        } else {
            throw std::runtime_error("No element found in the magical container");
        }
    }
}

size_t MagicalContainer::size() const {
    return elementsContainer.size();
}

bool MagicalContainer::sortPointers(int *int1, int *int2) {
    return *int1 < *int2;

}

bool MagicalContainer::operator==(const MagicalContainer &rhs) const {
    return elementsContainer == rhs.elementsContainer &&
           pointerPrime == rhs.pointerPrime;
}

bool MagicalContainer::operator!=(const MagicalContainer &rhs) const {
    return !(rhs == *this);
}

//*****************
//AscendingIterator
//*****************
MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container) : container(container),
                                                                                      it(this->container.elementsContainer.begin()),
                                                                                      index(1) {

}


MagicalContainer::AscendingIterator::AscendingIterator(
        const AscendingIterator &other) : container(
        other.container), it(other.it), index(1) {

}

MagicalContainer::AscendingIterator &
MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other) {
    if (this != &other) {
        if (this->container != other.container)throw std::runtime_error("Not the same container");
        this->it = other.it;
        index = other.index;
        return *this;
    }
    return *this;
}


bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const {
    if (this->container.elementsContainer != other.container.elementsContainer)
        throw std::runtime_error("Not the same container");
    return container == other.container && this->index == other.index;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const {
    return (!(this->index == other.index));
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const {
    if (this->container.elementsContainer != other.container.elementsContainer)
        throw std::runtime_error("Not the same container");
    return this->index > other.index;
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const {
    if (this->container.elementsContainer != other.container.elementsContainer)
        throw std::runtime_error("Not the same container");
    return this->index < other.index;
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
    if (it == container.elementsContainer.end()) {
        throw std::runtime_error("Iterator is out of bounds");
    }
    it++;
    index++;
    return *this;
}

int MagicalContainer::AscendingIterator::operator*() {
    if (it == container.elementsContainer.end()) {
        throw std::runtime_error("Error encountered returning the value of the iterator");
    }
    return *it;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
    return AscendingIterator(this->container);
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
    AscendingIterator EndAscIt(this->container);
    EndAscIt.it = this->container.elementsContainer.end();
    EndAscIt.index = this->container.elementsContainer.size() + 1;
    return EndAscIt;
}

MagicalContainer::AscendingIterator &
MagicalContainer::AscendingIterator::operator=(MagicalContainer::AscendingIterator &&other) noexcept {
    if (this != &other) {
        container = other.container;
        it = std::move(other.it);
        index = other.index;
    }
    return *this;
}


//*****************
// SideCrossIterator
//*****************
MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container) : container(container),
                                                                                      frontElement(
                                                                                              container.elementsContainer.begin()),
                                                                                      endElement(
                                                                                              --container.elementsContainer.end()),
                                                                                      flip(true), index(1) {

}

MagicalContainer::SideCrossIterator::SideCrossIterator(
        const SideCrossIterator &other) : container(
        other.container), frontElement(other.container.elementsContainer.begin()),
                                          endElement(--other.container.elementsContainer.end()),
                                          flip(true), index(1) {

}


MagicalContainer::SideCrossIterator &
MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other) {
    if (this != &other) {
        if (this->container != other.container)throw std::runtime_error("Not the same container");
        this->frontElement = other.frontElement;
        this->endElement = other.endElement;
        return *this;
    }
    return *this;
}


bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const {
    if (this->container.elementsContainer != other.container.elementsContainer)
        throw std::runtime_error("Not the same container");
    return this->index == other.index;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const {
    return (!(this->index == other.index));
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const {
    if (this->container.elementsContainer != other.container.elementsContainer)
        throw std::runtime_error("Not the same container");
    return this->index > other.index;
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const {
    if (this->container.elementsContainer != other.container.elementsContainer)
        throw std::runtime_error("Not the same container");
    return this->index < other.index;
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
    if (index >= this->container.size() + 1) {
        throw std::runtime_error("Iterator cannot be promoted");
    }

//If flip is true, frontElement (an iterator pointing to the start of the container) is incremented
//otherwise endElement(an iterator pointing to the end of the container) is decremented.
    flip ? ++frontElement : --endElement;
    flip = !flip;

    ++index;

    return *this;
}

int MagicalContainer::SideCrossIterator::operator*() {
    if (index > this->container.size()) {
        throw std::runtime_error("Iterator is out of bounds");
    }
//flip is true, it returns the value pointed to by frontElement
//otherwise, it returns the value pointed to by endElement
    return flip ? *frontElement : *endElement;
}


MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
    return SideCrossIterator(this->container);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
    SideCrossIterator EndScIt(this->container);
    EndScIt.frontElement = this->container.elementsContainer.end();
    EndScIt.endElement = this->container.elementsContainer.end();
    EndScIt.index = this->container.size() + 1;
    return EndScIt;
}

MagicalContainer::SideCrossIterator &
MagicalContainer::SideCrossIterator::operator=(MagicalContainer::SideCrossIterator &&other) noexcept {
    if (this != &other) {
        container = other.container;
        frontElement = std::move(other.frontElement);
        endElement = std::move(other.endElement);
        index = other.index;
    }
    return *this;
}


//*****************
//PrimeIterator
//*****************
MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container) : container(container),
                                                                              it(this->container.pointerPrime.begin()),
                                                                              index(1) {

}

MagicalContainer::PrimeIterator::PrimeIterator(
        const PrimeIterator &other) : container(other.container), it(other.it), index(1) {

}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) {
    if (this != &other) {
        if (this->container.pointerPrime != other.container.pointerPrime)
            throw std::runtime_error("Not the same container");
        this->it = other.it;
        return *this;
    }

    return *this;
}


bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const {
    if (this->container.pointerPrime != other.container.pointerPrime)
        throw std::runtime_error("Not the same container");
    return container == other.container && this->index == other.index;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const {
    return (!(this->index == other.index));
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const {
    if (this->container.pointerPrime != other.container.pointerPrime)
        throw std::runtime_error("Not the same container");
    return this->index > other.index;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const {
    if (this->container.pointerPrime != other.container.pointerPrime)
        throw std::runtime_error("Not the same container");
    return this->index < other.index;
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
    if (it == container.pointerPrime.end()) {
        throw std::runtime_error("Iterator is out of bounds");
    }
    it++;
    index++;
    return *this;
}

int MagicalContainer::PrimeIterator::operator*() {
    if (it == container.pointerPrime.end()) {
        throw std::runtime_error("Error encountered returning the value of the iterator");
    }
    return **it;
}


MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
    return PrimeIterator(this->container);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
    PrimeIterator EndPrimeIt(*this);
    EndPrimeIt.it = this->container.pointerPrime.end();
    EndPrimeIt.index = this->container.pointerPrime.size() + 1;
    return EndPrimeIt;
}

MagicalContainer::PrimeIterator &
MagicalContainer::PrimeIterator::operator=(MagicalContainer::PrimeIterator &&other) noexcept {
    if (this != &other) {
        container = other.container;
        it = std::move(other.it);
        index = other.index;
    }
    return *this;
}




//************************
//helper functions
//************************

const std::vector<int *> &MagicalContainer::getPointerPrime() const {
    return pointerPrime;
}

bool MagicalContainer::is_Prime(int element) {
    if (element <= 1) {
        return false;
    }
    if (element == 2) {
        return true;
    }
    if (element % 2 == 0) {
        return false;
    }
    for (int i = 3; i <= std::sqrt(element); i += 2) {
        if (element % i == 0) {
            return false;
        }
    }
    return true;
}

bool MagicalContainer::is_exist(int element) {
    if (std::find(this->elementsContainer.begin(), this->elementsContainer.end(), element) !=
        this->elementsContainer.end())
        return true;
    return false;
}

MagicalContainer::~MagicalContainer() {
    for (size_t i = 0; i < this->pointerPrime.size(); ++i) {
        delete pointerPrime.at(i);
    }

}


