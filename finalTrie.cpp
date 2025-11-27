#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <string>
using namespace std;




// -------------------- TRIE NODE --------------------
struct TrieNode {
    map<char, unique_ptr<TrieNode>> children;
    bool isEnd;


    TrieNode() : isEnd(false) {}
};




// -------------------- TRIE CLASS --------------------
class Trie {
private:
    unique_ptr<TrieNode> root;


    // Recursive delete helper
    bool deleteHelper(TrieNode* node, const string& word, int depth) {
        if (!node) return false;


        if (depth == word.size()) {
            if (!node->isEnd) return false;
            node->isEnd = false;
            return node->children.empty();
        }


        char c = word[depth];
        if (node->children.find(c) == node->children.end())
            return false;


        if (deleteHelper(node->children[c].get(), word, depth + 1)) {
            node->children.erase(c);
            return !node->isEnd && node->children.empty();
        }


        return false;
    }


    // Recursive word collection for prefix search
    void collect(TrieNode* node, const string& prefix, vector<string>& result) {
        if (!node) return;


        if (node->isEnd)
            result.push_back(prefix);


        for (auto& pair : node->children)
            collect(pair.second.get(), prefix + pair.first, result);
    }


public:
    Trie() {
        root = make_unique<TrieNode>();
    }


    // Insert a word
    void insert(const string& word) {
        TrieNode* cur = root.get();
        for (char c : word) {
            if (cur->children.find(c) == cur->children.end())
                cur->children[c] = make_unique<TrieNode>();
            cur = cur->children[c].get();
        }
        cur->isEnd = true;
    }


    // Search exact word
    bool search(const string& word) {
        TrieNode* cur = root.get();
        for (char c : word) {
            if (cur->children.find(c) == cur->children.end())
                return false;
            cur = cur->children[c].get();
        }
        return cur->isEnd;
    }


    // Delete word
    void remove(const string& word) {
        deleteHelper(root.get(), word, 0);
    }


    // Prefix search
    vector<string> prefixSearch(const string& prefix) {
        TrieNode* cur = root.get();
        for (char c : prefix) {
            if (cur->children.find(c) == cur->children.end())
                return {};
            cur = cur->children[c].get();
        }


        vector<string> result;
        collect(cur, prefix, result);
        return result;
    }
};




// -------------------- MAIN PROGRAM --------------------
int main() {
    Trie trie;


    // Dataset #1 - Keywords
    vector<string> keywords = {
           "apple","arrow","breeze","bucket","butter",
    "cactus","castle","circle","crystal","dragon",
    "daisy","dance","ember","engine","eagle",
    "energy","feather","forest","flame","galaxy",
    "garden","guitar","harvest","hollow","ivory",
    "island","jungle","jacket","kingdom","kitten",
    "lantern","legend","lemon","meadow","mirror",
    "nebula","northern","oasis","oxygen","petal",
    "puzzle","quartz","quiver","ribbon","rookie",
    "shadow","starling","thunder","unicorn","velvet",
    "whisper","yonder","zephyr"
    };


    // Dataset #2 - Phrases
    vector<string> phrases = {
        "Black Jaguar T-shirt",
        "Blazer for UB's 25th Anniversy",
        "Kinkajou UB T-Shirt Special",
        "Bland UB Hoodie",
        "Jaguar Pride T-shirt",
        "Scented UB Candle",
        "Jabiru UB T-shirt Special",
        "Black Jaguar Joggers",
        "Manatee UB T-Shirt Special",
        "Scarlet Macaw UB T-Shirt Special"
    };


    // Insert both data sets
    for (auto& w : keywords) trie.insert(w);
    for (auto& p : phrases) trie.insert(p);


    int choice;
    string input;


    while (true) {
        cout << "\n--------- TRIE SEARCH SYSTEM ---------\n";
        cout << "1. Insert Word/Phrase\n";
        cout << "2. Search Word/Phrase\n";
        cout << "3. Delete Word/Phrase\n";
        cout << "4. Prefix Search (Auto-Complete)\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // Fix space input from getline


        switch (choice) {
        case 1:
            cout << "Enter word/phrase: ";
            getline(cin, input);
            trie.insert(input);
            cout << "Inserted.\n";
            break;


        case 2:
            cout << "Search for: ";
            getline(cin, input);
            cout << (trie.search(input) ? "FOUND\n" : "NOT FOUND\n");
            break;


        case 3:
            cout << "Enter word/phrase to delete: ";
            getline(cin, input);
            trie.remove(input);
            cout << "Deleted (if existed).\n";
            break;


        case 4:
            cout << "Enter prefix: ";
            getline(cin, input);
            {
                vector<string> results = trie.prefixSearch(input);
                cout << "\nMatches (" << results.size() << "):\n";
                for (auto& r : results)
                    cout << " - " << r << endl;
            }
            break;


        case 5:
            return 0;


        default:
            cout << "Invalid option.\n";
        }
    }
}

