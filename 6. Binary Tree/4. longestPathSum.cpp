#include <iostream>
#include <string>
using namespace std;
#include <queue>
#include <utility> // for std::pair

class BTNode
{
public:
    int val;
    BTNode *left;
    BTNode *right;
    BTNode()
    {
        this->left = this->right = NULL;
    }
    BTNode(int val)
    {
        this->val = val;
        this->left = this->right = NULL;
    }
    BTNode(int val, BTNode *&left, BTNode *&right)
    {
        this->val = val;
        this->left = left;
        this->right = right;
    }
};
int longestPathSum(BTNode *root)
{
    // Nếu cây rỗng, trả về 0
    if (root == NULL)
        return 0;

    // Biến để lưu trữ độ dài đường đi dài nhất và tổng giá trị của nó
    int maxLength = -1; // Độ dài path dài nhất Tổng số node
    int maxSum = 0;     // Tổng giá trị path dài nhất của tất cả cách Node

    // Sử dụng hàng đợi để duyệt cây theo chiều rộng (BFS)
    // Mỗi phần tử trong hàng đợi lưu: {node, chiều dài path tới node, tổng giá trị path tới node}
    queue<pair<BTNode *, pair<int, int>>> q;
    // Khởi tạo hàng đợi với nút gốc
    // Bắt đầu từ nút gốc với chiều dài 1 và tổng giá trị bằng giá trị của nút gốc
    q.push({root, {1, root->val}}); // Độ dài là 1 vì bắt đầu từ nút gốc
    // Duyệt hàng đợi cho đến khi nó rỗng
    while (!q.empty())
    {
        // Mỗi phần tử trong hàng đợi chứa ba thông tin:

        BTNode *node = q.front().first;      // Một con trỏ đến nút hiện tại
        int length = q.front().second.first; // Độ dài của đường đi từ gốc đến nút hiện tại
        int sum = q.front().second.second;   // Tổng giá trị của tất cả các nút trên đường đi đó
        q.pop();

        // Kiểm tra nếu là nút lá (không có con trái và phải)
        // Khi gặp một nút lá (không có con trái và con phải),
        // so sánh độ dài đường đi với độ dài đường đi dài nhất đã tìm thấy:
        if (node->left == NULL && node->right == NULL)
        {
            // Cập nhật maxLength và maxSum tương ứng nếu tìm thấy
            //  đường đi hiện tại dài hơn
            //  đường đi hiện tại có cùng độ dài với đường đi dài nhất,nhưng có tổng giá trị lớn hơn
            if (length > maxLength || (length == maxLength && sum > maxSum))
            {
                maxLength = length;
                maxSum = sum;
            }
        }
        // Thêm con trái vào hàng đợi nếu tồn tại
        if (node->left != NULL)
        {
            q.push({node->left, {length + 1, sum + node->left->val}});
        }
        // Thêm con phải vào hàng đợi nếu tồn tại
        if (node->right != NULL)
        {
            q.push({node->right, {length + 1, sum + node->right->val}});
        }
    }
    // Cuối cùng, hàm trả về tổng giá trị của đường đi dài nhất
    // từ gốc đến nút lá (hoặc nếu có nhiều đường đi cùng độ dài thì trả về đường đi có tổng lớn nhất).
    return maxSum;
}
/*
Độ phức tạp:
Thời gian: O(n) - mỗi nút trong cây được duyệt qua đúng một lần
Không gian: O(w) - với w là chiều rộng lớn nhất của cây (số lượng nút tối đa ở một tầng)
*/
