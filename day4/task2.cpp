#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <cmath>

using namespace std;
vector<string> splitString(const string &s, char delimiter) {
    vector<string> tokens;
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

int calc(vector<string>& input) {
  vector<int> ans(input.size(), 1);
  for (int i = 0; i < input.size(); i++) {
    string line = input[i];
    vector<string> split = splitString(splitString(line, ':')[1], '|');
    // cout << line << endl;
    set<int> wins;
    int count = 0;
    for (string s : splitString(split[0], ' ')) {
      // cout << s << endl;
      wins.emplace(stoi(s));
    }
    for (string s : splitString(split[1], ' ')) {
      int num = stoi(s);
      if (wins.contains(num)) {
        count++;
      }
    }
    
    for (int j = 1; j <= count && j < input.size(); j++) {
      ans[i+j] += ans[i];
    }
  }
  int sum = 0;
  for (int i = 0; i < ans.size(); i++) {
    sum += ans[i];
  }
  return sum;
}

void executeFile(string filename) {
  cout << "excecuting " << filename << endl;
  ifstream inputFile(filename);

  vector<string> input;
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


