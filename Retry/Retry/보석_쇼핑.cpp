#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>

using namespace std;

vector<int> solution(vector<string> gems) {
    vector<int> answer;
    set<string> gems_set;
    map<string,int> gems_count;
    for(int i=0; i<gems.size(); i++){
        gems_set.insert(gems[i]);
    }
    int start = 0, end = 0;
    int min_start, min_end;
    int found = false;
    int length;
    for(int i=0; i<gems.size(); i++){
        gems_count[gems[i]]++;
        end = i;
        if(!found && gems_count.size() == gems_set.size()){
            found = true;
            length = end - start;
            min_start = start;
            min_end = end;
        }
        if(found){
            while(gems_count[gems[start]] > 1){
                gems_count[gems[start]]--;
                start++;
            }
            if(end - start < length){
                length = end - start;
                min_start = start;
                min_end = end;
            }
        }
    }
    answer.push_back(min_start+1);
    answer.push_back(min_end+1);
    return answer;
}
