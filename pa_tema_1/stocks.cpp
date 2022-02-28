#include <bits/stdc++.h>

using namespace std;

struct Action {
  int current_value;
  int loss;
  int profit;

  Action(int _current_value, int _loss, int _profit):
    current_value(_current_value), loss(_loss), profit(_profit) {}
};

int main() {
  ifstream file("stocks.in");
  ofstream out("stocks.out");
  vector < Action > actions;

  int N, B, L;

  file >> N >> B >> L;

  actions.push_back(Action(-1, -1, -1));
  for (int i = 1, current_value, min_value, max_value; i <= N; i++) {
    file >> current_value >> min_value >> max_value;
    actions.push_back(Action(current_value,
    current_value - min_value, max_value - current_value));
  }

  file.close();

  vector < vector < vector < int >>> dp(N + 1,
  vector < vector < int >> (B + 1, vector < int > (L + 1, 0)));

  for (int i = 0; i <= B; i++)
    for (int j = 0; j <= L; j++)
      dp[0][i][j] = 0;

  for (int i = 1; i <= N; i++) {
    for (int j = 0; j <= B; j++) {
      for (int k = 0; k <= L; k++) {
        dp[i][j][k] = dp[i - 1][j][k];

        if (j - actions[i].current_value >= 0 && k - actions[i].loss >= 0) {
          int sol_aux = dp[i - 1][j - actions[i].current_value][k -
                        actions[i].loss] + actions[i].profit;

          dp[i][j][k] = max(sol_aux, dp[i - 1][j][k]);
        }
      }
    }
  }

  cout << dp[N][B][L] << endl;
  out << dp[N][B][L] << endl;
  out.close();

  return 0;
}
