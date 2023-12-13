#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <cmath>

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
using VVVC = vector<VVC>;

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

LL calc(VVVC& input) {
  int ans = 0;
  for (VVC &map : input) {
    int val = 0;
    for (int i = 0; i < map.size()-1; i++) {
      // horizontal
      int diffs = 0;
      for (int j = 0; j <= i; j++) {
        if (i + j + 1 >= map.size()) break;
        for (int k = 0; k < map[0].size(); k++) {
          if (map[i-j][k] != map[i+j+1][k]) {
            diffs++;
            if (diffs >= 2) {
              break;
            }
          }
        }
      }
      if (diffs == 1) {
        val = (i+1) * 100;
        break;
      }
    }
    for (int i = 0; i < map[0].size()-1; i++) {
      // vertical
      int diffs = 0;
      for (int j = 0; j <= i; j++) {
        if (i + j + 1 >= map[0].size()) break;
        for (int k = 0; k < map.size(); k++) {
          if (map[k][i-j] != map[k][i+j+1]) {
            diffs++;
          }
        }
      }
      if (diffs == 1) {
        val = i+1;
        break;
      }
    }
    ans += val;  
  }
  
  // for (VVC &map : input) {
  //   for (VC &line : map) {
  //     for (char c : line) {
  //       cout << c;
  //     }
  //     cout << endl;
  //   }
  //   cout << endl;
  //   cout << "next map: " << endl;
  // }
  return ans; // solution 
}

void executeFile(string filename) {
  cout << "excecuting " << filename << endl;
  ifstream inputFile(filename);

  VVVC input;
  if (inputFile.is_open()) {
    string line;
    char c;
    VVC map;
    while (getline(inputFile, line)) {
      if (line == "") {
        input.emplace_back(map);
        map.clear();
      }
      else {
        VC x;
        stringstream ss(line);
        while (ss >> c) {
          x.emplace_back(c);
        }
        map.emplace_back(x);
      }
    }
    input.emplace_back(map);
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


