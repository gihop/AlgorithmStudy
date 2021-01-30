#include <iostream>
using namespace std;
//퀵정렬
int n,cnt, quick[10];

void quickSort(int i, int j)
{
    if(i>=j) return;
    int pivot = quick[(i+j)/2];
    int left = i;
    int right = j;
    
    while(left<=right)
    {
        while(quick[left]<pivot) left++;
        while(quick[right]>pivot) right--;
        if(left<=right)
        {
            swap(quick[left],quick[right]);
            left++; right--;
        }
    }
    quickSort(i,right);
    quickSort(left,j);
}

int main()
{
    n = 7;
    
    quick[0] = 3;
    quick[1] = 2;
    quick[2] = 5;
    quick[3] = 1;
    quick[4] = 7;
    quick[5] = 4;
    quick[6] = 6;
    
    
    quickSort(0,n-1);
    
    for(int j = 0; j < n; j++) // 출력
        printf("%d\n",quick[j]);
}
