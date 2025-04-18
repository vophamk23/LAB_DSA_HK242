
#include <iostream>
using namespace std;

template <class T>
class Sorting
{
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        int size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    static void selectionSort(T *start, T *end);
};

template <class T>
void Sorting<T>::selectionSort(T *start, T *end)
{
    T* result = start;
    while(start != end - 1){
//! Con trỏ min trỏ đến phần tử nhỏ nhất trong phạm vi chưa sắp xếp
        T* min = start;
//! Con trỏ tmp dùng để duyệt qua các phần tử còn lại
        T* tmp = start + 1;
        while(tmp != end){
//! Nếu phần tử tại tmp nhỏ hơn phần tử nhỏ nhất hiện tại, cập nhật min
            if(*tmp < * min){
                min = tmp;
            }
            tmp++;
        }
//! Hoán đổi phần tử nhỏ nhất tìm được với phần tử đầu tiên trong phạm vi chưa sắp xếp
        swap(*start, *min);
//! in ra phần tử 
        Sorting<T>::printArray(result,end);
        start++;
       
    }
}

int main(){
    int arr[] = {9, 2, 8, 1, 0, -2};
    Sorting<int>::selectionSort(&arr[0], &arr[6]);
    /*
    *-2, 0, 8, 1, 2, 9
    *-2, 0, 1, 8, 2, 9
    *-2, 0, 1, 2, 8, 9
    *-2, 0, 1, 2, 8, 9

    */
}