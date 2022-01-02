#pragma once
#include <forward_list>
#include <queue>
#include <stack>
#include <iostream>

using namespace std;

template <class T>
class Tree {
    private:
        const T data;
        Tree* parent;
        unsigned size = 1;
        unsigned height = 1;

        forward_list<Tree*>* children;

        void addChild(Tree* tree);

        void increaseSize(unsigned value);

        void setHeight(unsigned value);

        #include "iterators.h"

    public:

        typedef Iterator<Tree> iterator;
        typedef Iterator<const Tree> const_iterator;
        typedef ReverseIterator<Tree> riterator;
        typedef ReverseIterator<const Tree> const_riterator;

        Tree(const T& data, Tree* parent);

        Tree(const Tree<T>& r);

        Tree(Tree&& r) noexcept;

        ~Tree();

        void insertNode(const T& toInsert , const T& parent);

        Tree& search(const T& toFind);

        const Tree& search(const T& toFind) const;

        int children_count() const;

        iterator begin() {
            return iterator(this);
        }

        iterator end() {
            return iterator(nullptr);
        }

        const_iterator cbegin() const {
            return const_iterator(this);
        }

        const_iterator cend() const {
            return const_iterator(nullptr);
        }

        riterator rbegin() {
            return riterator(this);
        }

        riterator rend() {
            return riterator(nullptr);
        }

        const_riterator rcbegin() const {
            return const_riterator(this);
        }

        const_riterator rcend() const {
            return const_riterator(nullptr);
        }

        const T& getData();

        const T& getData() const;

        const unsigned getSize() const;

        const unsigned getSize();

        const unsigned getHeight() const;

        const unsigned getHeight();

        const Tree* getParent() const;

        forward_list<Tree*>* getChildren() const;

        bool operator==(Tree other);

        void remove(const T& toDelete);

        string print() const;

        bool operator<(Tree& other);
        bool operator>(Tree& other);
        bool operator=(Tree& other);
        bool operator!=(Tree& other);
};

#include "../src/tree.inl"