#include <iterator>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::swap;
using std::unordered_map;
using std::vector;

struct Person {
  int age;
  string name;
};

void GroupByAge(vector<Person>* people) {
  unordered_map<int, int> m;  // age <-> count
  for (const Person& p : *people) {
    m[p.age]++;
  }

  unordered_map<int, int> age_to_idx;  // age <-> idx
  int idx = 0;

  for (const auto& p : m) {
    age_to_idx[p.first] = idx;
    idx += p.second;
  }

  while (!age_to_idx.empty()) {
    auto from = age_to_idx.begin();
    auto to = age_to_idx.find((*people)[from->second].age);
    swap((*people)[from->second], (*people)[to->second]);

    // use m to see when we are finished with a particular age
    --m[to->first];
    if (m[to->first] > 0) {
      ++to->second;
    } else {
      age_to_idx.erase(to);
    }
  }

  return;
}

namespace test_framework {
template <>
struct SerializationTrait<Person> : UserSerTrait<Person, int, string> {};
}  // namespace test_framework

void GroupByAgeWrapper(TimedExecutor& executor, vector<Person>& people) {
  if (people.empty()) {
    return;
  }
  std::multiset<Person, std::function<bool(Person, Person)>> values(
      begin(people), end(people), [](const Person& a, const Person& b) {
        return a.age == b.age ? a.name < b.name : a.age < b.age;
      });

  executor.Run([&] { GroupByAge(&people); });

  if (people.empty()) {
    throw TestFailure("Empty result");
  }

  std::set<int> ages;
  int last_age = people[0].age;
  for (auto& x : people) {
    if (ages.count(x.age)) {
      throw TestFailure("Entries are not grouped by age");
    }
    if (x.age != last_age) {
      ages.insert(last_age);
      last_age = x.age;
    }
    auto it = values.find(x);
    if (it == end(values)) {
      throw TestFailure("Entry set changed");
    }
    values.erase(it);
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "people"};
  return GenericTestMain(args, "group_equal_entries.cc",
                         "group_equal_entries.tsv", &GroupByAgeWrapper,
                         DefaultComparator{}, param_names);
}
