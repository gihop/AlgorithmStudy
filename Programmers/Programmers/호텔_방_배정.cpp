#include <string>
#include <vector>
#include <set>

using namespace std;

set<long long> s;

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    
    for(int i=0; i<room_number.size(); i++){
        long long num = room_number[i];
        if(s.count(num)==0){
            s.insert(num);
            answer.push_back(num);
        }
        else{
            num++;
            while(true){
                if(s.count(num)==0){
                    s.insert(num);
                    answer.push_back(num);
                    break;
                }
                else num++;
            }
        }
    }
    
    return answer;
}
