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
    void push(T item);     // Thêm một phần tử mới vào heap
    bool isEmpty();        // Kiểm tra heap có rỗng không
    bool contains(T item); // Kiểm tra phần tử có tồn tại trong heap không
    T peek();              // Lấy phần tử lớn nhất (không xóa)
    bool pop();            // Xóa phần tử lớn nhất
    int size();            // Trả về kích thước của heap

    int getItem(T item); // Tìm vị trí của phần tử trong heap
    void remove(T item); // Xóa một phần tử khỏi heap
    void clear();        // Xóa tất cả các phần tử trong heap

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
template <class T>
int Heap<T>::getItem(T item)
{
    // Tìm vị trí của phần tử có giá trị bằng item
    for (int i = 0; i < count; i++)
    {
        if (elements[i] == item)
        {
            return i; // Trả về chỉ số nếu tìm thấy
        }
    }
    return -1; // Trả về -1 nếu không tìm thấy phần tử
}

template <class T>
void Heap<T>::remove(T item)
{
    // Tìm vị trí của phần tử cần xóa
    int index = getItem(item);

    // Nếu không tìm thấy phần tử, kết thúc
    if (index == -1)
        return;

    // Thay thế phần tử cần xóa bằng phần tử cuối cùng
    elements[index] = elements[count - 1];
    count--; // Giảm kích thước heap

    // Nếu heap rỗng hoặc phần tử vừa xóa là phần tử cuối cùng, không cần sắp xếp lại
    if (count <= 0 || index == count)
        return;

    // Điều chỉnh heap để duy trì tính chất max heap
    // Nếu phần tử mới lớn hơn phần tử cha, reheapUp
    if (index > 0 && elements[index] > elements[(index - 1) / 2])
    {
        reheapUp(index);
    }
    // Ngược lại, reheapDown
    else
    {
        reheapDown(index);
    }
}

template <class T>
void Heap<T>::clear()
{
    // Đặt lại số lượng phần tử về 0
    count = 0;
    // Không cần giải phóng bộ nhớ vì chúng ta vẫn giữ mảng với dung lượng hiện tại
    // Chỉ cần đặt lại số lượng phần tử, các phần tử cũ sẽ bị ghi đè khi thêm phần tử mới
}