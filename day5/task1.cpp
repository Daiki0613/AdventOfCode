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
  int i = -1;
  VL seeds;
  vector<VVL> vvvi(7, VVL());
  for (string line : input) {
    stringstream ss(line);
    if (line.substr(0, 6) == "seeds:") {
      
      string s; ss >> s;
      LL x;
      while (ss >> x) {
        seeds.emplace_back(x);
      }
      continue;
    }
    if (line[line.size()-1]  == ':') {
    //   seed-to-soil map:
    // soil-to-fertilizer map:
    // fertilizer-to-water map:
    // water-to-light map:
    // light-to-temperature map:
    // temperature-to-humidity map:
    // umidity-to-location map:
      i++;
      continue;
    }
    if (line == "") {
      continue;
    }
    
    VL vi(3);
    ss >> vi[0] >> vi[1] >> vi[2];
    vvvi[i].emplace_back(vi);
  }

  VL locations;
  for (int i = 0; i < seeds.size(); i++) {
    LL cur = seeds[i];
    for (int j = 0; j < 7; j++) {
      for (int k = 0; k < vvvi[j].size(); k++) {
        VL vi = vvvi[j][k];
        if (vi[1] <= cur && cur < vi[1] + vi[2]) {
          cur = cur - vi[1] + vi[0];
          break;
        }
      }
    }
    locations.emplace_back(cur);
  }


  LL minimum = locations[0];
  for (LL loc : locations) {
    minimum = min(minimum, loc);
  }
  return minimum; // solution 
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


