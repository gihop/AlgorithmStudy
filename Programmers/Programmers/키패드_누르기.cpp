#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

vector<vector<int>> keypad(4, vector<int>(3, 0));

int findDistance(int start, int end){
    int startX, startY, endX, endY;
    
    bool foundStart = false, foundEnd = false;
    
    for(int i=0; i<4; i++){
        for(int j=0; j<3; j++){
            if(start == keypad[i][j]){
                startX = i;
                startY = j;
                foundStart = true;
            }
            if(end == keypad[i][j]){
                endX = i;
                endY = j;
                foundEnd = true;
            }
            if(foundStart && foundEnd) break;
        }
        if(foundStart && foundEnd) break;
    }
    
    return abs(startX - endX) + abs(startY - endY);
}

string solution(vector<int> numbers, string hand) {
    string answer = "";
    
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            keypad[i][j] = (i*3) + j+1;
    
    keypad[3][0] = -1;
    keypad[3][0] = 0;
    keypad[3][0] = -1;
    
    int leftNow = -1, rightNow = -1;
    for(int i=0; i<numbers.size(); i++){
        if(numbers[i] == 1 || numbers[i] == 4 || numbers[i] == 7){
            answer += "L";
            leftNow = numbers[i];
        }
        else if(numbers[i] == 3 || numbers[i] == 6 || numbers[i] == 9){
            answer += "R";
            rightNow = numbers[i];
        }
        else{
            int leftDistance = findDistance(leftNow, numbers[i]);
            int rightDistance = findDistance(rightNow, numbers[i]);
            
            if(leftDistance == rightDistance){
                if(hand == "left"){
                    leftNow = numbers[i];
                    answer += "L";
                }
                else{
                    rightNow = numbers[i];
                    answer += "R";
                }
            }
            else if(leftDistance < rightDistance){
                leftNow = numbers[i];
                answer += "L";
            }
            else{
                rightNow = numbers[i];
                answer += "R";
            }
        }
    }
    
    return answer;
}
