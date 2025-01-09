#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;
    TrieNode()
    {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

struct Trie {
    TrieNode* root;
    Trie()
    {
        root = new TrieNode();
    }
    void insert(const string& word)
    {
        TrieNode* node = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }
    bool search(const string& word)
    {
        TrieNode* node = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!node->children[index])
                return false;
            node = node->children[index];
        }
        return node->isEndOfWord;
    }
    bool startsWith(const string& prefix)
    {
        TrieNode* node = root;
        for (char ch : prefix) {
            int index = ch - 'a';
            if (!node->children[index])
                return false;
            node = node->children[index];
        }
        return true;
    }
};

int main()
{
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("bat");

    cout << (trie.search("app") ? "Found 'app'\n" : "Not Found 'app'\n"); // Found 'app'
    cout << (trie.search("bat") ? "Found 'bat'\n" : "Not Found 'bat'\n"); // Found 'bat'
    cout << (trie.search("cat") ? "Found 'cat'\n" : "Not Found 'cat'\n"); // Not Found 'cat'
    cout << (trie.startsWith("ap") ? "Prefix 'ap' exists\n" : "Prefix 'ap' doesn't exist\n"); // Prefix 'ap' exists
    cout << (trie.startsWith("ca") ? "Prefix 'ca' exists\n" : "Prefix 'ca' doesn't exist\n"); // Prefix 'ca' doesn't exist

    return 0;
}
