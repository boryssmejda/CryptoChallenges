#include "ThreeSum.hpp"

#include <iostream>

UniqueTriples threeSum(std::vector<int>& nums)
{
    std::sort(nums.begin(), nums.end());
    UniqueTriples result;

    for(size_t i = 0; i < nums.size(); ++i)
    {
        if(i > 0 && nums[i] == nums[i-1])
        {
            continue;
        }

        size_t l {i+1};
        size_t r {nums.size() - 1};

        while(l < r)
        {
            int64_t sum = nums.at(l) + nums.at(r) + nums.at(i);
            if(sum == 0)
            {
                result.emplace_back(std::vector{nums[i], nums[l], nums[r]});
                ++l;
                while(l < r && nums[l] == nums[l-1])
                {
                    ++l;
                }
            }
            else if(sum > 0)
            {
                --r;
            }
            else
            {
                ++l;
            }
        }
    }

    return result;
}