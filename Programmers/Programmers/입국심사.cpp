#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//이분 탐색 문제.
//이분 탐색 문제의 핵심은 우선 가장 큰 값을 구한다.
//여기서 가장 큰 값은 times(각 심사관이 심사를 보는데 걸리는 시간) 내에 있는 가장 큰 수와 n을 곱한 값이다.

//이 문제에서 주의해야할 점은 count == n일 때 바로 탐색을 끝내면 안된다는 것이다.
//count는 mid/times[i]의 합으로 이루어지는데
//나머지로 버려지는 값들 때문에 mid의 값이 답이 아니더라도 count와 n이 같을 수 있다.

//예를 들어 심사관이 2,3,4이고 n=23이고 답이 22일 때
//mid의 값이 23이어도 답이 나온다.
//23/2 = 11, 23/3 = 7, 23/4 = 5 따라서 11+7+5 = 23이기 때문에 while문을 벗어난다.

//그래서 count==n인 경우에 while문을 벗어나지 말고 start = mid을 해서 계속 이분 탐색을 한다.
//이후의 탐색은 count==n인 경우에만 end가 답인 mid로 움직이기만 하고, start만 계속 커지기 때문에
//결국 start+1 == end인 상황이 오게되고 답은 end에 담기게 된다.

long long solution(int n, vector<int> times) {
    long long answer = 0;
    
    int maxElement = *max_element(times.begin(), times.end());
    long long start = 0, end = maxElement * n;
    bool found = false;
    while(true){
        long long mid = (start + end) / 2;
        long long count = 0;
        bool found = false;
        for(int i=0; i<times.size(); i++){
            count += mid/times[i];
        }
        if(start+1 == end) break;
        if(count > n){
            end = mid;
        }
        else if(count < n){
            start = mid;
        }
        else{
            end = mid;
        }
    }
    
    return end;
}
