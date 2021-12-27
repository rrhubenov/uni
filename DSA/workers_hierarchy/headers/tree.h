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

        void addChild(Tree* tree) {
            if(children == nullptr) {
                children = new forward_list<Tree*>;
            }
            children->push_front(tree);
        }

        void increaseSize(unsigned value) {
            size += value;
            Tree* next_parent = parent;
            while(next_parent != nullptr) {
                next_parent->size += value;
                next_parent = next_parent->parent;
            }
        }

        void setHeight(unsigned value) {
            this->height = value;
            if(children != nullptr) {
                for(typename forward_list<Tree*>::iterator it = children->begin(); it != children->end(); ++it) {
                    (*it)->setHeight(value + 1);
                }
            }
        }

        #include "iterators.h"

    public:

        typedef Iterator<Tree> iterator;
        typedef Iterator<const Tree> const_iterator;
        typedef ReverseIterator<Tree> riterator;
        typedef ReverseIterator<const Tree> const_riterator;

        Tree(const T& data, Tree* parent): data(data), parent(parent), children(nullptr) {
            if(this->parent != nullptr) {
                this->height = this->parent->height + 1;
            }
        };

        Tree(const Tree<T>& r): data(r.getData()), parent(nullptr), children(nullptr) {
            Tree<T>::const_iterator it = r.cbegin();
            ++it;
            for(;it != r.cend(); ++it) {
                this->insertNode(it->getData(), it->getParent()->getData());
            }
        }

        void insertNode(const T& toInsert , const T& parent) {
            //TODO: A lot of refactoring is needed
            //TODO: If parent does not exists, throw error
            try {
                Tree& already_exists = search(toInsert);

                assert(already_exists.parent != nullptr);
                assert(already_exists.parent->children != nullptr);

                already_exists.parent->children->remove(&already_exists);
                already_exists.parent->increaseSize(-1);

                Tree& new_parent = search(parent);
                new_parent.addChild(&already_exists);
                new_parent.increaseSize(1);
                already_exists.parent = &new_parent;
                already_exists.setHeight(new_parent.getHeight() + 1);

            } catch(runtime_error e) {
                if(strcmp(e.what(), "Element not found") == 0) {
                    Tree& tree_parent = search(parent);
                    tree_parent.addChild(new Tree(toInsert, &tree_parent));

                    tree_parent.increaseSize(1);
                } else {
                    throw e;
                }
            }
        }

        Tree& search(const T& toFind) {
            for(Tree<T>::iterator it = begin(); it != end(); ++it) {
                if(it->getData() == toFind) {
                    return *it;
                }
            }

            throw runtime_error("Element not found");
        }

        const Tree& search(const T& toFind) const {
            for(Tree<T>::const_iterator it = cbegin(); it != cend(); ++it) {
                if(it->getData() == toFind) {
                    return *it;
                }
            }

            throw runtime_error("Element not found");
        }

        int children_count() const {
            int count = 0;

            if(children != nullptr) {
                for(typename forward_list<Tree*>::iterator it = children->begin(); it != children->end(); ++it) {
                    count++;
                }
            }

            return count;
        }

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

        const T& getData() {
            return data;
        }

        const T& getData() const {
            return data;
        }

        const unsigned getSize() const {
            return size;
        }

        const unsigned getSize() {
            return size;
        }

        const unsigned getHeight() const {
            return height;
        }

        const unsigned getHeight() {
            return height;
        }

        const Tree* getParent() const {
            return this->parent;
        }

        forward_list<Tree*>* getChildren() const {
            return this->children;
        }

        bool operator==(Tree other) {
            return data == other.data;
        }

        void remove(const T& toDelete) {
            assert(toDelete != "Uspeshnia");
            Tree& tree = search(toDelete);
            assert(tree.parent != nullptr);
            assert(tree.parent->children != nullptr);

            tree.parent->children->remove(&tree);

            if(tree.children != nullptr) {
                for(typename forward_list<Tree*>::iterator it = tree.children->begin(); it != tree.children->end(); ++it) {
                    (*it)->parent = tree.parent;
                    (*it)->setHeight((*it)->getHeight() - 1);
                }
                tree.parent->children->splice_after(tree.parent->children->cbefore_begin(), *tree.children);
            }

            tree.parent->increaseSize(-1);

            delete &tree;
        }

        string print() const {
            string output;
            for(Tree<T>::const_iterator it = cbegin(); it != cend(); ++it) {
                if(it->getParent() != nullptr) {
                    output.append(it->getParent()->getData());
                    output.append("-");
                    output.append(it->getData());
                    output.append("\n");
                }
            }

            return output;
        }

        bool operator<(Tree& other) {
            cout << "Operator called" << endl;
            return data < other.getData();
        }
        
        bool operator>(Tree& other) {
            return data > other.getData();
        }

        bool operator=(Tree& other) {
            return data == other.getData();
        }

        bool operator!=(Tree& other) {
            return data != other.getData();
        }
};