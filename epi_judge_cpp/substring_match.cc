#include <string>

#include "test_framework/generic_test.h"
using std::string;

// Returns the index of the first character of the substring if found, -1
// otherwise.
// Drawback: Need to have a good hash function to reduce collision
int RabinKarp(const string &t, const string &s) {
  if (s.size() > t.size()) {
    return -1;
  }

  // Addtive hash function (Rolling hash)
  const int kBase = 26;
  int t_hash = 0, s_hash = 0;  // hash codes
  int power_s = 1;             // kBase^|s|

  // get hash codes
  for (int i = 0; i < s.size(); ++i) {
    power_s = i ? power_s * kBase : 1;
    t_hash = t_hash * kBase + t[i];
    s_hash = s_hash * kBase + s[i];
  }

  // sliding window, check substrings
  for (int i = s.size(); i < t.size(); ++i) {
    if (t_hash == s_hash && !t.compare(i - s.size(), s.size(), s)) {
      return i - s.size();
    }

    t_hash -= t[i - s.size()] * power_s;
    t_hash = t_hash * kBase + t[i];
  }

  if (t_hash == s_hash && t.compare(t.size() - s.size(), s.size(), s) == 0) {
    return t.size() - s.size();
  }

  return -1;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"t", "s"};
  return GenericTestMain(args, "substring_match.cc", "substring_match.tsv",
                         &RabinKarp, DefaultComparator{}, param_names);
}
