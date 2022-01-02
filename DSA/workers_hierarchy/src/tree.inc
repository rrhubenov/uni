
template <class T>
Tree<T>::Tree(const T &data, Tree *parent) : data(data), parent(parent), children(nullptr)
{
    if (this->parent != nullptr)
    {
        this->height = this->parent->height + 1;
    }
};

template <class T>
Tree<T>::Tree(const Tree<T> &r) : data(r.getData()), parent(nullptr), children(nullptr)
{
    Tree<T>::const_iterator it = r.cbegin();
    ++it;
    for (; it != r.cend(); ++it)
    {
        this->insertNode(it->getData(), it->getParent()->getData());
    }
}

template <class T>
Tree<T>::Tree(Tree &&r) noexcept : data(r.data), size(r.size), height(r.height)
{
    parent = r.parent;
    children = r.children;

    if (children != nullptr)
    {
        for (typename forward_list<Tree *>::iterator it = children->begin(); it != children->end(); ++it)
        {
            (*it)->parent = this;
        }
    }

    r.children = nullptr;
    r.parent = nullptr;
    r.size = 1;
    r.height = 1;
}

template <class T>
Tree<T>::~Tree()
{
    if (children != nullptr)
    {
        for (typename forward_list<Tree *>::iterator it = children->begin(); it != children->end(); ++it)
        {
            delete (*it);
        }
    }
}

template <class T>
Tree<T> &Tree<T>::search(const T &toFind)
{
    for (Tree<T>::iterator it = begin(); it != end(); ++it)
    {
        if (it->getData() == toFind)
        {
            return *it;
        }
    }

    throw runtime_error("Element not found");
}

template <class T>
void Tree<T>::insertNode(const T &toInsert, const T &parent)
{
    //TODO: A lot of refactoring is needed
    //TODO: If parent does not exists, throw error
    try
    {
        Tree &already_exists = search(toInsert);

        assert(already_exists.parent != nullptr);
        assert(already_exists.parent->children != nullptr);

        already_exists.parent->children->remove(&already_exists);
        already_exists.parent->increaseSize(-1);

        Tree &new_parent = search(parent);
        new_parent.addChild(&already_exists);
        new_parent.increaseSize(1);
        already_exists.parent = &new_parent;
        already_exists.setHeight(new_parent.getHeight() + 1);
    }
    catch (runtime_error e)
    {
        if (strcmp(e.what(), "Element not found") == 0)
        {
            Tree &tree_parent = search(parent);
            tree_parent.addChild(new Tree(toInsert, &tree_parent));
            tree_parent.increaseSize(1);
        }
        else
        {
            throw e;
        }
    }
}

template <class T>
const Tree<T> &Tree<T>::search(const T &toFind) const
{
    for (Tree<T>::const_iterator it = cbegin(); it != cend(); ++it)
    {
        if (it->getData() == toFind)
        {
            return *it;
        }
    }

    throw runtime_error("Element not found");
}

template <class T>
int Tree<T>::children_count() const
{
    int count = 0;

    if (children != nullptr)
    {
        for (typename forward_list<Tree *>::iterator it = children->begin(); it != children->end(); ++it)
        {
            count++;
        }
    }

    return count;
}

template <class T>
const T &Tree<T>::getData()
{
    return data;
}

template <class T>
const T &Tree<T>::getData() const
{
    return data;
}

template <class T>
const unsigned Tree<T>::getSize() const
{
    return size;
}

template <class T>
const unsigned Tree<T>::getSize()
{
    return size;
}

template <class T>
const unsigned Tree<T>::getHeight() const
{
    return height;
}

template <class T>
const unsigned Tree<T>::getHeight()
{
    return height;
}

template <class T>
const Tree<T> *Tree<T>::getParent() const
{
    return this->parent;
}

template <class T>
forward_list<Tree<T> *> *Tree<T>::getChildren() const
{
    return this->children;
}

template <class T>
bool Tree<T>::operator==(Tree other)
{
    return data == other.data;
}

template <class T>
void Tree<T>::remove(const T &toDelete)
{
    assert(toDelete != "Uspeshnia");
    Tree &tree = search(toDelete);
    assert(tree.parent != nullptr);
    assert(tree.parent->children != nullptr);

    tree.parent->children->remove(&tree);

    if (tree.children != nullptr)
    {
        for (typename forward_list<Tree *>::iterator it = tree.children->begin(); it != tree.children->end(); ++it)
        {
            (*it)->parent = tree.parent;
            (*it)->setHeight((*it)->getHeight() - 1);
        }
        tree.parent->children->splice_after(tree.parent->children->cbefore_begin(), *tree.children);
    }

    tree.parent->increaseSize(-1);

    delete &tree;
}

template <class T>
string Tree<T>::print() const
{
    string output;
    for (Tree<T>::const_iterator it = cbegin(); it != cend(); ++it)
    {
        if (it->getParent() != nullptr)
        {
            output.append(it->getParent()->getData());
            output.append("-");
            output.append(it->getData());
            output.append("\n");
        }
    }

    return output;
}

template <class T>
bool Tree<T>::operator<(Tree &other)
{
    cout << "Operator called" << endl;
    return data < other.getData();
}

template <class T>
bool Tree<T>::operator>(Tree &other)
{
    return data > other.getData();
}

template <class T>
bool Tree<T>::operator=(Tree &other)
{
    return data == other.getData();
}

template <class T>
bool Tree<T>::operator!=(Tree &other)
{
    return data != other.getData();
}

template <class T>
void Tree<T>::addChild(Tree *tree)
{
    if (children == nullptr)
    {
        children = new forward_list<Tree *>;
    }
    children->push_front(tree);
}

template <class T>
void Tree<T>::increaseSize(unsigned value)
{
    size += value;
    Tree *next_parent = parent;
    while (next_parent != nullptr)
    {
        next_parent->size += value;
        next_parent = next_parent->parent;
    }
}

template <class T>
void Tree<T>::setHeight(unsigned value)
{
    this->height = value;
    if (children != nullptr)
    {
        for (typename forward_list<Tree *>::iterator it = children->begin(); it != children->end(); ++it)
        {
            (*it)->setHeight(value + 1);
        }
    }
}