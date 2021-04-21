#include <string>
#include <vector>
using namespace std;

int answer = 0;

void dfs(vector<int> numbers, int target, int idx, int now){
    if(idx == numbers.size()){
        if(now == target) answer++;
        return;
    }
    dfs(numbers, target, idx+1, now+numbers[idx]);
    dfs(numbers, target, idx+1, now-numbers[idx]);
}

int solution(vector<int> numbers, int target) {
    dfs(numbers, target, 0, 0);
    
    return answer;
}
