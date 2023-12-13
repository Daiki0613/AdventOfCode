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

bool verify(string spring, VI splits) {
  int id = 0;
  bool in_spr = false;
  REP(i,0,spring.size()) {
    if (spring[i] == '#') {
      in_spr = true;
      if (id >= splits.size()) {
        return false;
      }
      splits[id]--;
    }
    else if (spring[i] == '.' && in_spr) {
      in_spr = false;
      id++;
    }
  }
  
  REP(i,0,splits.size()) {
    if (splits[i] != 0) {
      return false;
    }
  }
  return true;
}

int bindfs(string spring, VI& splits) {
  int c = 0;
  REP(i,0,spring.size()) {
    if (spring[i] == '?') {
      spring[i] = '.';
      c += bindfs(spring, splits);
      spring[i] = '#';
      c += bindfs(spring, splits);
      return c;
    }
  }
  if (verify(spring, splits)) {
    return 1;
  }
  else return 0;
}

int count(string spring, VI& splits) {
  int ans = bindfs(spring, splits);
  cout << ans << endl;
  return ans;
}

int calc(VS& input) {
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

  int ans = 0;
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


