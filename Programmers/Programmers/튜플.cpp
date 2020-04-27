#include <string>
#include <vector>
#include <map>

using namespace std;

int transform(string num){
    int number=0;
    for(int i=0; i<num.size(); i++){
        number*=10;
        number+=num[i]-'0';
    }
    return number;
}

vector<int> solution(string s) {
    vector<int> answer;
    
    map<int,int> m;
    string num="";
    bool check=false;
    for(int i=0; i<s.size(); i++){
        if(s[i]>='0' && s[i]<='9'){
            if(!check){
                check=true;
                num = s[i];
            }
            else{
                num += s[i];
            }
        }
        else{
            check=false;
            if(num!=""){
                int number = transform(num);
                if(m.count(number)==0)
                    m[number]=1;
                else
                    m[number]++;
                num="";
            }
        }
    }
    
    answer.assign(m.size(), 0);
    
    for(map<int,int>::iterator iter = m.begin(); iter!=m.end(); iter++){
        answer[m.size()-iter->second] = iter->first;
    }
    
    return answer;
}
