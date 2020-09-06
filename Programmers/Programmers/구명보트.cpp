#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

//그리디 문제.
//한 보트에 최대한 2명을 담아야한다.
//먼저 deque에 사람들을 옮긴다.
//현재 가장 무거운 값을 dq에서 제거하고, 가장 무거운 값과 limit에 최대한 딱 맞게 넣을 사람을 구한다.
//이 구조는 vector, list(이중연결리스트)로도 구현이 가능하다.
//하지만 vector, list 모두 효율성에서 시간초과가 발생한다.
//vector는 끝에 있는 원소가 아닌 원소를 삭제할 때 시간이 많이 소요되서 시간초과가 발생하는 것 같다.
//list는 순회가 느려서 시간초과가 발생하는 것 같다.
//(추가적으로 이 코드 그대로 dq를 list로 사용하고 싶다면 sort는 algorithm이 아닌 List의 자체 sort를 사용한다. 또한 인덱스로 접근이 불가능하기 때문에 iterator로 접근해야 한다.)
//결론적으로 deque로 해결했지만 처음에 vector에서 deque로 옮겨야하기 때문에 최적의 방법은 아니라고 생각한다.

//++추가
//먼저 잘못 생각했던 부분은 이전에는 가장 무거운 사람과 limit에 가장 딱 맞는 사람을 최적의 수라고 생각했다.
//물론 이렇게도 풀 수 있지만 좀 더 최적의 방법으로 푸는 방법은
//가장 무거운 사람이 가장 가벼운 사람과 동시에 탈 수 있다면 그것이 최적의 방법이다.
//이를 이용해서 투포인터 알고리즘을 이용해서 log(n)으로 풀 수 있다.
//또한 deque로 옮기지 않아도 되기 때문에 시간을 좀 더 줄일 수 있다.
//이전에 풀었던 방법은 아래 주석 처리했다.

int solution(vector<int> people, int limit) {
    int answer = 0;
    
    //내림 차순으로 people을 정렬한다.
    sort(people.begin(), people.end(), greater<int>());
    
    //i가 start, j가 end.
    //둘다 보트에 탈 수 있다면 j--로 탐색의 범위를 -2 한다.
    //가장 무거운 사람과 가장 가벼운 사람이 같이 탈 수 없다면 i만 증가시켜서 탐색의 범위를 -1한다.
    for(int i=0, j=people.size()-1; i<=j; i++){
        if(people[i] + people[j] <= limit){
            j--;
        }
        answer++;
    }
    
    return answer;
}

//int solution(vector<int> people, int limit) {
//    int answer = 0;
//
//    deque<int> dq;
//
//    for(int i=0; i<people.size(); i++){
//        dq.push_back(people[i]);
//    }
//
//    sort(dq.begin(), dq.end());
//
//    while(!dq.empty()){
//        int Max = dq.back();
//        dq.pop_back();
//        int rest = limit - Max;
//        bool twoPerson = false;
//        int nextIdx = 0;
//        for(int i=0; i<dq.size(); i++){
//            if(dq[i] > rest) {
//                break;
//            }
//            if(dq[i] == rest){
//                twoPerson = false;
//                dq.erase(dq.begin()+i);
//                break;
//            }
//            else{
//                nextIdx = i;
//                twoPerson = true;
//            }
//        }
//        if(twoPerson){
//            dq.erase(dq.begin() + nextIdx);
//        }
//        answer++;
//    }
//
//    return answer;
//}
