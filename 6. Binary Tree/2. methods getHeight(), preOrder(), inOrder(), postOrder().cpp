#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

template <class K, class V>
class BinaryTree
{
public:
    class Node;

private:
    Node *root;

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }
    class Node
    {
    private:
        K key;
        V value;
        Node *pLeft, *pRight;
        friend class BinaryTree<K, V>;

    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    void addNode(string posFromRoot, K key, V value)
    {
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }
        Node *walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l - 1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L')
            walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R')
            walker->pRight = new Node(key, value);
    }
    // STUDENT ANSWER BEGIN
    // Hàm đệ quy để tính chiều cao của cây từ một nút cụ thể
    int getHeightRecursive(Node *node)
    {
        // Trường hợp cơ bản: nếu nút hiện tại là NULL, trả về 0
        // (để khi cộng 1 thì chiều cao là 1 cho lá gốc)
        if (node == nullptr)
            return 0;

        // Tính chiều cao của cây con bên trái và bên phải
        int leftHeight = getHeightRecursive(node->pLeft);
        int rightHeight = getHeightRecursive(node->pRight);

        // Chiều cao của cây là chiều cao lớn nhất giữa cây con trái và phải, cộng thêm 1
        return 1 + max(leftHeight, rightHeight);
    }
    // Hàm chính để trả về chiều cao của cây
    int getHeight()
    {
        return getHeightRecursive(this->root);
    }

    // Hàm đệ quy để duyệt cây theo thứ tự trước (pre-order): gốc -> trái -> phải
    void preOrderRecursive(Node *node, string &result)
    {
        // Nếu nút hiện tại là NULL, không làm gì cả
        if (node == nullptr)
            return;

        // Thêm giá trị của nút hiện tại vào kết quả
        // Nếu kết quả không rỗng, thêm dấu cách trước giá trị mới
        if (!result.empty())
            result += " ";
        result += to_string(node->value);
        // Duyệt cây con bên trái
        preOrderRecursive(node->pLeft, result);
        // Duyệt cây con bên phải
        preOrderRecursive(node->pRight, result);
    }
    // Hàm chính để trả về chuỗi các giá trị theo thứ tự trước
    string preOrder()
    {
        string result = "";
        preOrderRecursive(this->root, result);
        return result;
    }

    // Hàm đệ quy để duyệt cây theo thứ tự giữa (in-order): trái -> gốc -> phải
    void inOrderRecursive(Node *node, string &result)
    {
        // Nếu nút hiện tại là NULL, không làm gì cả
        if (node == nullptr)
            return;

        // Duyệt cây con bên trái
        inOrderRecursive(node->pLeft, result);
        // Thêm giá trị của nút hiện tại vào kết quả
        // Nếu kết quả không rỗng, thêm dấu cách trước giá trị mới
        if (!result.empty())
            result += " ";
        result += to_string(node->value);
        // Duyệt cây con bên phải
        inOrderRecursive(node->pRight, result);
    }
    // Hàm chính để trả về chuỗi các giá trị theo thứ tự giữa
    string inOrder()
    {
        string result = "";
        inOrderRecursive(this->root, result);
        return result;
    }

    // Hàm đệ quy để duyệt cây theo thứ tự sau (post-order): trái -> phải -> gốc
    void postOrderRecursive(Node *node, string &result)
    {
        // Nếu nút hiện tại là NULL, không làm gì cả
        if (node == nullptr)
            return;

        // Duyệt cây con bên trái
        postOrderRecursive(node->pLeft, result);
        // Duyệt cây con bên phải
        postOrderRecursive(node->pRight, result);
        // Thêm giá trị của nút hiện tại vào kết quả
        // Nếu kết quả không rỗng, thêm dấu cách trước giá trị mới
        if (!result.empty())
            result += " ";
        result += to_string(node->value);
    }
    // Hàm chính để trả về chuỗi các giá trị theo thứ tự sau
    string postOrder()
    {
        string result = "";
        postOrderRecursive(this->root, result);
        return result;
    }
    // STUDENT ANSWER END
};
