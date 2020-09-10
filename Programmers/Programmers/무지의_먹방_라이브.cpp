#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <iostream>

using namespace std;

//무지의 먹방 라이브 재도전.
//전에는 효율성을 해결하지 못했었다.

//이거 정말 기가 막히게 풀었다.
//우선 각 음식에 필요한 시간인 food_times의 원소와 index를 pair로 묶어서 times 벡터를 만든다.
//i+1 하는 이유는 정답에서 원소를 0,1,2,3 순서가 아닌 1,2,3,4이기 때문.

//그 다음 times 벡터를 필요한 시간을 오름차순으로 정렬한다.
//이제부터 순서가 작은 음식부터 다먹고 버린다.
//가장 작은 음식을 먹는데 필요한 시간이 2이고 남은 음식의 수가 5라면 총 시간인 k에서 2*5를 뺀다.
//그다음 idx를 1 증가시키고 다음 음식이 3이라면 남은 음식이 4이기 때문에 k에서 3*4를 뺀다.

//이런 방식으로 빼다가 k가 (음식 시간 * 남은 음식 수) 보다 작으면 벗어난다.
//이 뜻은 더이상 음식을 버릴만큼 k가 크지 않다는 뜻.
//그 다음 남은 음식들을 pair->second 즉 음식의 번호 idx 순서대로 정렬한다.
//k를 남은 음식 수로 나머지연산을 해서 나머지를 구하고 남은 음식에서 나머지만큼 이동한 음식의 번호가 정답이다.

bool compare(const pair<long long, int> &a, const pair<long long, int> &b){
    return a.second < b.second;
}

int solution(vector<int> food_times, long long k) {
    int answer = 0;
    
    vector<pair<long long, int>> times;
    
    for(int i=0; i<food_times.size(); i++)
        times.push_back(make_pair(food_times[i], i+1));
    
    sort(times.begin(), times.end());
    
    int idx;
    for(idx=0; idx<times.size(); idx++){
        //처음에는 차이가 없으니까 0이고, 그 다음부터 전 원소에서 빼줘야 하기 때문에 이게 가장 효율적.
        long long diff = idx == 0 ? times[idx].first : times[idx].first - times[idx-1].first;
        if(k >= (diff*(times.size()-idx))) {//idx번째 음식을 다 먹을 수 있음.
            k -= (diff*(times.size()-idx));
        }
        
        else break;//이번 순서의 음식을 다 먹을수가 없는 경우.
    }
    if(idx == times.size()) return -1;//k가 남으면 음식을 다 먹어치우고 for문을 break없이 다 돌게 된다. 그래서 idx가 times.size()가 된다.
    k = k % (times.size() - idx);//k가 5이고 남은 음식들이 2,3,4면 3개 음식이 남기 때문.
    sort(times.begin()+idx, times.end(), compare);//begin()+idx가 핵심 포인트이다. 남은 음식들 범위에서 음식 번호 기준으로 정렬한다.
    
    answer = times[idx+k].second;
    
    return answer;
}

//int solution(vector<int> food_times, long long k) {
//    int answer = 0;
//    long long count = k/food_times.size();
//    if(count >= *max_element(food_times.begin(), food_times.end()))
//        return -1;
//    deque<pair<int,int>> dq;
//
//
//    for(int i=0; i<food_times.size(); i++)
//        dq.push_back(make_pair(food_times[i],i+1));
//
//    for(long long i=0; i<k; ){
//        int count = dq.size();
//        int Min, idx;
//        tie(Min, idx) = *min_element(dq.begin(), dq.end());
//        if(i+count*Min<=k){
//            for(int j=0; j<count; j++){
//                int n, idx;
//                tie(n,idx) = dq.front();
//                dq.pop_front();
//                n-=Min;
//                if(n) dq.push_back(make_pair(n,idx));
//                if(dq.size()==0) break;
//            }
//            i+=count*Min;
//        }
//        else{
//            for(int j=0; j<count && i<k; j++, i++){
//                int n, idx;
//                tie(n,idx) = dq.front();
//                dq.pop_front();
//                n--;
//                if(n) dq.push_back(make_pair(n,idx));
//                if(dq.size()==0) break;
//            }
//        }
//
//        if(dq.size()==0) break;
//    }
//    if(dq.size()>0) answer = dq[0].second;
//    else answer = -1;
//    return answer;
//}
