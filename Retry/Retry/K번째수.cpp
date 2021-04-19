#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    
    for(int i=0; i<commands.size(); i++){
        int start = commands[i][0], end = commands[i][1], order = commands[i][2];
        vector<int> numbers(end-start+1, 0);
        for(int j=start-1; j<end; j++)
            numbers[j-start+1] = array[j];
        sort(numbers.begin(), numbers.end());
        answer.push_back(numbers[order-1]);
    }
    
    return answer;
}
