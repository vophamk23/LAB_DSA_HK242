#include <iostream>
#include <string>
#include <queue>
#include <map>

using namespace std;

class PrinterQueue
{
private:
    // Sử dụng map để lưu trữ các file theo priority
    // key là priority, value là queue các file cùng priority đó
    // Sử dụng map<int, queue<string>> để lưu trữ các file theo priority
    map<int, queue<string>> requestMap;

public:
    // Thêm file mới vào hàng đợi
    // priority là độ ưu tiên (số nguyên dương), fileName là tên file
    // Nếu priority đã tồn tại, thêm file vào hàng đợi tương ứng
    void addNewRequest(int priority, string fileName)
    {
        requestMap[priority].push(fileName);
    }

    // In file theo quy tắc: ưu tiên cao nhất trước, cùng ưu tiên thì FIFO
    void print()
    {
        // Nếu hàng đợi trống
        if (requestMap.empty())
        {
            cout << "No file to print" << endl;
            return;
        }

        // Tìm priority cao nhất (map sắp xếp tăng dần => rbegin() là lớn nhất)
        // Sử dụng iterator để duyệt map từ cuối (priority cao nhất)
        // auto it = requestMap.end(); // Đặt it ở cuối map
        // it--; // Quay lại một bước để lấy phần tử cuối cùng (priority cao nhất)
        // Hoặc có thể sử dụng rbegin() để lấy iterator từ cuối map
        // auto it = requestMap.rbegin(); // Lấy iterator từ cuối map
        auto it = requestMap.rbegin();
        int highestPriority = it->first;
        string fileToPrint = it->second.front();
        it->second.pop(); // Xóa file vừa in ra khỏi queue

        cout << fileToPrint << endl;

        // Nếu queue tại priority này đã hết file, xóa luôn priority đó khỏi map
        if (it->second.empty())
        {
            requestMap.erase(highestPriority);
        }
    }
};
