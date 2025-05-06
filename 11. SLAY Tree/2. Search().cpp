#include <iostream>
#include <string>
using namespace std;

/**
 * Cây Splay (Splay Tree)
 *
 * Cây Splay là một cấu trúc dữ liệu cây nhị phân tìm kiếm tự cân bằng với đặc tính:
 * - Mỗi khi truy cập một node, node đó sẽ được đưa lên làm gốc (splay operation)
 * - Giúp tối ưu hóa việc truy cập các phần tử thường xuyên sử dụng
 * - Các thao tác cơ bản (insert, search, delete) có độ phức tạp trung bình là O(log n)
 */
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

    // Con trỏ đến node gốc của cây
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

    /**3.
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

    /**4.
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
};

/**
 * Giải thích chi tiết phương thức search:
 *
 * 1. Mục đích:
 *    - Tìm kiếm một giá trị trong cây Splay
 *    - Nếu tìm thấy, đưa node chứa giá trị đó lên làm gốc và trả về true
 *    - Nếu không tìm thấy, đưa node cuối cùng được truy cập lên làm gốc và trả về false
 *
 * 2. Thuật toán:
 *    a. Nếu cây rỗng, trả về false
 *    b. Bắt đầu từ gốc, tìm kiếm giá trị như trong BST thông thường:
 *       - Nếu tìm thấy, splay node đó lên làm gốc và trả về true
 *       - Nếu giá trị cần tìm nhỏ hơn node hiện tại, đi sang cây con trái
 *       - Nếu giá trị cần tìm lớn hơn node hiện tại, đi sang cây con phải
 *       - Trong quá trình tìm kiếm, luôn cập nhật node cuối cùng được truy cập
 *    c. Nếu không tìm thấy, splay node cuối cùng được truy cập lên làm gốc và trả về false
 *
 * 3. Ví dụ:
 *    - Nếu tìm kiếm giá trị 95 trong cây và tìm thấy, node chứa 95 sẽ trở thành gốc
 *    - Nếu tìm kiếm giá trị 250 trong cây và không tìm thấy, node gần nhất (node cuối cùng được truy cập)
 *      sẽ trở thành gốc (như trong ví dụ 2, node 300 trở thành gốc)
 *
 * 4. Phân tích độ phức tạp:
 *    - Thời gian: O(h) cho tìm kiếm + O(h) cho splay = O(h), với h là chiều cao của cây
 *      Trong trường hợp trung bình, h = O(log n)
 *    - Không gian: O(1) (không cần thêm bộ nhớ phụ)
 */

/**
 * Hàm main để chạy chương trình
 *
 * Quy trình:
 * 1. Đọc số lượng truy vấn
 * 2. Với mỗi truy vấn:
 *    - Nếu là "insert", thêm một giá trị vào cây
 *    - Nếu là "search", tìm kiếm một giá trị trong cây
 *    - Nếu là "print", in cây theo thứ tự tiền thứ tự
 * 3. Cuối cùng, in cấu trúc cây để kiểm tra
 */
int main()
{
    SplayTree tree; // Khởi tạo cây Splay rỗng

    int query;
    cin >> query; // Đọc số lượng truy vấn

    for (int i = 0; i < query; i++)
    {
        string op;
        int val;
        cin >> op >> val; // Đọc loại truy vấn và giá trị

        // if (op == "insert")
        // tree.insert(val); // Thêm giá trị vào cây
        if (op == "search")
            cout << (tree.search(val) ? "found" : "not found") << '\n'; // Tìm kiếm và in kết quả
        else if (op == "print")
            tree.printPreorder(); // In cây theo thứ tự tiền thứ tự
    }

    tree.printBinaryTree(); // In cấu trúc cây sau khi thực hiện tất cả các truy vấn

    return 0;
}