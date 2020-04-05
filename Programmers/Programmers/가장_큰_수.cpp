#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(const string &a, const string &b){
    if(a+b > b+a) return true;
    else return false;
}

string solution(vector<int> numbers) {
    string answer = "";
    vector<string> v;
    
    for(int i : numbers)
        v.push_back(to_string(i));
    
    sort(v.begin(), v.end(), compare);
    
    for(int i=0; i<v.size(); i++)
        answer+=v[i];
    
    if(answer[0]=='0')
        answer="0";
    
    return answer;
}
