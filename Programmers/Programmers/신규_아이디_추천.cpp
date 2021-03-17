#include <string>
#include <vector>
#include <iostream>

using namespace std;

string solution(string new_id) {
    for(int i=0; i<new_id.size(); i++){
        if(new_id[i] >= 'A' && new_id[i] <= 'Z'){
            new_id[i] = new_id[i] - 'A' + 'a';
        }
    }
    
    for(int i=0; i<new_id.size(); i++){
        if(!(new_id[i] >= 'a' && new_id[i] <= 'z') && !(new_id[i] >= '0' && new_id[i] <= '9') && new_id[i] != '_' && new_id[i] != '.' && new_id[i] != '-'){
            new_id.erase(new_id.begin()+i);
            i--;
        }
    }
    
    for(int i=0; i<new_id.size()-1; i++){
        if(new_id[i] == '.' && new_id[i+1] == '.'){
            new_id.erase(new_id.begin()+i);
            i--;
        }
    }
    
    if(new_id.size() > 0){
        if(new_id[0] == '.')
            new_id.erase(new_id.begin());
        if(new_id[new_id.size()-1] == '.')
            new_id.erase(new_id.begin()+new_id.size()-1);
    }
    
    if(new_id.size() == 0){
        new_id = "a";
    }
    
    if(new_id.size() >= 16){
        cout << "cut" << endl;
        new_id = new_id.substr(0, 15);
        
        if(new_id[0] == '.')
            new_id.erase(new_id.begin());
        if(new_id[new_id.size()-1] == '.')
            new_id.erase(new_id.begin()+new_id.size()-1);
    }
    
    if(new_id.size() <= 2){
        int iter = 3 - new_id.size();
        char new_ch = new_id[new_id.size()-1];
        while(iter--){
            new_id += new_ch;
        }
    }
    
    return new_id;
}
