//
//  LCD_TEST_2290.cpp
//  시뮬레이션
//
//  Created by jiho park on 2019/11/20.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

int main(){
    int n;
    string s;
    size_t length;
    
    cin >> n;
    cin >> s;
    
    length = s.length();
    
    for(int k = 0; k < (n*2)+3; k++){
        for(int i = 0; i < length; i++){
            if(k == 0){
                if(s.at(i) == '1' || s.at(i) == '4'){
                    for(int j = 0; j < n+3; j++){
                        cout << ' ';
                    }
                }
                else{
                    cout << ' ';
                    for(int j = 0; j < n; j++){
                        cout << '-';
                    }
                    cout << "  ";
                }
            }
            else if(k <= n){
                if(s.at(i) == '1' || s.at(i) == '2' || s.at(i) == '3' || s.at(i) == '7'){
                    for(int j = 0; j < n+1; j++){
                        cout << ' ';
                    }
                    cout << "| ";
                }
                else if(s.at(i) == '5' || s.at(i) == '6'){
                    cout << '|';
                    for(int j = 0; j < n+2; j++){
                        cout << ' ';
                    }
                }
                else{
                    cout << '|';
                    for(int j = 0; j < n; j++){
                        cout << ' ';
                    }
                    cout << "| ";
                }
            }
            else if(k == n + 1){
                if(s.at(i) == '1' || s.at(i) == '7' || s.at(i) == '0'){
                    for(int j = 0; j < n+3; j++){
                        cout << ' ';
                    }
                }
                else{
                    cout << ' ';
                    for(int j = 0; j < n; j++){
                        cout << '-';
                    }
                    cout << "  ";
                }
            }
            else if(k < 2*n+2){
                if(s.at(i) == '2'){
                    cout << '|';
                    for(int j = 0; j < n+2; j++){
                        cout << ' ';
                    }
                }else if(s.at(i) == '6' || s.at(i) == '8' || s.at(i) == '0'){
                    cout << '|';
                    for(int j = 0; j < n; j++){
                        cout << ' ';
                    }
                    cout << "| ";
                }else{
                    for(int j = 0; j < n+1; j++){
                        cout << ' ';
                    }
                    cout << "| ";
                }
            }else{
                if(s.at(i) == '1' || s.at(i) == '4' || s.at(i) == '7'){
                    for(int j = 0; j < n+3; j++){
                        cout << ' ';
                    }
                }
                else{
                    cout << ' ';
                    for(int j = 0; j < n; j++){
                        cout << '-';
                    }
                    cout << "  ";
                }
            }
        }
        cout << endl;
    }
    
}
