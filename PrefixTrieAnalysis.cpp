#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>
using namespace std;

struct TriePrefix {
    map<char, unique_ptr<TriePrefix>> child;
    bool EndOfWord;
    TriePrefix() : EndOfWord(false) {}
   
};

class TriePSearch {
private:
    unique_ptr<TriePrefix> root;


    void findAllWords(TriePrefix* node, string currentWord, vector<string>& result) const {
        if (node == nullptr) {
            return;
        }


        if (node->EndOfWord) {
            result.push_back(currentWord);
        }


        for (auto const& [character, childPtr] : node->child) {
            findAllWords(childPtr.get(), currentWord + character, result);
        }

    }
    };

int main() {

    return 0;
}