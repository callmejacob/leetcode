/**
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);
Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:

P     I    N
A   L S  I G
Y A   H R
P     I
*/

#include <string>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        // check
        if (numRows <= 1) return s;

        string ret;

        int len = s.length();
        int numCols = (len / (2 * numRows  - 2)) * 2 + 2;

        // 辅助空间: numRows个字符串空间和它们的当前索引
        char* p[numRows];
        for (auto i = 0; i < numRows; i++) {
            p[i] = new char[numCols];
        }

        int indexes[numRows];
        for (auto i = 0; i < numRows; i++) {
            indexes[i] = 0;
        }

        // 按zigzag方式，上下扫描字符串并存储到对应行的字符串中
        int scan_row = 0;
        int step = -1;
        for (auto i = 0; i < len; i++) {
            p[scan_row][indexes[scan_row]++] = s[i];

            if ((scan_row == 0) || (scan_row == numRows - 1)) {
                step = ((step == 1) ? -1 : 1);
            }

            scan_row += step;
        }

        // 按行顺序合并字符串
        for (auto i = 0; i < numRows; i++) {
            ret.append(p[i], indexes[i]);
        }

        // 清理辅助空间
        for (auto i = 0; i < numRows; i++) {
            delete[] p[i];
        }

        return ret;
    }
};

/*
// test
#include <iostream>
#include <chrono>

using namespace chrono;

int main(int argc, char** argv) {
    // prepare params
    const string& str = "Apalindromeisaword,phrase,number,orothersequenceofunitsthatcanbereadthesamewayineitherdirection,withgeneralallowancesforadjustmentstopunctuationandworddividers.";

    string params;
    for (auto i = 0; i < 10000; i++) {
        params.append(str.c_str(), str.length());
    }

    // exec 
    auto time1 = system_clock::now();
    Solution solution;
    auto ret = solution.convert(params, 4);
    auto time2 = system_clock::now();

    // print result and cost time
    cout << "zigzag result: " << ret << endl;
    cout << "used time:" << (time2 - time1).count() / 1000 << "ms" << endl;

    return 0;
}
*/