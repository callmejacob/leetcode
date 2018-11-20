/**
Given a 32-bit signed integer, reverse digits of an integer.

Example 1:

Input: 123
Output: 321
Example 2:

Input: -123
Output: -321
Example 3:

Input: 120
Output: 21
Note:
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
*/

#include <string>

using namespace std;

class Solution {
public:
    int reverse(int x) {
        long y = 0;
        int q = 0;

        do {
            y = y * 10 + x % 10;
            x /= 10;
        } while (x);

        const long max = (2L << 30);
        if (y >= max || y <= -max) {
            return 0;
        }
        return y;
    }
};

/**
// test
#include <iostream>

int main(int argc, char** argv) {
    Solution solution;

    auto ret = solution.reverse(120);
    std::cout << "reverse result: " << ret << std::endl;

    ret = solution.reverse(123);
    std::cout << "reverse result: " << ret << std::endl;

    ret = solution.reverse(-2147483648);
    std::cout << "reverse result: " << ret << std::endl;

    std::cout << "2^31 = " << (2 << 30) - 1 << std::endl;

    return 0;
}
*/