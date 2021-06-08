#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


vector<vector<int> > lcs(const string& s1, const string& s2) {
    vector<vector<int> > dp(s1.size() + 1, vector<int>(s2.size() + 1, 0));
    for (size_t i = 0; i < s1.size() + 1; ++i) {
        for (size_t j = 0; j < s2.size() + 1; ++j) {
            if (i == 0 || j == 0) {
                continue;
            }
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    return dp;
}
void dfs(const vector<vector<int> >& dp,
         const string& s1,
         const string& s2,
         int i, int j,
         string res,
         set<string>& allstr) {
    while (i > 0 && j > 0) {
        if (s1[i-1] == s2[j-1]) {
            res.push_back(s1[i-1]);
            i--;
            j--;
        } else {
            if (dp[i-1][j] > dp[i][j-1]) {
                i--;
            } else if (dp[i-1][j] < dp[i][j-1]) {
                j--;
            } else {
                dfs(dp, s1, s2, i-1, j, res, allstr);
                dfs(dp, s1, s2, i, j-1, res, allstr);
                return;
            }
        }
    }
    
    allstr.insert(res);
}

int main(int argc, char *argv[])
{
    string s1, s2;
    std::cin >> s1 >> s2;
    vector<vector<int> > dp = lcs(s1, s2);
    set<string> allstr;
    dfs(dp, s1, s2, s1.size(), s2.size(), "", allstr);
    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());
    dp = lcs(s1, s2);
    dfs(dp, s1, s2, s1.size(), s2.size(), "", allstr);
    for (set<string>::iterator iter = allstr.begin(); iter != allstr.end(); ++iter) {
        std::cout << *iter << std::endl;
    }
    return 0;
}
