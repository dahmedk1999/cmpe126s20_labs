#include "../inc/tree.h"
#include <iostream>
#include <math.h>
#include <string>


namespace lab8 {
    void clear(node *to_clear);

    // Construct an empty tree
    tree::tree() {
        root = nullptr;
        tree_size = 0;
    }

    // Copy constructor
    node* constr_h(node*current, node*rhs)
    {

       if(rhs== nullptr)
           return current;
       else
       {
            current=new node(rhs->data);
            constr_h(current->left,rhs->left);
            constr_h(current->right,rhs->right);
       }
    }

    tree::tree(const tree &copy)
    {
        if(copy.root== nullptr)root= nullptr;
        else constr_h(root,copy.root);
    }

    // Deconstruct tree
    tree::~tree() {
        clear(root);
    }

////////////////////////////////////// Auxiliary functions
    void node_print_gtl(node *top)
    {
        if (top == nullptr)
            return;
        node_print_gtl(top->right);
        for (int i = 0; i < top->frequency; i++)
            std::cout << top->data << " ";
        node_print_gtl(top->left);
    }

    void clear(node *to_clear) {
        if (to_clear == nullptr)
            return;
        if (to_clear->left != nullptr)
            clear(to_clear->left);
        if (to_clear->right != nullptr)
            clear(to_clear->right);
        delete to_clear;
    }
    node *search(node*root, int key)
    {
        if(root==nullptr||root->data==key)
            return root;
        if(root->data<key)
            return search(root->right,key);
        else
            return search(root->left,key);
    }

    int searchlevel(node*root, int key)
    {
        if(search(root,key)== nullptr)
            return -1;
        if(root== nullptr||root->data==key)
            return 0;
        if(root->data<=key)
            return 1+searchlevel(root->right,key);
        else
            return 1+searchlevel(root->left,key);
    }
//////////////////////////////////////////////////////////////
    // Insert
    void node_insert(lab8::node *temp, int key){
        if (key < temp->data && temp->left != nullptr) {
            node_insert(temp->left, key);
        }else if(key < temp->data){
            auto newNode = new lab8::node(key);
            temp->left = newNode;


        }else if(key > temp->data && temp->right != nullptr) {
            node_insert(temp->right, key);
        }else if(key > temp->data){
            auto newNode = new lab8::node(key);
            temp->right = newNode;
        }
    }
    void insert_helper_freq(node* temp,int value)
    {
        if(value==temp->data)
            temp->frequency++;
        else if(value<temp->data)
            insert_helper_freq(temp->left,value);
        else if(value>temp->data)
            insert_helper_freq(temp->right,value);

    }
    void tree::insert(int value)
    {
        auto temp= root;
        if(root== nullptr) {
            auto temp1 = new node(value);
            root=temp1;
            tree_size++;
        }
        else if (in_tree(value))
        {
            tree_size++;
            insert_helper_freq(temp,value);
        }
        else
        {
            node_insert(temp, value);
            tree_size++;
        }
    }
//        node*nN=new node(value);
//        if(in_tree(value))
//        {
//            search(root,value)->frequency++;exit;
//        }
//        if (root== nullptr)
//        {
//            tree_size++;
//            root=nN;
//        }
//        else
//        {
//            tree_size++;
//            insertNode(root, nN);
//        }

//        else if(root->data==value)
//            root->frequency++;
//        if(root->right== nullptr)
//            insert(value);
//        if(root->left== nullptr)
//            insert(value);



    // Remove key return true if the key is deleted, and false if it isn't in the tree
    bool tree::remove(int key)
    {
        if(in_tree(key))
        {
            auto temp=search(root,key);
            if(temp->frequency>=0) {tree_size--;temp->frequency--;}
            return true;
        }
        //tree_size--;
        return false;//if key doesnt exist in tree
    }

    // What level is key on?
    int tree::level(int key)
    {

        return searchlevel(root,key);
        //        if(root==NULL||root->data==key)
//            return 0;
//        if(root->left->data<=key)
//            return 1+level(key);

    }

    // Print the path to the key, starting with root
    void *path(node*root, int key)
    {
        if(root->data==key)
            std::cout<<root->data<<"\n";
        else if(key<root->data)
        {
            std::cout<<root->data<<" -> ";
            path(root->left,key);
        }
        else if(key>root->data)
        {
            std::cout<<root->data<<" -> ";
            path(root->right,key);
        }
        else std::cout<<"";
    }
    void tree::path_to(int key)
    {
        if(in_tree(key))
            path(root,key);
        else std::cout<<"";
    }

    // Number of items in the tree
    unsigned tree::size()
    {
//        if(root)
            return tree_size;
//        else return 0;
    }
//    unsigned maxDepth(node *rooT){
//        if(rooT)
//        {
//            return 1+(maxDepth(rooT->left) > maxDepth(rooT->right) ? maxDepth(rooT->left) : maxDepth(rooT->right));
//        }
//        return 0;
//    }
    // Calculate the depth of the tree, longest string of connections
    unsigned findepth(node* N,int currentD)//should always pass 0 to currentD when calling the function
    {
    if(!N) return currentD;

    unsigned leftd = findepth(N->left,currentD+1);
    unsigned rightd= findepth(N->right,currentD+1);

    return leftd>rightd ? (leftd) : (rightd);
    }

    unsigned tree::depth()
    {
        if(!root || tree_size==0)return 0;
        return findepth(root,0)-1;
    }
//        int cl=0;int cr=0;
//        if(root== nullptr)
//            return 0;
//        if(root->left)
//        {
//            root=root->left;
//            cl++;
//            depth();
//        }
//        else if(root->right)
//        {
//            cr++;
//            root=root->right;
//            depth();
//        }
//        return (cl > cr) ? cl : cr;
//        return (static_cast<int>(log(tree_size)));

    // Determine whether the given key is in the tree
    bool tree::in_tree(int key)
    {
        return search(root, key) != nullptr;
    }

    // Return the number of times that value is in the tree
    int tree::get_frequency(int key)
    {
        if(in_tree(key))
            return search(root,key)->frequency;
        else return 0;
    }

    // Return a string of all of the elements in the tree in order
    std::string in_order(node* root)
    {
        std::string temp;
        if (root == nullptr)
            return temp;
        in_order(root->left);
        for (int i = 0; i < root->frequency; i++)
        {
            std::cout << root->data << " ";
            temp+=std::to_string(root->data);
        }
        in_order(root->right);

//        if (root == nullptr)return;
//
//        in_order(root->left);
//        std::cout << root->data << " ";
//        in_order(root->right);
    }


    std::string tree::to_string(){
        std::cout<<"\n";
        return in_order((root));
    }

    //Use the to string function for the following two functions
    // Print the tree least to greatest, Include duplicates
    void node_print_ltg(node *root)
    {
        if (root == nullptr)
            return;

        node_print_ltg(root->left);
        for (int i = 0; i < root->frequency; i++)
            std::cout << root->data << " ";
        node_print_ltg(root->right);

    }

    void tree::print()
    {
        node_print_ltg(root);
        std::cout<<"\n";
    }

    // Print the tree least to greatest, Include duplicates
    std::ostream &operator<<(std::ostream &stream, tree &RHS)
    {
        std::string outString=in_order(RHS.root);
        stream << outString << std::endl;
    }

    // Operator= Overload. Allowing for copying of trees
    void op_helper(node*current, node*rhs)
    {
        if(rhs)
        {
            current=new node(rhs->data);
            if(rhs->right)
            {
                current->right=new node(rhs->right->data);
                op_helper(current->right, rhs->right);
            }
            if(rhs->left)
            {
                current->left=new node(rhs->left->data);
                op_helper(current->left, rhs->left);
            }
        }
    }

    tree &tree::operator=(const lab8::tree rhs)
    {
        if(this==&rhs) {
            return *this;
        }
        clear(root);
        auto temp=new node(rhs.root->data);

        root=temp;
        op_helper(root, rhs.root);
        return *this;
    }

    /**************************
     * Extra credit functions *
     **************************/

    // Return a vector with all of the nodes that are greater than the input key in the tree
    std::vector<int> vec_in_order(node* root, std::vector<int> b)
    {

//        if (root == nullptr)
//            return b;
//        in_order(root->left);
//        for (int i = 0; i < root->frequency; i++)
//        {
//            b.push_back(root->data);
//        }
//        in_order(root->right);

    }

    std::vector<int> tree::values_above(int key)
    {
//    std::vector<int> newV={0};
//    std::vector<int> b;
//
//    auto basenode= search(root,key);//nodes after the key should be the ones inorder
//    newV= vec_in_order(basenode,b);
//
//    return newV;
    }

    // Merge rhs into this. Demo to a TA for credit
    tree tree::operator+(const tree &rhs) const
    {

    }

    // Balance the tree using any published algorithm. Demo to a TA for credit
    void tree::balance() {

    }

    /*********************************************************************
     * Recursion Example                                                 *
     * Print the linked list from greatest to least using recursion      *
     *********************************************************************/



    // Class function
    void tree::print_gtl() {
        node_print_gtl(root);
        std::cout << std::endl;
    }
}