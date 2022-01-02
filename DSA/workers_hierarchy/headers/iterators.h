#pragma once

template <class DataType>
class Iterator
{
    friend class Tree;

private:
    DataType *tree;
    queue<DataType *> bfsqueue;

    Iterator(DataType *tree) : tree(tree) {}

    static bool sort_func(const DataType *t1, const DataType *t2)
    {
        return t1->getData() < t2->getData();
    }

public:
    DataType &operator*() const
    {
        assert(tree != nullptr);
        return *tree;
    }

    DataType &operator*()
    {
        assert(tree != nullptr);
        return *tree;
    }

    const DataType *operator->() const
    {
        assert(tree != nullptr);
        return tree;
    }

    DataType *operator->()
    {
        assert(tree != nullptr);
        return tree;
    }

    Iterator operator++()
    {
        assert(tree != nullptr);
        if (tree->children != nullptr)
        {
            tree->children->sort(sort_func);
            for (typename forward_list<Tree *>::iterator it = tree->children->begin(); it != tree->children->end(); ++it)
            {
                bfsqueue.push(*it);
            }
        }
        if (bfsqueue.empty())
        {
            tree = nullptr;
        }
        else
        {
            tree = bfsqueue.front();
            bfsqueue.pop();
        }
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator res(*this);
        ++(*this);
        return res;
    }

    bool operator==(Iterator other)
    {
        return other.tree == this->tree;
    }

    bool operator!=(Iterator other)
    {
        return !(*this == other);
    }
};

template <class DataType>
class ReverseIterator
{
    friend class Tree;

private:
    DataType *tree;
    stack<DataType *> children_stack;
    queue<DataType *> bfsqueue;

    ReverseIterator(DataType *tree) {
        if(tree != nullptr) {
            bfsqueue.push(tree);
            children_stack.push(nullptr);
            children_stack.push(tree);
            while(!bfsqueue.empty()) {
                DataType* curr = bfsqueue.front();
                bfsqueue.pop();
                if(curr->children != nullptr) {
                    tree->children->sort(sort_func);
                    for (typename forward_list<Tree *>::iterator it = curr->children->begin(); it != curr->children->end(); ++it)
                    {
                        bfsqueue.push(*it);
                        children_stack.push(*it);
                    }
                }
            }
            this->tree = children_stack.top();
            children_stack.pop();
        } else {
            this->tree = nullptr;
        }
    }

    static bool sort_func(const DataType *t1, const DataType *t2)
    {
        return t1->getData() < t2->getData();
    }

public:
    DataType &operator*() const
    {
        assert(tree != nullptr);
        return *tree;
    }

    DataType &operator*()
    {
        assert(tree != nullptr);
        return *tree;
    }

    const DataType *operator->() const
    {
        assert(tree != nullptr);
        return tree;
    }

    DataType *operator->()
    {
        assert(tree != nullptr);
        return tree;
    }

    ReverseIterator operator++()
    {
        tree = children_stack.top();
        children_stack.pop();
        return *this;
    }

    ReverseIterator operator++(int)
    {
        ReverseIterator res(*this);
        ++(*this);
        return res;
    }

    bool operator==(ReverseIterator other)
    {
        return other.tree == this->tree;
    }

    bool operator!=(ReverseIterator other)
    {
        return !(*this == other);
    }
};