#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <mutex>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <thread>
#include <time.h>
#include <vector>


#define INF 2E9
#define INF64 4E18

using namespace std;

template<class T1, class T2> void pr(const pair<T1,T2>& x);
template<class T, size_t SZ> void pr(const array<T,SZ>& x);
template<class T> void pr(const vector<T>& x);
template<class T> void pr(const deque<T>& x);
template<class T, class C> void pr(const set<T,C>& x);
template<class T, class C> void pr(const multiset<T,C>& x);
template<class T1, class T2> void pr(const map<T1,T2>& x);
template<class... T> void pr(const tuple<T...>& tup);

const string COLOR_RESET = "\033[0m", GREEN = "\033[1;32m";
template<class T> void pr(const T& x) { cout << GREEN << x << COLOR_RESET; }


template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) {
  pr(first); pr(rest...);
}
template<class T1, class T2> void pr(const pair<T1,T2>& x) {
  pr("{",x.first,", ",x.second,"}");
}
template<class T> void prContain(const T& x) {
  pr("{");bool fst = 1; for(auto &a: x) pr(!fst?", ":"",a), fst = 0;pr("}");
}
template<class T, size_t SZ> void pr(const array<T,SZ>& x) { prContain(x); }
template<class T> void pr(const vector<T>& x) { prContain(x); }
template<class T> void pr(const deque<T>& x) { prContain(x); }
template<class T, class C> void pr(const set<T,C>& x) { prContain(x); }
template<class T, class C> void pr(const multiset<T,C>& x) { prContain(x); }
template<class T1, class T2> void pr(const map<T1,T2>& x) { prContain(x); }

template<class T, size_t... I>
void pr(const T& tup, index_sequence<I...>) {
  pr("("); (..., (cout << (I == 0? "" : ", ") << get<I>(tup))); pr(")");
}
template<class... T>
void pr (const tuple<T...>& tup) {
  pr(tup, make_index_sequence<sizeof...(T)>());
}
void ps() { pr("\n"); }
void _ps_continue() { pr("\n"); }
template<class Arg, class... Args> void _ps_continue(const Arg& first, const Args&... rest) {
  pr(" ", first); _ps_continue(rest...);
}

#ifdef DEBUG_LOCAL
template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) {
  pr(first); _ps_continue(rest...);
}
#else
template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) {}
#endif

template<typename T> int remin(T& a,const T& b){if(b<a){a=b;return true;}return false;}
template<typename T> int remax(T& a,const T& b){if(a<b){a=b;return true;}return false;}

typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<>dist(0, 10);
uniform_int_distribution<>dist_1_100(1, 100);
uniform_int_distribution<>dist_0_20(0, 20);


class Account {
private:
  int balance = 0;
public:
  mutable recursive_mutex mutex_account;
  Account(){}
  ~Account(){}
  Account(int _balance) : balance(_balance) {}
  Account(const Account &t) {
    t.mutex_account.lock();
    balance = t.balance;
    t.mutex_account.unlock();
  }


  void credit(int val) {
    lock_guard<recursive_mutex> lg(mutex_account);
    // mutex_account.lock();
    balance += val;
    // mutex_account.unlock();
  }
  int get_balance() const {
    lock_guard<recursive_mutex> lg(mutex_account);
    return balance;
  }
  bool debit(int val) {
    lock_guard<recursive_mutex> lg(mutex_account);
    // mutex_account.lock();
    bool ret;
    if (balance >= val) {
      balance -= val;
      ret = true;
    } else {
      ret = false;
    }
    // mutex_account.unlock();
    return ret;
  }
};


class Bank {
private:
  vector<Account> accounts;
public:
  Bank(int k, int initial_balance) {
    for (int i = 0; i < k; ++i) {
      accounts.emplace_back(initial_balance);
    }
  }
  ~Bank() {}

  bool transfer(int id_debit, int id_credit, int val) {
    int ret = false;
    cout << "Try to transfer " << val << " from " << id_debit << " to " << id_credit << endl;
    if (id_debit < (int) accounts.size() && id_credit < (int)accounts.size()) {
      Account a = accounts[id_debit];
      Account b = accounts[id_credit];
      a.mutex_account.lock(); b.mutex_account.lock();
      if (a.debit(val)) {
        accounts[id_credit].credit(val);
        cout << "Success" << endl;
        ret = true;
      }
      a.mutex_account.unlock(); b.mutex_account.unlock();
    }
    if (!ret) cout << "Failure" << endl;
    return ret;
  }
};



void transaction(int k, Bank &bank) {
  int val = dist_1_100(gen);
  uniform_int_distribution<>dist(0, k-1);
  int i = dist(gen), j = dist(gen);
  bank.transfer(i, j, val);
  this_thread::sleep_for(chrono::milliseconds(dist_0_20(gen)));
}


void jackpot(Account *c, int id) {
  cout << "Started " << id << endl;
  for (int i = 0; i < 10000; ++i) {
    c->credit(1);
  }
  cout << "end " << id << endl;
}

void losepot(Account *c, int id) {
  cout << "Lose started " << id << endl;
  for (int i = 0; i < 10000; ++i) {
    c->debit(10);
  }
  cout << "Lose ended " << id << endl;
}

int create_and_wait(int n) {
  Account *account = new Account();
  account->credit(100000);
  cout << account->get_balance() << endl;

  vector<thread> vt;
  for (int i = 0; i < n; ++i) {
    vt.emplace_back(thread(&losepot, account, i));
  }

  for (int i = 0; i < n; ++i) {
    vt[i].join();
  }
  cout << account->get_balance() << endl;
  return 0;
}


int main(int argc, const char **argv) {
  srand(::time(nullptr));

  const int K = 5;
  const int initial_balance = 100;
  const int threads = 10000;
  Bank bank(K, initial_balance);

  vector<thread> vt;
  for (int i = 0; i < threads; ++i) {
    vt.emplace_back(thread(&transaction, K, ref(bank)));
  }

  for (thread &t: vt) {
    t.join();
  }


  return 0;
  // return create_and_wait(1000);
}
