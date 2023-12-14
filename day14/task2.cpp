#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;

using LL = long long;
using PII = pair<int,int>;
using PLL = pair<LL,LL>;
using VB = vector<bool>;
using VS = vector<string>;
using VC = vector<char>;
using VI = vector<int>;
using VL = vector<LL>;
using VD = vector<double>;
using VP = vector<PII>;
using VVB = vector<VB>;
using VVS = vector<VS>;
using VVC = vector<VC>;
using VVI = vector<VI>;
using VVL = vector<VL>;
using VVD = vector<VD>;
using VVP = vector<VP>;

#define REP(i, x, limit) for (int i = (int)x; i < (int)limit; i++)
#define RREP(i, x, limit) for (int i = (int)x; i <= (int)limit; i++)

VS splitString(const string &s, char delimiter) {
  VS tokens;
  string token;
  size_t start = 0, end;

  while ((end = s.find(delimiter, start)) != string::npos) {
    token = s.substr(start, end - start);
    start = end + 1; // Move to the next character after the delimiter
    if (token == "") continue;
    tokens.push_back(token);
  }

  // Handle the substring after the last delimiter (or the whole string if no delimiter found)
  token = s.substr(start);
  if (!token.empty()) {
    tokens.push_back(token);
  }

  return tokens;
}

void rotate(VVC& input) {
  for (int i = 0; i < input.size(); ++i) {
    for (int j = i; j < input[i].size(); ++j) {
      swap(input[i][j], input[j][i]);
    }
  }

  // Reverse each row
  for (int i = 0; i < input.size(); ++i) {
    reverse(input[i].begin(), input[i].end());
  }
}

void tilt(VVC& input) {
  for (int j = 0; j < input[0].size(); j++) {
    int start_i = 0;
    int count = 0;
    for (int i = 0; i < input.size(); i++) {
      if (input[i][j] == 'O') {
        count++;
      }
      if (input[i][j] == '#' || i == input.size() - 1) {
        // move up
        for (int k = 0; k < count; k++) {
          input[start_i + k][j] = 'O';
        }
        for (int k = start_i + count; k <= i; k++) {
          if (input[k][j] != '#'){
            input[k][j] = '.';
          } 
        }
        start_i = i+1;
        count = 0;
      }
    }
  }
}

LL calc(VVC& input) {
  LL ans = 0;
  for (int k = 0; k < 1000000000; k++) {
    ans = 0;
    for (int i = 0; i < 4; i++) {
      tilt(input);
      rotate(input);
    }
  }
  for (int i = 0; i < input.size(); i++) {
    for (int j = 0; j < input[0].size(); j++) {
      if (input[i][j] == 'O') {
        ans += (input.size() - i);
      }
    }
  }
  return ans; // solution 
}

void executeFile(string filename) {
  cout << "excecuting " << filename << endl;
  ifstream inputFile(filename);

  VVC input;
  if (inputFile.is_open()) {
    string line;
    
    while (getline(inputFile, line)) {
      char c;
      VC vc;
      stringstream ss(line);
      while (ss >> c) {
        vc.emplace_back(c);
      }
      input.emplace_back(vc);
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


