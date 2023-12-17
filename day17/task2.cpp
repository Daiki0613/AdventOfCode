#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <cmath>
#include <queue>

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
using VVVI = vector<VVI>;

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

struct mycmp {
  bool operator()(VI& a, VI& b)
  {
    return a[0] > b[0];
  }
};

bool valid_pos(int x, int y, VVI& input) {
  return 0 <= x && x < input.size() && 0 <= y && y < input[0].size();
}

int calc(VVI& input) {
  int ans = 0;
  VVVI visited(input.size(), VVI(input[0].size(), VI(4, 1 << 30)));

  VP direction = { PII(-1, 0), PII(1,0), PII(0, -1), PII(0, 1)}; // UDLR
  VI opposite = {1, 0, 3, 2};
  // each vector stores {priority, x, y, dir}
  priority_queue<VI, VVI, mycmp> pq;
  VI vi = {0, 0, 0, -1};
  pq.emplace(vi);
  while (!pq.empty()) {
    VI cur = pq.top(); pq.pop();
    if (cur[1] == input.size()-1 && cur[2] == input[0].size()-1) {
      ans = cur[0];
      break;
    }
      
    REP (i,0,4) {
      if (i == cur[3] || opposite[i] == cur[3]) {
        continue;
      }
      int weight = cur[0];
      int x = cur[1];
      int y = cur[2];
      REP(j,0,10) {
        x += direction[i].first;
        y += direction[i].second;
        if (!valid_pos(x, y, input)) {
          break;
        }
        weight += input[x][y];
        if (j < 3) continue;
        if (visited[x][y][i] > weight) {
          visited[x][y][i] = weight;
          pq.push({weight, x, y, i});
        }
      }
    }
  }
  return ans; // solution 
}

void executeFile(string filename) {
  cout << "excecuting " << filename << endl;
  ifstream inputFile(filename);

  VVI input;
  if (inputFile.is_open()) {
    string line;
    
    while (getline(inputFile, line)) {
      char c;
      VI vi;
      stringstream ss(line);
      while (ss >> c) {
        vi.emplace_back(c - '0');
      }
      input.emplace_back(vi);
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


