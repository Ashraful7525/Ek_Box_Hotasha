#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <set>
#include <random>
#include <iostream>
#include <string>
#include <queue>
#include <string>
#include <fstream>
using namespace std;
typedef long long LL;

ifstream fin("input.txt");
ofstream fout("output.txt");

struct node{
    int key, degree;
    node *parent, *child, *sibling;

    node(int k) : key(k), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
};

class Binomial_heap{
    node *head;

    void linktrees(node *y, node *z){ // y becomes child of z
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        ++z->degree;
    }

    node* mergerootlists(node *h1, node *h2){
        if(!h1) return h2;
        if(!h2) return h1;

        node *currhead = nullptr, *currtail = nullptr;

        while(h1 || h2){
            node *next;
            if(!h2 || (h1 && h1->degree <= h2->degree)){
                next = h1;
                h1 = h1->sibling;
            }
            else{
                next = h2;
                h2 = h2->sibling;
            }

            if(!currhead) currhead = currtail = next;
            else{
                currtail->sibling = next;
                currtail = next;
            }
        }

        return currhead;
    }

    void unionx(Binomial_heap &other){
        head = mergerootlists(head, other.head);
        other.head = nullptr;

        if(!head) return;

        node *prev = nullptr, *x = head, *next = x->sibling;

        while(next){
            bool duplicate = (x->degree == next->degree);
            bool triple = (next->sibling && next->sibling->degree == x->degree);

            if(!duplicate || triple){
                prev = x;
                x = next;
            }
            else if(x->key <= next->key){
                x->sibling = next->sibling;
                linktrees(next, x);
            }
            else{
                if(prev) prev->sibling = next;
                else head = next;

                linktrees(x, next);
                x = next;
            }

            next = x->sibling;
        }  
    }

    node* reverse(node *n){
        node *prev = nullptr;
        while(n){
            node *next = n->sibling;
            n->sibling = prev;
            n->parent = nullptr;
            prev = n;
            n = next;
        }

        return prev;
    }

public:

    Binomial_heap() : head(nullptr) {}
    explicit Binomial_heap(node *n) : head(n) {}

    bool empty() const { return head == nullptr; }

    node* insert(int key){
        node* newnode = new node(key);
        Binomial_heap tmp(newnode);

        unionx(tmp);
        return newnode;
    }

    node* minimum(){
        node *minroot = nullptr;
        int minkey = INT_MAX;

        for(node *r = head; r ; r = r->sibling){
            if(minkey > r->key){
                minkey = r->key;
                minroot = r;
            }
        }

        return minroot;
    }

    node* extractMin(){
        if(!head) return nullptr;
        node *prevmin = nullptr, *minroot = head;

        for(node *prev = nullptr, *cur = head; cur; prev = cur, cur = cur->sibling){
            if (cur->key < minroot->key){
                minroot = cur;
                prevmin = prev;
            }
        }

        if(prevmin) prevmin->sibling = minroot->sibling;
        else head = minroot->sibling;

        Binomial_heap tmp(reverse(minroot->child));
        unionx(tmp);

        return minroot;
    }

    void decreaseKey(node *x, int newkey){
        if(newkey > x->key) return;
        x->key = newkey;

        node* y = x;
        node* p = y->parent;
        while(p && y->key < p->key){
            swap(y->key, p->key);
            y = p;
            p = y->parent;
        }
    }

    void erase(node *x){
        decreaseKey(x, INT_MIN);
        node *m = extractMin();
        delete m;
    }

    void print(){
        fout <<"Printing Binomial Heap…"<<'\n';
        for (node *root = head; root; root = root->sibling) {
            fout<<"Binomial Tree, B"<<root->degree<<'\n';

            queue<pair<node*, int> > q;
            q.push(make_pair(root, 0));
            int currentLvl = 0;
            fout<<"Level 0: ";

            while (!q.empty()) {
                pair<node*, int> p = q.front(); q.pop();
                node *u = p.first;
                int lvl = p.second;

                if(lvl != currentLvl) {
                    fout<<'\n'<<"Level "<<lvl<<": ";
                    currentLvl = lvl;
                }
                fout<<u->key<<' ';

                for(node *c = u->child; c; c = c->sibling) q.push(make_pair(c, lvl + 1));
            }
            fout << '\n';
        }
    }
};


int main() {


    Binomial_heap heap;
    unordered_map<int, node*> locator;

    char op;
    while(fin >> op){
        if(op == 'I'){
            int k; fin>>k;

            node *n = heap.insert(k);
            locator[k] = n;
        }
        else if(op == 'F'){
            node *m = heap.minimum();
            if (m)  fout << "Find Min returned: " << m->key << '\n';
        }
        else if(op == 'E'){
            node *m = heap.extractMin();
            if (m) {
                fout << "Extract Min returned: " << m->key << '\n';
                locator.erase(m->key);
                delete m;
            }
        }
        else if(op == 'D'){
            int oldKey, newKey; fin >> oldKey >> newKey;
            auto it = locator.find(oldKey);
            if (it != locator.end()) {
                node *node = it->second;
                heap.decreaseKey(node, newKey);
                locator.erase(it);
                locator[newKey] = node;
            }
        }
        else if(op == 'R'){
            int key; fin >> key;
            auto it = locator.find(key);
            if (it != locator.end()) {
                heap.erase(it->second);
                locator.erase(it);
            }
        }
        else if(op == 'P'){
            heap.print();
        }
    }

    while (!heap.empty()) {
        node *m = heap.extractMin();
        delete m;
    }
    return 0;
}

