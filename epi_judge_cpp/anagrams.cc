#include <string>
#include <unordered_map>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::unordered_map;
using std::vector;

vector<vector<string>> FindAnagrams(const vector<string>& dictionary) {
  unordered_map<string, vector<string>> m;
  for (auto word : dictionary) {
    string sorted_word = word;
    sort(sorted_word.begin(), sorted_word.end());

    m[sorted_word].emplace_back(word);
  }

  vector<vector<string>> res;
  for (const auto& p : m) {
    if (p.second.size() >= 2) {
      res.emplace_back(p.second);
    }
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"dictionary"};
  return GenericTestMain(args, "anagrams.cc", "anagrams.tsv", &FindAnagrams,
                         UnorderedComparator{}, param_names);
}
