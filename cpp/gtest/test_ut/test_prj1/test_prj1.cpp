#include "status.h"
#include "gtest/gtest.h"

TEST(AdditionTest, HandlesPositiveInput) {
    EXPECT_EQ(Add(1, 2), 3);
}

TEST(AdditionTest, HandlesZeroInput) {
    EXPECT_EQ(Add(0, 0), 0);
}  

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}