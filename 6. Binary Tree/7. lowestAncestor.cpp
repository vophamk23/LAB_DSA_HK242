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
// Hàm trợ giúp để tìm một nút có giá trị cụ thể VAL trong cây nhị phân
BTNode *findNode(BTNode *root, int val)
{
    // Nếu cây rỗng (root là NULL), trả về NULL (không tìm thấy)
    // Nếu không tìm thấy nút có giá trị val, trả về NULL
    // Nếu tìm thấy nút có giá trị val, trả về con trỏ đến nút đó
    if (root == NULL)
        return NULL; // Nếu root là NULL, trả về NULL (không tìm thấy)
    if (root->val == val)
        return root; // Nếu giá trị của nút hiện tại bằng val, trả về nút hiện tại

    // Đệ quy tìm kiếm trong cây con trái
    BTNode *leftResult = findNode(root->left, val);
    if (leftResult != NULL)
        return leftResult; // Nếu tìm thấy trong cây con trái, trả về kết quả đó

    return findNode(root->right, val); // Nếu không, đệ quy tìm kiếm trong cây con phải và trả về kết quả
}

// Hàm trợ giúp để Tìm tổ tiên chung thấp nhất của hai nút nodeA và nodeB.
// Thuật toán: Dùng phương pháp đệ quy để tìm kiếm từ gốc xuống.
BTNode *findLCA(BTNode *root, BTNode *nodeA, BTNode *nodeB)
{
    // Nếu root là NULL, trả về NULL (không có tổ tiên chung)
    if (root == NULL)
        return NULL;

    // Nếu root trùng với nodeA hoặc nodeB, trả về root (vì một nút cũng là tổ tiên của chính nó)
    if (root == nodeA || root == nodeB)
        return root;

    // Tìm kiếm a và b trong cây con trái và cây con phải
    // Đệ quy tìm kiếm tổ tiên chung trong cây con trái (leftLCA)
    BTNode *leftLCA = findLCA(root->left, nodeA, nodeB);
    // Đệ quy tìm kiếm tổ tiên chung trong cây con phải (rightLCA)
    BTNode *rightLCA = findLCA(root->right, nodeA, nodeB);

    // Nếu cả leftLCA và rightLCA đều không NULL, có nghĩa là một nút
    // nằm trong cây con trái và nút kia nằm trong cây con phải,
    // do đó nút hiện tại (root) chính là tổ tiên chung thấp nhất
    if (leftLCA && rightLCA)
        return root;

    // Nếu không, kiểm tra xem LCA nằm trong cây con trái hay cây con phải
    // Nếu không, trả về nút không NULL trong hai kết quả trên (nếu có)
    return (leftLCA != NULL) ? leftLCA : rightLCA;
}

// Tìm và trả về giá trị của tổ tiên chung thấp nhất của hai nút có giá trị a và b.
int lowestAncestor(BTNode *root, int a, int b)
{
    // Đầu tiên, tìm con trỏ đến hai nút có giá trị a và b bằng cách gọi hàm findNode
    BTNode *nodeA = findNode(root, a);
    BTNode *nodeB = findNode(root, b);

    // Sau đó, tìm tổ tiên chung thấp nhất của hai nút này bằng cách gọi hàm findLCA
    BTNode *lca = findLCA(root, nodeA, nodeB);

    // Trả về giá trị của tổ tiên chung thấp nhất
    return lca->val;
}