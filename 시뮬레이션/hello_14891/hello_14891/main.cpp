//
//  main.cpp
//  hello_14891
//
//  Created by jiho park on 04/09/2019.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int num;
    cin >> num;
    
    vector<string> circle(num);
    
    for(int i = 0; i < num; i++) {
        cin >> circle[i];
    }
    
    int k;
    cin >> k;
    
    while(k--) {
        int no, dir;
        cin >> no >> dir;
        
        vector<int> d(num);
        d[no-1] = dir;
        
        for(int i = no - 1; i > 0; i--) {
            if(circle[i][6] != circle[i-1][2]) {
                d[i-1] = -d[i];
            }
            else {
                break;
            }
        }
        
        for(int i = no - 1; i < num - 1; i++){
            if(circle[i][2] != circle[i+1][6]){
                d[i+1] = -d[i];
            }
            else {
                break;
            }
        }
        
        for(int i = 0; i < num; i++){
            if(d[i] == 0) {
                continue;
            } else if(d[i] == 1) {
                int temp;
                temp = circle[i][7];
                for(int j = 7; j > 0; j--){
                    circle[i][j] = circle[i][j-1];
                }
                circle[i][0] = temp;
            } else {
                int temp;
                temp = circle[i][0];
                for(int j = 0; j < 7; j++){
                    circle[i][j] = circle[i][j+1];
                }
                circle[i][7] = temp;
            }
        }
    }
    
    int score = 0;
    
    for(int i = 0 ; i < num; i++) {
        if(circle[i][0] == '1')
            score += 1;
    }
    
    cout << score << endl;
}
 
