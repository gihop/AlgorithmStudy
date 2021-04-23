#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> triangle) {
    vector<vector<int>> dp(500, vector<int>(500));
    dp[0][0] = triangle[0][0];
    for(int i=0; i<triangle.size()-1; i++){
        for(int j=0; j<triangle[i].size(); j++){
            if(dp[i+1][j] < dp[i][j] + triangle[i+1][j])
                dp[i+1][j] = dp[i][j] + triangle[i+1][j];
            if(dp[i+1][j+1] < dp[i][j] + triangle[i+1][j+1])
                dp[i+1][j+1] = dp[i][j] + triangle[i+1][j+1];
        }
    }
    
    return *max_element(dp[triangle.size()-1].begin(), dp[triangle.size()-1].end());
}
