#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> stones, int k) {
    int answer = 200000001;
    
    for(int i=0; i<=stones.size()-k; i++){
        int Max = *max_element(stones.begin()+i,stones.begin()+i+k);
        if(answer > Max) answer = Max;
    }
    
    return answer;
}
