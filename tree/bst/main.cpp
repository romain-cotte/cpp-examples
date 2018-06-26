/**
 * Binary Search Tree
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


struct node {
  int key;
  node *left;
  node *right;
  node(int k): key(k) {
    left = NULL;
    right = NULL;
  }
};

class binaryTree {
public:
  binaryTree();
  ~binaryTree();

  void insert(int key);
  bool search(int key);
  void destroyTree();
  int countNodes();
  void print();

private:
  void destroyTree(node *n);
  void insert(int key, node *n);
  bool search(int key, node *n);
  int countNodes(node *n);
  void print(node *n);

  node *root;
};


binaryTree::binaryTree() {
  root = NULL;
}

void binaryTree::destroyTree(node *n) {
  if (n != NULL) {
    destroyTree(n->right);
    destroyTree(n->left);
    delete n;
  }
}

void binaryTree::destroyTree() {
  destroyTree(root);
}

binaryTree::~binaryTree() {
  destroyTree();
}


void binaryTree::insert(int key, node *n) {
  if (n->key < key) {
    if (n->left == NULL) {
      n->left = new node(key);
    } else {
      insert(key, n->left);
    }
  } else {
    if (n->right == NULL) {
      n->right = new node(key);
    } else {
      insert(key, n->right);
    }
  }
}

void binaryTree::insert(int key) {
  if (root == NULL) {
    root = new node(key);
  } else {
    insert(key, root);
  }
}

void binaryTree::print(node *n) {
  if (n == NULL) {
    return;
  }
  cout << n->key << endl;
  print(n->left);
  print(n->right);
}

void binaryTree::print() {
  if (root == NULL) {
    cout << "Empty tree" << endl;
    return;
  }
  print(root);
}

bool binaryTree::search(int key, node *n) {
  if (n == NULL) {
    return false;
  }

  if (n->key == key) {
    return true;
  }

  return search(key, n->left) || search(key, n->right);
}

bool binaryTree::search(int key) {
  return search(key, root);
}

int binaryTree::countNodes(node *n) {
  if (n == NULL) {
    return 0;
  }
  return 1 + countNodes(n->left) + countNodes(n->right);
}

int binaryTree::countNodes() {
  return countNodes(root);
}

int main(int argc, const char **argv) {
  clock_t time = clock();

  binaryTree *t = new binaryTree();
  t->insert(10);
  t->insert(15);
  t->insert(13);
  t->insert(13);
  t->insert(13);
  t->print();

  cout << "t->search(13):" << t->search(13) << endl;
  cout << t->countNodes() << endl;


  // assert(t->height() == 1);
  // t->insert(8);
  // assert(t->height() == 1);
  // t->insert(6);
  // assert(t->height() == 1);

  t->destroyTree();

  time = clock() - time;
  printf("Time %d clocks, %.3f milliseconds.\n",
         (int)time,
         ((float)time)/CLOCKS_PER_SEC * 1000);
  return 0;
}
