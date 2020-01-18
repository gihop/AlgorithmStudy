//
//  테트리스_3019.cpp
//  브루트포스
//
//  Created by jiho park on 2020/01/18.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

using namespace std;

int main(){
    int C[100];
    int c, p, ans=0;
    
    cin >> c >> p;
    
    for(int i=0; i<c; i++)
        cin >> C[i];
    
    switch(p){
        case 1:
            for(int i=0; i<c-3; i++)
                if(C[i]==C[i+1] && C[i+1]==C[i+2] && C[i+2]==C[i+3])
                    ans++;
            ans += c;
            break;
            
        case 2:
            for(int i=0; i<c-1; i++)
                if(C[i]==C[i+1])
                    ans++;
            break;
            
        case 3:
            for(int i=0; i<c-2; i++)
                if(C[i]==C[i+1] && C[i+1]==C[i+2]-1)
                    ans++;
            for(int i=0; i<c-1; i++)
                if(C[i]-1==C[i+1])
                    ans++;
            break;
            
        case 4:
            for(int i=0; i<c-2; i++)
                if(C[i]-1==C[i+1] && C[i+1]==C[i+2])
                    ans++;
            for(int i=0; i<c-1; i++)
                if(C[i]==C[i+1]-1)
                    ans++;
            break;
            
        case 5:
            for(int i=0; i<c-2; i++){
                if(C[i]==C[i+1] && C[i+1]==C[i+2])
                    ans++;
                if(C[i]==C[i+1]+1 && C[i+1]+1==C[i+2])
                    ans++;
            }
            for(int i=0; i<c-1; i++){
                if(C[i]==C[i+1]-1)
                    ans++;
                if(C[i]==C[i+1]+1)
                    ans++;
            }
            break;
            
        case 6:
            for(int i=0; i<c-2; i++){
                if(C[i]==C[i+1] && C[i+1]==C[i+2])
                    ans++;
                if(C[i]+1==C[i+1] && C[i+1]==C[i+2])
                    ans++;
            }
            for(int i=0; i<c-1; i++){
                if(C[i]==C[i+1]+2)
                    ans++;
                if(C[i]==C[i+1])
                    ans++;
            }
            break;
            
        case 7:
            for(int i=0; i<c-2; i++){
                if(C[i]==C[i+1] && C[i+1]==C[i+2])
                    ans++;
                if(C[i]==C[i+1] && C[i+1]==C[i+2]+1)
                    ans++;
            }
            for(int i=0; i<c-1; i++){
                if(C[i]==C[i+1]-2)
                    ans++;
                if(C[i]==C[i+1])
                    ans++;
            }
            break;
    }
    
    cout << ans;
    
    return 0;
}
