#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class Sorting {
private:
    static void printArray(T* start, T* end)
    {
        int size = end - start;
        for (int i = 0; i < size; i++)
            cout << start[i] << " ";

        cout << endl;
    }

public:
    // TODO: Write your code here
    static void sortSegment(T* start, T* end, int segment_idx, int cur_segment_total);
    static void ShellSort(T* start, T* end, int* num_segment_list, int num_phases);
};

template <class T>
// !Hàm sortSegment thực hiện sắp xếp một đoạn (segment) của mảng bằng phương pháp insertion sort
void Sorting<T>::sortSegment(T* start, T* end, int segment_idx, int cur_segment_total) {
   
//! Con trỏ left trỏ vào phần tử bắt đầu của segment hiện tại
    T* left = start + segment_idx;
  
    while(left <= end - cur_segment_total){
//! Con trỏ tmp dùng để duyệt qua các phần tử trong segment
        T* tmp = start + segment_idx;
     
        while(tmp <= end - cur_segment_total - 1){
//! So sánh phần tử hiện tại với phần tử cách cur_segment_total vị trí sau
            if(* tmp > * (tmp + cur_segment_total)) swap(*tmp,* (tmp + cur_segment_total));
//!  Di chuyển tmp đến phần tử tiếp theo cách cur_segment_total vị trí           
            tmp += cur_segment_total;
             
        }
//! Di chuyển left đến phần tử bắt đầu của segment tiếp theo
        left += cur_segment_total;
       
    }
      
}

template <class T>
//! Hàm ShellSort thực hiện thuật toán Shell sort trên mảng từ start đến end
 void  Sorting<T>::ShellSort(T* start, T* end, int* num_segment_list, int num_phases) {

//! Duyệt qua các pha sắp xếp theo danh sách độ dài segment đã cho   
    for(int i = num_phases-1; i >= 0; i--){
        //! Duyệt qua các segment trong pha hiện tại
        for(int j = 0; j < num_segment_list[i];j ++ ){

             //! Sắp xếp từng segment
            
            sortSegment(start, end,j , num_segment_list[i]);
          
        }
        cout << num_segment_list[i] << " segments: ";
        T* tmp = start;
        Sorting<T>::printArray(start,end);
    }
    
}

int main(){

int num_segment_list[] = {1, 3, 5};
int num_phases = 2;
int array[] = { 10, 9, 8 , 7 , 6, 5, 4, 3, 2, 1 };

Sorting<int>::ShellSort(&array[0], &array[10], &num_segment_list[0], num_phases);
    //!5 segments: 5 4 3 2 1 10 9 8 7 6 
    //!3 segments: 2 1 3 5 4 7 6 8 10 9 
   //!1 segments: 1 2 3 4 5 6 7 8 9 10 
}