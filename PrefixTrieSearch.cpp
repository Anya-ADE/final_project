#include <iostream>
#include <string>
#include <map>
#include <memory>
using namespace std;

struct TriePrefix {
    map<char, unique_ptr<TriePrefix>> child;
    bool EndOfWord;
    TriePrefix() : EndOfWord(false) {}
};

class TriePSearch {
private:
    unique_ptr<TriePrefix> root;


public:
    TriePSearch() {
        root = make_unique<TriePrefix>();
    }

    void insert(const string& word) {
        TriePrefix* curr = root.get();
        for (char a : word) {
            if (curr->child.find(a) == curr->child.end()) {
                curr->child[a] = make_unique<TriePrefix>();
            }
            curr = curr->child[a].get();
        }
        curr->EndOfWord = true;
    }

};

int main() {

    return 0;
}