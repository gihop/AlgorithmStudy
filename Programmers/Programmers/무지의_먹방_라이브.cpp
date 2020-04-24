#include <string>
#include <vector>
#include <deque>
#include <tuple>
#include <iostream>
#include <algorithm>

using namespace std;

int solution(vector<int> food_times, long long k) {
    int answer = 0;
    long long count = k/food_times.size();
    if(count >= *max_element(food_times.begin(), food_times.end()))
        return -1;
    deque<pair<int,int>> dq;
    
    
    for(int i=0; i<food_times.size(); i++)
        dq.push_back(make_pair(food_times[i],i+1));
    
    for(long long i=0; i<k; ){
        int count = dq.size();
        int Min, idx;
        tie(Min, idx) = *min_element(dq.begin(), dq.end());
        // cout << Min << endl;
        // cout << endl;
        if(i+count*Min<=k){
            for(int j=0; j<count; j++){
                int n, idx;
                tie(n,idx) = dq.front();
                dq.pop_front();
                n-=Min;
                // cout << n << endl;
                if(n) dq.push_back(make_pair(n,idx));
                if(dq.size()==0) break;
            }
            i+=count*Min;
        }
        else{
            for(int j=0; j<count && i<k; j++, i++){
                int n, idx;
                tie(n,idx) = dq.front();
                dq.pop_front();
                n--;
                // cout << n << endl;
                if(n) dq.push_back(make_pair(n,idx));
                if(dq.size()==0) break;
            }
        }
        
        // cout << i << "idx" << endl;
        // int n, idx;
        // tie(n,idx) = dq.front();
        // dq.pop_front();
        // n--;
        // if(n) dq.push_back(make_pair(n,idx));
        // if(dq.size()==0) break;
        if(dq.size()==0) break;
    }
    if(dq.size()>0) answer = dq[0].second;
    else answer = -1;
    return answer;
}
