#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>     // Để sử dụng std::reverse
#include <stack>         // Để sử dụng std::stack
#include <cmath>         // Để sử dụng std::abs
#include <limits>        // Để sử dụng std::numeric_limits
#include <string>        // Để sử dụng std::string
#include <unordered_map> // Để sử dụng std::unordered_map
#include <unordered_set> // Để sử dụng std::unordered_set
#include <map>           // Để sử dụng std::map

using namespace std;
class BSTNode
{
public:
    int val;
    BSTNode *left;
    BSTNode *right;
    BSTNode()
    {
        this->left = this->right = nullptr;
    }
    BSTNode(int val)
    {
        this->val = val;
        this->left = this->right = nullptr;
    }
    BSTNode(int val, BSTNode *&left, BSTNode *&right)
    {
        this->val = val;
        this->left = left;
        this->right = right;
    }
};

/**
 * Hàm chèn một giá trị vào cây nhị phân tìm kiếm (BST)
 * Nếu giá trị đã tồn tại trong cây, không làm gì cả
 */
BSTNode *insert(BSTNode *root, int val)
{
    if (root == nullptr)
    {
        return new BSTNode(val);
    }
    if (val < root->val)
    {
        root->left = insert(root->left, val);
    }
    else if (val > root->val)
    {
        root->right = insert(root->right, val);
    }
    return root;
}

/**
 * Hàm tìm phần tử nhỏ thứ k trong cây nhị phân tìm kiếm (BST)
 * Sử dụng duyệt inorder không đệ quy để lấy các phần tử theo thứ tự tăng dần
 * Sau đó trả về phần tử thứ k
 */
int kthSmallest(BSTNode *root, int k)
{
    // Sử dụng stack để duyệt inorder
    stack<BSTNode *> nodeStack;
    BSTNode *current = root;
    int count = 0;

    // Duyệt inorder không đệ quy
    while (current != nullptr || !nodeStack.empty())
    {
        // Đi xuống hết bên trái
        while (current != nullptr)
        {
            nodeStack.push(current);
            current = current->left;
        }
        // Lấy phần tử nhỏ nhất tiếp theo
        current = nodeStack.top();
        nodeStack.pop();

        // Tăng biến đếm
        count++;
        if (count == k)
        {
            return current->val;
        }

        // Chuyển sang duyệt cây con phải
        current = current->right;
    }

    return -1; // Trường hợp k > số lượng node trong cây
}