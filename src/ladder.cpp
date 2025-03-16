#include "ladder.h"
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <cerrno>
#include <cstring>

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (abs(static_cast<int>(str1.length()) - static_cast<int>(str2.length())) > d) {
        return false;
    }

    // If the lengths are the same, check for substitutions
    if (str1.length() == str2.length()) {
        int diff_count = 0;
        for (size_t i = 0; i < str1.length(); ++i) {
            if (str1[i] != str2[i]) {
                diff_count++;
                if (diff_count > d) {
                    return false;
                }
            }
        }
        return diff_count <= d;
    }

    // If the lengths differ by 1, check for insertions or deletions
    if (abs(static_cast<int>(str1.length()) - static_cast<int>(str2.length())) == 1) {
        string shorter = str1.length() < str2.length() ? str1 : str2;
        string longer = str1.length() > str2.length() ? str1 : str2;

        for (size_t i = 0; i < shorter.length(); ++i) {
            if (shorter[i] != longer[i]) {
                // Skip one character from the longer word
                return shorter.substr(i) == longer.substr(i + 1);
            }
        }
        return true; // If all characters match, it's a valid insertion or deletion
    }
    return false;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (word_list.find(end_word) == word_list.end()) {
        return {};
    }

    if (begin_word == end_word) {
        return {}; // No ladder needed, return the word itself
    }

    queue<vector<string>> ladders;
    ladders.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladders.empty()) {
        int size = ladders.size();

        for (int i = 0; i < size; ++i) {
            vector<string> current_ladder = ladders.front();
            ladders.pop();
            string last_word = current_ladder.back();

            if (last_word == end_word) {
                return current_ladder;
            }

            for (const string& word : word_list) {
                if (visited.find(word) == visited.end() && is_adjacent(last_word, word)) {
                    vector<string> new_ladder = current_ladder;
                    new_ladder.push_back(word);
                    ladders.push(new_ladder);
                    visited.insert(word);
                }
            }
        }
    }

    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    std::ifstream in(file_name);
    if (!in.is_open()) {
        // Print the error using strerror(errno) to give a more specific system error message
        std::cerr << "Error: unable to open file " << file_name << " (" << strerror(errno) << ")" << std::endl;
        return;
    }

    string w;
    while(in >> w)
    {
        for(auto &ch : w)
        {
            ch = tolower(ch);
        }
        word_list.insert(w);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }

    cout<< "Word ladder found: ";
    for(const auto& word : ladder){
        cout << word << " ";
    }

    cout << endl;
}

void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    auto ladder1 = generate_word_ladder("cat", "dog", word_list);
    cout << "car -> dog ladder size: " << ladder1.size() << endl;

    auto ladder2 = generate_word_ladder("marty", "curls", word_list);
    cout << "marty -> curls ladder size: " << ladder2.size() << endl;

    auto ladder3 = generate_word_ladder("code", "data", word_list);
    cout << "code -> data ladder size: " << ladder3.size() << endl;

    auto ladder4 = generate_word_ladder("work", "play", word_list);
    cout << "work -> play ladder size: " << ladder4.size() << endl;

    auto ladder5 = generate_word_ladder("sleep", "awake", word_list);
    cout << "sleep -> awake ladder size: " << ladder5.size() << endl;

    auto ladder6 = generate_word_ladder("car", "cheat", word_list);
    cout << "car -> cheat ladder size: " << ladder6.size() << endl;
}
