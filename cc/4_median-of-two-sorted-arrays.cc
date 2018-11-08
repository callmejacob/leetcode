/**
There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

You may assume nums1 and nums2 cannot be both empty.

Example 1:

nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:

nums1 = [1, 2]
nums2 = [3, 4]
*/

#include <vector>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {

        int n1 = nums1.size();
        int n2 = nums2.size();

        vector<int> out;
        out.reserve(n1 + n2);

        int cur1 = 0;
        int cur2 = 0;
        int cur = 0;
        while (cur1 < n1 || cur2 < n2) {
            if (cur1 < n1 && cur2 < n2) {
                if (nums1[cur1] < nums2[cur2]) {
                    out[cur++] = nums1[cur1];
                    cur1++;
                } else {
                    out[cur++] = nums2[cur2];
                    cur2++;
                }
            } else if (cur1 < n1) {
                out[cur++] = nums1[cur1++];
            } else if (cur2 < n2) {
                out[cur++] = nums2[cur2++];
            }
        }

        int m1 = (n1 + n2) / 2;
        int m2 = m1 - (n1 + n2 + 1) % 2;

        return (out[m1] + out[m2]) / 2.0f;
    }
};

/**
// test
#include <iostream>

int main(int argc, char** argv) {
    std::vector<int> nums1 = {1, 2};
    std::vector<int> nums2 = {3, 4};

    Solution solution;
    auto ret = solution.findMedianSortedArrays(nums1, nums2);

    std::cout << "find median: " << ret << std::endl;

    return 0;
}
*/