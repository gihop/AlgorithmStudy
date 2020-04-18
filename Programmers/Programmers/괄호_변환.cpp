#include <string>
#include <vector>
#include <tuple>

using namespace std;

pair<string,string> divide(string s){
    int open=0, close=0;
    int idx;
    for(idx=0; idx<s.size(); idx++){
        if(s[idx]=='(') open++;
        else close++;
        if(open==close) break;
    }
    string u = "", v = "";
    u = s.substr(0,idx+1);
    v = s.substr(idx+1,-1);
    return make_pair(u,v);
}

bool accept(string s){
    bool accepted=true;
    int open=0, close=0;
    for(int i=0; i<s.size(); i++){
        if(s[i]=='(') open++;
        else if(open<=0){
            accepted=false;
            break;
        }
        else open--;
    }
    return accepted;
}

string bracket(string s){
    if(s == "") return s;
    string u="", v="";
    tie(u,v) = divide(s);
    
    if(accept(u)) return u+=bracket(v);
    else{
        string str="(";
        str += bracket(v);
        str += ")";
        string tmp="";
        for(int i=1; i<u.size()-1; i++){
            if(u[i]=='(') tmp+=')';
            else tmp+='(';
        }
        str += tmp;
        return str;
    }
}

string solution(string p) {
    string answer = "";
    answer = bracket(p);
    return answer;
}
