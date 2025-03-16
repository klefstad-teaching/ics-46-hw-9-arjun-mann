#include "ladder.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <stack>
using namespace std;

void error(string word1, string word2, string msg) {
    cout << word1 << " " <<  word2 << " " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    cout << str1 << str2 << d << endl;
    return false;
}

bool is_adjacent(const string& word1, const string& word2) {
    int diff = 0;
    int w1s = static_cast<int>(word1.size());
    int w2s = static_cast<int>(word2.size());
    if(w1s == w2s) {
        for(int i = 0; i < w1s; ++i) {
            if(word1[i] != word2[i]) ++diff;
        }
        if(diff > 1) return false;
    } else if(w1s == w2s + 1) {
        int j = 0;
        for(int i = 0; i < w1s; ++i) {
            if(word1[i] != word2[j]) {
                ++diff;
                if(diff > 1) return false;
            } else {
                ++j;
            }
        } 
    } else if(w2s == w1s+1) {
        int j = 0;
        for(int i = 0; i < w2s; ++i) {
            if(word2[i] != word1[j]) {
                ++diff;
                if(diff > 1) return false;
            } else {
                ++j;
            }
        }
    } else {
        return false;
    }
    return true;
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> lq;
    vector<string> temp;
    temp.push_back(begin_word);
    lq.push(temp);
    set<string> visited;
    visited.insert(begin_word);
    while(!lq.empty()) {
        vector<string> ladder = lq.front();
        lq.pop();
        string lword = ladder[ladder.size()-1];
        for(string word : word_list) {
            if(is_adjacent(lword, word)) {
                if(visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder;
                    for(string word2 : ladder) {
                        new_ladder.push_back(word2);
                    }
                    new_ladder.push_back(word);
                    if(word == end_word) return new_ladder;
                    lq.push(new_ladder);
                }
            }
        }
    }
    cout << "no word found";
    return temp;
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    int limit = 45392;
    for(string word; (in >> word) && limit > 0; --limit) {
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    for(string word : ladder) {
        cout << word + " ";
    }
    cout << endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    print_word_ladder(generate_word_ladder("cat", "dog", word_list)); //4
    print_word_ladder(generate_word_ladder("marty", "curls", word_list)); //6
    print_word_ladder(generate_word_ladder("work", "play", word_list)); //6
    print_word_ladder(generate_word_ladder("sleep", "awake", word_list)); //8
    print_word_ladder(generate_word_ladder("car", "cheat", word_list)); //4
}