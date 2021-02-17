#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

const int ALPHABET_SIZE = numeric_limits<char>::max();

struct TrieNode {
  struct TrieNode *children[ALPHABET_SIZE];

  bool is_end_of_word;
};

TrieNode *get_node(void) {
  TrieNode *node = new TrieNode;
  node->is_end_of_word = false;
  for (int i = 0; i < ALPHABET_SIZE; i++) node->children[i] = NULL;
  return node;
}

void insert(TrieNode *root, string key) {
  int ord;
  TrieNode *node = root;

  for (int i = 0; i < key.length(); i++) {
    ord = key[i];
    if (node->children[ord] == NULL) node->children[ord] = get_node();
    node = node->children[ord];
  }

  node->is_end_of_word = true;
}

bool search(TrieNode *root, string key) {
  int ord;
  TrieNode *node = root;

  for (int i = 0; i < key.length(); i++) {
    ord = key[i];
    if ((node = node->children[ord]) == NULL) return false;
  }

  return (node != NULL && node->is_end_of_word);
}

bool has_children(TrieNode *root) {
  for (int i = 0; i < ALPHABET_SIZE; i++)
    if (root->children[i] != NULL) return true;
  return false;
}

TrieNode *remove(TrieNode *root, string key, int depth = 0) {
  if (root == NULL) return NULL;

  if (depth == key.length()) {
    if (root->is_end_of_word) root->is_end_of_word = false;
    if (!has_children(root)) {
      delete root;
      root = NULL;
    }
  } else {
    int ord = key[depth];
    root->children[ord] = remove(root->children[ord], key, depth + 1);
    if (!has_children(root) && !root->is_end_of_word) {
      delete root;
      root = NULL;
    }
  }
  return root;
}

int main() {
  string keys[] = {"hello", "there", "sir",   "how",
                   "are",   "you",   "doing", "today?"};

  struct TrieNode *root = get_node();
  for (string key : keys) insert(root, key);

  // Search for different keys
  search(root, "sir") ? cout << "Yes\n" : cout << "No\n";
  search(root, "signior") ? cout << "Yes\n" : cout << "No\n";
  search(root, "how") ? cout << "Yes\n" : cout << "No\n";
  remove(root, "how");
  search(root, "how") ? cout << "Yes\n" : cout << "No\n";
  search(root, "the") ? cout << "Yes\n" : cout << "No\n";
  return 0;
}
