//
//  main.cpp
//  hello_merge_sort
//
//  Created by jiho park on 06/08/2019.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
vector<T> merge(const vector<T>& A, const vector<T>& B) {
    if(A.empty()){
        return B;
    } else if(B.empty()){
        return A;
    }
    
    vector<T> merged;
    merged.reserve(A.size() + B.size());
    
    size_t current_a = 0, current_b = 0;
    
    while(current_a < A.size() && current_b < B.size()) {
        if(A[current_a] <= B[current_b]) {
            merged.push_back(A[current_a++]);
            if(current_a == A.size()) {
                merged.insert(merged.end(), B.begin() + current_b, B.end());
                return merged;
            }
        } else if(A[current_a] > B[current_b]) {
            merged.push_back(B[current_b++]);
            if(current_b == B.size()){
                merged.insert(merged.end(), A.begin() + current_a, A.end());
                return merged;
            }
        }
    }
    return merged;
}

int main() {
    vector<int> A = {2, 5, 7, 10};
    vector<int> B = {1, 3, 8, 9};
    vector<int> merged = merge(A, B);
    
    for(int num : merged) {
        cout << num << " ";
    }
    
}
