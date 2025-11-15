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

    vector<string> getWordsWithPrefix(const string& prefix) const {
        vector<string> result;
        TriePrefix* curr = root.get();
        for (char c : prefix) {
            if (curr->child.find(c) == curr->child.end()) {
                return result;
            }
            curr = curr->child.at(c).get();
        }
        findAllWords(curr, prefix, result);
        return result;
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

    cout << endl;
   
    string prefix1 = "Bla";
    vector<string> words1 = trie.getWordsWithPrefix(prefix1);
    cout << "Words starting with '" << prefix1 << "':" << endl;
    for (const string& word : words1) {
        cout << "- " << word << endl;
    }

    cout <<  endl;

    string prefix2 = "Jaguar";
    vector<string> words2 = trie.getWordsWithPrefix(prefix2);
    cout << "Words starting with '" << prefix2 << "':" << endl;
    for (const string& word : words2) {
        cout << "- " << word << endl;
    }

    return 0;
}