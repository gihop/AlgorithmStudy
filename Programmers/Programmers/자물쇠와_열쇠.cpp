#include <string>
#include <vector>

using namespace std;

int key_size, lock_size, size;

vector<vector<int>> rotate(vector<vector<int>> key){
    vector<vector<int>> next(key_size, vector<int>(key_size,0));
    for(int i=0; i<next.size(); i++){
        for(int j=0; j<next.size(); j++){
            next[j][next.size()-1-i] = key[i][j];
        }
    }
    return next;
}

bool check(vector<vector<int>> array){
    bool checked=true;
    
    for(int i=key_size-1; i<key_size+lock_size-1; i++){
        for(int j=key_size-1; j<key_size+lock_size-1; j++){
            if(array[i][j]!=1){
                checked = false;
                break;
            }
        }
        if(!checked) break;
    }
    return checked;
}

bool add(vector<vector<int>> array, vector<vector<int>> key, int x, int y){
    for(int i=0; i<key_size; i++){
        for(int j=0; j<key_size; j++){
            array[i+x][j+y]+=key[i][j];
        }
    }
    return check(array);
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    bool answer = false;
    size = lock.size()+key.size()*2-2;
    lock_size = lock.size();
    key_size = key.size();
    vector<vector<int>> array(size, vector<int>(size,0));
    for(int i=key_size-1; i<key_size+lock_size-1; i++){
        for(int j=key_size-1; j<key_size+lock_size-1; j++){
            array[i][j] = lock[i-key_size+1][j-key_size+1];
        }
    }
    for(int rot=0; rot<4; rot++){
        for(int i=0; i<size-key.size()+1; i++){
            for(int j=0; j<size-key.size()+1; j++){
                if(add(array, key, i,j)){
                    answer = true;
                    break;
                }
            }
            if(answer) break;
        }
        if(answer) break;
        key = rotate(key);
    }
    
    return answer;
}
