//
//  main.cpp
//  hello_quicksort
//
//  Created by jiho park on 08/08/2019.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename T>
size_t partition(vector<T>& data, size_t start, size_t end) {
    const auto& pivot = data[end];
    size_t current_small_loc = start;   //검은색 지시자
    
    // i 가 빨간색 지시자 역할을 한다
    for (size_t i = start; i <= end; i++) {
        if(data[i] <= pivot) {
            swap(data[current_small_loc++], data[i]);
        }
    }
    return current_small_loc - 1;
}

template <typename T>
void quicksort(vector<T>& data, size_t start, size_t end) {
    if(start >= end){
        return;
    }
    size_t pivot_pos = partition(data, start, end);
    quicksort(data, start, pivot_pos - 1);
    quicksort(data, pivot_pos + 1, end);
}
