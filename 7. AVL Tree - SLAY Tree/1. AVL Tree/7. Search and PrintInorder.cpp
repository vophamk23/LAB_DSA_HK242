#include <iostream>
#include <string>
using namespace std;

#define SEPARATOR "##"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

template <class T>
class AVLTree
{
public:
    class Node;

private:
    Node *root;

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() {}

    // Hàm in cây theo thứ tự inorder (trái-gốc-phải)
    void printInorder()
    {
        printInorderRec(root);
    }

    // Hàm đệ quy để duyệt cây theo thứ tự inorder
    void printInorderRec(Node *node)
    {
        if (node != nullptr)
        {
            // Duyệt cây con trái
            printInorderRec(node->pLeft);

            // In giá trị của node hiện tại
            cout << node->data << " ";

            // Duyệt cây con phải
            printInorderRec(node->pRight);
        }
    }

    // Hàm tìm kiếm một giá trị trong cây
    bool search(const T &value)
    {
        return searchRec(root, value);
    }

    // Hàm đệ quy để tìm kiếm một giá trị trong cây
    bool searchRec(Node *node, const T &value)
    {
        // Nếu node hiện tại là null, giá trị không tồn tại trong cây
        if (node == nullptr)
        {
            return false;
        }

        // Nếu giá trị bằng với giá trị của node hiện tại, trả về true
        if (value == node->data)
        {
            return true;
        }

        // Nếu giá trị nhỏ hơn giá trị của node hiện tại, tìm kiếm ở cây con trái
        if (value < node->data)
        {
            return searchRec(node->pLeft, value);
        }

        // Nếu giá trị lớn hơn giá trị của node hiện tại, tìm kiếm ở cây con phải
        return searchRec(node->pRight, value);
    }

    // Hàm insert đã được định nghĩa trong code gốc nhưng không được hiển thị

    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};