#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

//호텔 방 배정 문제 재도전.
//전에는 효율성을 통과하지 못했다.
//union find 알고리즘 사용으로 풀 수 있었다.
//부모 노드가 다음 빈 방 번호 값을 갖게 하는 방식이다.
//재귀를 이용해서 값을 계속 갱신시킨다.

map<long long, long long> m;

long long find(long long num){
    //처음 찾는 숫자라면 map에서 0이다. 바로 num을 반환해준다.
    if(m[num] == 0) return num;
    //처음 찾는 숫자가 아니라면 가리켜야할 숫자가 저장되어 있다.
    //여기서 m[num]을 갱신시켜주면서 재귀를 줄일 수 있다.
    else return m[num] = find(m[num]);
}

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    
    for(int i=0; i<room_number.size(); i++){
        long long assign = find(room_number[i]);
        answer.push_back(assign);
        m[assign] = assign+1;//빈 방이 이제 채워졌으니 다음 방을 가리키도록 한다.
    }
    
    return answer;
}

//set<long long> s;
//
//vector<long long> solution(long long k, vector<long long> room_number) {
//    vector<long long> answer;
//
//    for(int i=0; i<room_number.size(); i++){
//        long long num = room_number[i];
//        if(s.count(num)==0){
//            s.insert(num);
//            answer.push_back(num);
//        }
//        else{
//            num++;
//            while(true){
//                if(s.count(num)==0){
//                    s.insert(num);
//                    answer.push_back(num);
//                    break;
//                }
//                else num++;
//            }
//        }
//    }
//
//    return answer;
//}
