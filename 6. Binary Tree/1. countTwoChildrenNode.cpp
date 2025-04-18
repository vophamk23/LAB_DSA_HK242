
#include <iostream>
#include <string>
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
    // You can define other functions here to help you.

    // Hàm đệ quy để đếm số nút có hai con từ một nút cụ thể
    int countTwoChildrenNodeRecursive(Node *node)
    {
        // Nếu nút hiện tại là NULL, trả về 0
        if (node == nullptr)
            return 0;

        // Khởi tạo biến đếm
        int count = 0;

        // Kiểm tra nút hiện tại có hai con không
        if (node->pLeft != nullptr && node->pRight != nullptr)
        {
            count = 1; // Tăng biến đếm lên 1 nếu nút hiện tại có hai con
        }

        // Đệ quy đếm các nút có hai con ở cây con bên trái
        count += countTwoChildrenNodeRecursive(node->pLeft);

        // Đệ quy đếm các nút có hai con ở cây con bên phải
        count += countTwoChildrenNodeRecursive(node->pRight);

        // Trả về tổng số nút có hai con
        return count;
    }

    // Hàm chính để đếm số nút có hai con trong toàn bộ cây
    int countTwoChildrenNode()
    {
        // Gọi hàm đệ quy từ nút gốc
        return countTwoChildrenNodeRecursive(this->root);
    }
    // STUDENT ANSWER END
};