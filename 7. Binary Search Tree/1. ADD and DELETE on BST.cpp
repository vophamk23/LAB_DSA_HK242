#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#include <stdexcept> // Thêm thư viện này để sử dụng std::runtime_error
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
        // Bạn phải xóa tất cả các Node trong BinaryTree. Tuy nhiên trong bài này, bạn có thể bỏ qua phần này.
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

    /*
     * Hàm đệ quy để tìm kiếm một giá trị trong cây Nhị phân tìm kiếm
     * @param node: Nút đang xét
     * @param value: Giá trị cần tìm
     * @return con trỏ đến nút chứa giá trị nếu tìm thấy, nullptr nếu không tìm thấy
     */
    Node *searchRec(Node *node, T value)
    {
        // Nếu cây rỗng hoặc đã tìm thấy giá trị
        if (node == nullptr || node->value == value)
        {
            return node; // Trả về nút hiện tại
        }

        // Nếu giá trị nhỏ hơn giá trị của nút hiện tại, tìm trong cây con bên trái
        if (value < node->value)
        {
            return searchRec(node->pLeft, value);
        }
        // Nếu giá trị lớn hơn giá trị của nút hiện tại, tìm trong cây con bên phải
        else
        {
            return searchRec(node->pRight, value);
        }
    }

    // Ham them khong de quy
    Node *interative_Add(Node *node, T value)
    {
        Node *newNode = new Node(value);
        if (node == nullptr)
        {
            return newNode;
        }
        Node *current = node;
        Node *parent = nullptr;

        while (current != nullptr)
        {
            parent = current;
            if (value < current->value)
            {
                current = current->pLeft;
            }
            else
            {
                current = current->pRight;
            }
        }

        if (value < parent->value)
        {
            parent->pLeft = newNode;
        }
        else
        {
            parent->pRight = newNode;
        }

        return node;
    }

    /*
     * Hàm đệ quy để thêm/ADD một giá trị vào cây Nhị phân tìm kiếm
     * @param node: Nút đang xét
     * @param value: Giá trị cần thêm
     * @return con trỏ đến nút gốc của cây con sau khi thêm
     */
    Node *addRec(Node *node, T value)
    {
        // Nếu cây rỗng hoặc đã đến vị trí cần thêm
        if (node == nullptr)
        {
            return new Node(value); // Tạo một nút mới và trả về
        }
        // Nếu giá trị nhỏ hơn hoặc bằng giá trị của nút hiện tại
        if (value <= node->value)
        {
            // Thêm vào cây con bên trái
            // Lưu ý: Khi thêm nút có giá trị bằng với nút hiện tại, thêm vào bên trái theo yêu cầu
            node->pLeft = addRec(node->pLeft, value);
        }
        else
        {
            // Thêm vào cây con bên phải nếu giá trị của Value lớn hơn giá trị của nút hiện tại
            node->pRight = addRec(node->pRight, value);
        }

        // Trả về nút hiện tại sau khi đã thêm giá trị mới
        return node;
    }

    /*
     * Hàm thêm một giá trị vào cây
     * @param value: Giá trị cần thêm
     */
    void add(T value)
    {
        root = addRec(root, value);
    }

    // Ham xoa node khong de quy
    Node *interative_Delete(Node *node, T value)
    {
        Node *parent = nullptr;
        Node *current = node;

        // Tìm nút cần xóa và lưu lại cha của nó
        while (current != nullptr && current->value != value)
        {
            parent = current;
            if (value < current->value)
            {
                current = current->pLeft;
            }
            else
            {
                current = current->pRight;
            }
        }

        // Nếu không tìm thấy nút cần xóa
        if (current == nullptr)
        {
            return node; // Trả về cây không thay đổi
        }

        // Trường hợp 1: Nút không có con (nút lá)
        if (current->pLeft == nullptr && current->pRight == nullptr)
        {
            if (current == node) // Nếu nút cần xóa là nút gốc
            {
                delete current; // Xóa nút
                return nullptr; // Trả về nullptr để cập nhật con trỏ từ cha
            }
            else if (parent->pLeft == current)
            {
                parent->pLeft = nullptr; // Cập nhật con trỏ của cha
            }
            else
            {
                parent->pRight = nullptr; // Cập nhật con trỏ của cha
            }
        }
        // Trường hợp 2: Nút chỉ có một con
        else if (current->pLeft == nullptr)
        {
            if (current == node) // Nếu nút cần xóa là nút gốc
            {
                Node *temp = current->pRight; // Lưu lại con trỏ đến con bên phải
                delete current;               // Xóa nút
                return temp;                  // Trả về con trỏ đến con bên phải để cập nhật từ cha
            }
            else if (parent->pLeft == current)
            {
                parent->pLeft = current->pRight; // Cập nhật con trỏ của cha
            }
            else
            {
                parent->pRight = current->pRight; // Cập nhật con trỏ của cha
            }
        }
        else if (current->pRight == nullptr)
        {
            if (current == node) // Nếu nút cần xóa là nút gốc
            {
                Node *temp = current->pLeft; // Lưu lại con trỏ đến con bên trái
                delete current;              // Xóa nút
                return temp;                 // Trả về con trỏ đến con bên trái để cập nhật từ cha
            }
            else if (parent->pLeft == current)
            {
                parent->pLeft = current->pLeft; // Cập nhật con trỏ của cha
            }
            else
            {
                parent->pRight = current->pLeft; // Cập nhật con trỏ của cha
            }
        }
        // Trường hợp 3: Nút có hai con
        else
        {
            // Tìm nút kế tiếp theo thứ tự inorder (nút nhỏ nhất trong cây con bên phải)
            Node *successor = findMin(current->pRight);

            // Sao chép giá trị của nút kế tiếp vào nút hiện tại
            current->value = successor->value;

            // Xóa nút kế tiếp từ vị trí ban đầu của nó
            current->pRight = deleteNodeRec(current->pRight, successor->value);
        }
        // Trả về nút hiện tại sau khi đã xóa
        return node;
    }

    Node *findMax(Node *node)
    {
        Node *current = node;
        // Đi theo con trỏ bên phải cho đến khi không thể đi tiếp
        while (current && current->pRight != nullptr)
        {
            current = current->pRight;
        }
        return current; // Trả về nút có giá trị lớn nhất
    }
    /*
     * Tìm nút có giá trị nhỏ nhất trong cây con
     * @param node: Nút gốc của cây con
     * @return con trỏ đến nút có giá trị nhỏ nhất
     */
    Node *findMin(Node *node)
    {
        Node *current = node;
        // Đi theo con trỏ bên trái cho đến khi không thể đi tiếp
        while (current && current->pLeft != nullptr)
        {
            current = current->pLeft;
        }
        return current; // Trả về nút có giá trị nhỏ nhất
    }

    /*
     * Hàm đệ quy để xóa một nút có giá trị cụ thể
     * @param node: Nút đang xét
     * @param value: Giá trị cần xóa
     * @return con trỏ đến nút gốc của cây con sau khi xóa
     */
    Node *deleteNodeRec(Node *node, T value)
    {
        // Nếu cây rỗng
        if (node == nullptr)
        {
            return nullptr;
        }

        // Tìm nút cần xóa
        if (value < node->value)
        {
            // Nếu giá trị cần xóa nhỏ hơn giá trị nút hiện tại, tìm trong cây con bên trái
            node->pLeft = deleteNodeRec(node->pLeft, value);
        }
        else if (value > node->value)
        {
            // Nếu giá trị cần xóa lớn hơn giá trị nút hiện tại, tìm trong cây con bên phải
            node->pRight = deleteNodeRec(node->pRight, value);
        }
        else
        {
            // Đã tìm thấy nút cần xóa

            // Trường hợp 1: Nút không có con (nút lá)
            if (node->pLeft == nullptr && node->pRight == nullptr)
            {
                delete node;    // Xóa nút
                return nullptr; // Trả về nullptr để cập nhật con trỏ từ cha
            }
            // Trường hợp 2: Nút chỉ có một con bên phải
            else if (node->pLeft == nullptr)
            {
                Node *temp = node->pRight; // Lưu lại con trỏ đến con bên phải
                delete node;               // Xóa nút
                return temp;               // Trả về con trỏ đến con bên phải để cập nhật từ cha
            }
            // Trường hợp 2: Nút chỉ có một con bên trái
            else if (node->pRight == nullptr)
            {
                Node *temp = node->pLeft; // Lưu lại con trỏ đến con bên trái
                delete node;              // Xóa nút
                return temp;              // Trả về con trỏ đến con bên trái để cập nhật từ cha
            }
            // Trường hợp 3: Nút có hai con
            else
            {
                /*  Node *successor = findMax(node->pLeft); // Tìm nút lớn nhất trong cây con bên trái
                  // Sao chép giá trị của nút kế tiếp vào nút hiện tại
                  node->value = successor->value;
                  // Xóa nút kế tiếp từ vị trí ban đầu của nó
                  node->pLeft = deleteNodeRec(node->pLeft, successor->value);
                 */

                // Hoặc bạn có thể tìm nút nhỏ nhất trong cây con bên phải

                // Tìm nút kế tiếp theo thứ tự inorder (nút nhỏ nhất trong cây con bên phải)
                Node *successor = findMin(node->pRight);

                // Sao chép giá trị của nút kế tiếp vào nút hiện tại
                node->value = successor->value;

                // Xóa nút kế tiếp từ vị trí ban đầu của nó
                node->pRight = deleteNodeRec(node->pRight, successor->value);
            }
        }

        // Trả về nút hiện tại sau khi đã xóa
        return node;
    }
    /*
     * Hàm xóa một nút có giá trị cụ thể
     * @param value: Giá trị cần xóa
     */
    void deleteNode(T value)
    {
        root = deleteNodeRec(root, value);
    }

    /*
     * Hàm đệ quy để duyệt cây theo thứ tự inorder
     * @param root: Nút gốc của cây con
     * @return chuỗi chứa các giá trị theo thứ tự inorder
     */
    string inOrderRec(Node *root)
    {
        stringstream ss;
        if (root != nullptr)
        {
            ss << inOrderRec(root->pLeft);  // Duyệt cây con bên trái
            ss << root->value << " ";       // In giá trị của nút hiện tại
            ss << inOrderRec(root->pRight); // Duyệt cây con bên phải
        }
        return ss.str();
    }
    /**
     * Hàm duyệt cây theo thứ tự inorder
     * @return chuỗi chứa các giá trị theo thứ tự inorder
     */
    string inOrder()
    {
        return inOrderRec(this->root);
    }
    /*
    2. Hàm deleteNode:
    Xóa node lá (không có con): Đơn giản là xóa node và trả về NULL
    Xóa node có một con: Xóa node và thay thế nó bằng node con
    Xóa node có hai con: Theo yêu cầu, tìm node kế tiếp trong duyệt inorder (successor)

    => Successor chính là node nhỏ nhất trong cây con bên phải của node cần xóa
    => Copy giá trị của successor vào node cần xóa
    => Xóa successor từ vị trí ban đầu (đệ quy)*/

    /*
      // Hàm hỗ trợ để kiểm tra xem cây có rỗng hay không
      bool isEmpty() const
      {
          return root == nullptr;
      }
      // Hàm hỗ trợ để lấy giá trị của nút gốc
      T getRootValue() const
      {
          if (root != nullptr)
          {
              return root->value;
          }
          else
          {
              throw runtime_error("Cây rỗng, không có giá trị gốc.");
          }
      }
      // Hàm hỗ trợ để lấy con trỏ đến nút gốc
      Node *getRoot() const
      {
          return root;
      }
      // Hàm hỗ trợ để lấy con trỏ đến nút con trái
      Node *getLeftChild(Node *node) const
      {
          if (node != nullptr)
          {
              return node->pLeft;
          }
          else
          {
              throw runtime_error("Nút không hợp lệ, không có con trái.");
          }
      }
      // Hàm hỗ trợ để lấy con trỏ đến nút con phải
      Node *getRightChild(Node *node) const
      {
          if (node != nullptr)
          {
              return node->pRight;
          }
          else
          {
              throw runtime_error("Nút không hợp lệ, không có con phải.");
          }
      }
      // Hàm hỗ trợ để lấy giá trị của nút
      T getNodeValue(Node *node) const
      {
          if (node != nullptr)
          {
              return node->value;
          }
          else
          {
              throw runtime_error("Nút không hợp lệ, không có giá trị.");
          }
      }
        // Hàm hỗ trợ để kiểm tra xem nút có phải là nút lá hay không
    bool isLeaf(Node *node) const
        {
            return (node != nullptr && node->pLeft == nullptr && node->pRight == nullptr);
        }
        // Hàm hỗ trợ để kiểm tra xem nút có phải là nút gốc hay không
    bool isRoot(Node *node) const
        {
            return (node == root);
        }
    */
};