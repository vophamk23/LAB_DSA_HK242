#include <iostream>
#include <string>
#include <queue>
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
    // Breadth First Search algorithm
    void BFS()
    {
        // Kiểm tra nếu cây rỗng (root là nullptr), không thực hiện gì cả.
        if (this->root == nullptr)
            return;
        // Tạo một hàng đợi (`queue`) và thêm nút gốc (root) vào hàng đợi ban đầu.
        queue<Node *> q;
        q.push(this->root);

        // Biến để theo dõi xem đã in ra phần tử đầu tiên chưa
        // Sử dụng biến `isFirst` để theo dõi khi nào cần in dấu cách giữa các giá trị nút.
        // Điều này giúp đảm bảo không có dấu cách thừa ở cuối chuỗi kết quả.
        bool isFirst = true;

        // Thực hiện vòng lặp chính của BFS:
        // Duyệt qua từng nút trong cây
        while (!q.empty())
        {
            // Lấy nút hiện tại từ đầu hàng đợi
            Node *current = q.front();
            q.pop();

            // In ra giá trị của nút hiện tại
            // Nếu là nút đầu tiên, không cần in dấu cách phía trước
            if (isFirst)
            {
                cout << current->value;
                isFirst = false;
            }
            else
            {
                cout << " " << current->value;
            }

            // Thêm các nút con (trái trước, phải sau) vào cuối hàng đợi nếu chúng tồn tại
            // Đẩy con trái vào hàng đợi nếu có
            if (current->pLeft != nullptr)
            {
                q.push(current->pLeft);
            }
            // Đẩy con phải vào hàng đợi nếu có
            if (current->pRight != nullptr)
            {
                q.push(current->pRight);
            }
        }
    }
    // STUDENT ANSWER END
    /*
    - Thuật toán này đảm bảo duyệt các nút theo từng tầng,
    từ trên xuống dưới, từ trái sang phải - đây chính là nguyên tắc của thuật toán BFS.
    - Độ phức tạp thời gian của thuật toán là O(n) với n là số lượng nút trong cây,
    vì mỗi nút được thêm và lấy ra khỏi hàng đợi đúng một lần.
    */
};