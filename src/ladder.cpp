#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (abs(static_cast<int>(str1.length()) - static_cast<int>(str2.length())) > d) {
        return false;
    }

    int diff_count = 0;
    for (size_t i = 0; i < str1.length() && i < str2.length(); ++i) {
        if (str1[i] != str2[i]) {
            diff_count++;
            if (diff_count > d) {
                return false;
            }
        }
    }
    return diff_count <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (word_list.find(end_word) == word_list.end()) {
        return {};
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
    ifstream file(file_name);
    if (!file) {
        cerr << "Error opening file: " << file_name << endl;
        return;
    }

    string word;
    while (file >> word) {
        for(auto &ch : word){
            ch = tolower(ch);
        }
        word_list.insert(word);
    }

    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }

    for(const auto& word : ladder){
        cout << w << " ";
    }

    cout << endl;
}

void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "words.txt");

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
