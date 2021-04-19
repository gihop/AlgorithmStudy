#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    
    bool found = false;
    for(int row=1; row<=yellow; row++){
        if(yellow % row == 0){
            int col = yellow / row;
            if((row * 2) + (col * 2) + 4 == brown){
                answer.push_back(max(row+2, col+2));
                answer.push_back(min(row+2, col+2));
                break;
            }
        }
    }
    
    return answer;
}
