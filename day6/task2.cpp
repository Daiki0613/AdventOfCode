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

LL calc(VS& input) {
  vector<LL> time;
  vector<LL> distance;
  int line_num = 0;
  for (string line : input) {
    // VS split = splitString(line, ':');
    stringstream ss(line);
    string x;
    ss >> x;

    string num;
    string concat = "";
    while(ss >> num) {
      concat += num;
    }
    stringstream s2(concat);
    LL n;
    s2 >> n;
    if (line_num == 0) {
      time.emplace_back(n);
    }
    else {
      distance.emplace_back(n);
    }
    line_num++;
  }

  LL ans = 1;
  for(LL i = 0; i < time.size(); i++) {
    LL count = 0;
    for (LL j = 0; j <= time[i]; j++) {
      LL dist = j * (time[i] - j);
      if (dist > distance[i]) {
        count++;
      } 
    }
    ans *= count;
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


