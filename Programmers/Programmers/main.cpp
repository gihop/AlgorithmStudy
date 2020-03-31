#include <string>
#include <vector>

using namespace std;

vector<int> nums;
int n, size;
int ans = 0;

void go(int cnt, int idx, int num){
    if(cnt == size){
        if(num == n) ans++;
        return;
    }
    num += nums[idx];
    go(cnt+1, idx+1, num);
    num = num-nums[idx]*2;
    go(cnt+1, idx+1, num);
}

int solution(vector<int> numbers, int target) {
    int answer = 0;
    
    nums = numbers;
    n = target;
    size = numbers.size();
    
    go(0, 0, 0);
    
    answer = ans;
    
    return answer;
}
