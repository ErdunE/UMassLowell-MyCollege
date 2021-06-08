template <class T> class BSTree;

template <class T>
class BSTNode{
    friend class BSTree<T>;

private:
    T value;
    BSTNode<T>* left;
    BSTNode<T>* right;

public:
    explicit BSTNode(T value) {
        this->value = value;
        left = right = nullptr;
    }

};


template <class T>
class BSTree {
private:
    BSTNode<T>* root;
    void clear(BSTNode<T>* rt);
public:
    explicit BSTree() {
        root = nullptr;
    }

    ~BSTree() {
        clear(root);
    }

    void add(T ele) {
        BSTNode<T>* cur, *parent;
        cur = parent = nullptr;
        if(root == nullptr) {
            root = new BSTNode<T>(ele);
            return;
        }

        cur = parent = root;
        while(cur) {
            if(ele < cur->value) {
                parent = cur;
                cur = cur->left;
            } else if(ele > cur->value) {
                parent = cur;
                cur = cur->right;
            } else {
                return;
            }
        }

        cur = new BSTNode<T>(ele);
        if(ele < parent->value) {
            parent->left = cur;
        } else {
            parent->right = cur;
        }
    }

    bool remove(T ele) {
        BSTNode<T>* cur,*parent;
        if (root == nullptr) {
            return false;
        }
        parent = cur = root;
        while(cur) {
            if(ele < cur->value) {
                parent = cur;
                cur = cur->left;
            } else if (ele > cur->value) {
                parent = cur;
                cur = cur->right;
            } else {
                break;
            }
        }

        if(cur) {
            BSTNode<T>* del = cur;
            if (cur->left == nullptr && cur->right == nullptr) {
                if (root == cur)
                    root = nullptr;
                if(parent->left == cur)
                    parent->left = nullptr;
                else
                    parent->right = nullptr;
                delete cur;
            } else if(!cur->left || !cur->right) {
                if (cur == root) {
                    if(cur->left) {
                        root = root->left;
                    } else {
                        root = root->right;
                    }
                } else {
                    if(parent->left == cur) {
                        if(cur->left) {
                            parent->left = cur->left;
                        } else {
                            parent->left = cur->right;
                        }
                    } else {
                        if (cur->left) {
                            parent->right = cur->left;
                        } else {
                            parent->right = cur->right;
                        }
                    }

                }
                delete cur;
            } else {
                parent = cur;
                del = cur->right;
                while(del->left)
                {
                    parent = del;
                    del = del->left;
                }
                cur->value = del->value;
                if(parent == cur)
                    parent->right = del->right;
                else
                    parent->left = del->right;
                delete del;
            }
            return true;
        }
        return false;
    }

    bool search(T ele) {
        BSTNode<T>* node = root;
        while(node) {
            if(ele < node->value)
                node = node->left;
            else if(ele > node->value)
                node = node->right;
            else
                return true;
        }
        return false;
    }

};

template<class T>
void BSTree<T>::clear(BSTNode<T> *rt) {
    if (rt == nullptr) {
        return;
    }
    clear(rt->left);
    clear(rt->right);
    delete rt;
}
