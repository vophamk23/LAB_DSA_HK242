#include <iostream>
#include <string>
using namespace std;

class SplayTree
{
    /**
     * Cấu trúc Node trong cây Splay
     * - val: giá trị của node
     * - pLeft: con trỏ đến node con bên trái
     * - pRight: con trỏ đến node con bên phải
     * - pParent: con trỏ đến node cha
     */
    struct Node
    {
        int val;
        Node *pLeft;
        Node *pRight;
        Node *pParent;
        // Constructor với các giá trị mặc định
        Node(int val = 0, Node *l = nullptr, Node *r = nullptr, Node *par = nullptr) : val(val), pLeft(l), pRight(r), pParent(par) {}
    };

    Node *root;

    /**
     * Hàm in cây nhị phân dạng ngang (cho mục đích kiểm tra)
     * Giúp trực quan hóa cấu trúc cây trong quá trình debug
     */
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

    /**
     * Duyệt cây theo thứ tự tiền thứ tự (Preorder)
     * - Thứ tự: gốc -> trái -> phải
     * - Thường dùng để in ra cây hoặc sao chép cây
     */
    void printPreorder(Node *p)
    {
        if (!p)
        {
            return;
        }
        cout << p->val << ' ';    // In giá trị node hiện tại
        printPreorder(p->pLeft);  // Duyệt cây con trái
        printPreorder(p->pRight); // Duyệt cây con phải
    }

    /**1.
     * Xoay phải node p (Right Rotation)
     *
     * Trước khi xoay:        Sau khi xoay:
     *      P                      L
     *     / \                    / \
     *    L   R     --->         X   P
     *   / \                        / \
     *  X   Y                      Y   R
     *
     * Độ phức tạp: O(1)
     */
    void rightRotate(Node *p)
    {
        // Kiểm tra điều kiện: không thể xoay nếu p hoặc con trái của p là nullptr
        if (!p || !p->pLeft)
            return;

        // Lưu tham chiếu đến con trái của p
        Node *l = p->pLeft;

        // Cập nhật con trái của p thành con phải của l
        p->pLeft = l->pRight;
        if (l->pRight)
        {
            l->pRight->pParent = p; // Cập nhật parent của con phải của l
        }

        // Cập nhật cha của l thành cha của p
        l->pParent = p->pParent;

        // Cập nhật con trỏ từ cha của p đến l
        if (!p->pParent)
        {
            root = l; // Nếu p là root, l trở thành root mới
        }
        else if (p == p->pParent->pLeft)
        {
            p->pParent->pLeft = l; // Nếu p là con trái của cha nó
        }
        else
        {
            p->pParent->pRight = l; // Nếu p là con phải của cha nó
        }

        // Đặt p là con phải của l và cập nhật cha của p
        l->pRight = p;
        p->pParent = l;
    }

    /**2.
     * Xoay trái node p (Left Rotation)
     *
     * Trước khi xoay:        Sau khi xoay:
     *      P                      R
     *     / \                    / \
     *    L   R     --->         P   Y
     *       / \                / \
     *      X   Y              L   X
     *
     * Độ phức tạp: O(1)
     */
    void leftRotate(Node *p)
    {
        // Kiểm tra điều kiện: không thể xoay nếu p hoặc con phải của p là nullptr
        if (!p || !p->pRight)
            return;

        // Lưu tham chiếu đến con phải của p
        Node *r = p->pRight;

        // Cập nhật con phải của p thành con trái của r
        p->pRight = r->pLeft;
        if (r->pLeft)
        {
            r->pLeft->pParent = p; // Cập nhật parent của con trái của r
        }

        // Cập nhật cha của r thành cha của p
        r->pParent = p->pParent;

        // Cập nhật con trỏ từ cha của p đến r
        if (!p->pParent)
        {
            root = r; // Nếu p là root, r trở thành root mới
        }
        else if (p == p->pParent->pLeft)
        {
            p->pParent->pLeft = r; // Nếu p là con trái của cha nó
        }
        else
        {
            p->pParent->pRight = r; // Nếu p là con phải của cha nó
        }

        // Đặt p là con trái của r và cập nhật cha của p
        r->pLeft = p;
        p->pParent = r;
    }

    /**3.
     * Tìm node có giá trị lớn nhất trong cây con
     * Được sử dụng trong quá trình xóa node
     *
     * @param p Node gốc của cây con
     * @return Node có giá trị lớn nhất trong cây con
     */
    Node *findMax(Node *p)
    {
        // Nếu cây con rỗng, trả về nullptr
        if (!p)
            return nullptr;

        // Node lớn nhất nằm ở phía ngoài cùng bên phải
        while (p->pRight)
        {
            p = p->pRight;
        }

        return p;
    }

public:
    /**
     * Constructor: Khởi tạo cây Splay rỗng
     */
    SplayTree()
    {
        root = nullptr;
    }

    /**
     * Destructor: Giải phóng bộ nhớ
     * Ở đây không thực hiện việc xóa các node (giả định sẽ được quản lý bởi bên ngoài)
     */
    ~SplayTree()
    {
        // Chú ý: Trong thực tế cần giải phóng tất cả các node để tránh rò rỉ bộ nhớ
    }

    /**
     * In cây nhị phân dạng trực quan
     * Phương thức public để gọi từ bên ngoài lớp
     */
    void printBinaryTree()
    {
        printBinaryTree("", root, false, false);
    }

    /**
     * In cây theo thứ tự tiền thứ tự
     * Phương thức public để gọi từ bên ngoài lớp
     */
    void printPreorder()
    {
        printPreorder(root);
        cout << "\n"; // Xuống dòng sau khi in xong
    }

    /**4.
     * Phương thức splay: Đưa một node lên làm gốc của cây
     *
     * Được thực hiện qua 3 trường hợp chính:
     * 1. Zig: Node p là con trực tiếp của gốc
     * 2. Zig-Zig: Node p và cha của p đều là con trái (hoặc đều là con phải)
     * 3. Zig-Zag: Node p là con trái nhưng cha của p là con phải (hoặc ngược lại)
     *
     * Độ phức tạp: O(h) với h là chiều cao của cây
     */
    void splay(Node *p)
    {
        // Kiểm tra điều kiện: nếu p là nullptr hoặc đã là root, không cần splay
        if (!p || !p->pParent)
            return;

        // Tiếp tục splay cho đến khi p trở thành root
        while (p->pParent)
        {
            Node *parent = p->pParent;
            Node *grandparent = parent->pParent;

            // Trường hợp 1: Zig (parent là root)
            if (!grandparent)
            {
                if (p == parent->pLeft)
                {
                    rightRotate(parent); // Xoay phải nếu p là con trái
                }
                else
                {
                    leftRotate(parent); // Xoay trái nếu p là con phải
                }
            }
            // Trường hợp 2: Zig-Zig (p và parent đều là con trái hoặc đều là con phải)
            else if ((p == parent->pLeft && parent == grandparent->pLeft) ||
                     (p == parent->pRight && parent == grandparent->pRight))
            {

                if (p == parent->pLeft)
                {
                    // Xoay phải 2 lần (xoay grandparent trước, sau đó xoay parent)
                    rightRotate(grandparent);
                    rightRotate(parent);
                }
                else
                {
                    // Xoay trái 2 lần (xoay grandparent trước, sau đó xoay parent)
                    leftRotate(grandparent);
                    leftRotate(parent);
                }
            }
            // Trường hợp 3: Zig-Zag (p là con trái nhưng parent là con phải hoặc ngược lại)
            else
            {
                if (p == parent->pLeft && parent == grandparent->pRight)
                {
                    // Xoay phải rồi xoay trái
                    rightRotate(parent);
                    leftRotate(grandparent);
                }
                else
                {
                    // Xoay trái rồi xoay phải
                    leftRotate(parent);
                    rightRotate(grandparent);
                }
            }
        }
    }

    /**5.
     * Phương thức tìm kiếm một giá trị trong cây Splay
     *
     * Thuật toán:
     * 1. Tìm kiếm như trong BST thông thường
     * 2. Nếu tìm thấy, splay node đó lên làm gốc và trả về true
     * 3. Nếu không tìm thấy, splay node cuối cùng được truy cập lên làm gốc và trả về false
     *
     * Độ phức tạp: O(h) với h là chiều cao của cây
     */
    bool search(int val)
    {
        // Kiểm tra trường hợp đặc biệt: cây rỗng
        if (!root)
        {
            return false; // Không thể tìm thấy trong cây rỗng
        }

        Node *curr = root;
        Node *lastAccessed = nullptr; // Lưu node cuối cùng được truy cập

        // Tìm kiếm như trong BST thông thường
        while (curr)
        {
            lastAccessed = curr; // Cập nhật node cuối cùng được truy cập

            // Nếu tìm thấy giá trị cần tìm
            if (val == curr->val)
            {
                splay(curr); // Splay node này lên làm gốc
                return true; // Trả về true
            }

            // Tiếp tục tìm kiếm trong cây con phù hợp
            if (val < curr->val)
            {
                curr = curr->pLeft; // Đi sang cây con trái nếu giá trị nhỏ hơn
            }
            else
            {
                curr = curr->pRight; // Đi sang cây con phải nếu giá trị lớn hơn
            }
        }

        // Nếu không tìm thấy, splay node cuối cùng được truy cập lên làm gốc
        // Đây là một đặc điểm quan trọng của Splay Tree giúp tối ưu các truy vấn tương tự trong tương lai
        splay(lastAccessed);
        return false; // Trả về false
    }

    /**6.
     * Phương thức xóa một node có giá trị cho trước khỏi cây Splay
     *
     * Thuật toán:
     * 1. Tìm kiếm node có giá trị cần xóa và splay nó lên làm gốc
     * 2. Nếu không tìm thấy, trả về nullptr
     * 3. Nếu tìm thấy, tách cây thành 2 cây con: cây con trái và cây con phải
     * 4. Nếu cây con trái rỗng, cây con phải trở thành cây mới
     * 5. Nếu cây con trái không rỗng, tìm node lớn nhất trong cây con trái và splay nó lên làm gốc của cây con trái
     * 6. Gắn cây con phải vào là con phải của gốc mới của cây con trái
     * 7. Trả về node đã xóa
     *
     * Độ phức tạp: O(h) với h là chiều cao của cây
     */
    Node *remove(int val)
    {
        // Trường hợp 1: Cây rỗng, không thể xóa
        if (!root)
        {
            return nullptr;
        }

        // Bước 1: Tìm kiếm node có giá trị cần xóa và splay nó lên làm gốc
        bool found = search(val);

        // Bước 2: Nếu không tìm thấy node có giá trị val, trả về nullptr
        if (!found || root->val != val)
        {
            return nullptr;
        }

        // Bước 3: Lưu lại node cần xóa
        Node *nodeToRemove = root;

        // Bước 4: Tạo 2 cây con tách biệt
        Node *leftSubtree = root->pLeft;
        Node *rightSubtree = root->pRight;

        // Ngắt liên kết giữa node cần xóa với 2 cây con
        if (leftSubtree)
        {
            leftSubtree->pParent = nullptr;
        }
        if (rightSubtree)
        {
            rightSubtree->pParent = nullptr;
        }

        // Bước 5: Xác định root mới
        if (!leftSubtree)
        {
            // Trường hợp 5.1: Cây con trái rỗng, cây con phải trở thành cây mới
            root = rightSubtree;
        }
        else
        {
            // Trường hợp 5.2: Cây con trái không rỗng

            // Lưu lại root cũ để cập nhật thông tin
            root = leftSubtree;

            // Tìm node lớn nhất trong cây con trái
            Node *maxNodeInLeft = findMax(leftSubtree);

            // Splay node lớn nhất lên làm gốc của cây con trái
            splay(maxNodeInLeft);

            // Gắn cây con phải vào là con phải của gốc mới
            root->pRight = rightSubtree;
            if (rightSubtree)
            {
                rightSubtree->pParent = root;
            }
        }

        // Bước 6: Ngắt liên kết của node cần xóa
        nodeToRemove->pLeft = nullptr;
        nodeToRemove->pRight = nullptr;
        nodeToRemove->pParent = nullptr;

        // Bước 7: Trả về node đã xóa
        return nodeToRemove;
    }
};

// Hàm main
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
        // if (op == "insert")
        //  tree.insert(val);
        if (op == "remove")
            cout << (tree.remove(val) != nullptr ? "removed" : "not found") << '\n';
        else if (op == "search")
            cout << (tree.search(val) ? "found" : "not found") << '\n';
        else if (op == "print")
            tree.printPreorder();
    }
    tree.printBinaryTree();

    return 0;
}