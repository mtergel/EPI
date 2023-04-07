#include <list>
#include <unordered_map>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

using std::list;
using std::pair;
using std::unordered_map;

class LruCache {
 private:
  using Table = unordered_map<int, pair<list<int>::iterator, int>>;

  // Forces this key-value pair to move to the front.
  void MoveToFront(int isbn, const Table::iterator& it) {
    lru_queue_.erase(it->second.first);
    lru_queue_.emplace_front(isbn);
    it->second.first = begin(lru_queue_);
  }

  int capacity_;
  Table isbn_price_table_;
  list<int> lru_queue_;  // front recently, least recently

 public:
  LruCache(size_t capacity) { capacity_ = capacity; }
  int Lookup(int isbn) {
    auto it = isbn_price_table_.find(isbn);
    if (it == isbn_price_table_.end()) {
      return -1;
    } else {
      int price = it->second.second;
      MoveToFront(isbn, it);

      return price;
    }
  }
  void Insert(int isbn, int price) {
    auto it = isbn_price_table_.find(isbn);
    if (it != isbn_price_table_.end()) {
      MoveToFront(isbn, it);
    } else {
      if (isbn_price_table_.size() == capacity_) {
        isbn_price_table_.erase(lru_queue_.back());
        lru_queue_.pop_back();
      }

      lru_queue_.emplace_front(isbn);
      isbn_price_table_[isbn] = {lru_queue_.begin(), price};
    }

    return;
  }
  bool Erase(int isbn) {
    auto it = isbn_price_table_.find(isbn);
    if (it == isbn_price_table_.end()) {
      return false;
    } else {
      lru_queue_.erase(it->second.first);
      isbn_price_table_.erase(it);
      return true;
    }
  }
};

struct Op {
  std::string code;
  int arg1;
  int arg2;
};

namespace test_framework {
template <>
struct SerializationTrait<Op> : UserSerTrait<Op, std::string, int, int> {};
}  // namespace test_framework

void LruCacheTester(const std::vector<Op>& commands) {
  if (commands.empty() || commands[0].code != "LruCache") {
    throw std::runtime_error("Expected LruCache as first command");
  }
  LruCache cache(commands[0].arg1);

  for (int i = 1; i < commands.size(); i++) {
    auto& cmd = commands[i];
    if (cmd.code == "lookup") {
      int result = cache.Lookup(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Lookup: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else if (cmd.code == "insert") {
      cache.Insert(cmd.arg1, cmd.arg2);
    } else if (cmd.code == "erase") {
      bool result = cache.Erase(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Erase: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else {
      throw std::runtime_error("Unexpected command " + cmd.code);
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"commands"};
  return GenericTestMain(args, "lru_cache.cc", "lru_cache.tsv", &LruCacheTester,
                         DefaultComparator{}, param_names);
}
