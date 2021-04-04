#include "gtest/gtest.h"

#include "ThreeSum.hpp"

#include <vector>

namespace three_sum
{
    struct TestParameters
    {
        std::vector<int> input;
        UniqueTriples expectedResult;
    };
}

class TestThreeSumImplementation : public ::testing::TestWithParam<three_sum::TestParameters>
{};

TEST_P(TestThreeSumImplementation, test_input)
{
    auto [input, expectedResult] = GetParam();
    const auto result = threeSum(input);

    ASSERT_EQ(result.size(), expectedResult.size());
}

INSTANTIATE_TEST_CASE_P(TestInput, TestThreeSumImplementation, ::testing::Values(
    three_sum::TestParameters{std::vector{0}, UniqueTriples{}},
    three_sum::TestParameters{std::vector{0, 0}, UniqueTriples{}},
    three_sum::TestParameters{std::vector{0, 0, 0}, std::vector{{std::vector{0,0,0}}}},
    three_sum::TestParameters{std::vector{0, 0, 0, 0}, std::vector{{std::vector{0,0,0}}}},

    three_sum::TestParameters{std::vector{-1, 0, 1, 2, -1, -4},
        std::vector{
            {
                std::vector{-1, 0, 1},
                std::vector{-1, -1, 2}
            }
        }
    },

    three_sum::TestParameters{std::vector{-1,0,1,2,-1,-4,-2,-3,3,0,4},
        std::vector{
            {
                std::vector{-4,  0, 4},
                std::vector{-4,  1, 3},
                std::vector{-3, -1, 4},
                std::vector{-3,  0, 3},
                std::vector{-3,  1, 2},
                std::vector{-2, -1, 3},
                std::vector{-2,  0, 2},
                std::vector{-1, -1, 2},
                std::vector{-1,  0, 1}
            }
        }
    }
));
