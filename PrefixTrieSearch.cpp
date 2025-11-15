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
};

int main() {

    return 0;
}