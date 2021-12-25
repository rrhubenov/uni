#pragma once
#include <forward_list>
#include <stack>
#include <iostream>

using namespace std;

template <class T>
class Tree {
    private:
        const T data;

        forward_list<Tree*>* children;

        class Iterator {
            friend class Tree;
            private:
                Tree* tree;
                stack<Tree*> dfsstack;

                Iterator(Tree* tree): tree(tree) {}

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
                        for(typename forward_list<Tree*>::iterator it = tree->children->begin(); it != tree->children->end(); ++it) {
                            dfsstack.push(*it);
                        }
                    }
                    if(dfsstack.empty()) {
                        tree = nullptr;
                    } else {
                        tree = dfsstack.top();
                        dfsstack.pop();
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

    public:

        Tree(const T& data): data(data), children(nullptr) {};

        void insertNode(const T& toInsert , const T& parent) {
            //TODO: Check if toInsert already exists
            Tree& tree_parent = search(parent);
            tree_parent.addChild(new Tree(toInsert));
        }

        Tree& search(const T& toFind) {
            for(Tree<T>::Iterator it = begin(); it != end(); ++it) {
                if(it->getData() == toFind) {
                    return *it;
                }
            }

            throw runtime_error("Element not found");
        }

        int children_count() {
            int count;

            if(children == nullptr) {
                count = 0;
            } else {
                for(typename forward_list<T>::iterator it = children->begin(); it != children->end; ++it) {
                    count++;
                }
            }

            return count;
        }

        Iterator begin() {
            return Iterator(this);
        }

        Iterator end() {
            return Iterator(nullptr);
        }

        void addChild(Tree* tree) {
            if(children == nullptr) {
                children = new forward_list<Tree*>;
            }
            children->push_front(tree);
        }

        const T& getData() {
            return data;
        }

        bool operator==(Tree other) {
            return data == other.data;
        }

        void print() {
            for(Tree<T>::Iterator it = begin(); it != end(); ++it) {
                cout << it->getData() << endl;
            }
        }
};