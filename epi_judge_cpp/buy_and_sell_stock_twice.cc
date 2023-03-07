#include <limits>
#include <vector>

#include "test_framework/generic_test.h"
using std::max;
using std::min;
using std::numeric_limits;
using std::vector;

double BuyAndSellStockTwice(const vector<double>& prices) {
  double profit_one = 0, profit_two = 0;
  double to_buy_one = numeric_limits<double>::max(),
         to_buy_two = numeric_limits<double>::max();

  for (auto& price : prices) {
    to_buy_one = min(to_buy_one, price);
    profit_one = max(profit_one, price - to_buy_one);

    to_buy_two = min(to_buy_two, price - profit_one);
    profit_two = max(profit_two, price - to_buy_two);
  }

  return profit_two;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
                         "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
                         DefaultComparator{}, param_names);
}
