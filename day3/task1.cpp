#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
bool isNumber(char c) {
  return '0' <= c && c <= '9';
}

int getNumber(int i, int j1, int j2, vector<vector<char>>& input) {
  int x = 0;
  for (int j = j1; j <= j2; j++) {
    x *= 10;
    x += (input[i][j] - '0');
  }
  return x;
}

int aroundSymbol(int i, int j1, int j2, vector<vector<char>>& input) {
  for (int x = i-1; x <= i+1; x++) {
    if (x < 0 || x >= input.size()) {
      continue;
    }
    for (int y = j1-1; y <= j2+1; y++) {
      if (y < 0 || y >= input[0].size()) {
        continue;
      }
      if (x == i && y >= j1 && y <= j2) {
        continue;
      }
      if (isNumber(input[x][y])) {
        cout << "ERROR" << endl;
        return 0;
      } 
      if (input[x][y] != '.') {
        int num = getNumber(i, j1, j2, input);
        // cout << num << endl;
        return num;
      }
    }
  }
  return 0;
}

int calc(vector<vector<char>>& input) {
    int sum = 0;
    int numStart = -1;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[0].size(); j++) {
          if (isNumber(input[i][j])) {
            if (numStart == -1) {
              numStart = j;
            }
            if (j == input[0].size() - 1) {
              sum += aroundSymbol(i, numStart, j, input);
              numStart = -1;
            }
          }
          else {
            if (numStart != -1) {
              // num ended at previous
              sum += aroundSymbol(i, numStart, j-1, input);
              numStart = -1;
            }
          }
        }
    }
    return sum;
}


int main() {
    ifstream inputFile("input.txt"); // Replace "example.txt" with your file name

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
    return 0;
}


