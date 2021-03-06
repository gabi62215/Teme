#include <bits/stdc++.h>

using namespace std;

int main() {
  long long N;
  vector < long long > mountain;

  ifstream file("valley.in");
  ofstream out("valley.out");

  file >> N;

  for (int i = 0; i < N; i++) {
    long long peak;
    file >> peak;
    mountain.push_back(peak);
  }

  long long c_st = -1;
  long long c_dr = -1;

  long long j = N - 1;

  long long cost = 0;

  long long min = * min_element(mountain.begin(), mountain.end());

  bool i_nex = false;
  bool j_nex = false;
  long long i = 0;

  for (long long i = 0; i < N - 1; i++) {
    if (mountain[i + 1] > mountain[i]) {
      c_st = i;
      break;
    }
  }

  for (long long j = N - 1; j > 0; j--) {
    if (mountain[j - 1] > mountain[j]) {
      c_dr = j;
      break;
    }
  }

  if (c_dr == -1) {
    cost = mountain[1] - mountain[0];
    mountain[1] = mountain[0];
    out << cost;
    out.close();
    file.close();
    return 0;
  }

  if (c_st == -1) {
    cost = mountain[N - 2] - mountain[N - 1];
    mountain[N - 2] = mountain[N - 1];
    out << cost;
    out.close();
    file.close();
    return 0;
  }

  if (N == 3) {
    if (mountain[1] > mountain[0] && mountain[0] > mountain[2]) {
      cost += mountain[2] - mountain[1];
    } else {
      cost += mountain[1] - mountain[1];
    }
    return 0;
  }

  while (i < j) {
    i_nex = false;
    j_nex = false;

    if (mountain[i] == min) {
      if (mountain[j] >= mountain[j - 1]) {
        j--;
        continue;
      } else {
        cost += mountain[j - 1] - mountain[j];
        mountain[j - 1] = mountain[j];
        j--;
        continue;
      }
    }

    if (mountain[j] == min) {
      if (mountain[i] >= mountain[i + 1]) {
        i++;
        continue;
      } else {
        cost += mountain[i + 1] - mountain[i];
        mountain[i + 1] = mountain[i];
        i++;
        continue;
      }
    }

    if (mountain[i] >= mountain[i + 1]) {
      i++;
      continue;
    } else {
      i_nex = true;
    }

    if (mountain[j] >= mountain[j - 1]) {
      j--;
      continue;
    } else {
      j_nex = true;
    }

    if (i_nex && j_nex) {
      if (mountain[j - 1] - mountain[j] < mountain[i + 1] - mountain[i]) {
        cost += mountain[j - 1] - mountain[j];
        mountain[j - 1] = mountain[j];
        j--;
      } else {
        cost += mountain[i + 1] - mountain[i];
        mountain[i + 1] = mountain[i];
        i++;
      }
    }

    if (i_nex == false && j_nex) {
      cost += mountain[j - 1] - mountain[j];
      mountain[j - 1] = mountain[j];
      j--;
    }

    if (i_nex && j_nex == false) {
      cost += mountain[i + 1] - mountain[i];
      mountain[i + 1] = mountain[i];
      i++;
    }
  }
  out << cost;
  out.close();
  file.close();
  return 0;
}
