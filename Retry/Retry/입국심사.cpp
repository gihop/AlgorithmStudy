#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
 max_el을 선언하지 않고 바로 end = *max_element(times.begin(), times.end())*n;
 해버리면 틀린다.
 뭐가 다른지 잘 모르겠다.
 */

long long solution(int n, vector<int> times) {
    sort(times.begin(), times.end());
    long long max_el = *max_element(times.begin(), times.end());
    long long start = 0, end = max_el*n;
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
