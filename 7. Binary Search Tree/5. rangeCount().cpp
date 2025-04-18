#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> // Để sử dụng std::reverse

using namespace std;

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

// Đếm số nút có giá trị nằm trong khoảng [lo, hi] trong BST
int rangeCount(BTNode *root, int lo, int hi)
{
    // Trường hợp cơ sở: cây rỗng
    if (root == NULL)
    {
        return 0;
    }

    int count = 0;

    // Kiểm tra nếu nút hiện tại nằm trong khoảng
    if (root->val >= lo && root->val <= hi)
    {
        count = 1;
    }

    // Nếu giá trị hiện tại lớn hơn hoặc bằng lo, duyệt cây con trái
    if (root->val >= lo)
    {
        count += rangeCount(root->left, lo, hi);
    }
    // Nếu giá trị hiện tại nhỏ hơn hoặc bằng hi, duyệt cây con phải
    if (root->val <= hi)
    {
        count += rangeCount(root->right, lo, hi);
    }

    return count;
}