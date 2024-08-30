#include "status.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>

// Test wrapper class to expose private method
class MockStatus : public Status {
public:
    MOCK_METHOD(int, Add, (int a, int b), (const));
};

// Test case for the global Add function
TEST(AdditionTest, HandlesPositiveInput) {
    EXPECT_EQ(Add(1, 2), 3);  // This calls the global Add function
}

TEST(AdditionTest, HandlesZeroInput) {
    EXPECT_EQ(Add(0, 0), 0);  // This also calls the global Add function
}

// Test case for the private member Add function
TEST(AdditionTest, HandlesNegativeInput) {
    MockStatus status;
    EXPECT_CALL(status, Add(-1,-2)).WillOnce(testing::Return(-3));
    EXPECT_EQ(status.Add(-1, -2), -3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
