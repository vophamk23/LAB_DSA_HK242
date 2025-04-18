#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> // Để sử dụng std::reverse

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
 * Hàm đếm số nút "có một nút con" trong BST
 * Nút đó có nút con bên trái nhưng không có nút con bên phải, HOẶC
 * Nút đó có nút con bên phải nhưng không có nút con bên trái
 */
int singleChild(BSTNode *root)
{
    // Trường hợp cơ sở: nếu cây rỗng (root là nullptr), không có nút nào
    if (root == nullptr)
    {
        return 0;
    }
    int count = 0;

    // Kiểm tra nếu nút hiện tại có đúng một nút con
    // Trường hợp 1: Có con trái nhưng không có con phải
    if (root->left != nullptr && root->right == nullptr)
    {
        count++; // Nút con trái là "single child"
    }
    // Trường hợp 2: Có con phải nhưng không có con trái
    if (root->left == nullptr && root->right != nullptr)
    {
        count++; // Nút con phải là "single child"
    }

    // Đệ quy đếm số "single child" trong các cây con
    if (root->left != nullptr)
    {
        count += singleChild(root->left); // Đệ quy cho cây con trái
    }
    if (root->right != nullptr)
    {
        count += singleChild(root->right); // Đệ quy cho cây con phải
    }
    return count;
}
/*
// Biến toàn cục để theo dõi trong quá trình duyệt
int count = 0;
int result = -1; // Giá trị của phần tử nhỏ thứ k

// Hàm duyệt inorder
void inorderTraversal(BSTNode *node, int k)
{
    int count = 0; // Biến đếm số lượng phần tử đã duyệt
    // Nếu nút hiện tại là nullptr hoặc đã tìm thấy k phần tử, dừng lại
    if (node == nullptr || count >= k)
        return;

    // Duyệt cây con trái
    inorderTraversal(node->left, k);

    // Tăng biến đếm và kiểm tra
    count++;
    if (count == k)
    {
        result = node->val;
        return;
    }

    // Duyệt cây con phải
    inorderTraversal(node->right, k);
}

int kthSmallest(BSTNode *root, int k)
{
    // Reset biến toàn cục
    int count = 0;
    int result = -1;

    // Bắt đầu duyệt
    inorderTraversal(root, k);
    return result;
}*/