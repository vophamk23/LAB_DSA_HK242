#include <iostream>
#include <algorithm> // Cho hàm min
using namespace std;

template <class T>
class Sorting
{
public:
    // Hàm in mảng từ vị trí start đến end
    static void printArray(T *start, T *end)
    {
        while (start < end)
        {
            cout << *start << " ";
            start++;
        }
        cout << endl;
    }

    // Hàm trộn hai mảng con đã sắp xếp
    static void merge(T *start, T *middle, T *end)
    {
        // Tính kích thước của hai mảng con cần trộn
        int left_size = middle - start;
        int right_size = end - middle;

        // Tạo các mảng tạm thời
        T *left = new T[left_size];
        T *right = new T[right_size];

        // Sao chép dữ liệu vào mảng tạm thời bên trái
        for (int i = 0; i < left_size; i++)
            left[i] = start[i];

        // Sao chép dữ liệu vào mảng tạm thời bên phải
        for (int j = 0; j < right_size; j++)
            right[j] = *(middle + j); // Sửa lại thành middle + j

        // Trộn các mảng tạm thời trở lại mảng gốc
        int i = 0; // Chỉ số đầu tiên của mảng con thứ nhất
        int j = 0; // Chỉ số đầu tiên của mảng con thứ hai
        int k = 0; // Chỉ số đầu tiên của mảng sau khi trộn

        // So sánh và trộn các phần tử từ hai mảng con
        while (i < left_size && j < right_size)
        {
            if (left[i] <= right[j])
            {
                start[k] = left[i];
                i++;
            }
            else
            {
                start[k] = right[j];
                j++;
            }
            k++;
        }

        // Sao chép các phần tử còn lại của mảng left[] (nếu có)
        while (i < left_size)
        {
            start[k] = left[i];
            i++;
            k++;
        }

        // Sao chép các phần tử còn lại của mảng right[] (nếu có)
        while (j < right_size)
        {
            start[k] = right[j];
            j++;
            k++;
        }

        // Giải phóng bộ nhớ đã cấp phát
        delete[] left;
        delete[] right;
    }

    // Thuật toán Insertion Sort để sắp xếp các mảng con nhỏ
    static void InsertionSort(T *start, T *end)
    {
        int size = end - start;

        for (int i = 1; i < size; i++)
        {
            T key = start[i]; // Lấy phần tử hiện tại
            int j = i - 1;

            // Di chuyển các phần tử lớn hơn key về sau một vị trí
            while (j >= 0 && start[j] > key)
            {
                start[j + 1] = start[j];
                j--;
            }
            start[j + 1] = key; // Đặt key vào vị trí đúng
        }
    }

    // Thuật toán TimSort - kết hợp Insertion Sort và Merge Sort
    static void TimSort(T *start, T *end, int min_size)
    {
        int size = end - start;

        // Sắp xếp các mảng con có kích thước min_size bằng InsertionSort
        for (int i = 0; i < size; i += min_size)
        {
            int subarray_end = min(i + min_size, size);
            InsertionSort(start + i, start + subarray_end);
        }

        // In mảng sau khi đã sắp xếp bằng Insertion Sort
        cout << "Sau Insertion Sort: ";
        printArray(start, end);

        // Giai đoạn trộn
        int merge_count = 1;

        // Bắt đầu với min_size, sau đó nhân đôi kích thước của các mảng con được trộn
        for (int curr_size = min_size; curr_size < size; curr_size = 2 * curr_size)
        {
            // Duyệt qua mảng với bước nhảy 2*curr_size
            for (int left_start = 0; left_start < size; left_start += 2 * curr_size)
            {
                // Tìm điểm kết thúc của mảng con bên trái
                int mid = min(left_start + curr_size, size);

                // Tìm điểm kết thúc của mảng con bên phải
                int right_end = min(left_start + 2 * curr_size, size);

                // Trộn các mảng con nếu điểm giữa nằm trước right_end
                if (mid < right_end)
                {
                    merge(start + left_start, start + mid, start + right_end);
                    cout << "Trộn lần " << merge_count << ": ";
                    printArray(start, end);
                    merge_count++;
                }
            }
        }
    }
};

int main()
{
    int arr[] = {5, 21, 7, 23, 19, 45, 8, 56, 12, 15, 45, 89, 22, 13, 24, 43};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Mảng ban đầu: ";
    Sorting<int>::printArray(arr, arr + n);

    // Sử dụng TimSort với min_size = 4
    Sorting<int>::TimSort(arr, arr + n, 4);

    cout << "Mảng sau khi sắp xếp: ";
    Sorting<int>::printArray(arr, arr + n);

    return 0;
}