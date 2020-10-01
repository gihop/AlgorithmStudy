#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long solution(int a, int b) {
    long long answer = 0;
    
    int Max = max(a, b), Min = min(a, b);
    
    long long sumMax = (long long)Max * (Max+1) / 2;
    long long sumMin = (long long)Min * (Min-1) / 2;
    
    answer = sumMax - sumMin;
    
    return answer;
}
