#include <iostream>
#include <vector>
using namespace std;

// Lớp chứa các phương thức sắp xếp
template <typename T>
class Sorting
{
public:
    // Hàm in mảng trong khoảng từ start đến end
    static void printArray(T *start, T *end)
    {
        while (start <= end)
        {
            cout << *start << " ";
            start++;
        }
        cout << endl;
    }

    // Hàm trộn hai nửa đã sắp xếp
    static void merge(T *left, T *middle, T *right)
    {
        int leftSize = middle - left + 1;
        int rightSize = right - middle;

        // Tạo mảng tạm cho hai nửa
        std::vector<T> leftArray(left, middle + 1);
        std::vector<T> rightArray(middle + 1, right + 1);

        int i = 0, j = 0;
        T *k = left;

        // Trộn hai nửa
        while (i < leftSize && j < rightSize)
        {
            if (leftArray[i] <= rightArray[j])
            {
                *k = leftArray[i++];
            }
            else
            {
                *k = rightArray[j++];
            }
            k++;
        }

        // Sao chép phần còn lại của mảng trái (nếu có)
        while (i < leftSize)
        {
            *k = leftArray[i++];
            k++;
        }

        // Sao chép phần còn lại của mảng phải (nếu có)
        while (j < rightSize)
        {
            *k = rightArray[j++];
            k++;
        }

        Sorting::printArray(left, right); // In mảng sau khi gộp
    }

    // Thuật toán MergeSort
    static void mergeSort(T *start, T *end)
    {
        if (start >= end)
            return; // Điều kiện dừng đệ quy

        T *middle = start + (end - start) / 2; // Tìm phần tử giữa

        // Đệ quy sắp xếp hai nửa
        mergeSort(start, middle);   // Sắp xếp nửa bên trái
        mergeSort(middle + 1, end); // Sắp xếp nửa bên phải

        // Gộp hai nửa đã sắp xếp
        merge(start, middle, end);
    }
};

int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Mảng ban đầu: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Các bước thực hiện MergeSort:" << endl;
    Sorting<int>::mergeSort(&arr[0], &arr[n - 1]);

    cout << "Mảng sau khi sắp xếp: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
/*
int main()
{

    int arr[] = {0, 2, 4, 3, 1, 4};
    Sorting<int>::mergeSort(&arr[0], &arr[5]);

    /*
     *0, 2
     *0, 2, 4
     *1, 3
     *1, 3, 4
     *0, 1, 2, 3, 4, 4
     */