/**
 * Self Balancing Binary Search Tree
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <limits>
#include <sstream>
#include <ctime>
#include <time.h>
#include <iomanip>
#include <map>
#include <assert.h>

using namespace std;

typedef vector<int> vi;
typedef vector<string> vs;
typedef long long ll;
typedef long long int lli;
typedef pair<int, int> pii;

class Node {
public:
  int height, data;
  Node *left, *right;

  Node() {
    left = NULL;
    right = NULL;
    data = 0;
    height = 1;
  }

  Node(int n) {
    left = NULL;
    right = NULL;
    data = n;
    height = 1;
  }
};

class SelfBalancingBinarySearchTree {
private:
  Node *root;
public:
  SelfBalancingBinarySearchTree() {
    root = NULL;
  }

  bool isEmpty() {
    return root == NULL;
  }

  void makeEmpty() {
    root = NULL;
  }

  int height(Node *n) {
    return n == NULL ? -1 : n->height;
  }

  int height() {
    return height(root);
  }

  int countNodes(Node *n) {
    if (n == NULL) {
      return 0;
    }
    int l = 1;
    l += countNodes(n->left);
    l += countNodes(n->right);
    return l;
  }

  int countNodes() {
    return countNodes(root);
  }

  Node *rotateWithLeftChild(Node* n) {
    Node *tmp = n->left;
    n->left = n->right;
    n->right = tmp;
    n->height = max(height(n->left), height(n->right)) + 1;
    tmp->height = max(height(tmp->right), n->height) + 1;
    return n;
  }

  Node *rotateWithRightChild(Node* n) {
    Node *tmp = n->right;
    n->right = n->left;
    n->left = tmp;
    n->height = max(height(n->left), height(n->right)) + 1;
    tmp->height = max(height(tmp->right), n->height) + 1;
    return n;
  }

  void insert(int data) {
    root = insert(data, root);
  }

  Node *insert(int data, Node *n) {
    if (n == NULL) {
      n = new Node(data);
    }

    return n;
  }

  // void insert(int data) {
  //   Node * node = new Node(data);
  // }

};


int main(int argc, const char **argv) {
  clock_t time = clock();

  SelfBalancingBinarySearchTree *t = new SelfBalancingBinarySearchTree();
  t->insert(10);
  assert(t->height() == 1);
  t->insert(8);
  assert(t->height() == 1);
  t->insert(6);
  assert(t->height() == 1);


  time = clock() - time;
  printf("Time %d clocks, %.3f milliseconds.\n",
         (int)time,
         ((float)time)/CLOCKS_PER_SEC * 1000);
  return 0;
}
