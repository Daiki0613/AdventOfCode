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
using PCC = pair<char,char>;
using PLL = pair<LL,LL>;
using VB = vector<bool>;
using VS = vector<string>;
using VC = vector<char>;
using VI = vector<int>;
using VL = vector<LL>;
using VD = vector<double>;
using VP = vector<PII>;
using VPC = vector<PCC>;
using VVB = vector<VB>;
using VVS = vector<VS>;
using VVC = vector<VC>;
using VVI = vector<VI>;
using VVL = vector<VL>;
using VVD = vector<VD>;
using VVP = vector<VP>;
using VVPC = vector<VPC>;
using VVVB = vector<VVB>;

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

string pipes = "|-LJ7F.";
map<int, int> opposite = {{0, 1}, {1, 0}, {2, 3}, {3, 2}};

VP moves(PII& cur, VVVB& g) {
  VB dirs = g[cur.first][cur.second];
  VP vp;
  for (int i = 0; i < dirs.size(); i++) {
    if (!dirs[i]) continue;

    PII next;
    if (i == 0) {
      next = PII(cur.first - 1, cur.second);
    }
    else if (i == 1) {
      next = PII(cur.first + 1, cur.second);
    }
    else if (i == 2) {
      next = PII(cur.first, cur.second - 1);
    }
    else if (i == 3) {
      next = PII(cur.first, cur.second + 1);
    }
    else break;

    if (next.first < 0 || next.first >= g.size() || next.second < 0 || next.second >= g[0].size()) {
      break;
    }
    if (g[next.first][next.second][opposite[i]]) {
      vp.emplace_back(next);
    }
  }
  return vp;
}

void dfs(PII& S, PII& cur, VVVB& g, VVI& visited) {
  for (PII move : moves(cur, g)) {
    if (move == S) {
      visited[move.first][move.second] = max(visited[move.first][move.second], visited[cur.first][cur.second] + 1);    
      continue;
    }
    if (visited[move.first][move.second] != 0) {
      continue;
    }
    visited[move.first][move.second] = visited[cur.first][cur.second] + 1;    
    dfs(S, move, g, visited);
  }
  return;
}

int calc(VVC input) {
  PII S;
  VVVB g(input.size(), VVB(input[0].size()));
  REP(i,0,input.size()) {
    REP(j,0,input[0].size()) {
      char c = input[i][j];
      VB vb; // "NSWE"
      if (c == '|') vb = {true, true, false, false};
      else if (c == '-') vb = {false, false, true, true};
      else if (c == 'L') vb = {true, false, false, true};
      else if (c == 'J') vb = {true, false, true, false};
      else if (c == '7') vb = {false, true, true, false};
      else if (c == 'F') vb = {false, true, false, true};
      else if (c == 'S') vb = {true, true, true, true};
      else vb = {false, false, false, false};
      g[i][j] = vb;

      if (c == 'S') {
        S.first = i;
        S.second = j;
      }
    }
  }

  VVI visited(input.size(), VI(input[0].size(), 0));
  dfs(S, S, g, visited);
  
  return (visited[S.first][S.second] + 1) / 2; // solution 
}

void executeFile(string filename) {
  cout << "excecuting " << filename << endl;
  ifstream inputFile(filename);

  VVC input;
  if (inputFile.is_open()) {
    string line;
    while (getline(inputFile, line)) {
      VC vc;
      stringstream ss(line);
      char c;
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


