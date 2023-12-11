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

int calc(VVC& input) {
  VI vertical(input.size(), 2);
  VI horizontal(input[0].size(), 2);
  VP stars;

  REP(i,0,input.size()) {
    REP(j,0,input[0].size()) {
      if (input[i][j] != '.') {
        vertical[i] = 1;
        break;
      }
    }
    if (i == 0) {
      vertical[i]--;
    }
    else {
      vertical[i] += vertical[i-1];
    }
  }

  REP(j,0,input[0].size()) {
    REP(i,0,input.size()) {
      if (input[i][j] != '.') {
        horizontal[j] = 1;
        break;
      }
    }
    if (j == 0) {
      horizontal[j]--;
    }
    else {
      horizontal[j] += horizontal[j-1];
    }
  }

  REP(i,0,input.size()) {
    REP(j,0,input[0].size()) {
      if (input[i][j] == '#') {
        stars.emplace_back(PII(vertical[i],horizontal[j]));
      }
    }
  }

  int ans = 0;
  REP(i,0,stars.size()) {
    REP(j,i,stars.size()) {
      ans += abs(stars[i].first - stars[j].first) +  abs(stars[i].second - stars[j].second);
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
      stringstream ss(line);
      char c;
      VC vc;
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


