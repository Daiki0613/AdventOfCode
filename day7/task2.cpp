#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <cmath>
#include <algorithm>
#include <map>

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

int type(string hand) {
  map<char, int> freqs;
  int jacks = 0;
  for (char c : hand) {
    if (c == 'J') {
      jacks++;
    }
    else {
      freqs[c] += 1;
    }
  }
  if (freqs.size() <= 1) {
    // full house
    return 1;
  }
  if (freqs.size() == 2) {
    for (pair<char, int> p : freqs) {
      if (p.second + jacks == 4) {
      // 4 of a kind
        return 2;
      }
    }
    // full house
    return 3;
  }
  if (freqs.size() == 3) {
    for (pair<char, int> p : freqs) {
      if (p.second + jacks == 3) {
        // 3 of a kind
        return 4;
      }
    }
    // two pair
    return 5;
  }
  if (freqs.size() == 4) {
    // one pair
    return 6;
  }
  // High card
  return 7;
}

map<char, int> card = {{'A', 1}, {'K', 2}, {'Q', 3}, {'J', 14}, {'T', 5},
  {'9', 6}, {'8', 7}, {'7', 8}, {'6', 9}, {'5', 10}, {'4', 11},
  {'3', 12}, {'2', 13}
};

bool comp(pair<string, int> a, pair<string, int> b) {
  // determine type
  int a_type = type(a.first);
  int b_type = type(b.first);

  if (a_type != b_type) {
    return a_type > b_type;
  }
  // if same compare card strength

  REP(i, 0, 5) {
    if (a.first[i] == b.first[i]) {
      continue;
    }
    return card[a.first[i]] > card[b.first[i]];
  }
  return true;
}

int calc(VS& input) {
  vector<pair<string, LL>> hands;
  for (string line : input) {
    stringstream ss(line);
    pair<string, LL> p;
    ss >> p.first >> p.second;
    hands.emplace_back(p);
  }

  sort(hands.begin(), hands.end(), comp);

  int ans = 0;
  for (int i = 0; i < hands.size(); i++) {
    cout << hands[i].first << " " << hands[i].second << endl;
    ans += hands[i].second * (i+1);
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


