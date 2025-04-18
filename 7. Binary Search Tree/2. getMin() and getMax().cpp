#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <class T>
class BinarySearchTree
{
public:
    class Node;

private:
    Node *root;

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    class Node
    {
    private:
        T value;
        Node *pLeft, *pRight;
        friend class BinarySearchTree<T>;

    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };

    Node *addRec(Node *root, T value);
    void add(T value);
    Node *findMin(Node *node);     // Tìm nút có giá trị nhỏ nhất trong cây con
    T getMin();                    // Tìm giá trị nhỏ nhất trong cây
    Node *findMax(Node *node);     // Tìm nút có giá trị lớn nhất trong cây con
    T getMax();                    // Tìm giá trị lớn nhất trong cây
    string inOrderRec(Node *root); // Duyệt cây theo thứ tự inorder
    string inOrder();              // Duyệt cây theo thứ tự inorder
    bool isEmpty() const;          // Kiểm tra xem cây có rỗng hay không
    Node *findMax(Node *node);
    Node *deleteNodeRec(Node *node, T value);
    void deleteNode(T value);

    /**
     * Phương thức tìm GIÁ TRỊ nhỏ nhất trong cây nhị phân tìm kiếm
     * Trong một cây nhị phân tìm kiếm, giá trị nhỏ nhất sẽ nằm ở nút ngoài cùng bên trái
     * @return giá trị nhỏ nhất trong cây
     * @throws runtime_error nếu cây rỗng
     */
    T getMin()
    {
        // Kiểm tra nếu cây rỗng
        if (root == nullptr)
        {
            throw runtime_error("Tree is empty"); // Ném ngoại lệ nếu cây rỗng
        }
        // Bắt đầu từ nút gốc
        Node *current = root;
        // Đi xuống bên trái cho đến khi không thể đi tiếp
        // Theo tính chất của cây nhị phân tìm kiếm, nút nhỏ nhất sẽ là nút ngoài cùng bên trái
        while (current->pLeft != nullptr)
        {
            current = current->pLeft;
        }
        // Trả về giá trị của nút nhỏ nhất
        return current->value;
    }

    /**
     * Phương thức tìm giá trị lớn nhất trong cây nhị phân tìm kiếm
     * Trong một cây nhị phân tìm kiếm, giá trị lớn nhất sẽ nằm ở nút ngoài cùng bên phải
     * @return giá trị lớn nhất trong cây
     * @throws runtime_error nếu cây rỗng
     */
    T getMax()
    {
        // Kiểm tra nếu cây rỗng
        if (root == nullptr)
        {
            throw runtime_error("Tree is empty"); // Ném ngoại lệ nếu cây rỗng
        }
        // Bắt đầu từ nút gốc
        Node *current = root;
        // Đi xuống bên phải cho đến khi không thể đi tiếp
        // Theo tính chất của cây nhị phân tìm kiếm, nút lớn nhất sẽ là nút ngoài cùng bên phải
        while (current->pRight != nullptr)
        {
            current = current->pRight;
        }
        // Trả về giá trị của nút lớn nhất
        return current->value;
    }
};

template <class T>
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::addRec(Node *root, T value)
{
    // Nếu cây rỗng, tạo nút mới
    if (root == nullptr)
    {
        return new Node(value);
    }

    // Nếu giá trị nhỏ hơn giá trị nút hiện tại, thêm vào cây con bên trái
    if (value < root->value)
    {
        root->pLeft = addRec(root->pLeft, value);
    }
    // Nếu giá trị lớn hơn giá trị nút hiện tại, thêm vào cây con bên phải
    else if (value > root->value)
    {
        root->pRight = addRec(root->pRight, value);
    }

    // Trả về nút hiện tại sau khi đã thêm giá trị mới
    return root;
}
template <class T>
void BinarySearchTree<T>::add(T value)
{
    root = addRec(root, value);
}
template <class T>
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::findMin(Node *node)
{
    Node *current = node;
    // Đi theo con trỏ bên trái cho đến khi không thể đi tiếp
    while (current && current->pLeft != nullptr)
    {
        current = current->pLeft;
    }
    return current; // Trả về nút có giá trị nhỏ nhất
}
template <class T>
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::findMax(Node *node)
{
    Node *current = node;
    // Đi theo con trỏ bên phải cho đến khi không thể đi tiếp
    while (current && current->pRight != nullptr)
    {
        current = current->pRight;
    }
    return current; // Trả về nút có giá trị lớn nhất
}