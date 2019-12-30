//
//  링크와_스타트_15661.cpp
//  브루트포스
//
//  Created by jiho park on 2019/11/21.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;
//
//void push(vector<int> &a, int n){
//    for(int i=1; i<=n; i++){
//        a.push_back(i);
//    }
//}
//
//int main() {
//    int n, N, index, answer = INT_MAX, a, b;
//    int arr[20][20];
//    vector<int> first, second;
//
//    cin >> n;
//
//
//    for(int i=0; i<n; i++){
//        for(int j=0; j<n; j++){
//            cin >> arr[i][j];
//        }
//    }
//
//    for(int i=1; i<=n; i++){
////        a = 0;
////        b = 0;
//        first.clear();
//        push(second, n);
//        N = n;
//        index = i;
//        int index2 = i-1;
//        while(N--){
//            a = 0;
//            b = 0;
//            if(second.size() <= index2)
//                index2 = 0;
////            if(second.size() == 1)
////                index2 = 0;
////            int t = second.size();
//            second.erase(second.begin()+index2);
//            first.push_back(index);
//
//            for(int j=0; j<first.size(); j++){
//                for(int k=0; k<first.size(); k++){
//                    a += arr[first[j]-1][first[k]-1];
//                }
//            }
//
//            for(int j=0; j<second.size(); j++){
//                for(int k=0; k<second.size(); k++){
//                    b += arr[second[j]-1][second[k]-1];
//                }
//            }
//            int temp;
//            if(a>b)
//                temp = a-b;
//            else
//                temp = b-a;
//
//            if(answer > temp)
//                answer = temp;
//            if(index+1 > n)
//                index = (index+1)%n;
//            else
//                index++;
//        }
//    }
//    cout << answer << endl;
//}

int s[20][20];
int n;

int go(int index, vector<int> first, vector<int> second){
    if(index == n){
        if(first.size() == 0)
            return -1;
        if(second.size() == 0)
            return -1;
        int t1 = 0, t2 = 0;
        
        for(int i=0; i<first.size(); i++)
            for(int j=0; j<first.size(); j++)
                t1 += s[first[i]][first[j]];
            
        for(int i=0; i<second.size(); i++)
            for(int j=0; j<second.size(); j++)
                t2 += s[second[i]][second[j]];
        
        int diff = t1 - t2;
        if(diff < 0) diff = -diff;
        
        return diff;
    }
    int ans = -1;
    first.push_back(index);
    int t1 = go(index+1, first, second);
    if(ans == -1 || (t1 != -1 && ans > t1))
        ans = t1;
    first.pop_back();
    
    second.push_back(index);
    int t2 = go(index+1, first, second);
    if(ans == -1 || (t2 != -1 && ans > t2))
        ans = t2;
    second.pop_back();
    
    return ans;
}

int main(){
    cin >> n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> s[i][j];
    
    vector<int> first, second;
    
    cout << go(0, first, second) << endl;
}
