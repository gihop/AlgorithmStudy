#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> answers) {
    vector<int> answer;
    
    vector<int> a {1,2,3,4,5};
    vector<int> b {2,1,2,3,2,4,2,5};
    vector<int> c {3,3,1,1,2,2,4,4,5,5};
    
    int cnt1,cnt2,cnt3;
    cnt1=cnt2=cnt3=0;
    
    for(int i=0; i<answers.size(); i++){
        int aa = i%5, bb = i%8, cc = i%10;
        
        if(answers[i]==a[aa]) cnt1++;
        if(answers[i]==b[bb]) cnt2++;
        if(answers[i]==c[cc]) cnt3++;
    }
    int max;
    if(cnt1>cnt2) max=cnt1;
    else max=cnt2;
    if(max<cnt3) max=cnt3;
    
    if(max==cnt1) answer.push_back(1);
    if(max==cnt2) answer.push_back(2);
    if(max==cnt3) answer.push_back(3);
    
    return answer;
}
