#pragma once
#include <forward_list>
#include <stack>

using namespace std;

template <class T>
class Tree {
    private:
        T* data;
        int height;
        int size;

        Tree* parent;
        forward_list<Tree*>* children;

        class Iterator {
            friend class Tree;
            private:
                Tree* tree;
                stack<Tree*> dfsstack;

                Iterator(Tree& tree): tree(tree) {}

            public:
                const T& operator*() const {
                    return tree->data;
                }

                T& operator*() {
                    return tree->data;
                }

                const T* operator->() const {
                    return tree->data;
                }

                T* operator->() {
                    return tree->data;
                }

                Iterator& operator++() {
                    // This typename confuses me quite a bit
                    for(typename forward_list<Tree*>::iterator it = tree->children.begin(); it != tree->children.end(); ++it) {
                        dfsstack.push(*it);
                    }
                    if(dfsstack.empty()) {
                        return nullptr;
                    } else {
                        tree = dfsstack.pop();
                        return this;
                    }
                }

                Iterator operator++(int) {
                    Iterator res(*this);
                    ++(*this);
                    return res;
                }
        };

    public:

        Tree(T& root) {
            this->data = root;
        };

        void insert(const T& toInsert , const T& parent);
        const Tree& search(const T& toFind);

        int children_count();
        const Tree& get_parent();

        Iterator begin() const {
            return Iterator(&data);
        }

        Iterator end() const {
            return Iterator(nullptr);
        }
};