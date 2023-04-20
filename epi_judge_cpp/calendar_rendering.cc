#include <algorithm>
#include <map>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Event {
  int start, finish;
};

struct Endpoint {
  bool operator<(const Endpoint& that) const {
    return time != that.time ? time < that.time : (isStart && !that.isStart);
  }

  int time;
  bool isStart;
};

int FindMaxSimultaneousEvents(const vector<Event>& A) {
  vector<Endpoint> E;
  for (const Event& event : A) {
    E.emplace_back(Endpoint{event.start, true});
    E.emplace_back(Endpoint{event.finish, false});
  }

  sort(E.begin(), E.end());
  int res = 0, count = 0;

  for (const Endpoint& endpoint : E) {
    if (endpoint.isStart) {
      ++count;

      res = std::max(res, count);
    } else {
      --count;
    }
  }

  return res;
}
namespace test_framework {
template <>
struct SerializationTrait<Event> : UserSerTrait<Event, int, int> {};
}  // namespace test_framework

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "calendar_rendering.cc",
                         "calendar_rendering.tsv", &FindMaxSimultaneousEvents,
                         DefaultComparator{}, param_names);
}
