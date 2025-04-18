#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
class QuickSortImplementation
{
public:
    static T *Partition(T *start, T *end)
    {
        // Trả về con trỏ đến phần tử pivot sau khi sắp xếp lại mảng
        T *arr = start;
        int low = 0, high = end - start - 1;
        int pivot = arr[low]; // Chọn phần tử đầu tiên làm pivot
        int i = low, j = high + 1;

        do
        {
            // Tìm phần tử bên trái đầu tiên lớn hơn hoặc bằng pivot
            do
            {
                i++;
            } while (i <= high && arr[i] < pivot);

            // Tìm phần tử bên phải đầu tiên nhỏ hơn hoặc bằng pivot
            do
            {
                j--;
            } while (j >= low && arr[j] > pivot);

            // Nếu hai con trỏ gặp nhau, kết thúc vòng lặp
            if (i >= j)
            {
                break;
            }

            // Đổi chỗ hai phần tử không đúng thứ tự
            swap(arr[i], arr[j]);
        } while (i <= j);

        // Đưa pivot vào vị trí đúng trong mảng
        swap(arr[low], arr[j]);

        // In ra vị trí của pivot sau khi phân vùng
        cout << j << " ";

        // Trả về con trỏ đến vị trí của pivot
        return start + j;
    }

    static void QuickSort(T *start, T *end)
    {
        // Thuật toán QuickSort sử dụng đệ quy
        // In ra chỉ số của pivot trong mảng con sau mỗi lần gọi phương thức Partition
        if (start < end)
        {
            T *pivot = Partition(start, end);
            QuickSort(start, pivot);   // Sắp xếp mảng con bên trái của pivot
            QuickSort(pivot + 1, end); // Sắp xếp mảng con bên phải của pivot
        }
    }

    // Hàm tiện ích để in mảng
    static void printArray(T arr[], int size)
    {
        cout << "Mảng sau khi sắp xếp: ";
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Mảng ban đầu: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Các vị trí pivot sau mỗi lần phân vùng: ";
    QuickSortImplementation<int>::QuickSort(arr, arr + n);
    cout << endl;

    QuickSortImplementation<int>::printArray(arr, n);

    return 0;
}