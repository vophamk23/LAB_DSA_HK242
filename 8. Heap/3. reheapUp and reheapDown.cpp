#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template <class T>
class Heap
{
protected:
    T *elements;  // Mảng động lưu trữ các phần tử của heap
    int capacity; // Sức chứa hiện tại của mảng
    int count;    // Số lượng phần tử hiện có trong heap
public:
    Heap()
    {
        this->capacity = 10;              // Khởi tạo sức chứa ban đầu là 10
        this->count = 0;                  // Khởi tạo số lượng phần tử ban đầu là 0
        this->elements = new T[capacity]; // Cấp phát mảng động
    }
    ~Heap()
    {
        delete[] elements; // Giải phóng bộ nhớ khi đối tượng bị hủy
    }
    void push(T item);

    bool isEmpty();        // Kiểm tra heap có rỗng không
    bool contains(T item); // Kiểm tra phần tử có tồn tại trong heap không
    T peek();              // Lấy phần tử lớn nhất (không xóa)
    bool pop();            // Xóa phần tử lớn nhất
    int size();            // Trả về kích thước của heap

    void printHeap() // In ra tất cả các phần tử trong heap
    {
        cout << "Max Heap [ ";
        for (int i = 0; i < count; i++)
            cout << elements[i] << " ";
        cout << "]\n";
    }

private:
    void ensureCapacity(int minCapacity); // Đảm bảo mảng có đủ dung lượng
    void reheapUp(int position);          // Sắp xếp lại heap khi thêm phần tử mới
    void reheapDown(int position);        // Sắp xếp lại heap khi xóa phần tử
};

// Hàm reheapDown cho một max heap
// Hàm này được sử dụng khi một phần tử có thể nhỏ hơn các phần tử con của nó
// và cần được di chuyển xuống để duy trì tính chất của max heap
void reheapDown(int maxHeap[], int numberOfElements, int index)
{
    // Tính chỉ số của con trái và con phải
    int leftChildIndex = 2 * index + 1;
    int rightChildIndex = 2 * index + 2;
    int largestIndex = index; // Giả định vị trí hiện tại có giá trị lớn nhất

    // Kiểm tra nếu con trái tồn tại và có giá trị lớn hơn giá trị lớn nhất hiện tại
    if (leftChildIndex < numberOfElements && maxHeap[leftChildIndex] > maxHeap[largestIndex])
    {
        largestIndex = leftChildIndex;
    }

    // Kiểm tra nếu con phải tồn tại và có giá trị lớn hơn giá trị lớn nhất hiện tại
    if (rightChildIndex < numberOfElements && maxHeap[rightChildIndex] > maxHeap[largestIndex])
    {
        largestIndex = rightChildIndex;
    }

    // Nếu giá trị lớn nhất không nằm ở vị trí hiện tại, hoán đổi và tiếp tục reheap down
    if (largestIndex != index)
    {
        // Hoán đổi các phần tử
        int temp = maxHeap[index];
        maxHeap[index] = maxHeap[largestIndex];
        maxHeap[largestIndex] = temp;

        // Đệ quy reheap down từ vị trí mới
        reheapDown(maxHeap, numberOfElements, largestIndex);
    }
}

// Hàm reheapUp cho một max heap
// Hàm này được sử dụng khi một phần tử có thể lớn hơn phần tử cha của nó
// và cần được di chuyển lên để duy trì tính chất của max heap
void reheapUp(int maxHeap[], int numberOfElements, int index)
{
    // Nếu đang ở gốc hoặc phần tử cha lớn hơn, không cần làm gì cả
    if (index == 0)
    {
        return;
    }

    // Tính chỉ số của phần tử cha
    int parentIndex = (index - 1) / 2;

    // Nếu phần tử hiện tại lớn hơn phần tử cha, hoán đổi chúng và tiếp tục reheap up
    if (maxHeap[index] > maxHeap[parentIndex])
    {
        // Hoán đổi các phần tử
        int temp = maxHeap[index];
        maxHeap[index] = maxHeap[parentIndex];
        maxHeap[parentIndex] = temp;

        // Đệ quy reheap up từ vị trí cha
        reheapUp(maxHeap, numberOfElements, parentIndex);
    }
}

/**

1. Hàm reheapDown:
Mục đích: Di chuyển một phần tử xuống vị trí thích hợp trong heap để duy trì tính chất của max heap.
Cách hoạt động:
- Tìm chỉ số của hai phần tử con (trái và phải)
- Xác định phần tử lớn nhất trong ba phần tử (phần tử hiện tại và hai phần tử con)
- Nếu phần tử lớn nhất không phải là phần tử hiện tại, thực hiện hoán đổi
- Tiếp tục đệ quy quá trình này cho nút con đã bị hoán đổi

2. Hàm reheapUp:
Mục đích: Di chuyển một phần tử lên vị trí thích hợp trong heap để duy trì tính chất của max heap.
Cách hoạt động:
- Tính chỉ số của phần tử cha
- So sánh phần tử hiện tại với phần tử cha
- Nếu phần tử hiện tại lớn hơn phần tử cha, thực hiện hoán đổi
- Tiếp tục đệ quy quá trình này cho vị trí cha


Hai hàm này là nền tảng để xây dựng và duy trì một max heap. Chúng thường được sử dụng trong các hoạt động như:
- Thêm một phần tử mới vào heap (sử dụng reheapUp)
- Xóa phần tử lớn nhất khỏi heap (sử dụng reheapDown)
- Xây dựng một heap từ một mảng ban đầu (sử dụng cả hai hàm)

Trong các ví dụ kiểm thử:

Khi gọi reheapDown(arr,size,0) trên mảng [1,2,3,4,5,6,7,8], hàm sẽ điều chỉnh phần tử tại vị trí 0 (giá trị 1) và các phần tử con của nó để tạo thành một max heap cục bộ.
Khi gọi reheapUp(arr,size,7) trên mảng [1,2,3,4,5,6,7,8], hàm sẽ điều chỉnh phần tử tại vị trí 7 (giá trị 8) và các phần tử cha của nó để tạo thành một max heap cục bộ.
 */