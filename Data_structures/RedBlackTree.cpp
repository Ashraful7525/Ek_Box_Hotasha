#include <vector>
#include <climits>
#include <algorithm>
#include <set>
#include <random>
#include <iostream>
#include <functional>
using namespace std;

enum Color{black, red};

template<typename Key, typename Value, typename Compare = std::less<Key>>
class RedBlackTree{
    struct Node{
        Key key;
        Value value;
        Color color;
        Node *left, *right, *parent;

        Node(const Key& k, const Value& v, Color c){
            this->key = k;
            this->value = v;
            this->color = c;
            left = right = parent = nullptr;
        }
    };

    Node *root;
    int sz;
    Compare comp;

    void leftrotate(Node* v){
        Node *r = v->right;
        v->right = r->left;
        if (r->left) r->left->parent = v;
        r->parent = v->parent;

        if(!v->parent) root = r;
        else if(v->parent->left == v) v->parent->left = r;
        else v->parent->right = r;

        r->left = v;
        v->parent = r;
    }

    void rightrotate(Node* v) {
        Node* l = v->left;
        v->left = l->right;
        if (l->right) l->right->parent = v;

        l->parent = v->parent;
        if (!v->parent) root = l;
        else if (v == v->parent->right) v->parent->right = l;
        else v->parent->left = l;

        l->right = v;
        v->parent = l;
    }

    void insert(Node *newnode){
        Node *curr =  root, *abba = nullptr;

        while(curr){
            abba = curr;
            if(comp(newnode->key, curr->key)) curr = curr->left;
            else curr = curr->right;
        }

        newnode->parent = abba;
        if(!abba) root = newnode;
        else if(comp(newnode->key, abba->key)) abba->left = newnode;
        else abba->right = newnode;

        sz++;
        insertfixup(newnode);
    }

    void insertfixup(Node *v){
        while(v->parent && v->parent->color == red){
            Node *gp = v->parent->parent;
            if(!gp) break;
            if(v->parent == gp->left){
                if(gp->right && gp->right->color == red){
                    gp->color = red;
                    v->parent->color = black;
                    gp->right->color = black;
                    v = gp;
                }
                else{
                    if(gp->left->right == v){
                        v = v->parent;
                        leftrotate(v);
                    }

                    gp->color = red;
                    v->parent->color = black;
                    rightrotate(gp);
                }
            }
            else{
                if(gp->left && gp->left->color == red){
                    gp->color = red;
                    v->parent->color = black;
                    gp->left->color = black;
                    v = gp;
                }
                else{
                    if(gp->right->left == v){
                        v = v->parent;
                        rightrotate(v);
                    }

                    gp->color = red;
                    v->parent->color = black;
                    leftrotate(gp);
                }
            }
        }

        root->color = black;
    }

    void transplant(Node *u, Node *v){
        if(!u->parent) root = v;
        else if(u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;

        if(v) v->parent = u->parent; 
    }

    void erase(Node *u){
        if(!u) return;

        Color c = u->color;
        Node *x;
        Node *fixupParent = nullptr;

        if(!u->left){
            x = u->right;
            fixupParent = u->parent;
            transplant(u, x);
        }
        else if(!u->right){
            x = u->left;
            fixupParent = u->parent;
            transplant(u, x);
        }
        else{
            Node *y = u->right;
            while(y->left) y = y->left;

            c = y->color;
            x = y->right;

            fixupParent = y->parent;

            transplant(y, y->right);
            
            y->right = u->right;
            if (u->right) u->right->parent = y;

            transplant(u, y);

            y->left = u->left;
            if (u->left) u->left->parent = y;
            
            y->color = u->color;
        }

        delete u;
        sz--;

        if(c == black){
            deletefixup(x, fixupParent);
        }
    }

    void deletefixup(Node *v, Node *p){
        while(v != root && ( !v || v->color == black)){
            p = v ? v->parent : nullptr;
            if (!p) break; 
            if(v == p->left){
                Node *w = p->right;

                if(w && w->color == red){
                    w->color = black;
                    p->color = red;
                    leftrotate(p);

                    w = p->right;
                }

                if((!w || !w->left  || w->left->color  == black) && (!w || !w->right || w->right->color == black)){
                    if(w) w->color = red;
                    v = p;
                    p = v->parent;
                }
                else{
                    if(!w->right || w->right->color == black){
                        if(w->left) w->left->color = black;
                        w->color = red;
                        rightrotate(w);
                        w = p->right;
                    }

                    if(w) w->color = p->color;
                    p->color = black;
                    if(w && w->right) w->right->color = black;
                    leftrotate(p);
                    v = root;

                }
            }
            else{
                Node *w = p->left;
                if(w && w->color == red){
                    w->color = black;
                    p->color = red;
                    rightrotate(p);

                    w = p->left;
                }

                if((!w || !w->right  || w->right->color  == black) && (!w || !w->left || w->left->color == black)){
                    if(w) w->color = red;
                    v = p;
                    p = v->parent;
                }
                else{
                    if(!w->left || w->left->color == black){
                        if(w->right) w->right->color = black;
                        w->color = red;
                        leftrotate(w);
                        w = p->left;
                    }

                    if(w) w->color = p->color;
                    p->color = black;
                    if(w && w->left) w->left->color = black;
                    rightrotate(p);
                    v = root;
                }
            }

            if(v != root) p = v ? v->parent : p;
        }

        if(v) v->color = black;
    }

    void inorderhelper(Node *v, function<void(const Key&, const Value&)> visit){
        if(!v) return; 
        inorderhelper(v->left, visit);
        visit(v->key, v->value);
        inorderhelper(v->right, visit);
    }

    void printgraph(Node* v, ostream& out = cout){
        if (!v) return;
        if (v->color == red) {
            out<<"\033[31m"<<v->key<<"\033[0m";
        }
        else out << v->key;

        if (v->left || v->right) {
            out << '(';
            if (v->left)  printgraph(v->left, out);
            out << ',';
            if (v->right) printgraph(v->right, out);
            out << ')';
        }
    }

    Node* find(const Key& key){
        Node *curr = root;
        while(curr){
            if(comp(key, curr->key)) curr = curr->left;
            else if(comp(curr->key, key)) curr = curr->right;
            else return curr;
        }
        return nullptr;
    }

    void clearhelper(Node *v){
        if(!v) return;
        clearhelper(v->left);
        clearhelper(v->right);
        delete v;
    }

    int depthhelper(Node *v){
        if(!v) return 0;
        int leftDepth = depthhelper(v->left);
        int rightDepth = depthhelper(v->right);
        return 1 + max(leftDepth, rightDepth);
    }

public:
    RedBlackTree(const Compare& c = Compare()){
        sz = 0;
        root = nullptr;
        comp = c;
    }

    ~RedBlackTree(){
        clear();
    }

    // Insert key-value pair
    void insert(const Key& key, const Value& value){
        Node *v = find(key);
        if(v){
            v->value = value;  // Update existing value
        }
        else{
            v = new Node(key, value, red);
            insert(v);
        }
    }

    // Erase by key
    bool erase(const Key& key){
        Node* node = find(key);
        if(!node) return false;
        erase(node);
        return true;
    }

    // Find value by key
    Value* findValue(const Key& key){
        Node* node = find(key);
        return node ? &(node->value) : nullptr;
    }

    // Check if key exists
    bool contains(const Key& key){
        return find(key) != nullptr;
    }

    // Print tree structure
    void printTree(ostream& out = cout){
        printgraph(root, out);
        out << "\n";
    }

    // Clear all elements
    void clear(){
        if(!root) return;
        clearhelper(root);
        root = nullptr;
        sz = 0;
    }

    // Get size
    int size(){
        return sz;
    }

    // Check if empty
    bool empty(){
        return sz == 0;
    }

    // Traverse in order
    void inorder(function<void(const Key&, const Value&)> visit){
        inorderhelper(root, visit);
    }

    // Get maximum depth of tree
    int depth(){
        return depthhelper(root);
    }
};