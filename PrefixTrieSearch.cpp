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

int main() {

    return 0;
}