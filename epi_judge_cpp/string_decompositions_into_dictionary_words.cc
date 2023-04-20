#include <string>
#include <unordered_map>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::unordered_map;
using std::vector;

bool MatchAllWordInDict(const string& s, const unordered_map<string, int>& m,
                        int start, int num_words, int word_len) {
  unordered_map<string, int> currM;
  for (int i = 0; i < num_words; ++i) {
    string curr_word = s.substr(start + i * word_len, word_len);
    auto iter = m.find(curr_word);

    if (iter == m.end()) {
      return false;
    }

    ++currM[curr_word];

    // curr word larger than word in m
    if (currM[curr_word] > iter->second) {
      return false;
    }
  }

  return true;
}
vector<int> FindAllSubstrings(const string& s, const vector<string>& words) {
  unordered_map<string, int> m;
  for (auto& w : words) {
    ++m[w];
  }

  int word_len = words[0].size();
  vector<int> res;
  for (int i = 0; i + word_len * words.size() <= s.size(); i++) {
    if (MatchAllWordInDict(s, m, i, words.size(), word_len)) {
      res.emplace_back(i);
    }
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s", "words"};
  return GenericTestMain(args, "string_decompositions_into_dictionary_words.cc",
                         "string_decompositions_into_dictionary_words.tsv",
                         &FindAllSubstrings, DefaultComparator{}, param_names);
}
