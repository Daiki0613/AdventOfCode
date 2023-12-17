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

int calc(VS& input) {
  int ans = 0;
  vector<vector<pair<string, int>>> boxes(256);
  for (string line : input) {
    int val = 0;
    VS split;
    bool insert = true;
    if (line.find('=') != string::npos) {
      split = splitString(line, '=');
    }
    else {
      split = splitString(line, '-');
      insert = false;
    }

    for (char c : split[0]) {
      val += c;
      val *= 17;
      val %= 256;
    }

    if (insert) {
      bool inserted = false;
      for (int i = 0; i < boxes[val].size(); i++) {
        pair<string, int> lens = boxes[val][i];
        if (lens.first == split[0]) {
          boxes[val][i].second = stoi(split[1]);
          inserted = true;
          break;
        }
      }
      if (!inserted) {
        boxes[val].emplace_back(pair<string, int>(split[0], stoi(split[1])));
      }
    }
    else {
      for (int i = 0; i < boxes[val].size(); i++) {
        pair<string, int> lens = boxes[val][i];
        if (lens.first == split[0]) {
          boxes[val].erase(boxes[val].begin()+i);
          break;
        }
      }
    }
    // VS split = splitString(line, ':');
    // stringstream ss(line);
    // char x;
    // ss >> x;
  }

  for (int i = 0; i < boxes.size(); i++) {
    for (int j = 0; j < boxes[i].size(); j++) {
      cout << boxes[i][j].first << " " << (i+1) * (j+1) * boxes[i][j].second << endl;
      ans += (i+1) * (j+1) * boxes[i][j].second;
    }
  }
  return ans; // solution 
}

void executeFile(string filename) {
  cout << "excecuting " << filename << endl;
  ifstream inputFile(filename);

  VS input;
  if (inputFile.is_open()) {
    string line;
    while (getline(inputFile, line)) {
      VS strs = splitString(line, ',');
      for (auto str : strs) {
        input.emplace_back(str);
      }
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


