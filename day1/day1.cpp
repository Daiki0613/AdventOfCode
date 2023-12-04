#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
int main() {
    ifstream inputFile("a.txt"); // Replace "example.txt" with your file name

    string words[] = {"one", "two", "three", "four", 
                        "five", "six", "seven", "eight", "nine"};
    int sum = 0;
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            for (int i = 0; i < line.size(); i++) {
                if ('0' <= line[i] && line[i] <= '9') {
                    sum += (line[i] - '0') * 10;
                    break;
                }
                bool found = false;
                for (int j = 0; j < 9; j++) {
                    string word = words[j];
                    for (int k = 0; k < word.size(); k++) {
                        if (i + k >= line.size() || word[k] != line[i+k]) {
                            break;
                        }
                        else if (k == word.size()-1) {
                            found = true;
                            sum += (j + 1) * 10;
                            break;
                        }
                    }
                    if (found) {
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
            for (int i = line.size()-1; i >= 0; i--) {
                if ('0' <= line[i] && line[i] <= '9') {
                    sum += (line[i] - '0');
                    break;
                }
                bool found = false;
                for (int j = 0; j < 9; j++) {
                    string word = words[j];
                    for (int k = word.size()-1; k >= 0; k--) {
                        if  (i - k < 0 || word[word.size()-k-1] != line[i-k]) {
                            break;
                        }
                        else if (k == 0) {
                            found = true;
                            sum += (j + 1);
                            break;
                        }
                    }
                    if (found) {
                        break;
                    }
                }
                if (found) {
                    break;
                }
                
            }
        }
        inputFile.close(); // Remember to close the file after reading
    } else {
        cout << "Unable to open file!" << endl;
    }
    cout << sum << endl;
    return 0;
}


