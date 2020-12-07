#ifndef CMPE126S20_LABS_TREE_H
#define CMPE126S20_LABS_TREE_H
#include "node.h"
#include <iostream>
#include <vector>

namespace lab8 {
    class tree {
        node *root;
        int tree_size;
    public:
        tree();
        tree(const tree& copy);     //Recursivelyyyyyyyyyyyyyyyyy
        ~tree();                    //Recursivelyyyyyyyyyyyyyyyyy

        void insert(int value);     //Recursivelyyyyyyyyyyyyyyyy
        bool remove(int key);
        bool in_tree(int key);      //Recursivelyyyyyyyyyyyyyyyyyy
        int get_frequency(int key); //Recursivelyyyyyyyyyyyyyyyy

        std::string to_string();    //Recursivelyyyyyyyyyyyyyyy
        int level(int key);         //Recursivelyyyyyyyyyyyyyy
        void path_to(int key);      //Recursivelyyyyyyyyyyyyyyyyy
        unsigned size();
        unsigned depth();           //Recursivelyyyyyyyyyyyyyyyyy
        void print();               //Recursivelyyyyyyyyyyyyyyyyy

        tree& operator=(tree rhs);   //Recursively
        friend std::ostream& operator<<(std::ostream& stream, tree& RHS); //Recursivelyyyyyyyyyyyyyyyy

        // Extra credit
        std::vector<int> values_above(int key); //Recursivelyyyyyyyyyyyyyyyyy
        tree operator+(const tree &rhs) const;  //Recursivelyyyyyyyyyyyyyyyyyyy
        void balance();

        // Example recursionyyyyyyyyyyyy
        void print_gtl();
    };
}

#endif //CMPE126S20_LABS_TREE_H
