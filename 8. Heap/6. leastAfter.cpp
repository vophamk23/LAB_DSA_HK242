#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Hàm thực hiện k lần lấy số nhỏ nhất, nhân đôi và trả lại số nhỏ nhất cuối cùng
int leastAfter(vector<int> &nums, int k)
{
    // Khởi tạo min-heap (priority_queue kiểu nhỏ nhất)
    // Sử dụng greater<int> để tạo min-heap từ vector<int>
    // Cú pháp: priority_queue<type, container_type, comparison_type>
    // type: kiểu dữ liệu của phần tử trong heap
    // container_type: kiểu dữ liệu của container (vector<int>)
    // comparison_type: kiểu so sánh (greater<int> để tạo min-heap)
    // priority_queue<int, vector<int>, greater<int>> minHeap;
    // Tạo min-heap từ vector nums
    priority_queue<int, vector<int>, greater<int>> minHeap;

    // Đưa tất cả phần tử mảng vào min-heap
    for (int num : nums)
    {
        minHeap.push(num);
    }

    // Thực hiện k lần thao tác: lấy nhỏ nhất, nhân đôi, đưa lại vào heap
    for (int i = 0; i < k; ++i)
    {
        int smallest = minHeap.top(); // lấy số nhỏ nhất
        minHeap.pop();                // loại bỏ khỏi heap
        minHeap.push(smallest * 2);   // nhân đôi và đưa lại vào heap
    }

    // Giá trị nhỏ nhất còn lại sau k lần thao tác
    return minHeap.top();
}
