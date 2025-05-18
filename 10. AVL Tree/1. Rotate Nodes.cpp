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

    void insert(const T &value);

    int getBalance(Node *subroot)
    {
        if (!subroot)
            return 0;
        return getHeightRec(subroot->pLeft) - getHeightRec(subroot->pRight);
    }

    // Hàm rotateLeft: Thực hiện quay trái một node trong cây AVL khi Cây và Cây con Phải lệch Phải
    // subroot là node gốc của cây con cần quay
    // Hàm này sẽ thay đổi cấu trúc của cây để đảm bảo tính cân bằng của cây AVL
    // Right of Right (RR) imbalance
    Node *rotateLeft(Node *subroot)
    {
        // Kiểm tra xem subroot có tồn tại hay không
        if (subroot == nullptr)
            return nullptr;

        // Lưu lại node con bên phải của subroot, node này sẽ trở thành root mới sau khi quay
        Node *newRoot = subroot->pRight;

        // Kiểm tra xem có thể quay không (newRoot phải tồn tại)
        if (newRoot == nullptr)
            return subroot;

        // Thực hiện quay trái:
        // 1. Gán con phải của subroot là con trái của newRoot
        subroot->pRight = newRoot->pLeft;

        // 2. Gán con trái của newRoot là subroot
        newRoot->pLeft = subroot;

        // 3. Cập nhật giá trị balance nếu cần (trong trường hợp này không cập nhật)
        // Có thể bổ sung dựa trên chiều cao của các nhánh

        // 4. Trả về root mới sau khi quay
        return newRoot;
    }

    // Hàm rotateRight: Thực hiện quay phải một node trong cây AVL khi cây và cây con trái lệch trái
    // subroot là node gốc của cây con cần quay
    // Hàm này sẽ thay đổi cấu trúc của cây để đảm bảo tính cân bằng của cây AVL
    // Left of Left (LL) imbalance
    Node *rotateRight(Node *subroot)
    {
        // Kiểm tra xem subroot có tồn tại hay không
        if (subroot == nullptr)
            return nullptr;

        // Lưu lại node con bên trái của subroot, node này sẽ trở thành root mới sau khi quay
        Node *newRoot = subroot->pLeft;

        // Kiểm tra xem có thể quay không (newRoot phải tồn tại)
        if (newRoot == nullptr)
            return subroot;

        // Thực hiện quay phải:
        // 1. Gán con trái của subroot là con phải của newRoot
        subroot->pLeft = newRoot->pRight;

        // 2. Gán con phải của newRoot là subroot
        newRoot->pRight = subroot;

        // 3. Cập nhật giá trị balance nếu cần (trong trường hợp này không cập nhật)
        // Có thể bổ sung dựa trên chiều cao của các nhánh

        // 4. Trả về root mới sau khi quay
        return newRoot;
    }

    // Hàm rotateLeftRight: Thực hiện quay trái rồi quay phải một node trong cây AVL
    // Cây Cây lệch Trái và Cây con Trai lệch Phải
    // subroot là node gốc của cây con cần quay
    // Hàm này sẽ thay đổi cấu trúc của cây để đảm bảo tính cân bằng của cây AVL
    // Right of Left (RL) imbalance
    Node *rotateLeftRight(Node *subroot)
    {
        // Kiểm tra xem subroot có tồn tại hay không
        if (subroot == nullptr)
            return nullptr;

        // Thực hiện quay trái trước
        subroot->pLeft = rotateLeft(subroot->pLeft);

        // Sau đó thực hiện quay phải
        return rotateRight(subroot);
    }
    // Hàm rotateRightLeft: Thực hiện quay phải rồi quay trái một node trong cây AVL
    // Cây Cây lệch Phải và Cây con Phải lệch Trái
    // subroot là node gốc của cây con cần quay
    // Hàm này sẽ thay đổi cấu trúc của cây để đảm bảo tính cân bằng của cây AVL
    // Left of Right (LR) imbalance
    Node *rotateRightLeft(Node *subroot)
    {
        // Kiểm tra xem subroot có tồn tại hay không
        if (subroot == nullptr)
            return nullptr;

        // Thực hiện quay phải trước
        subroot->pRight = rotateRight(subroot->pRight);

        // Sau đó thực hiện quay trái
        return rotateLeft(subroot);
    }
    /*
    CHÚ THÍCH CHI TIẾT:

    1. Quay trái (rotateLeft):
       - Mục đích: Khi cây bị mất cân bằng vì cây con bên phải cao hơn cây con bên trái quá nhiều.
       - Quá trình:
         a. Node con bên phải của root hiện tại (subroot->pRight) sẽ trở thành root mới.
         b. Root hiện tại sẽ trở thành con trái của root mới.
         c. Cây con trái của root mới cũ (nếu có) sẽ trở thành cây con phải của root cũ.

       Minh họa:
            A              B
           / \            / \
          X   B    ->    A   Z
             / \        / \
            Y   Z      X   Y

    2. Quay phải (rotateRight):
       - Mục đích: Khi cây bị mất cân bằng vì cây con bên trái cao hơn cây con bên phải quá nhiều.
       - Quá trình:
         a. Node con bên trái của root hiện tại (subroot->pLeft) sẽ trở thành root mới.
         b. Root hiện tại sẽ trở thành con phải của root mới.
         c. Cây con phải của root mới cũ (nếu có) sẽ trở thành cây con trái của root cũ.

       Minh họa:
              A            B
             / \          / \
            B   Z  ->    X   A
           / \              / \
          X   Y            Y   Z

    LƯU Ý:
    - Khi thực hiện phép quay, chúng ta cần thận trọng với việc gán các con trỏ để không bị mất liên kết.
    - Thứ tự các bước rất quan trọng để đảm bảo không làm mất dữ liệu.
    - Trong các hàm quay này, chúng ta không cập nhật giá trị balance. Việc cập nhật balance
      thường được thực hiện trong hàm insert hoặc delete sau khi thực hiện phép quay.
    */

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