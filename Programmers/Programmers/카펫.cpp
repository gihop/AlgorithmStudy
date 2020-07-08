#include <string>
#include <vector>

using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    
    int total=brown+yellow;
    int row, column;
    for(int r=2; r<total/2; r++){
        if(total%r==0){
            int c = total/r;
            if((r-2)*(c-2)==yellow){
                column = c;
                row = r;
            }
        }
    }
    
    answer.push_back(row);
    answer.push_back(column);
    
    return answer;
}
