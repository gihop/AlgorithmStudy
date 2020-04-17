#include <string>
#include <vector>

using namespace std;

int number(int n){
    int cnt=0;
    while(n){
        n/=10;
        cnt++;
    }
    return cnt;
}

int solution(string s) {
    int answer = s.size();
    
    for(int i=1; i<=s.size()/2; i++){
        string str="";
        int length = s.size();
        int idx=1;
        for(int j=0; j<s.size(); j+=i){
            string nextstr=s.substr(j,i);
            if(str == nextstr){
                idx++;
            }
            else if(idx>1){
                length -= i*(idx-1)-number(idx);
                idx=1;
            }
            str = nextstr;
        }
        if(idx>1){
            length -= i*(idx-1)-number(idx);
            idx=1;
        }
        if(length < answer) answer = length;
    }
    
    return answer;
}
