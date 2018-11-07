/**
Given a string, find the length of the longest substring without repeating characters.

Example 1:

Input: "abcabcbb"
Output: 3 
Explanation: The answer is "abc", with the length of 3. 
Example 2:

Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3. 
             Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/

#include <string>
#include <map>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int record[256] = {0};

        int find_len = 0;
        for (int i = 0; i < s.length(); i++) {
            int len = 0;
            int skip = 0;
            for (int j = i; j < s.length(); j++) {
                if (record[s[j]] == 0) {
                    record[s[j]] = j + 1;
                    len++;
                } else {
                    skip = record[s[j]] - 1 - i;
                    break;
                }
            }
            if (len > find_len) {
                find_len = len;
            }
            i += skip;
            memset(record, 0, sizeof(record));
        }

        return find_len;
    }
};


/**
// test
#include <iostream>

int main(int argc, char** argv) {

    Solution solution;

    int length = solution.lengthOfLongestSubstring("abcabcbb");
    std::cout << "find: " << length << std::endl;


    return 0;
}
*/