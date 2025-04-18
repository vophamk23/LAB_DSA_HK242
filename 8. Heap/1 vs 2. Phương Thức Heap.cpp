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

// Kiểm tra heap có rỗng không
template <class T>
bool Heap<T>::isEmpty()
{
    return count == 0; // Nếu count = 0 thì heap rỗng
}

// Trả về số lượng phần tử trong heap
template <class T>
int Heap<T>::size()
{
    return count; // count lưu số lượng phần tử hiện tại
}

// Trả về phần tử lớn nhất (không xóa nó)
template <class T>
T Heap<T>::peek()
{
    if (count == 0)
        return (T)-1;   // Nếu heap rỗng, trả về -1
    return elements[0]; // Phần tử lớn nhất luôn ở vị trí đầu tiên (gốc) trong max heap
}

// Loại bỏ phần tử lớn nhất
template <class T>
bool Heap<T>::pop()
{
    if (count == 0)
        return false; // Nếu heap rỗng, không thể xóa, trả về false

    // Thay thế gốc (phần tử lớn nhất) bằng phần tử cuối cùng
    elements[0] = elements[count - 1];
    count--; // Giảm số lượng phần tử

    // Khôi phục tính chất của heap bằng cách di chuyển gốc mới xuống vị trí thích hợp
    reheapDown(0);
    return true; // Xóa thành công
}

// Kiểm tra một phần tử có tồn tại trong heap không
template <class T>
bool Heap<T>::contains(T item)
{
    // Duyệt qua tất cả các phần tử để tìm kiếm
    for (int i = 0; i < count; i++)
    {
        if (elements[i] == item)
            return true; // Nếu tìm thấy, trả về true
    }
    return false; // Không tìm thấy, trả về false
}

// Thêm một phần tử mới vào heap
template <class T>
void Heap<T>::push(T item)
{
    ensureCapacity(count + 1); // Đảm bảo có đủ dung lượng
    elements[count] = item;    // Thêm phần tử mới vào cuối
    reheapUp(count);           // Điều chỉnh vị trí để duy trì tính chất max heap
    count++;                   // Tăng số lượng phần tử
}

// Đảm bảo mảng có đủ dung lượng cho các phần tử mới
template <class T>
void Heap<T>::ensureCapacity(int minCapacity)
{
    if (minCapacity > capacity)
    {                                   // Nếu cần dung lượng lớn hơn hiện tại
        int newCapacity = capacity * 2; // Tăng gấp đôi dung lượng
        if (newCapacity < minCapacity)
            newCapacity = minCapacity; // Đảm bảo đủ dung lượng tối thiểu

        // Tạo mảng mới với dung lượng lớn hơn
        T *newElements = new T[newCapacity];
        // Sao chép các phần tử từ mảng cũ sang mảng mới
        for (int i = 0; i < count; i++)
        {
            newElements[i] = elements[i];
        }

        delete[] elements;      // Giải phóng bộ nhớ của mảng cũ
        elements = newElements; // Cập nhật con trỏ elements trỏ đến mảng mới
        capacity = newCapacity; // Cập nhật dung lượng mới
    }
}

// Điều chỉnh heap sau khi thêm phần tử mới
template <class T>
void Heap<T>::reheapUp(int position)
{
    if (position <= 0)
        return; // Nếu đã ở gốc, không cần điều chỉnh nữa

    int parent = (position - 1) / 2; // Tính vị trí của nút cha
    // Nếu phần tử hiện tại lớn hơn phần tử cha (vi phạm tính chất max heap)
    if (elements[position] > elements[parent])
    {
        // Hoán đổi phần tử hiện tại với phần tử cha
        T temp = elements[position];
        elements[position] = elements[parent];
        elements[parent] = temp;
        // Tiếp tục điều chỉnh từ vị trí cha
        reheapUp(parent);
    }
}

// Điều chỉnh heap sau khi xóa phần tử gốc
template <class T>
void Heap<T>::reheapDown(int position)
{
    int leftChild = position * 2 + 1;  // Vị trí con trái
    int rightChild = position * 2 + 2; // Vị trí con phải
    int largest = position;            // Giả sử vị trí hiện tại là lớn nhất

    // Kiểm tra nếu con trái tồn tại và lớn hơn vị trí hiện tại
    if (leftChild < count && elements[leftChild] > elements[largest])
    {
        largest = leftChild; // Cập nhật vị trí lớn nhất
    }

    // Kiểm tra nếu con phải tồn tại và lớn hơn vị trí lớn nhất hiện tại
    if (rightChild < count && elements[rightChild] > elements[largest])
    {
        largest = rightChild; // Cập nhật vị trí lớn nhất
    }

    // Nếu một trong các con lớn hơn vị trí hiện tại
    if (largest != position)
    {
        // Hoán đổi phần tử hiện tại với phần tử lớn nhất trong các con
        T temp = elements[position];
        elements[position] = elements[largest];
        elements[largest] = temp;

        // Tiếp tục điều chỉnh từ vị trí đã hoán đổi
        reheapDown(largest);
    }
}

// Hàm main để kiểm thử
int main()
{
    Heap<int> maxHeap;

    // Kiểm tra push và size
    for (int i = 0; i < 10; i++)
    {
        maxHeap.push(i);
    }
    cout << "Size: " << maxHeap.size() << endl;

    // Kiểm tra isEmpty
    cout << "Is empty: " << maxHeap.isEmpty() << endl;

    // Kiểm tra printHeap
    maxHeap.printHeap();

    // Kiểm tra peek
    cout << "Peek: " << maxHeap.peek() << endl;

    // Kiểm tra contains
    cout << "Contains 5: " << maxHeap.contains(5) << endl;
    cout << "Contains 15: " << maxHeap.contains(15) << endl;

    // Kiểm tra pop
    cout << "Pop: " << maxHeap.pop() << endl;
    maxHeap.printHeap();

    return 0;
}