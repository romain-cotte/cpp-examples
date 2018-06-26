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

struct Node {
  int data;
  Node * next;
  Node(int n) : data(n) { }
};

class linkedList {
public:
  linkedList() {
    first = NULL;
  };

  void pushBack(int el) {
    Node * newNode = new Node(el);
    if (first == NULL) {
      first = newNode;
      return;
    }

    Node * p = first;
    while (p->next != NULL) {
      p = p->next;
    }
    p->next = newNode;
  }

  bool deleteNode(int el) {
    Node *curr = first;
    if (curr == NULL) { return false; }
    if (curr->data == el) {
      first = curr->next;
      delete curr;
      return true;
    }
    if (curr->next == NULL) {
      return false;
    }
    curr = curr->next;
    Node *prev = first;
    while (curr != NULL) {
      if (curr->data == el) {
        prev->next = curr->next;
        delete curr;
        return true;
      }
      prev = curr;
      curr = curr->next;
    }
    return false;
  }

  void print() {
    int i = 0;
    Node * p = first;
    cout << "[";
    while (p != NULL) {
      if (i++) {
        cout << ", " << p->data;
      } else {
        cout << p->data;
      }
      p = p->next;
    }
    cout << "]" << endl;
  }

private:
  Node * first;
};

int main(int argc, const char **argv) {
  clock_t time = clock();

  linkedList l = linkedList();

  l.pushBack(10);
  l.pushBack(15);
  l.pushBack(45);
  l.print();

  l.deleteNode(10);
  l.deleteNode(45);
  l.deleteNode(15);
  l.deleteNode(15);
  l.print();

  time = clock() - time;
  printf("Time %d clocks, %.3f milliseconds.\n",
         (int)time,
         ((float)time)/CLOCKS_PER_SEC * 1000);
  return 0;
}
