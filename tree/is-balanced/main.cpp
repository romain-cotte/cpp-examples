/**
 * Implement a function to check if a binary tree is balanced. For the purposes
 * of this question, a balanced tree is defined to be a tree such that the
 * heights of the two subtrees of any node never differ by more than one.
 */

#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <unordered_set>
#include <map>
#include <set>
#include <sstream>
#include <time.h>
#include <vector>

using namespace std;
typedef vector<string> vs;
typedef long long ll;
typedef long long int lli;
typedef pair<int, int> pii;

struct Node {
  int key;
  Node *left;
  Node *right;
  Node(int k): key(k) {}
};

int height(Node *root) {
  if (root == NULL) return 0;
  return max(height(root->left), height(root->right));
}

bool isBalanced(Node *root) {
  if (root == NULL) return true;
  if (height(root->left) - height(root->right) > 1) {
    return false;
  }
  return isBalanced(root->left) && isBalanced(root->right);
}


int main(int argc, const char **argv) {
  Node *root = new Node(10);
  Node *l = new Node(3);
  Node *r = new Node(9);
  Node *rl = new Node(15);
  Node *rr = new Node(20);
  root->left = l;
  root->right = r;
  root->right->left = rl;
  root->right->right = rr;
  root->right->right->right = rr;
  std::cout << "isBalanced():" << isBalanced(root) << std::endl;
  return 0;
}
