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
// Hàm loại bỏ các nút trong (BST) có giá trị nằm ngoài khoảng [lo, hi]
// Trả về con trỏ đến gốc của cây mới
// Các nút có giá trị nằm ngoài khoảng [lo, hi] sẽ bị loại bỏ
// Các nút có giá trị nằm trong khoảng [lo, hi] sẽ được giữ lại
BSTNode *subtreeWithRange(BSTNode *root, int lo, int hi)
{
    // Trường hợp cơ sở: nếu cây rỗng
    if (root == nullptr)
    {
        return nullptr;
    }
    // Nếu giá trị của nút hiện tại nhỏ hơn lo,
    // bỏ qua nút hiện tại và cây con trái, chỉ xét cây con phải
    if (root->val < lo)
    {
        return subtreeWithRange(root->right, lo, hi);
    }
    // Nếu giá trị của nút hiện tại lớn hơn hi,
    // bỏ qua nút hiện tại và cây con phải, chỉ xét cây con trái
    if (root->val > hi)
    {
        return subtreeWithRange(root->left, lo, hi);
    }

    // Nếu giá trị của nút hiện tại nằm trong khoảng [lo, hi]
    // Giữ lại nút này và tiếp tục xử lý cả cây con trái và phải
    root->left = subtreeWithRange(root->left, lo, hi);
    root->right = subtreeWithRange(root->right, lo, hi);

    return root; // Trả về NÚT hiện tại (nó nằm trong khoảng [lo, hi])
}