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
    TriePSearch trie;


    trie.insert("Black Jaguar T-shirt");
    trie.insert("Blazer for UB's 25th Anniversy");
    trie.insert("Kinkajou UB T-Shirt Special");
    trie.insert("Bland UB Hoodie");
    trie.insert("Jaguar Pride T-shirt");
    trie.insert("Scented UB Candle");
    trie.insert("Jabiru UB T-shirt Special");
    trie.insert("Black Jaguar Joggers");
    trie.insert("Manatee UB T-Shirt Special");
    trie.insert("Scarlet Macaw UB T-Shirt Special");


    cout << "\nSearch 'Black': " << (trie.search("Black") ? "True" : "False") << endl;
    cout << "Search 'Bla': " << (trie.search("Bla") ? "True" : "False") << endl;
    cout << "Search 'Black Jaguar T-shirt': " << (trie.search("Black Jaguar T-shirt") ? "True" : "False") << endl;    
    cout << "Search 'Jaguar': " << (trie.search("Jaguar") ? "True" : "False") << endl;    
    cout << "\nStarts with 'Ja': " << (trie.beginsWith("Ja") ? "True" : "False") << endl;
    cout << "Starts with 'Bla': " << (trie.beginsWith("Bla") ? "True" : "False") << endl;
    cout << "Starts with 'Sc': " << (trie.beginsWith("Sc") ? "True" : "False") << endl;
    cout << "Starts with 'Ig': " << (trie.beginsWith("Ig") ? "True" : "False") << endl;
    return 0;
}