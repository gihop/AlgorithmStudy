#include <string>
#include <vector>
#include <iostream>
#include <set>

using namespace std;

int user_size;
int bann_size;
int ans=0;

vector<string> bann, user;
set<string> s;

bool bann_check(string bann_id, string user_id){
    bool check = true;
    // cout << bann_id << " " << user_id << endl;
    if(bann_id.size() == user_id.size()){
        for(int i=0; i<bann_id.size(); i++){
            if(bann_id[i]=='*') continue;
            if(bann_id[i] != user_id[i]){
                check = false;
                break;
            }
        }
    }
    else check = false;
    return check;
}

void go(vector<bool> &v, int cnt, int idx){
    if(cnt == bann_size){
        string st="";
        for(int i=0; i<v.size(); i++){
            if(v[i]){
                st+=user[i];
            }
        }
        if(s.count(st)==0){
            s.insert(st);
            ans++;
        }
        return;
    }
    for(int i=idx; i<bann_size; i++){
        for(int j=0; j<user_size; j++){
            if(v[j]) continue;
            
            if(bann_check(bann[i], user[j])){
                v[j]=true;
                go(v, cnt+1, i+1);
                v[j]=false;
            }
        }
    }
}

int solution(vector<string> user_id, vector<string> banned_id) {
    int answer = 0;
    
    user_size = user_id.size();
    bann_size = banned_id.size();
    user = user_id;
    bann = banned_id;
    
    vector<bool> v(user_size, false);
    go(v, 0, 0);
    answer=ans;
    return answer;
}
