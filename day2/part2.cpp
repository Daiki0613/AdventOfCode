#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

int extractGameNumber(const string& input) {
  istringstream iss(input);
  string game;
  int number = -1;

  iss >> game >> number;

  if (game == "Game" && number >= 0) {
    return number;
  } else {
    // Return -1 if the pattern "Game <number>" is not found
    return -1;
  }
}

void countBallsByColor(const string& input, unordered_map<string, int>& colorCount) {
  istringstream iss(input);

  string color;
  int count;

  while (iss >> count >> color) {
      // Remove any non-alphabetic characters from the color string
      color.erase(remove_if(color.begin(), color.end(), [](char c) { return !isalpha(c); }), color.end());

      if (colorCount[color] < count) {
        colorCount[color] = count;
      }
  }
}

int check(const string& input) {
  vector<string> sections;
  string currentSection;

  for (char ch : input) {
    if (ch == ';' || ch == ':') {
      sections.push_back(currentSection);
      currentSection.clear();
    } else {
      currentSection += ch;
    }
  }

  if (!currentSection.empty()) {
    sections.push_back(currentSection);
  }

  unordered_map<string, int> colorCount;
  colorCount["red"] = 0;
  colorCount["green"] = 0;
  colorCount["blue"] = 0;
  int sum = 0;
  for (int i = 1; i < sections.size(); i++) {
    countBallsByColor(sections[i], colorCount);
  }

  return colorCount["red"] * colorCount["green"] * colorCount["blue"];
}

int main() {
    ifstream inputFile("input.txt"); // Replace "example.txt" with your file name
    int sum = 0;
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            sum += check(line);
        }
        inputFile.close(); // Remember to close the file after reading
    } else {
        cout << "Unable to open file!" << endl;
    }
    cout << sum << endl;
    return 0;
}
