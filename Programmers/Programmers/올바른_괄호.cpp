#include<string>
#include <iostream>

using namespace std;

bool solution(string s)
{
    bool answer = false;
    
    int count=0;
    for(int i=0; i<s.size(); i++){
        if(s[i]==')' && count>0) count--;
        else if(s[i]=='(') count++;
        else return false;
    }
    
    if(count==0) answer=true;
    return answer;
}
