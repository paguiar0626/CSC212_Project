#pragma once
#include <utility>
#include <string>
#include <fstream>
#include <cctype>

//--------------------------NODE CLASS---------------------------//
class node {

  private:
    std::pair<std::string, char> data;
    int countof;
    node* left;
    node* right;

  public:
    node(std::string d);
    node(std::string d, int c);
    ~node();

    friend class tree;
		
};

//--------------------------TREE CLASS---------------------------//
class tree {

  private:

    std::ofstream output_file;
    node* root;
    int treecount = 0;

    // Main Methods 

    node* insertNode(std::string d, node* parent);
    node* insertNodeC(std::string d, int c, node* parent);
    node* removeNodeN(std::string d, node* parent);
    node* removeNodeC(std::string d, node* parent);
    node* findNode(std::string d, node* currentNode);   
    void destroyTree(node* target);
    
    // Supporting Methods
    node* rotateRight(node* parent);
    node* rotateLeft(node* parent);
    void colorSwap(node* parent);

    node* removeNo(node* target);
    node* remove1(node* parent, node* child);
    node* remove2(node* base);
    
    node* balanceTree(node* base); 

    void preorder(node* base);
    void inorder(node* base);
    void postorder(node* base);
    void DotOut(node* base, int& i);

    
  public:

    tree();
    ~tree();

    // Main Methods
    void insert(std::string d);
    void insertC(std::string d, int c);
    void removeN(std::string d);
    void removeD(std::string d);
    node* find(std::string d);
    bool search(std::string d);
    int getNodeCount(std::string d);
	
    // Extra Methods / Bugfixing Methods
    void printPre();
    void printIn();
    void printPost();
    void printDOT();

    std::string Lower(std::string in);
};
