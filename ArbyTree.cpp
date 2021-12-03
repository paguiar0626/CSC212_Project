#include "ArbyTree.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <cctype>

//--------------------------NODE METHODS-------------------------//
// Default Constructor
node::node(std::string d) {
  data.first = d;
  data.second = 'r';
  countof = 1;
  left = nullptr;
  right = nullptr;
}

node::node(std::string d, int c) {
  data.first = d;
  data.second = 'r';
  countof = c;
  left = nullptr;
  right = nullptr;
}

// Destructor
node::~node() {
}

//--------------------------TREE METHODS-------------------------//

/*
Private ----------------------------------------------------------
*/

// Default Constructor
tree::tree() {
  root = nullptr;
}

// Destructor
tree::~tree() {
  destroyTree(root);
}

// This function rotates the parent node to the left, raising its right child and reassigning the child's left pointer to the parent.
node* tree::rotateLeft(node* parent) {
  node* child = parent->right;
  node* grandchild = child->left;

  parent->right = grandchild;
  child->left = parent;

  child->data.second = parent->data.second;
  parent->data.second = 'r';
  return child;
}

// This function rotates the parent node to the right, raising its left child and reassigning the child's right pointer to the parent.
node* tree::rotateRight(node* parent) {
  node* child = parent->left;
  node* grandchild = child->right;

  parent->left = grandchild;
  child->right = parent;

	char temp = child->data.second;
  child->data.second = parent->data.second;
  parent->data.second = 'r';
  return child;
}

// This functions swaps the color of a parent node to red and its two child nodes to become black 
void tree::colorSwap(node* parent) {
  parent->left->data.second = 'b';
  parent->right->data.second = 'b';
  parent->data.second = 'r';
  return;
}

// This function takes a node and balances the tree accordingly using rotation calls and color swapping. This function is called after insertion and deletion as those two functions lead to changes in the tree which may make the tree unbalanced.
node* tree::balanceTree(node* base) {
  bool baseR = base->right;
  bool baseL = base->left;

  if ((baseR) && ((base->right->data.second == 'r') && ((base->left == nullptr)||(base->left->data.second == 'b')))) {
    base = rotateLeft(base);
  }

  baseL = base->left;
  bool baseLL = false;
  if (baseL) { baseLL = base->left->left; }
  if ((baseL && baseLL) && (base->left->data.second == 'r') && (base->left->left->data.second == 'r')) {
    base = rotateRight(base);
  }

  baseR = base->right;
  baseL = base->left;

  if ((baseR && baseL) && (base->left->data.second == 'r') && (base->right->data.second == 'r')) {
    colorSwap(base);
  }

  return base;
}

// This function removes a node with no children. The idea behind this function is to call this function to equal a parent node's right/left pointer. This means that once you delete the node, you return a null pointer back to the parent which sets where that child was to a null pointer.
node* tree::removeNo(node* target) {
  (*target).~node();
  return nullptr;
}

// This function removes a node with one child. The idea behind this function is to call this function to equal a parent node's right/left pointer. This means that once you delete the node, you return the pointer to its only child back to the parent which sets the pointer, where that child was, to the grandchild which was attached below the deleted node.
node* tree::remove1(node* parent, node* child) {
  (*parent).~node();
	return child;
}

// This function removes a node with two children. The idea behind this function is to call this function to equal a parent node's right/left pointer. Essentially, this function finds a suitable node to take its value, and delete the other node. In other words, it sets the value of the node of interest to a different node's value and deletes the other node instead.
node* tree::remove2(node* base) {
  node* parentNode = base->left;
  node* successorNode = parentNode->right;

  if (successorNode != nullptr) {
    while (successorNode->right != nullptr) {
      parentNode = successorNode;
      successorNode = successorNode->right;
    }
    base->data.first = successorNode->data.first;
    parentNode->right = successorNode->left;
    (*successorNode).~node();
  } else {
    base->data.first = parentNode->data.first;
    base->left = parentNode->left;
    (*parentNode).~node();
  }
	return base;
}

// This function inserts a node with the given value. The program will traverse through the tree to find a suitable spot to put the node, then it will create the node returning a pointer to itself so that the parent node can point to the new node. After that, the tree will recursively balance itself back up the tree until it hits the root
node* tree::insertNode(std::string d, node* parent) {
	if (parent == nullptr) { // Base Case
    parent = new node(d);
		return parent;
  }
  if (d < parent-> data.first) { // Left
    parent->left = insertNode(d, parent->left);
	} else if (d > parent->data.first) { // Right
    parent->right = insertNode(d, parent->right);
	} else { // Duplicate
    parent->countof += 1;
  }

  parent = balanceTree(parent);

  return parent;
}

// This function inserts a node with the given value and a given count of duplicates. The program will traverse through the tree to find a suitable spot to put the node, then it will create the node returning a pointer to itself so that the parent node can point to the new node. After that, the tree will recursively balance itself back up the tree until it hits the root
node* tree::insertNodeC(std::string d, int c, node* parent) {
	if (parent == nullptr) { // Base Case
    parent = new node(d, c);
		return parent;
  }
  if (d < parent-> data.first) { // Left
    parent->left = insertNodeC(d, c, parent->left);
	} else if (d > parent->data.first) { // Right
    parent->right = insertNodeC(d, c, parent->right);
	} else { // Duplicate
    parent->countof += 1;
  }

  parent = balanceTree(parent);

  return parent;
}

// This function removes a node from the tree regardless of how many duplicates the node may have. If this method is called using removeN, then the node will be deleted,even if it has 14 duplicates. Naturally, the tree will rebalance itself incase any discrepencies are made during the deletion
node* tree::removeNodeN(std::string d, node* target) {
  if (target == nullptr) {return nullptr;}

  if (target->data.first == d) { // If we find the desired node
    if ((target->left == nullptr) && (target->right == nullptr)){ // No children
      return removeNo(target);
    } else if ((target->left != nullptr) && (target->right == nullptr)){ // Left child
			return remove1(target, target->left);
		} else if ((target->left == nullptr) && (target->right != nullptr)){ // Right child
      return remove1(target, target->right);
		} else { // 2 Children
      return remove2(target);
    }

  } else if (d < target->data.first) { // Traverse Left
    target->left = removeNodeN(d, target->left);
  } else if (d > target->data.first) { // Traverse Right
    target->right = removeNodeN(d, target->right);
  }

  balanceTree(target);
  return target;
}

// This function removes one node duplicate from the tree. If this method is called using removeD, then a node with 14 duplicates will now have 13 duplicates. In the instance that there are no duplicates of a node, then the tree will simply delete the node. Naturally, the tree will rebalance itself incase any discrepencies are made during the deletion
node* tree::removeNodeC(std::string d, node* target) {
  if (target == nullptr) {return nullptr;}

  if (target->data.first == d) { // If we find the desired node
    target->countof -= 1;
    if (target->countof <= 0) {
      if ((target->left == nullptr) && (target->right == nullptr)){ // No children
        return removeNo(target);
      } else if ((target->left != nullptr) && (target->right == nullptr)){ // Left child
			  return remove1(target, target->left);
		  } else if ((target->left == nullptr) && (target->right != nullptr)){ // Right child
        return remove1(target, target->right);
		  } else { // 2 Children
        return remove2(target);
      }
    }

  } else if (d < target->data.first) { // Traverse Left
    target->left = removeNodeC(d, target->left);
  } else if (d > target->data.first) { // Traverse Right
    target->right = removeNodeC(d, target->right);
  }

  balanceTree(target);

  return target;
}

// This function searches through the tree to find a certain node with the input data. If the node is found, then the function will recursively return a pointer to the node. If the data member doesn't exist in the tree, the program will return a nullpointer signifying it is not in the tree.
node* tree::findNode(std::string d, node* currentNode) {
  if (currentNode == nullptr) {
    return nullptr;
  }
  if (currentNode->data.first == d) { // End Search
    return currentNode;
  } else if (d < currentNode->data.first) { // Left
    if (currentNode->left != nullptr) {
      return findNode(d, currentNode->left);
    }
  } else { // Right
      if (currentNode->right != nullptr) {
        return findNode(d, currentNode->right);
      }
  }
  return nullptr;
}

// This function traverses through the entire tree and deletes all nodes in the process, deleting the root node last to prevent data leaks.
void tree::destroyTree(node* target) {
	if (target->left != nullptr) {
		destroyTree(target->left);
	}
	if (target->right != nullptr) {
		destroyTree(target->right);
	}
	
	(*target).~node();
	return;
}

// This function prints the data stored at each node in preorder notation, meaning it prints the node it is currently at, then traverses left and right.
void tree::preorder(node* base){
    if(!base){
        return;
    }

    std::cout << base->data.first << ":" << base->data.second << ", ";
    preorder(base->left);
    preorder(base->right);

    return;
}

// This function prints the data stored at each node in inorder notation, meaning it traverses to the left of a node, once it comes back it prints the node and traverses to the right of the node.
void tree::inorder(node* base){
  if(!base){
      return;
  }

  inorder(base->left);
  std::cout << base->data.first << ":" << base->data.second << ", ";
  inorder(base->right);
  return;
}

// This function prints the data stored at each node in postorder notation, meaning it traverses to the left and right of a node before it prints its own value. This idea is used in the destroyTree method
void tree::postorder(node* base){
  if(!base){
    return;
  }
  postorder(base->left);
  postorder(base->right);
  std::cout << base->data.first << ":" << base->data.second << ":" << base->countof << ", ";
  return;
}


//Function to convert the tree stored in memory to a visual representation. Uses a preorder traversal method.
void tree::DotOut(node* base, int& i){

	if (base == nullptr){
		return;
	}

  output_file << "\t\"" << base->data.first << "\" [label = \"" << base->data.first << ": " << base->countof << "\" shape = box ]\n";

	if (base->left == nullptr){
		output_file << "\tNULL" << i << " [shape = \"point\"]\n\t\"" << base->data.first << "\" -- NULL" << i << " [style = bold]\n";
    i++;
	} else {
		if (base->left->data.second == 'r'){
			output_file << "\t\"" << base->data.first << "\" -- \"" << base->left->data.first << "\" [color = red style = bold]\n";	
		} else{
			output_file << "\t\"" << base->data.first << "\" -- \"" << base->left->data.first << "\" [style = bold]\n";
		}
	}

	if (base->right == nullptr){
		output_file << "\tNULL" << i << " [shape = \"point\"]\n\t\"" << base->data.first << "\" -- NULL" << i << " [style = bold]\n";
    i++;
	} else {
		output_file << "\t\"" << base->data.first << "\" -- \"" << base->right->data.first << "\" [style = bold]\n";
	}

	//std::cout << "beep";

	DotOut(base->left, i);
	DotOut(base->right, i);
}



/*
PUBLIC ------------------------------------------------------------
*/

// This method calls the insert function given just a data value and inserts it into the tree
void tree::insert(std::string d) {
  root = insertNode(d, root);
  root->data.second = 'b';
  return;
}

void tree::insertC(std::string d, int c) {
  root = insertNodeC(d, c, root);
  root->data.second = 'b';
  return;
}

// This method calls the find function given just a data value and returns a pointer to that node. If nothing is found, it will return a null pointer.
node* tree::find(std::string d) {
  return findNode(d, root);
}

// This method calls the find function given just a data value and returns a boolean true or false whether the data is in the tree, true if it is and false if it isn't.
bool tree::search(std::string d) {
  if (findNode(d, root) == nullptr) {
    return false;
  }
  return true;
}

// This method calls the removeNodeN function, which deletes a node regardless of duplicates. More information can be seen in its function description above
void tree::removeN(std::string d) {
  removeNodeN(d, root);
  return;
}

// This method calls the removeNodeD function, which deletes a duplicate node. More information can be seen in its function description above
void tree::removeD(std::string d) {
  removeNodeC(d, root);
  return;
}

// This method calls the preorder function, which prints out all of the data in the nodes of the tree in preorder notation.
void tree::printPre() {
  preorder(root);
  return;
}

// This method calls the inorder function, which prints out all of the data in the nodes of the tree in inorder notation.
void tree::printIn() {
  inorder(root);
  return;
}

// This method calls the postorder function, which prints out all of the data in the nodes of the tree in postorder notation.
void tree::printPost() {
  postorder(root);
  return;
}

void tree::printDOT(){
	output_file.open("graph.dot");
	output_file << "graph {\n";
	DotOut(root, treecount);
	output_file << '}';
  output_file.close();
	return;
}

// This method finds the node of interest and returns how many times the word was repeated.
int tree::getNodeCount(std::string d) {
  node* curios = findNode(d, root);
  if (curios) {
    return curios->countof;
  }
  return 0;
}

std::string tree::Lower(std::string in){
  for (int i = 0; i < in.size(); i++){
    in[i] = tolower(in[i]);
  }
  return in;
}
