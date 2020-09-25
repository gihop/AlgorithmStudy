#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> arr)
{
    vector<int> answer;
    
    int pre = -1;
    for(int i=0; i<arr.size(); i++){
        if(pre != arr[i]) answer.push_back(arr[i]);
        pre = arr[i];
    }
    
    return answer;
}
