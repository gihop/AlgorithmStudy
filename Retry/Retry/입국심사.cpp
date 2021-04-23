#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
 max_el을 선언하지 않고 바로 end = *max_element(times.begin(), times.end())*n;
 해버리면 틀린다.
 뭐가 다른지 잘 모르겠다.
 +++추가
 end = *max_element(times.begin(), times.end())*n; 이렇게 하면
 max_element와 n모두 int형이기 때문에 큰 수를 곱했을 때 정확한 값이 end에 저장되지 않는다.
 그래서 max_element를 long long으로 형변환해주면 된다.
 */

long long solution(int n, vector<int> times) {
    sort(times.begin(), times.end());
    long long start = times[0], end = (long long)*max_element(times.begin(), times.end())*n;
    while(start <= end){
        long long mid = (start + end) / 2;
        long long count = 0;
        for(int i=0; i<times.size(); i++){
            count += mid/times[i];
            if(count >= n) break;
        }
        if(count >= n){
            end = mid-1;
        }
        else{
            start = mid+1;
        }
    }    
    return start;
}
