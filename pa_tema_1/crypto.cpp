#include <bits/stdc++.h>

using namespace std;

struct Computer {
  long long coins;
  long long upgrade_cost;

  Computer(long long _coins, long long _upgrade_cost):
    coins(_coins), upgrade_cost(_upgrade_cost) {}
};

bool compByCoins(Computer & e1, Computer & e2) {
  return e1.coins < e2.coins;
}

bool compByUpgrade(Computer & e1, Computer & e2) {
  return e1.upgrade_cost < e2.upgrade_cost;
}

int main() {
  ifstream file("crypto.in");
  ofstream out("crypto.out");
  long long N, B;
  vector < Computer > computers;
  bool can_spend = true;

  file >> N;
  file >> B;

  for (long long i = 0, coins, upgrade_cost; i < N; i++) {
    file >> coins >> upgrade_cost;
    computers.push_back(Computer(coins, upgrade_cost));
  }

  file.close();

  sort(computers.begin(), computers.end(), compByCoins);

  for (long long i = 1; i < N; i++) {
    while ((computers[i].coins > computers[i - 1].coins) && (B > 0)) {
      can_spend = false;
      for (long long x = 0; x < i; x++) {
        if (B - computers[x].upgrade_cost >= 0) {
          computers[x].coins++;
          B -= computers[x].upgrade_cost;
          can_spend = true;
        } else {
          break;
        }
      }
      if (!can_spend)
        break;
    }
  }

  while (B > 0) {
    can_spend = false;
    for (int i = 0; i < N; i++) {
      if (B - computers[i].upgrade_cost >= 0) {
        computers[i].coins++;
        B -= computers[i].upgrade_cost;
        can_spend = true;
      } else {
        break;
      }
    }

    if (!can_spend)
      break;
  }

  sort(computers.begin(), computers.end(), compByCoins);
  out << computers[0].coins;

  out.close();
  return 0;
}
