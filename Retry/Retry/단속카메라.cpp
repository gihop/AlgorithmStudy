#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
 간단하게 풀 수 있는 문제를 어렵게 풀었다.
 routes 배열을 먼저 sort 해준다.
 0번째 원소를 start, end로 설정하고
 iteration을 돌면서 start와 end의 범위가 겹치도록 계속 좁힌다.
 그 때 start가 end보다 커지는 경우는 새로운 범위가 나와서 새로운 감시카메라가 필요하다는 뜻이다.
 */

int solution(vector<vector<int>> routes) {
    int answer = 1;
    
    sort(routes.begin(), routes.end());
    
    int start = routes[0][0], end = routes[0][1];
    
    for(int i=1; i<routes.size(); i++){
        start = max(start, routes[i][0]);
        end = min(end, routes[i][1]);
        
        if(start > end){
            answer++;
            start = routes[i][0];
            end = routes[i][1];
        }
    }
    
    return answer;
}
