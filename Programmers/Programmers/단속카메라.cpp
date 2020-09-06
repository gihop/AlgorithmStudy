#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//생각보다 간단하게 풀려서 기뻤다.
//두 구간 a->b, c->d가 있을 때, 두 구간이 겹치는 부분이 있는지 보려면
//두 개의 출발 지점 중에 큰 값과, 두 개의 종료 지점 중에 작은 값을 비교 했을 때,
//출발 지점이 종료 지점보다 값이 크다면 둘은 겹치는 구간이 없다는 점을 이용을 했다.
//다른 문제에서도 이와 같은 문제가 나온다면 이를 활용하면 좋을 것 같다.

int solution(vector<vector<int>> routes) {
    int answer = 0;
    
    sort(routes.begin(), routes.end());
    
    int start = routes[0][0], end = routes[0][1];
    for(int i=1; i<routes.size(); i++){
        int nextStart = max(start,routes[i][0]), nextEnd = min(end,routes[i][1]);
        if(nextStart > nextEnd){
            answer++;
            start = routes[i][0];
            end = routes[i][1];
        }
        else{
            start = nextStart;
            end = nextEnd;
        }
    }
    answer++;
    return answer;
}
