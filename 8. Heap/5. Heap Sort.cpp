#define SEPARATOR "#<ab@17943918#@>#"
#ifndef SORTING_H
#define SORTING_H
#include <iostream>
#include <queue>
using namespace std;
template <class T>
class Sorting
{
private:
    // Hàm heapify để chuyển một cây con có gốc tại vị trí i thành một max heap
    static void heapify(T *arr, int n, int i)
    {
        int largest = i;       // Khởi tạo largest là root
        int left = 2 * i + 1;  // Vị trí con trái = 2*i + 1
        int right = 2 * i + 2; // Vị trí con phải = 2*i + 2

        // Nếu con trái lớn hơn gốc
        if (left < n && arr[left] > arr[largest])
            largest = left;

        // Nếu con phải lớn hơn gốc hoặc con trái
        if (right < n && arr[right] > arr[largest])
            largest = right;

        // Nếu largest không phải là gốc
        if (largest != i)
        {
            swap(arr[i], arr[largest]);

            // Đệ quy heapify cho cây con bị ảnh hưởng
            heapify(arr, n, largest);
        }
    }

public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        long size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    // Thuật toán Heap Sort
    static void heapSort(T *start, T *end)
    {
        int n = end - start;

        // Xây dựng max heap (sắp xếp mảng)
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(start, n, i);

        // Trích xuất từng phần tử từ heap
        for (int i = n - 1; i > 0; i--)
        {
            // Di chuyển current root về cuối
            swap(start[0], start[i]);

            // Gọi max heapify cho heap đã giảm kích thước
            heapify(start, i, 0);
        }

        Sorting<T>::printArray(start, end);
    }
};
#endif /* SORTING_H */