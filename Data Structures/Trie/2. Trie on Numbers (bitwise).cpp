struct TrieNode {
    TrieNode* children[2];
    TrieNode()
    {
        children[0] = children[1] = nullptr;
    }
};

struct Trie {
    TrieNode* root;
    Trie()
    {
        root = new TrieNode();
    }
    void insert(int num)
    {
        TrieNode* node = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!node->children[bit]) {
                node->children[bit] = new TrieNode();
            }
            node = node->children[bit];
        }
    }
    int maxXor(int num)
    {
        TrieNode* node = root;
        int res = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (node->children[1 - bit]) {
                res |= (1LL << i);
                node = node->children[1 - bit];
            } else if (node->children[bit]) {
                node = node->children[bit];
            } else {
                break;
            }
        }
        return res;
    }
};