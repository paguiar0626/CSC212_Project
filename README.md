<h1 align="center"> Left-Leaning Red-Black Binary Search Tree  </h1>

<h2 align="center"> CSC212 Fall 2021: Norman Winn, Cam Amarel, Quinn Aguilar, Zach Breene </h2>

### **Background:**

The Left-Leaning Red-Black Binary Search Tree (LLRBBST) is a specialized version of the Red-Black Binary Search Tree. Left Leaning refers to an added set of rules where red nodes must be the left child of their parent node. The implication of this rule adds a couple of mechanisms which increases the efficiency of the dataset by improving the worst case runtimes. As a result of these added rules, our implementation of the LLRBBST performs the following standard methods (insertion, deletion, and search) in log(n) runtime.

### **Documentation**

#### 1. ArbyTree.h

This is the header file which contains the class declarations for both nodes and trees. The only methods declared in the node class are two overloaded constructors and one default destructor. The tree class contains many methods. The specific methods will be detailed under their categories in ArbyTree.cpp. Nodes store data in a pair, where the first is a string and the second is a char (representing color), as well as the number of duplicate insertions for that data, named "countof". Trees store the memory of the root node, aptly named "root", and an output file to write DOT files.

#### 2. ArbyTree.cpp

This is a supporting file for all methods declared in ArbyTree.h. The main methods are as follows:

---
*Insertion*: There two variations of the insertion method
- `insert(string)`: This insertion method makes a node and stores the string parameter. The initial value of "countof" will be 1.
- `insertC(string,int)`: This insertion method makes a node and stores the string parameter. The value of "countof" will be initialized to int.

After inserting a non-duplicate node, the tree will autobalance itself using a series of left/right rotations and color swaps.

---

*Deletion*: There are two variations of the deletion method
- `removeN(string)`: This deletion method will delete a node entirely regardless of how high "countof" is.
- `removeD(string)`: This deletion method will delete one duplicate of a node from the tree by subracting one from "countof". If "countof" becomes 0, then the node will be deleted from the tree.

After removing a non-duplicate node, the tree will autobalance itself using a series of left/right roations and color swaps.

---
*Search*: There are three variations of the search method
- `find(string)`: This search method will find a node with the given string value stored in it and return a pointer to it.
- `search(string)`: This search method will find a node with the given string value stored in it and return a boolean, false representing the node not existing and true representing the existence of the node.
- `getNodeCount(string)`: This search method will find a node with the given string value stored in it and return its "countof" value.

Since these methods do not change the tree, no balancing is needed.

---
*Print*: There are four variations of the print functions which print out the tree, three which print to the user's terminal and one which prints to a DOT file
- `printPre`: This method prints a tree in Pre-Order notation to the console
- `printIn`: This method prints a tree in In-Order notation to the console
- `printPost`: This method prints a tree in Post-Order notation to the console
- `printDOT`: This method prints a tree in DOT file format to the output file. We used Graphviz to visual the DOT file

---
#### 3. main.cpp

(WIP)

#### 4. beeMovieScript.txt

This file is a simple text file with a copypasta (a common type of internet joke which involves long lines of text which usually require copy and pasting) of the entire script of the movie, "Bee Movie". This is a sample text file that can be used with our implementation.

#### 5. shrekScript.txt

This file is a simple text file with a script of the entire movie, "Shrek". This is a sample text file that can be used with our implementation.

#### 6. dataset.txt

This file is a comprehensive text file with Google Search data taken from Kaggle. See [here] for more information about the data itself.

### **Compilation**

The process of compilation is fairly straight forward. Simply download the `main.cpp`, `ArbyTree.cpp`, `ArbyTree.h`, and one text file of interest. Next, upload them into your IDE. All that's left to do is update the main.cpp to function however you'd like. Should you use either of the movie scripts, you will want to run the prepared function `readMovie(string)` to read from the movie script and store all of the words into a tree. If you want to see the output visualization of the DOT file, we recommend you to use [Graphviz]. If you decide to use our dataset, then you may want to run the `dataset()` function, which will run a console based program to write trend data to an output file.

Contributors:
Norman Winn, Cam Amarel, Zach Breene, Quinn Aguilar
