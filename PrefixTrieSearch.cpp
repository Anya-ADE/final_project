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

    bool search(const string& word) const {
        TriePrefix* curr = root.get();
        for (char b : word) {
            if (curr->child.find(b) == curr->child.end()) {
                return false;
            }
            curr = curr->child.at(b).get();
        }
        return curr != nullptr && curr->EndOfWord;
    }


    bool beginsWith(const string& prefix) const {
        TriePrefix* curr = root.get();
        for (char c : prefix) {
            if (curr->child.find(c) == curr->child.end()) {
                return false;
            }
            curr = curr->child.at(c).get();
        }
        return true;
    }

};

int main() {

    return 0;
}