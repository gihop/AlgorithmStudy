#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

int time_to_int(string time_string){
    int hour = stoi(time_string.substr(0,2));
    int minute = stoi(time_string.substr(3,5));
    int sec = stoi(time_string.substr(6,8));
    return (hour * 3600) + (minute * 60) + sec;
}

string time_to_string(int time_int){
    string time = "";
    int hour = time_int / 3600;
    int minute = time_int % 3600 / 60;
    int sec = time_int % 3600 % 60;
    if(hour >= 10)
        time += to_string(hour) + ":";
    else
        time += "0" + to_string(hour) + ":";
    if(minute >= 10)
        time += to_string(minute) + ":";
    else
        time += "0" + to_string(minute) + ":";
    if(sec >= 10)
        time += to_string(sec);
    else
        time += "0" + to_string(sec);
    
    return time;
}

string solution(string play_time, string adv_time, vector<string> logs) {
    string answer = "";
    
    vector<pair<string,string>> log_table(logs.size(), make_pair("", ""));
    
    for(int i=0; i<logs.size(); i++){
        string start = "", end = "";
        int split = logs[i].find('-');
        start = logs[i].substr(0, split);
        end = logs[i].substr(split+1, logs[i].size());
        log_table[i] = make_pair(start, end);
    }
    sort(log_table.begin(), log_table.end());
    
    vector<pair<string,int>> log_comb(logs.size()*2, make_pair("", 0));
    for(int i=0; i<log_table.size(); i++){
        log_comb[i*2] = make_pair(log_table[i].first, i);
        log_comb[i*2+1] = make_pair(log_table[i].second, i);
    }
    
    sort(log_comb.begin(), log_comb.end());
    
    int adv = time_to_int(adv_time);
    string adv_start = "00:00:00", adv_end = adv_time;
    int time_index = -1;
    int max_time = 0;
    
    while(true){
        int tmp_idx = time_index;
        if(tmp_idx == -1) tmp_idx++;
        
        int watch_sum = 0;
        set<int> s;
        while(log_comb[tmp_idx].first >= adv_start && log_comb[tmp_idx].first <= adv_end){
            if(s.count(log_comb[tmp_idx].second) > 0) {
                tmp_idx++;
                continue;
            }
            s.insert(log_comb[tmp_idx].second);
            string watch_start = max(log_table[log_comb[tmp_idx].second].first, adv_start);
            string watch_end = min(log_table[log_comb[tmp_idx].second].second, adv_end);
            watch_sum += time_to_int(watch_end) - time_to_int(watch_start);
            tmp_idx++;
        }
        
        if(watch_sum > max_time){
            max_time = watch_sum;
            answer = adv_start;
        }
        time_index++;
        if(time_index == logs.size() * 2) break;
        adv_start = log_comb[time_index].first;
        int next_adv_end_sec = time_to_int(adv_start) + adv;
        if(next_adv_end_sec >= 360000) break;
        adv_end = time_to_string(next_adv_end_sec);
        if(adv_end > play_time) break;
    }
    
    return answer;
}

int main(){
//    vector<string> logs = {"69:59:59-89:59:59", "01:00:00-21:00:00", "79:59:59-99:59:59", "11:00:00-31:00:00"};
//    cout << solution("99:59:59", "25:00:00", logs);
    vector<string> logs = {"15:36:51-38:21:49", "10:14:18-15:36:51", "38:21:49-42:51:45"};
    cout << solution("50:00:00", "50:00:00", logs);
    
    return 0;
}
