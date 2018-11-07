/**
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
*/

#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::map<int, int> related;

        for (int i = 0; i < nums.size(); i++) {
            auto other = target - nums[i];
            auto iter = related.find(other);
            if (iter != related.end()) {
                std::vector<int> ret;
                ret.push_back(iter->second);
                ret.push_back(i);
                return ret;
            }
            related.insert(pair<int, int>(nums[i], i));
        }

        return vector<int>();
    }
};


// test
/**
#include <iostream>

int main(int argc, char** argv) {
    vector<int> nums = {2, 7, 11, 15};
    auto target = 9;

    Solution solution;
    auto result = solution.twoSum(nums, target);

    cout << result.size() << endl;;
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << endl;
    }

    return 0;
}
*/