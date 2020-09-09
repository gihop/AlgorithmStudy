#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//징검다리 건너기 문제 재도전.
//개인적으로 아래 주석처리 해놓은 이전에 풀었던 풀이도 좋다고 생각하지만,
//효율성 테스트케이스를 모두 통과하진 못했다.
//이분 탐색을 이용해서 모든 테스트 케이스를 통과할 수 있었다.

//먼저 max 값은 stones안에 있는 가장 큰 값이 최대로 건널 수 있는 숫자이기 때문에 end로 설정한다.

int solution(vector<int> stones, int k) {
    int answer = 0;
    
    int start = 0, end = *max_element(stones.begin(), stones.end());
    
    while(start <= end){
        int mid = (start + end) / 2;
        
        int count = k;
        bool success = true;
        
        //mid명이 건너려면 현재 위치에서 k개 안의 디딤돌에 mid값 이상의 디딤돌이 있어야 한다.
        for(int i=0; i<stones.size(); i++){
            if(stones[i] >= mid) count = k;
            else count--;
            if(count == 0) {//mid값 이상의 디딤돌이 k개 안에 없는 경우.
                success = false;
                break;
            }
        }
        if(success){
            answer = mid;
            start = mid+1;
        }
        else{
            end = mid-1;
        }
    }
    
    return answer;
}

//int solution(vector<int> stones, int k) {
//    int answer = 200000001;
//
//    for(int i=0; i<=stones.size()-k; i++){
//        int Max = *max_element(stones.begin()+i,stones.begin()+i+k);
//        if(answer > Max) answer = Max;
//    }
//
//    return answer;
//}
