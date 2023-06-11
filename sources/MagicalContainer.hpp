//
// Created by beni on 5/28/23.
//
#include <vector>
#include <cstddef>


#ifndef MAGICAL_ITERATORS_PARTA_MAGICALCONTAINER_HPP
#define MAGICAL_ITERATORS_PARTA_MAGICALCONTAINER_HPP
namespace ariel {

    class MagicalContainer {
    private:
        std::vector<int> elementsContainer;
        std::vector<int *> pointerPrime;


    public:
        //constructor
        MagicalContainer() = default;

        //destructor
        ~MagicalContainer() ;

        //copy constructor
        MagicalContainer(const MagicalContainer &other) = default;

        //move constructor
        MagicalContainer(MagicalContainer &&other) = default;

        //assignment operators
        MagicalContainer &operator=(MagicalContainer &&other) = default;

        MagicalContainer &operator=(const MagicalContainer &other) = default;

        //MagicalContainer Functions
        void addElement(int element);

        void removeElement(int element);

        bool is_Prime(int element);

        size_t size() const;

        bool sortPointers(int *int1, int *int2);

        std::vector<int *>::iterator findInsertionPoint(std::vector<int *> &vec, int *element);

        bool is_exist(int element);

        bool operator==(const MagicalContainer &rhs) const;

        bool operator!=(const MagicalContainer &rhs) const;

        const std::vector<int *> &getPointerPrime() const;


//Iterators Classes

        //*****************
        //AscendingIterator
        //*****************
        class AscendingIterator {
            MagicalContainer &container;
            std::vector<int>::iterator it;
            size_t index;


        public:
            explicit AscendingIterator(MagicalContainer &container);

            AscendingIterator(const AscendingIterator &other);

            AscendingIterator(AscendingIterator &&other) = default;

            AscendingIterator &operator=(const AscendingIterator &other);

            ~AscendingIterator() = default;

            bool operator==(const AscendingIterator &other) const;

            bool operator!=(const AscendingIterator &other) const;

            bool operator>(const AscendingIterator &other) const;

            bool operator<(const AscendingIterator &other) const;

            AscendingIterator &operator++();

            int operator*();

            AscendingIterator begin();

            AscendingIterator end();

            AscendingIterator &operator=(AscendingIterator &&other) noexcept;
        };

        //*****************
        // SideCrossIterator
        //*****************
        class SideCrossIterator {
             MagicalContainer &container;
            std::vector<int>::iterator frontElement;
            std::vector<int>::iterator endElement;
            bool flip; //true=frontElement, false=endElement
            size_t index;


        public:
            explicit SideCrossIterator(MagicalContainer &container);

            SideCrossIterator(const SideCrossIterator &other);

            SideCrossIterator(SideCrossIterator &&other) = default;

            SideCrossIterator &operator=(const SideCrossIterator &other);

            ~SideCrossIterator() = default;

            bool operator==(const SideCrossIterator &other) const;

            bool operator!=(const SideCrossIterator &other) const;

            bool operator>(const SideCrossIterator &other) const;

            bool operator<(const SideCrossIterator &other) const;

            SideCrossIterator &operator++();

            int operator*();

            SideCrossIterator begin();

            SideCrossIterator end();

            SideCrossIterator &operator=(SideCrossIterator &&other) noexcept;
        };

        //*****************
        //PrimeIterator
        //*****************
        class PrimeIterator {

            MagicalContainer &container;
            std::vector<int *>::iterator it;
            size_t index;

        public:
            explicit PrimeIterator(MagicalContainer &container);

            PrimeIterator(const PrimeIterator &other);

            PrimeIterator(PrimeIterator &&other) = default;

            PrimeIterator &operator=(const PrimeIterator &other);

            ~PrimeIterator() = default;

            bool operator==(const PrimeIterator &other) const;

            bool operator!=(const PrimeIterator &other) const;

            bool operator>(const PrimeIterator &other) const;

            bool operator<(const PrimeIterator &other) const;

            PrimeIterator &operator++();

            int operator*();

            PrimeIterator begin();

            PrimeIterator end();

            PrimeIterator &operator=(PrimeIterator &&other) noexcept;
        };


    };
}

#endif
