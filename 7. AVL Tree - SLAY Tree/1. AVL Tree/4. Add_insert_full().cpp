#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template <class T>
class AVLTree
{
public:
    class Node;

private:
    Node *root;

protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }

    // 1. Hàm lấy hệ số cân bằng của một node
    int getBalance(Node *node)
    {
        if (node == NULL)
            return 0;
        return getHeightRec(node->pLeft) - getHeightRec(node->pRight);
    }

    // 2. Hàm quay phải - xử lý trường hợp Left-Left
    Node *rotateRight(Node *y)
    {
        // Lưu node con trái của y
        Node *x = y->pLeft;
        // Lưu con phải của x
        Node *T2 = x->pRight;

        // Thực hiện phép quay
        x->pRight = y; // y trở thành con phải của x
        y->pLeft = T2; // T2 trở thành con trái của y

        // Cập nhật giá trị balance nếu cần
        // (ở đây dựa vào hàm getBalance khi cần)

        // Trả về node gốc mới sau khi quay
        return x;
    }

    // 3. Hàm quay trái - xử lý trường hợp Right-Right
    Node *rotateLeft(Node *x)
    {
        // Lưu node con phải của x
        Node *y = x->pRight;
        // Lưu con trái của y
        Node *T2 = y->pLeft;

        // Thực hiện phép quay
        y->pLeft = x;   // x trở thành con trái của y
        x->pRight = T2; // T2 trở thành con phải của x

        // Cập nhật giá trị balance nếu cần

        // Trả về node gốc mới sau khi quay
        return y;
    }

    // 4. Hàm đệ quy thực hiện chèn node vào cây AVL
    Node *insertNode(Node *node, const T &value)
    {
        /* 1. Thực hiện chèn BST bình thường */
        if (node == NULL)
            return new Node(value);

        // Nếu giá trị bằng node hiện tại, chèn vào cây con bên phải
        if (value == node->data)
            node->pRight = insertNode(node->pRight, value);
        // Nếu giá trị nhỏ hơn node hiện tại, chèn vào cây con bên trái
        else if (value < node->data)
            node->pLeft = insertNode(node->pLeft, value);
        // Nếu giá trị lớn hơn node hiện tại, chèn vào cây con bên phải
        else
            node->pRight = insertNode(node->pRight, value);

        /* 2. Kiểm tra và cân bằng lại cây nếu cần */
        // Tính hệ số cân bằng của node hiện tại
        int balance = getBalance(node);

        // Trường hợp Left-Left: Cây lệch trái và node chèn vào bên trái của con trái
        if (balance > 1 && value < node->pLeft->data)
            return rotateRight(node);

        // Trường hợp Right-Right: Cây lệch phải và node chèn vào bên phải của con phải
        if (balance < -1 && (value > node->pRight->data || value == node->pRight->data))
            return rotateLeft(node);

        // Trường hợp Left-Right: Cây lệch trái nhưng node chèn vào bên phải của con trái
        if (balance > 1 && (value > node->pLeft->data || value == node->pLeft->data))
        {
            node->pLeft = rotateLeft(node->pLeft);
            return rotateRight(node);
        }

        // Trường hợp Right-Left: Cây lệch phải nhưng node chèn vào bên trái của con phải
        if (balance < -1 && value < node->pRight->data)
        {
            node->pRight = rotateRight(node->pRight);
            return rotateLeft(node);
        }

        // Trả về node hiện tại (không cần cân bằng)
        return node;
    }

    // Cân bằng sau khi thêm vào cây con trái
    void balanceLeft(Node *&node, bool &taller)
    {
        switch (node->balance)
        {
        case LH: // Nếu cây đã lệch trái, cần cân bằng lại
            if (node->pLeft->balance == LH)
            {
                // Trường hợp L-L: xoay phải đơn giản
                rotateRight(node);
            }
            else if (node->pLeft->balance == RH)
            {
                // Trường hợp L-R: xoay kép
                doubleRotateLeftRight(node);
            }
            taller = false; // Sau khi cân bằng, chiều cao không tăng nữa
            break;
        case EH: // Nếu cây ban đầu cân bằng, giờ sẽ lệch trái
            node->balance = LH;
            break;
        case RH: // Nếu cây ban đầu lệch phải, giờ sẽ cân bằng
            node->balance = EH;
            taller = false; // Chiều cao tổng thể không tăng
            break;
        }
    }

    // Cân bằng sau khi thêm vào cây con phải
    void balanceRight(Node *&node, bool &taller)
    {
        switch (node->balance)
        {
        case LH: // Nếu cây ban đầu lệch trái, giờ sẽ cân bằng
            node->balance = EH;
            taller = false; // Chiều cao tổng thể không tăng
            break;
        case EH: // Nếu cây ban đầu cân bằng, giờ sẽ lệch phải
            node->balance = RH;
            break;
        case RH: // Nếu cây đã lệch phải, cần cân bằng lại
            if (node->pRight->balance == RH)
            {
                // Trường hợp R-R: xoay trái đơn giản
                rotateLeft(node);
            }
            else if (node->pRight->balance == LH)
            {
                // Trường hợp R-L: xoay kép
                doubleRotateRightLeft(node);
            }
            taller = false; // Sau khi cân bằng, chiều cao không tăng nữa
            break;
        }
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() {}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }

    // 5. Hàm insert công khai gọi từ bên ngoài
    void insert(const T &value)
    {
        this->root = insertNode(this->root, value);
    }

    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};

// Hàm main để kiểm tra chức năng
int main()
{
    // Test case 1: Thêm các số từ 0 đến -10
    cout << "Test case 1:" << endl;
    AVLTree<int> avl;
    for (int i = 0; i >= -10; i--)
    {
        avl.insert(i);
    }
    avl.printTreeStructure();

    cout << endl
         << "----------------------------------" << endl;

    // Test case 2: Thêm các số 5, 7, 6
    cout << "Test case 2:" << endl;
    AVLTree<int> avlTree;
    avlTree.insert(5);
    avlTree.insert(7);
    avlTree.insert(6);
    avlTree.printTreeStructure();

    return 0;
}

/*
CHÚ THÍCH CHI TIẾT BẰNG TIẾNG VIỆT:

1. Hàm insert:
   - Hàm công khai insert gọi hàm insertNode để thực hiện việc chèn và cập nhật lại root.
   - Hàm insertNode thực hiện chèn node mới vào cây như BST thông thường, sau đó kiểm tra và cân bằng cây.

2. Các trường hợp mất cân bằng và xử lý:

   a. Left-Left Case (LL):
      - Xảy ra khi: Cây lệch trái (balance > 1) và node mới được chèn vào bên trái của con trái.
      - Xử lý: Thực hiện quay phải (rotateRight) một lần tại node hiện tại.

      Minh họa:
          z                                      y
         / \                                   /   \
        y   T4      Right Rotate (z)          x      z
       / \          - - - - - - - - ->      /  \    /  \
      x   T3                               T1  T2  T3  T4
     / \
   T1   T2

   b. Right-Right Case (RR):
      - Xảy ra khi: Cây lệch phải (balance < -1) và node mới được chèn vào bên phải của con phải.
      - Xử lý: Thực hiện quay trái (rotateLeft) một lần tại node hiện tại.

      Minh họa:
        z                                y
       /  \                            /   \
      T1   y     Left Rotate(z)       z      x
          /  \   - - - - - - - ->    / \    / \
         T2   x                     T1  T2 T3  T4
             / \
           T3  T4

   c. Left-Right Case (LR):
      - Xảy ra khi: Cây lệch trái (balance > 1) và node mới được chèn vào bên phải của con trái.
      - Xử lý: Thực hiện quay trái tại con trái, sau đó quay phải tại node hiện tại.

      Minh họa:
           z                               z                           x
          / \                            /   \                        /  \
         y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
        / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
      T1   x                          y    T3                    T1  T2  T3  T4
          / \                        / \
        T2   T3                    T1   T2

   d. Right-Left Case (RL):
      - Xảy ra khi: Cây lệch phải (balance < -1) và node mới được chèn vào bên trái của con phải.
      - Xử lý: Thực hiện quay phải tại con phải, sau đó quay trái tại node hiện tại.

      Minh họa:
         z                            z                            x
        / \                          / \                          /  \
      T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
          / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
         x   T4                      T2   y                  T1  T2  T3  T4
        / \                              /  \
      T2   T3                           T3   T4

3. Xử lý trường hợp giá trị trùng lặp:
   - Theo yêu cầu, khi thêm node có giá trị bằng với node cha, ta chèn vào cây con bên phải.
   - Trong hàm insertNode, điều này được xử lý bằng cách kiểm tra node->data == value.

4. Lưu ý bổ sung:
   - Trong trường hợp LL và LR, chúng ta chỉ cần kiểm tra giá trị của node mới và node hiện tại.
   - Việc cập nhật giá trị balance không được thực hiện trực tiếp trong mã này, thay vào đó
     chúng ta tính giá trị balance dựa trên chiều cao cây con mỗi khi cần.
   - Cách tiếp cận này đơn giản hơn nhưng có thể kém hiệu quả hơn so với việc duy trì giá trị
     balance của mỗi node.
*/