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
  token = s.substr(start);
  if (!token.empty()) {
    tokens.push_back(token);
  }

  return tokens;
}

LL dp(string& spring, VI& splits) {
  VVL count(splits.size(), VL(spring.size()+1, 0));
  REP(i,0,splits.size()) {
    int num = splits[i]; // number of gears to place consecutively
    LL x = (i == 0) ? 1 : 0;
    REP(j,0,spring.size()) {
      if (j + num > spring.size()) {
        break;
      }

      bool placeable = true;
      REP(k,0,num) {
        if (spring[j + k] == '.') {
          placeable = false;
          break;
        }
      }
      if (placeable && (j + num == spring.size() || spring[j + num] != '#')) {
        if (i == splits.size()-1) {
          REP(id, j+num, spring.size()) {
            if (spring[id] == '#') {
              placeable = false;
            }
          }
        }
        if (placeable) count[i][j+num] = x;
      }
      if (spring[j] == '#') {
        x = 0;
      }
      if (i != 0) {
        x += count[i-1][j];
      }
      
    }
  }
  LL ans = 0;
  REP(i,0,count[0].size()) {
    ans += count[count.size()-1][i];
  }
  return ans;
}

LL count(string& spring, VI& splits) {
  string new_spring = spring;
  VI new_splits = splits;
  REP(i,0,4){
    new_spring += "?" + spring;
    for (auto split : splits) {
      new_splits.emplace_back(split);
    }
  }

  LL x = dp(new_spring, new_splits);
  return x;
}

LL calc(VS& input) {
  VS springs;
  VVI splits;
  for (string line : input) {
    VS split = splitString(line, ' ');
    VS nums = splitString(split[1], ',');
    springs.emplace_back(split[0]);
    
    VI split_nums;
    for (string num : nums) {
      split_nums.emplace_back(stoi(num));
    }
    splits.emplace_back(split_nums);
  }

  LL ans = 0;
  REP(i,0,input.size()) {
    // cout << i << " " << count(springs[i], splits[i]) << endl;
    ans += count(springs[i], splits[i]);
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
      input.emplace_back(line);
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


