/**
Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example 2:

Input: "cbbd"
Output: "bb"
*/

#include <string>

using namespace std;

#include <iostream>

class Solution {
public:
    string longestPalindrome(string s) {

        int max_len = 0;
        int max_start = 0;
        for (int i = 0; i < s.length(); i++) {
            int len = s.length() - i;
            if (len > i) len = i + 1;
            int find_len = 0;
            for (int k = 1; k < len; k++) {
                if (s[i - k] == s[i + k]) {
                    find_len++;
                } else {
                    break;
                }
            }

            if (find_len >= 0) {
                if (max_len < 2*find_len + 1) {
                    max_len = 2*find_len + 1;
                    max_start = i - find_len;

                    // std::cout << "find: [" << max_start << " " << max_len << "]" << std::endl;
                }
            }
        }

        if (max_len > 0) {
            string ret;
            ret.append(&s[max_start], max_len);
            return ret;
        }

        return "";
    }
};


/*
// test
#include <iostream>

int main(int argc, char** argv) {

    string example = "cbbd";

    Solution solution;
    auto ret = solution.longestPalindrome(example);

    std::cout << "longest substr:" << ret << std::endl;

    return 0;
}
*/