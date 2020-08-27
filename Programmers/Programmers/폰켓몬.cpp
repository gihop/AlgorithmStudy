#include <vector>
#include <set>

using namespace std;

int solution(vector<int> nums)
{
    int answer = 0;
    int numsSize = nums.size();
    
    set<int> s;
    
    for(int i=0; i<numsSize; i++){
        if(s.count(nums[i])==0)
            s.insert(nums[i]);
    }
    if(s.size() >= numsSize/2)
        answer = numsSize/2;
    else
        answer = s.size();
    
    return answer;
}
