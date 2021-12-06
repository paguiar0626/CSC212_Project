#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <iomanip>

#include "ArbyTree.h"

void readDataset(tree* Foodstuff, std::string inFile) {
  std::ifstream file(inFile);
  std::string line;
  
  
  std::string word;
  while (std::getline(file, line)) {

    std::istringstream ss(line);

    std::vector<std::string> lineInfo;
    while(ss >> word) {
      lineInfo.push_back(word);
    }
    //std::cout << lineInfo[3] << "\n";
    int count = std::stoi(lineInfo[3], nullptr);
    (*Foodstuff).insertC(lineInfo[0] + lineInfo[2], count);
    std::cout << (lineInfo[0] + lineInfo[2]) << '\n';
  }

  std::cout << "beep";

  return;
}

char displayOptions() {
  char choice;
  std::cout << "Which option would you like to do?\n";
  std::cout << "1. Compare the change in search frequency of one food item in different years\n";
  std::cout << "2. Compare two foods' search frequencies in the same year\n";
  std::cout << "3. Compare two foods' search frequencies in different years\n";
	std::cout << "Q. Quit Terminal\n\n";

	std::cout << "Enter Choice: ";
	std::cin >> choice;
	if ((choice != '1') && (choice != '2') && (choice != '3') && (choice != 'Q')) {
		std::cout << "\nInvalid Choice... please try again...\n\n";
		choice = displayOptions();
	}
  return choice;
}

void writeGraph(std::vector<std::vector<char>>* graph, std::string outFile) {
  std::ofstream output_file(outFile);
  for(int i = 0; i < graph->size(); i++){
    output_file << '|' << ' ';
    for(int j = 0; j < (*graph)[i].size(); j++){
      output_file << (*graph)[i][j] << " ";
    }
    output_file << "\n";
  }
  output_file << "__";
  for (int i = 0; i < graph->size(); i++) {
    output_file << "____";
  }
  output_file << "____";
  return;
}

void timeLapse(tree* Foodstuff) {
  std::string food;
  std::string year1;
  std::string year2;
  std::cout << "Please enter the food of interest: ";
  std::cin >> food;
  std::cout << "Please enter the first year: ";
  std::cin >> year1;
  std::cout << "Please enter the second year: ";
  std::cin >> year2;

  std::string outFile = food + year1 + year2 + ".txt";

  std::vector<std::vector<char>> graph;
  for (int i = 0; i < 25; i++) {
    std::vector<char> row;
    for (int j = 0; j < 52; j++) {
      row.push_back(' ');
    }
    graph.push_back(row);
  }

  std::string week;

  for (int i = 1; i <= 52; i++) {
    if (i < 10) {
      std::string thisWeek = std::to_string(i);
      week = ('0' + thisWeek);
    } else {
      week = std::to_string(i);
    }

    std::cout << (food + year1 + '-' + week) << "    ";

    int point1 = (*Foodstuff).getNodeCount(food + year1 + "-" + week);
    int point2 = (*Foodstuff).getNodeCount(food + year2 + "-" + week);

    std::cout << point1 << ' ' << point2 << ' ' << std::endl;


    if ((point1 == -1) && (point2 == -1)) {
      std::cout << "boop";
    } else if (point1 == -1) {
      graph[25 - point2/4][i-1] = 'O';
    } else if (point2 == -1) {
      graph[25 - point1/4][i-1] = 'X';
    } else if (point1 == point2) {
      graph[25 - point1/4][i-1] = 'H';
    } else {
      graph[25 - point1/4][i-1] = 'X';
      graph[25 - point2/4][i-1] = 'O';
    }
  }
  writeGraph(&graph, outFile);
  std::cout << "File successfully written\n\n";
  return;
}

void readMovie(std::string inFile) {
  tree Movia;
  std::ifstream file(inFile);
  std::string script;
  
  std::string word;

  while (std::getline(file,script)) {
    
    std::istringstream ss(script);

    while(ss >> word) {
      for (int i = 0; i < word.length(); i++){
        if (word[i] > 0x40 && word[i] < 0x5b){
          word[i] += 0x20;
        }
      }
      std::cout << word;
      Movia.insert(word);
    }
  }
  Movia.printDOT();
  Movia.~tree();
}

void time_func_ins(){
  
  unsigned long c_start, c_end;

  

  std::vector<std::string> Movia;

  std::ifstream file("beeMovieScript.txt");
  std::string script;
  
  std::string word;
  while (std::getline(file,script)) {
    
    std::istringstream ss(script);

    while(ss >> word) {
      for (int i = 0; i < word.length(); i++){
        if (word[i] > 0x40 && word[i] < 0x5b){
          word[i] += 0x20;
        }
      }
      Movia.push_back(word);
    }
  }

  c_start = std::clock();

  //Insertion Sort




  c_end = std::clock();

  float output = 1.0 * (c_end - c_start) / CLOCKS_PER_SEC;
  //std::cout << name << " euler(" << n << "):\t";
  std::cout << std::fixed << std::setprecision(4) << output << std::endl;
  return;


}

void time_func_tree() {

  unsigned long c_start, c_end;

  c_start = std::clock();

  tree Movia;
  std::ifstream file("beeMovieScript.txt");
  std::string script;
  
  std::string word;
  while (std::getline(file,script)) {
    
    std::istringstream ss(script);

    while(ss >> word) {
      for (int i = 0; i < word.length(); i++){
        if (word[i] > 0x40 && word[i] < 0x5b){
          word[i] += 0x20;
        }
      }
      Movia.insert(word);
    }
  }
  Movia.printDOT();
  Movia.~tree();

  c_end = std::clock();

  float output = 1.0 * (c_end - c_start) / CLOCKS_PER_SEC;
  //std::cout << name << " euler(" << n << "):\t";
  std::cout << std::fixed << std::setprecision(4) << output << std::endl;
  return;
}


int main(int argc, char** argv) {
  
  tree Movia;
  std::ifstream file("beeMovieScript.txt");
  std::string script;
  
  std::string word;

  while (std::getline(file,script)) {
    
    std::istringstream ss(script);

    while(ss >> word) {
      for (int i = 0; i < word.length(); i++){
        if (word[i] > 0x40 && word[i] < 0x5b){
          word[i] += 0x20;
        }
      }
      std::cout << word;
      Movia.insert(word);
    }
  }
  Movia.printDOT();
  Movia.~tree();




  /*
  tree Foodstuff;
  readDataset(&Foodstuff, argv[1]);
  bool running = true;
  while (running) {
    char choice = displayOptions();
    if (choice == 'Q') {
      running = false;
    } else if (choice == '1') {
      timeLapse(&Foodstuff);
    }
  }
  Foodstuff.~tree();
  */
  
  //time_func_tree();

  /*
	tree three;
	
  std::vector<std::string> Arr = {"chicken", "ball", "banana", "petabyte", "crumbling", "chicken", "arbys", "arbys", "powerful", "kanye", "gourmet", "eiffel", "alarm", "alarm", "curriculum", "negotiation", "rescue", "establish", "arbys", "petabyte", "doctor", "negotiation"};

  for (int i = 0;  i < Arr.size(); i++){
    three.insert(Arr[i]);
    
    //std::cin.get();  
  }
  
  three.printDOT();

	three.~tree();
  */ 
}