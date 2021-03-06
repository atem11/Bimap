//
// Created by artem on 28.04.18.
//

#ifndef BIGINT_BIMAP_H
#define BIGINT_BIMAP_H

#include <iostream>

template<typename LT, typename RT>
struct base_node {
    base_node *left_left;
    base_node *left_right;
    base_node *left_parent;
    base_node *right_left;
    base_node *right_right;
    base_node *right_parent;

    base_node() : left_left(nullptr),
                  left_right(nullptr),
                  left_parent(nullptr),
                  right_left(nullptr),
                  right_right(nullptr),
                  right_parent(nullptr) {}

    friend base_node *nextLeft_node(base_node *_root) {
        if (_root->left_right == nullptr) {
            while (_root->left_parent != nullptr && _root->left_parent->left_right == _root) {
                _root = _root->left_parent;
            }
            _root = _root->left_parent;
            return _root;
        }
        _root = _root->left_right;
        while (_root->left_left != nullptr) {
            _root = _root->left_left;
        }
        return _root;
    }

    friend base_node *prevLeft_node(base_node *_root) {
        if (_root->left_left == nullptr) {
            while (_root->left_parent != nullptr && _root->left_parent->left_left == _root) {
                _root = _root->left_parent;
            }
            if (_root->left_parent == nullptr) {
                return nullptr;
            }
            _root = _root->left_parent;
            return _root;
        }
        _root = _root->left_left;
        while (_root->left_right != nullptr) {
            _root = _root->left_right;
        }
        return _root;
    }

    friend base_node *nextRight_node(base_node *_root) {
        if (_root->right_right == nullptr) {
            while (_root->right_parent != nullptr && _root->right_parent->right_right == _root) {
                _root = _root->right_parent;
            }
            _root = _root->right_parent;
            return _root;
        }
        _root = _root->right_right;
        while (_root->right_left != nullptr) {
            _root = _root->right_left;
        }
        return _root;
    }

    friend base_node *prevRight_node(base_node *_root) {
        if (_root->right_left == nullptr) {
            while (_root->right_parent != nullptr && _root->right_parent->right_left == _root) {
                _root = _root->right_parent;
            }
            if (_root->right_parent == nullptr) {
                return nullptr;
            }
            _root = _root->right_parent;
            return _root;
        }
        _root = _root->right_left;
        while (_root->right_right != nullptr) {
            _root = _root->right_right;
        }
        return _root;
    }
};

template<typename LT, typename RT>
struct node : public base_node<LT, RT> {

    typedef LT left_t;
    typedef RT right_t;

    left_t left_data;
    right_t right_data;

    node(left_t left, right_t right) : base_node<left_t, right_t>(),
                                       left_data(left),
                                       right_data(right) {}

};

template<typename LT, typename RT>
struct tree {
    typedef LT left_t;
    typedef RT right_t;

    base_node<left_t, right_t> *root;

    tree() : root(new base_node<left_t, right_t>()) {}

    ~tree() {
        delete root;
    }

    void insert_left(node<left_t, right_t> *&elem) {
        if (root->left_left == nullptr) {
            root->left_left = elem;
            elem->left_parent = root;

        }
        node<left_t, right_t> *tmp = static_cast<node<left_t, right_t> * >(root->left_left);
        left_t eval = elem->left_data;
        while (tmp != nullptr) {
            left_t val = tmp->left_data;
            if (eval > val) {
                if (tmp->left_right == nullptr) {
                    tmp->left_right = elem;
                    elem->left_parent = tmp;
                    return;
                }
                tmp = static_cast<node<left_t, right_t> * >(tmp->left_right);
            } else {
                if (tmp->left_left == nullptr) {
                    tmp->left_left = elem;
                    elem->left_parent = tmp;
                    return;
                }
                tmp = static_cast<node<left_t, right_t> * >(tmp->left_left);
            }
        }
    }

    void insert_right(node<left_t, right_t> *&elem) {
        if (root->right_left == nullptr) {
            root->right_left = elem;
            elem->right_parent = root;

        }
        node<left_t, right_t> *tmp = static_cast<node<left_t, right_t> * >(root->right_left);
        right_t eval = elem->right_data;
        while (tmp != nullptr) {
            right_t val = tmp->right_data;
            if (eval > val) {
                if (tmp->right_right == nullptr) {
                    tmp->right_right = elem;
                    elem->right_parent = tmp;
                    return;
                }
                tmp = static_cast<node<left_t, right_t> * >(tmp->right_right);
            } else {
                if (tmp->right_left == nullptr) {
                    tmp->right_left = elem;
                    elem->right_parent = tmp;
                    return;
                }
                tmp = static_cast<node<left_t, right_t> * >(tmp->right_left);
            }
        }
    }

    node<left_t, right_t> *find_left(node<left_t, right_t> *_ptr, left_t const &val) {
        if (_ptr == nullptr || val == _ptr->left_data) {
            return _ptr;
        }
        if (val > _ptr->left_data) {
            return find_left(static_cast<node<left_t, right_t> * >(_ptr->left_right), val);
        }
        return find_left(static_cast<node<left_t, right_t> * >(_ptr->left_left), val);
    }

    node<left_t, right_t> *find_right(node<left_t, right_t> *_ptr, right_t const &val) {
        if (_ptr == nullptr || val == _ptr->right_data) {
            return _ptr;
        }
        if (val > _ptr->right_data) {
            return find_right(static_cast<node<left_t, right_t> * >(_ptr->right_right), val);
        }
        return find_right(static_cast<node<left_t, right_t> * >(_ptr->right_left), val);
    }

    node<left_t, right_t> *insert(left_t const &valL, right_t const &valR) {
        if (root->left_left == nullptr) {
            node<left_t, right_t> *tmp = new node<left_t, right_t>(valL, valR);
            root->left_left = tmp;
            root->right_left = tmp;
            tmp->left_parent = root;
            tmp->right_parent = root;
            return tmp;
        }
        if (find_left(static_cast<node<left_t, right_t> * >(root->left_left), valL) != nullptr ||
            find_right(static_cast<node<left_t, right_t> * >(root->right_left), valR) != nullptr) {
            return static_cast<node<left_t, right_t> * >(root);
        }
        node<left_t, right_t> *tmp = new node<left_t, right_t>(valL, valR);
        insert_left(tmp);
        insert_right(tmp);
        return tmp;
    }

    void eraseNode_left(base_node<left_t, right_t> *&_ptr) {
        if (_ptr->left_left != nullptr && _ptr->left_right != nullptr) {
            base_node<left_t, right_t> *tmp = _ptr->left_right;
            while (tmp->left_left != nullptr) {
                tmp = tmp->left_left;
            }
            if (tmp->left_parent != _ptr) {
                tmp->left_parent->left_left = tmp->left_right;
                if (tmp->left_right != nullptr) {
                    tmp->left_right->left_parent = tmp->left_parent;
                }
                tmp->left_parent = _ptr->left_parent;
                tmp->left_right = _ptr->left_right;
            } else {
                tmp->left_parent = _ptr->left_parent;
            }
            tmp->left_left = _ptr->left_left;
            if (tmp->left_right != nullptr) {
                tmp->left_right->left_parent = tmp;
            }
            if (tmp->left_left != nullptr) {
                tmp->left_left->left_parent = tmp;
            }
            if (_ptr == _ptr->left_parent->left_left) {
                _ptr->left_parent->left_left = tmp;
            } else {
                _ptr->left_parent->left_right = tmp;
            }
        } else if (_ptr->left_right != nullptr) {
            base_node<left_t, right_t> *tmp = _ptr->left_right;
            tmp->left_parent = _ptr->left_parent;
            if (_ptr == _ptr->left_parent->left_left) {
                _ptr->left_parent->left_left = tmp;
            } else {
                _ptr->left_parent->left_right = tmp;
            }
        } else if (_ptr->left_left != nullptr) {
            base_node<left_t, right_t> *tmp = _ptr->left_left;
            tmp->left_parent = _ptr->left_parent;
            if (_ptr == _ptr->left_parent->left_left) {
                _ptr->left_parent->left_left = tmp;
            } else {
                _ptr->left_parent->left_right = tmp;
            }
        } else {
            if (_ptr == _ptr->left_parent->left_left) {
                _ptr->left_parent->left_left = nullptr;
            } else {
                _ptr->left_parent->left_right = nullptr;
            }
        }
        _ptr->left_parent = nullptr;
        _ptr->left_left = nullptr;
        _ptr->left_right = nullptr;
    }

    void eraseNode_right(base_node<left_t, right_t> *&_ptr) {
        if (_ptr->right_left != nullptr && _ptr->right_right != nullptr) {
            base_node<left_t, right_t> *tmp = _ptr->right_right;
            while (tmp->right_left != nullptr) {
                tmp = tmp->right_left;
            }
            if (tmp->right_parent != _ptr) {
                tmp->right_parent->right_left = tmp->right_right;
                if (tmp->right_right != nullptr) {
                    tmp->right_right->right_parent = tmp->right_parent;
                }
                tmp->right_parent = _ptr->right_parent;
                tmp->right_right = _ptr->right_right;
            } else {
                tmp->right_parent = _ptr->right_parent;
            }
            tmp->right_left = _ptr->right_left;
            if (tmp->right_right != nullptr) {
                tmp->right_right->right_parent = tmp;
            }
            if (tmp->right_left != nullptr) {
                tmp->right_left->right_parent = tmp;
            }
            if (_ptr == _ptr->right_parent->right_left) {
                _ptr->right_parent->right_left = tmp;
            } else {
                _ptr->right_parent->right_right = tmp;
            }
        } else if (_ptr->right_right != nullptr) {
            base_node<left_t, right_t> *tmp = _ptr->right_right;
            tmp->right_parent = _ptr->right_parent;
            if (_ptr == _ptr->right_parent->right_left) {
                _ptr->right_parent->right_left = tmp;
            } else {
                _ptr->right_parent->right_right = tmp;
            }
        } else if (_ptr->right_left != nullptr) {
            base_node<left_t, right_t> *tmp = _ptr->right_left;
            tmp->right_parent = _ptr->right_parent;
            if (_ptr == _ptr->right_parent->right_left) {
                _ptr->right_parent->right_left = tmp;
            } else {
                _ptr->right_parent->right_right = tmp;
            }
        } else {
            if (_ptr == _ptr->right_parent->right_left) {
                _ptr->right_parent->right_left = nullptr;
            } else {
                _ptr->right_parent->right_right = nullptr;
            }
        }
        _ptr->right_parent = nullptr;
        _ptr->right_left = nullptr;
        _ptr->right_right = nullptr;
    }

    void erase(base_node<left_t, right_t>* _ptr) {
        eraseNode_left(_ptr);
        eraseNode_right(_ptr);
        delete(static_cast<node<left_t, right_t>*>(_ptr));
    }
};

template<typename LT, typename RT>
struct bimap {
    typedef LT left_t;
    typedef RT right_t;
private:
    /*data*/

    tree<left_t, right_t> *_tree;

    /*//////////////*/

    /*private func*/



    /*/////////////*/
public:
    /*iterators*/

    struct left_iterator;
    struct right_iterator;

    struct left_iterator {
        typedef std::ptrdiff_t difference_type;
        typedef left_t value_type;
        typedef left_t *pointer;
        typedef left_t &reference;
        typedef std::bidirectional_iterator_tag iterator_category;
        base_node<left_t, right_t> *ptr;

        left_iterator() {}

        left_iterator(base_node<left_t, right_t> *_ptr) : ptr(_ptr) {}

        left_iterator &operator=(left_iterator const &other) {
            ptr = other.ptr;
            return *this;
        }

        left_t const &operator*() const {
            return static_cast<node<left_t, right_t> *>(ptr)->left_data;
        }

        left_iterator &operator++() {
            ptr = nextLeft_node(ptr);
            return *this;
        }

        left_iterator operator++(int) {
            left_iterator copy(*this);
            ++(*this);
            return copy;
        }

        left_iterator &operator--() {
            ptr = prevLeft_node(ptr);
            return *this;
        }

        left_iterator operator--(int) {
            left_iterator copy(*this);
            --(*this);
            return copy;
        }

        right_iterator flip() const {
            return right_iterator(ptr);
        }

        friend bool operator==(left_iterator const &l, left_iterator const &r) {
            return l.ptr == r.ptr;
        }

        friend bool operator!=(left_iterator const &l, left_iterator const &r) {
            return l.ptr != r.ptr;
        }
    };

    struct right_iterator {
        typedef std::ptrdiff_t difference_type;
        typedef right_t value_type;
        typedef right_t *pointer;
        typedef right_t &reference;
        typedef std::bidirectional_iterator_tag iterator_category;
        base_node<left_t, right_t> *ptr;

        right_iterator() {}

        right_iterator(base_node<left_t, right_t> *_ptr) : ptr(_ptr) {}

        right_iterator &operator=(right_iterator const &other) {
            ptr = other.ptr;
            return *this;
        }

        right_t const &operator*() const {
            return static_cast<node<left_t, right_t> *>(ptr)->right_data;
        }

        right_iterator &operator++() {
            ptr = nextRight_node(ptr);
            return *this;
        }

        right_iterator operator++(int) {
            right_iterator copy(*this);
            ++(*this);
            return copy;
        }

        right_iterator &operator--() {
            ptr = prevRight_node(ptr);
            return *this;
        }

        right_iterator operator--(int) {
            right_iterator copy(*this);
            --(*this);
            return copy;
        }

        left_iterator flip() const {
            return left_iterator(ptr);
        }

        friend bool operator==(right_iterator const &l, right_iterator const &r) {
            return l.ptr == r.ptr;
        }

        friend bool operator!=(right_iterator const &l, right_iterator const &r) {
            return l.ptr != r.ptr;
        }
    };

    /*////////////*/

    /*public func*/
    bimap() : _tree(new tree<left_t, right_t>()) {}

    bimap(bimap const &) = delete;

    bimap &operator=(bimap const &) = delete;

    ~bimap() {
        while (begin_left() != end_left()) {
            erase(begin_left());
        }
        delete(_tree);
    }

    left_iterator insert(left_t const &left, right_t const &right) {
        left_iterator a = left_iterator(_tree->insert(left, right));
        /*_tree->print_l(static_cast<node<left_t, right_t>* >(_tree->root->left_left));
        std::cout << '\n';*/
        return a;
    }

    void erase(left_iterator it) {
        _tree->erase(it.ptr);
    }

    void erase(right_iterator it) {
        _tree->erase(it.ptr);
    }

    left_iterator find_left(left_t const &left) const {
        node<left_t, right_t>* ans = _tree->find_left(static_cast<node<left_t, right_t>*>(_tree->root->left_left), left);
        if (ans == nullptr) {
            return left_iterator(_tree->root);
        }
        return left_iterator(static_cast<base_node<left_t, right_t>*>(ans));
    }

    right_iterator find_right(right_t const &right) const {
        node<left_t, right_t>* ans = _tree->find_right(static_cast<node<left_t, right_t>*>(_tree->root->right_left), right);
        if (ans == nullptr) {
            return right_iterator(_tree->root);
        }
        return right_iterator(static_cast<base_node<left_t, right_t>*>(ans));
    }

    left_iterator begin_left() const {
        base_node<left_t, right_t>* ans = _tree->root;
        while (ans->left_left != nullptr) {
            ans = ans->left_left;
        }
        return left_iterator(ans);
    }

    left_iterator end_left() const {
        return left_iterator(_tree->root);
    }

    right_iterator begin_right() const{
        base_node<left_t, right_t>* ans = _tree->root;
        while (ans->right_left != nullptr) {
            ans = ans->right_left;
        }
        return right_iterator(ans);
    }

    right_iterator end_right() const {
        return right_iterator(_tree->root);
    }
};

#endif //BIGINT_BIMAP_H
