#pragma once
#include <forward_list>
#include <queue>
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

        class Iterator {
            friend class Tree;
            private:
                Tree* tree;
                queue<Tree*> bfsqueue;

                Iterator(Tree* tree): tree(tree) {}

                static bool sort_func(const Tree* t1, const Tree* t2)  {
                    return t1->getData() < t2->getData();
                }

            public:
                const Tree& operator*() const {
                    assert(tree != nullptr);
                    return *tree;
                }

                Tree& operator*() {
                    assert(tree != nullptr);
                    return *tree;
                }

                const Tree* operator->() const {
                    assert(tree != nullptr);
                    return tree;
                }

                Tree* operator->() {
                    assert(tree != nullptr);
                    return tree;
                }

                Iterator operator++() {
                    assert(tree != nullptr);
                    // This typename confuses me quite a bit
                    if(tree->children != nullptr) {
                        tree->children->sort(sort_func);
                        for(typename forward_list<Tree*>::iterator it = tree->children->begin(); it != tree->children->end(); ++it) {
                            bfsqueue.push(*it);
                        }
                    }
                    if(bfsqueue.empty()) {
                        tree = nullptr;
                    } else {
                        tree = bfsqueue.front();
                        bfsqueue.pop();
                    }
                    return *this;
                }

                Iterator operator++(int) {
                    Iterator res(*this);
                    ++(*this);
                    return res;
                }

                bool operator==(Iterator other) {
                    return other.tree == this->tree;
                }

                bool operator!=(Iterator other) {
                    return !(*this == other);
                }
        }; 

        class ConstIterator {
            friend class Tree;
            private:
                const Tree* tree;
                queue<Tree*> bfsqueue;

                ConstIterator(const Tree* tree): tree(tree) {}

                static bool sort_func(const Tree* t1, const Tree* t2)  {
                    return t1->getData() < t2->getData();
                }

            public:
                const Tree& operator*() const {
                    assert(tree != nullptr);
                    return *tree;
                }

                const Tree* operator->() const {
                    assert(tree != nullptr);
                    return tree;
                }

                ConstIterator operator++() {
                    assert(tree != nullptr);
                    // This typename confuses me quite a bit
                    if(tree->children != nullptr) {
                        tree->children->sort(sort_func);
                        for(typename forward_list<Tree*>::iterator it = tree->children->begin(); it != tree->children->end(); ++it) {
                            bfsqueue.push(*it);
                        }
                    }
                    if(bfsqueue.empty()) {
                        tree = nullptr;
                    } else {
                        tree = bfsqueue.front();
                        bfsqueue.pop();
                    }
                    return *this;
                }

                ConstIterator operator++(int) {
                    Iterator res(*this);
                    ++(*this);
                    return res;
                }

                bool operator==(ConstIterator other) {
                    return other.tree == this->tree;
                }

                bool operator!=(ConstIterator other) {
                    return !(*this == other);
                }
        };

    public:

        typedef Iterator iterator;
        typedef ConstIterator const_iterator;

        Tree(const T& data, Tree* parent): data(data), parent(parent), children(nullptr) {
            if(this->parent != nullptr) {
                this->height = this->parent->height + 1;
            }
        };

        void insertNode(const T& toInsert , const T& parent) {
            //TODO: Check if toInsert already exists
            Tree& tree_parent = search(parent);
            tree_parent.addChild(new Tree(toInsert, &tree_parent));

            tree_parent.increaseSize(1);
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
            return Iterator(this);
        }

        iterator end() {
            return Iterator(nullptr);
        }

        const_iterator cbegin() const {
            return ConstIterator(this);
        }

        const_iterator cend() const {
            return ConstIterator(nullptr);
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
                }
                tree.parent->children->splice_after(tree.parent->children->begin(), *tree.children);
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