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
    /*
Hàm sumOfLeafs() sẽ duyệt cây theo phương pháp đệ quy dạng duyệt sâu (Depth-First Search - DFS).
Cụ thể, quá trình duyệt diễn ra như sau:
- Bắt đầu từ nút gốc (root)
- Đối với mỗi nút đang xét:
Kiểm tra xem nút có phải là NULL không. Nếu là NULL, trả về 0.
Kiểm tra xem nút có phải là nút lá không (không có con trái và phải).
- Nếu là nút lá, trả về giá trị của nút đó.
- Nếu không phải nút lá, hàm sẽ đệ quy xuống cả cây con bên trái và cây con bên phải.
Cộng kết quả từ cả hai cây con lại với nhau và trả về tổng đó.
*/

    // Hàm tính tổng giá trị của tất cả các "nút lá" trong cây nhị phân.
    int sumOfLeafsHelper(Node *node)
    {
        // Trường hợp cơ sở: nếu nút hiện tại là NULL, trả về 0
        if (node == nullptr)
            return 0;
        // Kiểm tra xem nút hiện tại có phải là lá không (không có con trái và con phải)
        if (node->pLeft == nullptr && node->pRight == nullptr)
        {
            return node->value; // Trả về giá trị của nút lá
        }

        // Nếu không phải lá, đệ quy tính tổng của các nút lá ở cây con trái và phải
        return sumOfLeafsHelper(node->pLeft) + sumOfLeafsHelper(node->pRight);
    }

    int sumOfLeafs()
    {
        // Gọi hàm đệ quy helper từ nút gốc
        return sumOfLeafsHelper(this->root);
    }
};