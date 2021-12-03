# CSC212_Project

<h1 align="center"> Left-Leaning Red-Black Binary Search Tree </h1>

Background:

The Left-Leaning Red-Black Binary Search Tree (LLRBBST) is a specialized version of the Red-Black Binary Search Tree. The goal of an LLRBBST is to enhance the efficiency of a standard Red-Black Binary Search Tree. LLRBBST performs all standard methods (insertion, deletion, and search) in log(n) runtime.

Main Methods:

Insertion: Our implementation of insertion is fairly standard. The user inserts a data member (a string value) and the tree will insert the member and balance accordingly. Should the member already be in the tree, the data will be stored as a duplicate in the node.

Deletion: Our implementation includes two variations of the delete node function, one which deletes one duplicate of the node and one which deletes all duplicates of a node. Naturally, the tree will rebalance itself accordingly should balancing be necessary.

Search: Our implementation includes three variations of the search method. The first one, search, returns a boolean for whether the string is in the tree. The second one, find, returns a pointer to the node with a given data member. The final one, getNodeDuplicates, returns how many duplicates the data member's node has.

Set-Up:
In terms of compiling our LLRBBST, simply download the header file and function declaration file and place them in the same directory. Once you make a main.cpp, compile the .cpp files and the program should be ready to go. 

Contributors:
Norman Winn, Cam Amarel, Zach Breene, Quinn Aguilar
