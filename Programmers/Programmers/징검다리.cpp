#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//이분탐색 문제.
//이분탐색 문제는 어떤 부분을 이분탐색할건지 설정하는 것이 가장 중요하다.
//이 문제에서는 거리의 바위 거리간의 최솟값중에 가장 큰 값을 구하는 것이기 때문에 이를 이분탐색한다.

int solution(int distance, vector<int> rocks, int n) {
    int answer = 0;
    
    sort(rocks.begin(), rocks.end());
    
    rocks.push_back(distance);//도착지를 맨 마지막으로 넣는다.
    int start = 1, end = distance;
    
    while(start<=end){
        int mid = (start + end) / 2;
        
        int now = 0, count = 0;
        
        //rocks에 순서대로 담겨있는 바위들의 거릿값을 비교한다.
        for(int i=0; i<rocks.size(); i++){
            //이분 탐색한 mid 값보다 바위 사이의 거리가 더 작다면 바위를 없앤다.
            //여기서 now의 값을 갱신하지 않기 때문에 다음 바위는 전전 바위와의 거리로 계산된다.
            if(mid > rocks[i] - now){
                count++;
            }
            else{
                now = rocks[i];
            }
        }
        
        if(count > n) end = mid-1;
        //count == n에서 바로 while문을 빠져나가지 않는 이유는 최솟값중 '가장 큰 값'을 구하기 때문.
        //count의 값이 n과 같으면서 mid의 값이 더 큰 값이 존재할 수 있기 때문이다.
        else{
            start = mid+1;
            answer = mid;
        }
    }
    
    return answer;
}
