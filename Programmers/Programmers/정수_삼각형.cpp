#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

//처음에 깊이 우선 탐색을 했다가 효율성에서 틀렸었다.
//이 문제에서 깊이 우선 탐색은 효율적이지 않고, 각 행렬에서 담을 수 있는 가장 큰 수만 담는 방식으로 해결했다.

int dp[500][500];

int solution(vector<vector<int>> triangle) {
    int answer = 0;
    int size = triangle.size();
    
    dp[0][0] = triangle[0][0];
    for(int i=0; i<size-1; i++){
        for(int j=0; j<=i; j++){
            if(dp[i+1][j] < dp[i][j] + triangle[i+1][j])
                dp[i+1][j] = dp[i][j] + triangle[i+1][j];
            if(dp[i+1][j+1] < dp[i][j] + triangle[i+1][j+1])
                dp[i+1][j+1] = dp[i][j] + triangle[i+1][j+1];
        }
    }
    for(int i=0; i<size; i++){
        answer = max(answer, dp[size-1][i]);
    }
    
    return answer;
}
