typedef struct TrieNode {
    char character;
    struct TrieNode* children[26];
    bool isEndOfWord;
} TrieNode;

TrieNode* createNode(char c) {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->character = c;
    for (int i = 0; i < 26; i++) node->children[i] = NULL;
    node->isEndOfWord = false;
    return node;
}

void insertWord(TrieNode* root, const char* word) {
    TrieNode* currentNode = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (currentNode->children[index] == NULL) {
            currentNode->children[index] = createNode(word[i]);
        }
        currentNode = currentNode->children[index];
    }
    currentNode->isEndOfWord = true;
}

bool canSegmentString(TrieNode* root, const char* s, int start, int* memo, int s_len) {
    if (start == s_len) return true;

    if (memo[start] != -1) return memo[start] == 1;

    TrieNode* currentNode = root;
    for (int i = start; i < s_len; i++) {
        int index = s[i] - 'a';
        if (currentNode->children[index] == NULL) {
            memo[start] = 0;
            return false;
        }
        currentNode = currentNode->children[index];
        if (currentNode->isEndOfWord && canSegmentString(root, s, i + 1, memo, s_len)) {
            memo[start] = 1;
            return true;
        }
    }
    memo[start] = 0;
    return false;
}

bool wordBreak(char* s, char** wordDict, int wordDictSize) {
    TrieNode* root = createNode('\0');
    for (int i = 0; i < wordDictSize; i++) {
        insertWord(root, wordDict[i]);
    }
    int s_len = strlen(s);
    int* memo = (int*)malloc(s_len * sizeof(int));
    for (int i = 0; i < s_len; i++) memo[i] = -1;
    bool result = canSegmentString(root, s, 0, memo, s_len);
    free(memo);
    return result;
}