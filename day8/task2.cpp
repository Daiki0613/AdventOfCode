#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <map>
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

LL lcm(LL n1, LL n2) {
  LL gcd;
  for (LL i = 1; i <= n1 && i <= n2; ++i) {
    if (n1 % i == 0 && n2 % i == 0) gcd = i;
  }
  return (n1 * n2) / gcd;
}

LL calc(VS& input) {
  string instruction;
  map<string, VS> g;
  VS cur_list;
  for (int i = 0; i < input.size(); i++) {
    string line = input[i];
    stringstream ss(line);
    if (i == 0) {
      ss >> instruction;
      continue;
    }
    if (i == 1) {
      continue;
    }
    string loc; ss >> loc;
    string n, l, r; ss >> n >> l >> r;
    if (loc[2] == 'A') {
      cur_list.emplace_back(loc);
    }
    g[loc] = {l.substr(1,3), r.substr(0, 3)};
  }

  cout << "curlist size " << cur_list.size() << endl; 
  VL idxs;
  LL prev = 0;
  for (string cur : cur_list) {
    LL idx = 0;
    while (cur[2] != 'Z') {
      int L = (instruction[idx % instruction.size()] == 'L') ? 0 : 1;
      cur = g[cur][L];
      idx++;
    }
    // cout << idx << endl;
    idxs.emplace_back(idx);
  }

  LL ans = 1;
  for (LL idx : idxs) {
    ans = lcm(ans, idx);
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


