#include <iostream>
#include <string>
using namespace std;

class SplayTree
{
    struct Node
    {
        int val;
        Node *pLeft;
        Node *pRight;
        Node *pParent;
        Node(int val = 0, Node *l = nullptr, Node *r = nullptr, Node *par = nullptr) : val(val), pLeft(l), pRight(r), pParent(par) {}
    };
    Node *root;

    // print the tree structure for local testing
    void printBinaryTree(string prefix, const Node *root, bool isLeft, bool hasRightSibling)
    {
        if (!root && isLeft && hasRightSibling)
        {
            cout << prefix << "├──\n";
        }
        if (!root)
            return;
        cout << prefix;
        if (isLeft && hasRightSibling)
            cout << "├──";
        else
            cout << "└──";
        cout << root->val << '\n';
        printBinaryTree(prefix + (isLeft && hasRightSibling ? "|  " : "   "), root->pLeft, true, root->pRight);
        printBinaryTree(prefix + (isLeft && hasRightSibling ? "|  " : "   "), root->pRight, false, root->pRight);
    }

    void printPreorder(Node *p)
    {
        if (!p)
        {
            return;
        }
        cout << p->val << ' ';
        printPreorder(p->pLeft);
        printPreorder(p->pRight);
    }

    // Xoay phải hoặc trái tùy thuộc vào vị trí của node p
    // Xoay phải nếu p là con trái, ngược lại xoay trái
    // FUNCTION HELPERS
    /*
     * 1. Xoay phải node p
     * Trước khi xoay:        Sau khi xoay:
     *      P                      L
     *     / \                    / \
     *    L   R     --->         X   P
     *   / \                        / \
     *  X   Y                      Y   R
     */
    void rightRotate(Node *p)
    {
        // Không thể xoay nếu p hoặc con trái của p là nullptr
        if (!p || !p->pLeft)
            return;

        // Lưu tham chiếu đến con trái của p
        Node *l = p->pLeft;

        // Cập nhật con trái của p thành con phải của l
        p->pLeft = l->pRight;
        if (l->pRight)
        {
            l->pRight->pParent = p;
        }

        // Cập nhật cha của l
        l->pParent = p->pParent;

        // Nếu p là root
        if (!p->pParent)
        {
            root = l;
        }
        // Nếu p là con trái của cha nó
        else if (p == p->pParent->pLeft)
        {
            p->pParent->pLeft = l;
        }
        // Nếu p là con phải của cha nó
        else
        {
            p->pParent->pRight = l;
        }

        // Đặt p là con phải của l và cập nhật cha của p
        l->pRight = p;
        p->pParent = l;
    }

    /*
     * 2. Xoay trái node p
     * Trước khi xoay:        Sau khi xoay:
     *      P                      R
     *     / \                    / \
     *    L   R     --->         P   Y
     *       / \                / \
     *      X   Y              L   X
     */
    void leftRotate(Node *p)
    {
        // Không thể xoay nếu p hoặc con phải của p là nullptr
        if (!p || !p->pRight)
            return;

        // Lưu tham chiếu đến con phải của p
        Node *r = p->pRight;

        // Cập nhật con phải của p thành con trái của r
        p->pRight = r->pLeft;
        if (r->pLeft)
        {
            r->pLeft->pParent = p;
        }

        // Cập nhật cha của r
        r->pParent = p->pParent;

        // Nếu p là root
        if (!p->pParent)
        {
            root = r;
        }
        // Nếu p là con trái của cha nó
        else if (p == p->pParent->pLeft)
        {
            p->pParent->pLeft = r;
        }
        // Nếu p là con phải của cha nó
        else
        {
            p->pParent->pRight = r;
        }

        // Đặt p là con trái của r và cập nhật cha của p
        r->pLeft = p;
        p->pParent = r;
    }

public:
    SplayTree()
    {
        root = nullptr;
    }

    ~SplayTree()
    {
        // Ignore deleting all nodes in the tree
    }

    void printBinaryTree()
    {
        printBinaryTree("", root, false, false);
    }

    void printPreorder()
    {
        printPreorder(root);
        cout << "\n";
    }

    /* 3. Phương thức splay:
     * Đưa một node lên làm gốc của cây Splay Tree.
     * Phương thức splay thực hiện việc đưa một node lên làm gốc của cây.
     * Được thực hiện qua 3 bước chính:
     * 1. Zig: Node p là con trực tiếp của gốc
     * 2. Zig-Zig: Node p và cha của p đều là con trái (hoặc đều là con phải)
     * 3. Zig-Zag: Node p là con trái nhưng cha của p là con phải (hoặc ngược lại)
     */
    void splay(Node *p)
    {
        // Nếu p là nullptr hoặc đã là root, không cần splay
        if (!p || !p->pParent)
            return;

        // Tiếp tục splay cho đến khi p trở thành root
        while (p->pParent)
        {
            Node *parent = p->pParent;
            Node *grandparent = parent->pParent;

            // Trường hợp Zig (parent là root)
            if (!grandparent)
            {
                // Nếu p là con trái của parent
                if (p == parent->pLeft)
                {
                    rightRotate(parent);
                }
                // Nếu p là con phải của parent
                else
                {
                    leftRotate(parent);
                }
            }
            // Trường hợp Zig-Zig (p và parent đều là con trái hoặc đều là con phải)
            else if ((p == parent->pLeft && parent == grandparent->pLeft) ||
                     (p == parent->pRight && parent == grandparent->pRight))
            {

                // Nếu p và parent đều là con trái
                if (p == parent->pLeft)
                {
                    // Xoay phải 2 lần
                    rightRotate(grandparent);
                    rightRotate(parent);
                }
                // Nếu p và parent đều là con phải
                else
                {
                    // Xoay trái 2 lần
                    leftRotate(grandparent);
                    leftRotate(parent);
                }
            }
            // Trường hợp Zig-Zag (p là con trái nhưng parent là con phải hoặc ngược lại)
            else
            {
                // Nếu p là con trái của parent và parent là con phải của grandparent
                if (p == parent->pLeft && parent == grandparent->pRight)
                {
                    rightRotate(parent);
                    leftRotate(grandparent);
                }
                // Nếu p là con phải của parent và parent là con trái của grandparent
                else
                {
                    leftRotate(parent);
                    rightRotate(grandparent);
                }
            }
        }
    }

    /*4. Phương thức tìm kiếm:
     * Tìm kiếm một giá trị trong cây Splay Tree.
     * Phương thức insert thêm một giá trị mới vào cây Splay.
     * 1. Thêm node mới như trong BST thông thường
     * 2. Splay node mới lên làm gốc
     * Lưu ý: Nếu giá trị đã tồn tại, ta thêm vào cây con bên phải
     */
    void insert(int val)
    {
        // Trường hợp cây rỗng
        if (!root)
        {
            root = new Node(val);
            return;
        }

        // Tìm vị trí thích hợp để chèn node mới
        Node *curr = root;
        Node *parent = nullptr;

        while (curr)
        {
            parent = curr;

            // Nếu giá trị nhỏ hơn node hiện tại, đi sang cây con trái
            if (val < curr->val)
            {
                curr = curr->pLeft;
            }
            // Nếu giá trị lớn hơn hoặc bằng node hiện tại, đi sang cây con phải
            // (theo yêu cầu, nếu giá trị trùng lặp thì thêm vào cây con phải)
            else
            {
                curr = curr->pRight;
            }
        }

        // Tạo node mới
        Node *newNode = new Node(val, nullptr, nullptr, parent);

        // Gán node mới vào vị trí thích hợp
        if (val < parent->val)
        {
            parent->pLeft = newNode;
        }
        else
        {
            parent->pRight = newNode;
        }

        // Splay node mới lên làm gốc
        splay(newNode);
    }
};

/*
 * Giải thích lý thuyết:
 *
 * 1. Cây Splay Tree:
 *    - Là một loại cây nhị phân tìm kiếm tự cân bằng (self-balancing BST)
 *    - Không đảm bảo cây luôn cân bằng như AVL hay Red-Black Tree
 *    - Dựa trên nguyên tắc "splay" (rải): node được truy cập gần đây nhất sẽ được đưa lên làm gốc
 *
 * 2. Các thao tác cơ bản:
 *    a. Xoay (Rotation):
 *       - Leftrotate: Xoay một node sang trái
 *       - Rightrotate: Xoay một node sang phải
 *
 *    b. Splay (đưa một node lên làm gốc của cây):
 *       - Zig: Khi node cần splay là con trực tiếp của gốc
 *       - Zig-Zig: Khi node và cha của nó đều là con trái (hoặc đều là con phải)
 *       - Zig-Zag: Khi node là con trái nhưng cha là con phải (hoặc ngược lại)
 *
 *    c. Insert (chèn một giá trị mới):
 *       - Thêm node mới như trong BST thông thường
 *       - Sau đó splay node mới lên làm gốc
 *
 * 3. Phân tích độ phức tạp:
 *    - Thao tác splay: O(log n) trung bình, nhưng có thể là O(n) trong trường hợp xấu nhất
 *    - Thao tác insert: O(log n) trung bình (tìm vị trí + splay)
 *
 * 4. Ưu điểm của Splay Tree:
 *    - Tự động đưa các phần tử truy cập gần đây lên gần gốc (locality of reference)
 *    - Hiệu quả với các tác vụ có tính chất lặp lại (truy cập cùng một phần tử nhiều lần)
 *    - Không cần lưu trữ thông tin cân bằng (như chiều cao trong AVL tree)
 *
 * 5. Nhược điểm:
 *    - Không đảm bảo độ phức tạp O(log n) cho mọi thao tác đơn lẻ
 *    - Cấu trúc cây có thể thay đổi nhiều sau mỗi thao tác
 */

// Hàm main để chạy mã
int main()
{
    SplayTree tree;
    int query;
    cin >> query;
    for (int i = 0; i < query; i++)
    {
        string op;
        int val;
        cin >> op >> val;
        if (op == "insert")
            tree.insert(val);
    }
    // print preorder traversal of the tree
    tree.printPreorder();
    // print structure of the tree
    tree.printBinaryTree();

    return 0;
}