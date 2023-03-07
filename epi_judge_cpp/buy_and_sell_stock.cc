#include <limits>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
  double profit = 0;
  double to_buy = std::numeric_limits<double>::max();

  for (auto price : prices) {
    to_buy = std::min(price, to_buy);
    profit = std::max(profit, price - to_buy);
  }

  return profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
