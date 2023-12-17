#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <queue>
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
using PPI = pair<pair<int,int>, int>;
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

VP moves = {PII(1,0), PII(-1,0), PII(0,1), PII(0,-1)};

bool in_bounds(PII cur, VVC& input) {
  return 0 <= cur.first && cur.first < input.size() && 0 <= cur.second && cur.second < input[0].size();
}

PII move(PII cur, int dir) {
  return PII(cur.first + moves[dir].first, cur.second + moves[dir].second);
}

int get_energized(VVC& input, PII start, int dir) {
  VVVB visited(input.size(), VVB(input[0].size(), VB(4, false)));

  queue<PPI> q;
  q.push(PPI(start, dir));
  while (!q.empty()) {
    PPI p = q.front(); q.pop();
    PII cur = p.first;
    int dir = p.second;
    visited[cur.first][cur.second][dir] = true;
    vector<PPI> pushing;
    if (input[cur.first][cur.second] == '-') {
      if (dir == 0 || dir == 1) {
        // From North South
        pushing.emplace_back(PPI(move(cur, 2), 2));
        pushing.emplace_back(PPI(move(cur, 3), 3));
      }
      else {
        pushing.emplace_back(PPI(move(cur, dir), dir));
      }
    }
    else if (input[cur.first][cur.second] == '|') {
      if (dir == 2 || dir == 3) {
        // From West East
        pushing.emplace_back(PPI(move(cur, 0), 0));
        pushing.emplace_back(PPI(move(cur, 1), 1));
      }
      else {
        pushing.emplace_back(PPI(move(cur, dir), dir));
      }
    }
    else if (input[cur.first][cur.second] == '/') {
      if (dir == 0) {
        // From North, to West
        pushing.emplace_back(PPI(move(cur, 3), 3));
      }
      else if (dir == 1) {
        // From South, to East
        pushing.emplace_back(PPI(move(cur, 2), 2));
      }
      else if (dir == 2) {
        pushing.emplace_back(PPI(move(cur, 1), 1));
      }
      else if (dir == 3) {
        pushing.emplace_back(PPI(move(cur, 0), 0));
      }
    }
    else if (input[cur.first][cur.second] == '\\') {
      if (dir == 0) {
        // From North, to East
        pushing.emplace_back(PPI(move(cur, 2), 2));
      }
      else if (dir == 1) {
        // From South, to West
        pushing.emplace_back(PPI(move(cur, 3), 3));
      }
      else if (dir == 2) {
        pushing.emplace_back(PPI(move(cur, 0), 0));
      }
      else if (dir == 3) {
        pushing.emplace_back(PPI(move(cur, 1), 1));
      }
    }
    else {
      pushing.emplace_back(PPI(move(cur, dir), dir));
    }

    for (auto& p : pushing) {
      if (in_bounds(p.first, input) && !visited[p.first.first][p.first.second][p.second]) {
        q.push(p);
      }
    }
  }

  int ans = 0;
  for (VVB line : visited) {
    for (VB point : line) {
      if (point[0] || point[1] || point[2] || point[3]) {
        ans++;
        // cout << "#";
      }
      else {
        // cout << ".";
      }
    }
    // cout << endl;
  }
  return ans; // solution 
}

int calc(VVC& input) {
  int max_val = 0;
  // cout << get_energized(input, PII(0,3), 0) << endl;
  
  REP(i,0,input.size()) {
    max_val = max(max_val, get_energized(input, PII(i,0), 2));
    max_val = max(max_val, get_energized(input, PII(i,0), 3));
    max_val = max(max_val, get_energized(input, PII(i,input[0].size()-1), 2));
    max_val = max(max_val, get_energized(input, PII(i,input[0].size()-1), 3));
  }

  REP (i,0,input[0].size()) {
    max_val = max(max_val, get_energized(input, PII(0,i), 0));
    max_val = max(max_val, get_energized(input, PII(0,i), 1));
    max_val = max(max_val, get_energized(input, PII(input.size()-1,i), 0));
    max_val = max(max_val, get_energized(input, PII(input.size()-1,i), 1));
  }

  return max_val;
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


