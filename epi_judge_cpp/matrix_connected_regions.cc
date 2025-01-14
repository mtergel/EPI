#include <deque>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::deque;
using std::vector;

void helper(int x, int y, bool color, vector<deque<bool>> *image_ptr) {
  vector<deque<bool>> &image = *image_ptr;
  int n = image.size();
  int m = image[0].size();

  if (x < 0 || y < 0 || x >= n || y >= m || image[x][y] != color) {
    return;
  }

  image[x][y] = !color;

  helper(x + 1, y, color, image_ptr);
  helper(x - 1, y, color, image_ptr);
  helper(x, y + 1, color, image_ptr);
  helper(x, y - 1, color, image_ptr);
}

void FlipColor(int x, int y, vector<deque<bool>> *image_ptr) {

  helper(x, y, (*image_ptr)[x][y], image_ptr);

  return;
}
vector<vector<int>> FlipColorWrapper(TimedExecutor &executor, int x, int y,
                                     vector<vector<int>> image) {
  vector<deque<bool>> b;
  b.reserve(image.size());
  for (const vector<int> &row : image) {
    deque<bool> tmp;
    tmp.resize(row.size());
    for (int i = 0; i < row.size(); ++i) {
      tmp[i] = static_cast<bool>(row[i]);
    }
    b.push_back(tmp);
  }

  executor.Run([&] { FlipColor(x, y, &b); });

  image.resize(b.size());

  for (int i = 0; i < image.size(); ++i) {
    image[i].resize(b.size());
    for (int j = 0; j < image[i].size(); ++j) {
      image[i][j] = b[i][j];
    }
  }
  return image;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "x", "y", "image"};
  return GenericTestMain(args, "matrix_connected_regions.cc", "painting.tsv",
                         &FlipColorWrapper, DefaultComparator{}, param_names);
}
