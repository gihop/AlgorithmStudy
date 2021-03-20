#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;
vector<string> combinations;

void combination(string order, int idx, int count, string comb){
    if(comb.size() == count){
        combinations.push_back(comb);
        return;
    }
    for(int i=idx; i<order.size(); i++){
        comb += order[i];
        combination(order, i+1, count, comb);
        comb.pop_back();
    }
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    
    set<string> comb_set;
    
    string test = "abcde";
    
    
    for(int i=0; i<course.size(); i++){
        int count = course[i];
        int max_order = 0;
        vector<string> candidate;
        
        for(int j=0; j<orders.size(); j++){
            if(orders[j].size() < count) continue;
            combinations.clear();
            combination(orders[j], 0, count, "");
            for(int k=0; k<combinations.size(); k++){
                sort(combinations[k].begin(), combinations[k].end());
                if(comb_set.count(combinations[k]) > 0) continue;
                comb_set.insert(combinations[k]);
                
                int count_order = 0;
                for(int l=0; l<orders.size(); l++){
                    if(orders[l].size() < count) continue;
                    bool found = true;
                    for(int m=0; m<combinations[k].size(); m++){
                        if(orders[l].find(combinations[k][m]) == string::npos){
                            found = false;
                            break;
                        }
                    }
                    if(found){
                        count_order++;
                    }
                }
                
                if(count_order > max_order && count_order > 1){
                    candidate.clear();
                    candidate.push_back(combinations[k]);
                    max_order = count_order;
                }
                else if(count_order == max_order && count_order > 1){
                    candidate.push_back(combinations[k]);
                }
            }
        }
        
        for(int j=0; j<candidate.size(); j++){
            answer.push_back(candidate[j]);
        }
    }
    
    sort(answer.begin(), answer.end());
    
    return answer;
}
