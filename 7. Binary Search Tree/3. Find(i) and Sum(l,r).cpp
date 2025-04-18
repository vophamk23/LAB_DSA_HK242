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

    // STUDENT ANSWER BEGIN
    /**
     * Hàm đệ quy hỗ trợ cho phương thức find() để xác định xem một giá trị có tồn tại trong cây hay không
     * @param node: Node hiện tại đang xét
     * @param value: Giá trị cần tìm kiếm
     * @return true nếu tìm thấy giá trị, false nếu không tìm thấy
     */
    bool findRec(Node *node, T value)
    {
        // Trường hợp cơ sở: đã đến node NULL, không tìm thấy giá trị
        if (node == nullptr)
        {
            return false;
        }

        // Đã tìm thấy giá trị
        if (node->value == value)
        {
            return true;
        }

        // Tìm kiếm đệ quy trong cây con trái hoặc phải
        if (value < node->value)
        {
            // Nếu giá trị cần tìm nhỏ hơn giá trị node hiện tại, tìm trong cây con trái
            return findRec(node->pLeft, value);
        }
        else
        {
            // Nếu giá trị cần tìm lớn hơn giá trị node hiện tại, tìm trong cây con phải
            return findRec(node->pRight, value);
        }
    }

    /**
     * Kiểm tra xem một giá trị có tồn tại trong cây hay không
     * @param i: Giá trị cần kiểm tra
     * @return true nếu giá trị tồn tại trong cây, false nếu không tồn tại
     */
    bool find(T i)
    {
        return findRec(root, i);
    }

    /**
     * Hàm đệ quy hỗ trợ cho phương thức sum() để tính tổng các giá trị trong khoảng [l, r]
     * @param node: Node hiện tại đang xét
     * @param l: Giới hạn dưới của khoảng tính tổng
     * @param r: Giới hạn trên của khoảng tính tổng
     * @return Tổng các giá trị trong khoảng [l, r]
     */
    T sumRec(Node *node, T l, T r)
    {
        // Trường hợp cơ sở: đã đến node NULL
        if (node == nullptr)
        {
            return 0;
        }

        T sum = 0;

        // Nếu giá trị của node hiện tại nằm trong khoảng [l, r], cộng vào tổng
        if (node->value >= l && node->value <= r)
        {
            sum += node->value;
        }

        // Nếu giá trị của node hiện tại lớn hơn l, kiểm tra cây con trái
        // (vì cây con trái có thể chứa các giá trị nhỏ hơn node hiện tại và vẫn >= l)
        if (node->value > l)
        {
            sum += sumRec(node->pLeft, l, r);
        }

        // Nếu giá trị của node hiện tại nhỏ hơn r, kiểm tra cây con phải
        // (vì cây con phải có thể chứa các giá trị lớn hơn node hiện tại và vẫn <= r)
        if (node->value < r)
        {
            sum += sumRec(node->pRight, l, r);
        }

        return sum;
    }

    /**
     * Tính tổng các giá trị trong khoảng [l, r]
     * @param l: Giới hạn dưới của khoảng
     * @param r: Giới hạn trên của khoảng
     * @return Tổng các giá trị trong khoảng [l, r]
     */
    T sum(T l, T r)
    {
        return sumRec(root, l, r);
    }

    // STUDENT ANSWER END
};