#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::reverse;
using std::string;

void ReverseWords(string* s) {
  // clean solution
  reverse(s->begin(), s->end());
  size_t start = 0, end;

  while ((end = s->find(" ", start)) != string::npos) {
    reverse(s->begin() + start, s->begin() + end);
    start = end + 1;
  }

  reverse(s->begin() + start, s->end());
  return;

  // // initial
  // string& words = *s;
  // int l = 0, r = words.size() - 1;
  // while (l < r) {
  //   swap(words[l++], words[r--]);
  // }
  //
  // l = 0, r = 0;
  // while (r < words.size()) {
  //   if (isspace(words[r])) {
  //     reverse(words.begin() + l, words.begin() + r);
  //     l = r;
  //     ++l;
  //   }
  //   ++r;
  // }
  //
  // // reverse final word
  // reverse(words.begin() + l, words.end());
  //
  // return;
}
string ReverseWordsWrapper(TimedExecutor& executor, string s) {
  string s_copy = s;

  executor.Run([&] { ReverseWords(&s_copy); });

  return s_copy;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "s"};
  return GenericTestMain(args, "reverse_words.cc", "reverse_words.tsv",
                         &ReverseWordsWrapper, DefaultComparator{},
                         param_names);
}
