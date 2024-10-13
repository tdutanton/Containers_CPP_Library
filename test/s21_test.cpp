#include "s21_test.h"

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  int failed = RUN_ALL_TESTS();
  return failed;
}
