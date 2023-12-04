#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
int calc(vector<vector<char>>& input) {
  
}

void executeFile(string filename) {
  cout << "excecuting " << filename << endl;
  ifstream inputFile(filename);

  vector<vector<char>> input;
  if (inputFile.is_open()) {
    string line;
    while (getline(inputFile, line)) {
      vector<char> l;
      for (char c : line) {
        l.emplace_back(c);
      }
      input.emplace_back(l);
    }
    inputFile.close(); // Remember to close the file after reading
  } else {
    cout << "Unable to open file!" << endl;
  }
  cout << calc(input) << endl;
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    executeFile("input.txt");
  }
  else {
    for (int i = 1; i < argc; i++) {
      executeFile(argv[i]);
    }
  }
    
  return 0;
}


