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
    // 1. Xoay kép trái-phải (LR)
    void doubleRotateLeftRight(Node *&node)
    {
        // Thực hiện xoay kép: xoay trái node->pLeft, sau đó xoay phải node
        Node *temp = node->pLeft;
        Node *temp2 = temp->pRight;

        temp->pRight = temp2->pLeft;
        temp2->pLeft = temp;
        node->pLeft = temp2->pRight;
        temp2->pRight = node;

        // Cập nhật hệ số cân bằng dựa trên hệ số cân bằng của node giữa
        switch (temp2->balance)
        {
        case LH:                // Nếu node giữa lệch trái
            node->balance = RH; // Node gốc cũ sẽ lệch phải
            temp->balance = EH; // Node con trái (temp) sẽ cân bằng
            break;
        case EH:                // Nếu node giữa cân bằng
            node->balance = EH; // Cả hai node đều cân bằng
            temp->balance = EH;
            break;
        case RH:                // Nếu node giữa lệch phải
            node->balance = EH; // Node gốc cũ sẽ cân bằng
            temp->balance = LH; // Node con trái (temp) sẽ lệch trái
            break;
        }

        temp2->balance = EH; // Node gốc mới sẽ cân bằng
        node = temp2;        // Node gốc mới
    }

    // 2. Xoay kép phải-trái (RL)
    void doubleRotateRightLeft(Node *&node)
    {
        // Thực hiện xoay kép: xoay phải node->pRight, sau đó xoay trái node
        Node *temp = node->pRight;
        Node *temp2 = temp->pLeft;

        temp->pLeft = temp2->pRight;
        temp2->pRight = temp;
        node->pRight = temp2->pLeft;
        temp2->pLeft = node;

        // Cập nhật hệ số cân bằng
        switch (temp2->balance)
        {
        case LH:                // Nếu node giữa lệch trái
            node->balance = EH; // Node gốc cũ sẽ cân bằng
            temp->balance = RH; // Node con phải (temp) sẽ lệch phải
            break;
        case EH:                // Nếu node giữa cân bằng
            node->balance = EH; // Cả hai node đều cân bằng
            temp->balance = EH;
            break;
        case RH:                // Nếu node giữa lệch phải
            node->balance = LH; // Node gốc cũ sẽ lệch trái
            temp->balance = EH; // Node con phải (temp) sẽ cân bằng
            break;
        }

        temp2->balance = EH; // Node gốc mới sẽ cân bằng
        node = temp2;        // Node gốc mới
    }

    // 3. Tìm node có giá trị lớn nhất trong cây con
    Node *findMax(Node *node)
    {
        while (node->pRight != NULL)
        {
            node = node->pRight;
        }
        return node;
    }

    // 4. Cân bằng khi chiều cao cây con trái giảm sau khi xóa node
    void balanceLeftAfterRemove(Node *&node, bool &shorter)
    {
        switch (node->balance)
        {
        case LH: // Nếu trước đó cây lệch trái, giờ sẽ cân bằng
            node->balance = EH;
            break;
        case EH: // Nếu trước đó cây cân bằng, giờ sẽ lệch phải
            node->balance = RH;
            shorter = false; // Chiều cao tổng thể không giảm
            break;
        case RH: // Nếu trước đó cây lệch phải, giờ sẽ mất cân bằng nghiêm trọng
            Node *rightNode = node->pRight;
            BalanceValue rb = rightNode->balance;

            if (rb != LH)
            {
                // Trường hợp R-R hoặc cây con phải cân bằng
                rotateLeft(node);
                if (rb == EH)
                {
                    // Nếu cây con phải cân bằng, chiều cao tổng thể không giảm
                    shorter = false;
                }
            }
            else
            {
                // Trường hợp R-L
                doubleRotateRightLeft(node);
            }
            break;
        }
    }

    // 5. Cân bằng khi chiều cao cây con phải giảm sau khi xóa node
    void balanceRightAfterRemove(Node *&node, bool &shorter)
    {
        switch (node->balance)
        {
        case RH: // Nếu trước đó cây lệch phải, giờ sẽ cân bằng
            node->balance = EH;
            break;
        case EH: // Nếu trước đó cây cân bằng, giờ sẽ lệch trái
            node->balance = LH;
            shorter = false; // Chiều cao tổng thể không giảm
            break;
        case LH: // Nếu trước đó cây lệch trái, giờ sẽ mất cân bằng nghiêm trọng
            Node *leftNode = node->pLeft;
            BalanceValue lb = leftNode->balance;

            if (lb != RH)
            {
                // Trường hợp L-L hoặc cây con trái cân bằng
                rotateRight(node);
                if (lb == EH)
                {
                    // Nếu cây con trái cân bằng, chiều cao tổng thể không giảm
                    shorter = false;
                }
            }
            else
            {
                // Trường hợp L-R
                doubleRotateLeftRight(node);
            }
            break;
        }
    }

    // 6. Hàm hỗ trợ xóa node
    bool removeNode(Node *&node, const T &value, bool &shorter)
    {
        if (node == NULL)
        {
            return false; // Không tìm thấy giá trị cần xóa
        }

        bool removed = false;

        if (value < node->data)
        {
            // Xóa node từ cây con trái
            removed = removeNode(node->pLeft, value, shorter);
            if (shorter && removed)
            {
                // Nếu chiều cao cây con trái giảm, cần cân bằng lại
                balanceLeftAfterRemove(node, shorter);
            }
        }
        else if (value > node->data)
        {
            // Xóa node từ cây con phải
            removed = removeNode(node->pRight, value, shorter);
            if (shorter && removed)
            {
                // Nếu chiều cao cây con phải giảm, cần cân bằng lại
                balanceRightAfterRemove(node, shorter);
            }
        }
        else
        {
            // Đã tìm thấy node cần xóa
            if (node->pLeft == NULL && node->pRight == NULL)
            {
                // Trường hợp 1: Node lá (không có con)
                delete node;
                node = NULL;
                shorter = true; // Chiều cao giảm
                return true;
            }
            else if (node->pLeft == NULL)
            {
                // Trường hợp 2: Chỉ có con phải
                Node *temp = node;
                node = node->pRight;
                delete temp;
                shorter = true; // Chiều cao giảm
                return true;
            }
            else if (node->pRight == NULL)
            {
                // Trường hợp 2: Chỉ có con trái
                Node *temp = node;
                node = node->pLeft;
                delete temp;
                shorter = true; // Chiều cao giảm
                return true;
            }
            else
            {
                // Trường hợp 3: Có cả hai con
                // Tìm node có giá trị lớn nhất trong cây con trái
                Node *maxNode = findMax(node->pLeft);
                node->data = maxNode->data; // Thay thế giá trị
                // Xóa node trùng lặp (node maxNode ban đầu)
                removed = removeNode(node->pLeft, maxNode->data, shorter);
                if (shorter && removed)
                {
                    // Nếu chiều cao cây con trái giảm, cần cân bằng lại
                    balanceLeftAfterRemove(node, shorter);
                }
            }
        }

        return removed;
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

    // 7. Hàm xóa node và cân bằng lại cây AVL
    void remove(const T &value)
    {
        bool shorter = false;
        removeNode(root, value, shorter);
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