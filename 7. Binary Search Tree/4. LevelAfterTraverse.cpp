#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> // Để sử dụng std::reverse

using namespace std;

class BSTNode
{
public:
    int val;
    BSTNode *left;
    BSTNode *right;
    BSTNode()
    {
        this->left = this->right = nullptr;
    }
    BSTNode(int val)
    {
        this->val = val;
        this->left = this->right = nullptr;
    }
    BSTNode(int val, BSTNode *&left, BSTNode *&right)
    {
        this->val = val;
        this->left = left;
        this->right = right;
    }
};

/*
 * Cấu trúc nút của cây nhị phân tìm kiếm
struct BSTNode
{
    int val;        // Giá trị của nút
    BSTNode *left;  // Con trái
    BSTNode *right; // Con phải
    // Constructor
    BSTNode(int value) : val(value), left(nullptr), right(nullptr) {}
};
*/

/**
 * Hàm duyệt cây nhị phân tìm kiếm theo từng tầng, với hướng duyệt xen kẽ
 * - Các tầng chẵn (0, 2, 4, ...) duyệt từ trái sang phải
 * - Các tầng lẻ (1, 3, 5, ...) duyệt từ phải sang trái
 *
 * @param root Nút gốc của cây nhị phân tìm kiếm
 * @return Vector chứa giá trị các phần tử theo thứ tự duyệt
 */
vector<int> levelAlterTraverse(BSTNode *root)
{
    // Vector để lưu kết quả duyệt
    vector<int> result;

    // Kiểm tra trường hợp cây rỗng
    if (root == nullptr)
    {
        return result; // Trả về vector rỗng
    }

    // Sử dụng hàng đợi để duyệt cây theo tầng
    queue<BSTNode *> q;
    q.push(root); // Bắt đầu với nút gốc

    // Biến theo dõi tầng hiện tại (bắt đầu từ 0)
    int level = 0;

    // Duyệt từng tầng của cây
    while (!q.empty())
    {
        // Lấy số lượng nút ở tầng hiện tại
        int levelSize = q.size();

        // Vector tạm thời để lưu các nút ở tầng hiện tại
        vector<int> levelNodes;

        // Xử lý tất cả các nút ở tầng hiện tại
        for (int i = 0; i < levelSize; i++)
        {
            // Lấy nút đầu tiên từ hàng đợi
            BSTNode *current = q.front();
            q.pop();

            // Thêm giá trị của nút hiện tại vào vector tạm thời
            levelNodes.push_back(current->val);

            // Thêm các con của nút hiện tại vào hàng đợi để xử lý ở tầng tiếp theo
            if (current->left != nullptr)
            {
                q.push(current->left);
            }
            if (current->right != nullptr)
            {
                q.push(current->right);
            }
        }

        // Thêm các nút vào kết quả theo hướng duyệt tương ứng với tầng
        if (level % 2 == 0)
        {
            // Tầng chẵn (0, 2, 4, ...) - duyệt từ trái sang phải
            result.insert(result.end(), levelNodes.begin(), levelNodes.end());
        }
        else
        {
            // Tầng lẻ (1, 3, 5, ...) - duyệt từ phải sang trái
            result.insert(result.end(), levelNodes.rbegin(), levelNodes.rend());
        }

        // Chuyển sang tầng tiếp theo
        level++;
    }

    return result; // Trả về kết quả duyệt
}
/*
Tôi sẽ giải thích chi tiết hàm `levelAlterTraverse` bằng tiếng Việt:

```cpp
/**
 * Hàm duyệt cây nhị phân tìm kiếm theo từng tầng, với hướng duyệt xen kẽ
 * - Các tầng chẵn (0, 2, 4, ...) duyệt từ trái sang phải
 * - Các tầng lẻ (1, 3, 5, ...) duyệt từ phải sang trái
 *
 * @param root Nút gốc của cây nhị phân tìm kiếm
 * @return Vector chứa giá trị các phần tử theo thứ tự duyệt
 */
vector<int> levelAlterTraverse(BSTNode *root)
{
    // Vector để lưu kết quả duyệt
    vector<int> result;

    // Kiểm tra trường hợp cây rỗng
    if (root == nullptr)
    {
        return result; // Trả về vector rỗng
    }

    // Sử dụng hàng đợi để duyệt cây theo tầng
    queue<BSTNode *> q;
    q.push(root); // Bắt đầu với nút gốc

    // Biến theo dõi tầng hiện tại (bắt đầu từ 0)
    int level = 0;

    // Duyệt từng tầng của cây
    while (!q.empty())
    {
        // Lấy số lượng nút ở tầng hiện tại
        int levelSize = q.size();

        // Vector tạm thời để lưu các nút ở tầng hiện tại
        vector<int> levelNodes;

        // Xử lý tất cả các nút ở tầng hiện tại
        for (int i = 0; i < levelSize; i++)
        {
            // Lấy nút đầu tiên từ hàng đợi
            BSTNode *current = q.front();
            q.pop();

            // Thêm giá trị của nút hiện tại vào vector tạm thời
            levelNodes.push_back(current->val);

            // Thêm các con của nút hiện tại vào hàng đợi để xử lý ở tầng tiếp theo
            if (current->left != nullptr)
            {
                q.push(current->left);
            }
            if (current->right != nullptr)
            {
                q.push(current->right);
            }
        }

        // Thêm các nút vào kết quả theo hướng duyệt tương ứng với tầng
        if (level % 2 == 0)
        {
            // Tầng chẵn (0, 2, 4, ...) - duyệt từ trái sang phải
            result.insert(result.end(), levelNodes.begin(), levelNodes.end());
        }
        else
        {
            // Tầng lẻ (1, 3, 5, ...) - duyệt từ phải sang trái
            result.insert(result.end(), levelNodes.rbegin(), levelNodes.rend());
        }

        // Chuyển sang tầng tiếp theo
        level++;
    }

    return result; // Trả về kết quả duyệt
}
/*
```
## Giải thích chi tiết hàm `levelAlterTraverse`

### 1. Mục đích và ý tưởng của hàm:
Hàm này thực hiện việc duyệt cây nhị phân tìm kiếm (BST) theo từng tầng, trong đó:
- Tầng chẵn (bắt đầu từ 0): duyệt từ trái sang phải
- Tầng lẻ: duyệt từ phải sang trái

### 2. Các bước thực hiện:
#### a. Khởi tạo và xử lý trường hợp đặc biệt:
- Tạo một vector `result` để lưu kết quả duyệt.
- Nếu cây rỗng (root là nullptr), trả về vector rỗng.
#### b. Thiết lập cấu trúc dữ liệu để duyệt theo tầng:
- Sử dụng một hàng đợi (queue) `q` để thực hiện duyệt theo tầng - đây là cấu trúc dữ liệu lý tưởng cho duyệt theo chiều rộng (BFS).
- Đưa nút gốc vào hàng đợi để bắt đầu.
- Sử dụng biến `level` để theo dõi tầng hiện tại, bắt đầu từ 0.
#### c. Duyệt cây theo tầng:
- Vòng lặp while sẽ chạy cho đến khi hàng đợi rỗng (tức là đã duyệt qua tất cả các nút).
- Trong mỗi lần lặp:
  1. Xác định số lượng nút ở tầng hiện tại bằng cách gọi `q.size()`.
  2. Tạo một vector tạm thời `levelNodes` để lưu các giá trị của nút ở tầng hiện tại.
  3. Sử dụng vòng lặp for để xử lý tất cả các nút ở tầng hiện tại:
     - Lấy nút đầu tiên từ hàng đợi.
     - Thêm giá trị của nút vào `levelNodes`.
     - Thêm các nút con (nếu có) vào hàng đợi để xử lý ở tầng tiếp theo.
#### d. Xử lý thứ tự duyệt dựa trên tầng:
- Dựa vào biến `level`, quyết định thứ tự duyệt:
  - Nếu `level` là số chẵn: thêm các giá trị từ `levelNodes` vào `result` theo thứ tự từ trái sang phải.
  - Nếu `level` là số lẻ: thêm các giá trị từ `levelNodes` vào `result` theo thứ tự từ phải sang trái, sử dụng `rbegin()` và `rend()` để đảo ngược thứ tự.
- Tăng biến `level` lên 1 để chuyển sang tầng tiếp theo.
#### e. Kết thúc:
- Sau khi duyệt qua tất cả các tầng, trả về vector `result` chứa các giá trị đã duyệt theo yêu cầu.

### 3. Phân tích độ phức tạp:
- **Độ phức tạp thời gian**: O(n) với n là số nút trong cây.
  - Mỗi nút chỉ được xử lý một lần.
  - Các thao tác vector và queue đều có độ phức tạp O(1).

- **Độ phức tạp không gian**: O(n)
  - Vector `result` sẽ có kích thước n.
  - Trong trường hợp xấu nhất (cây cân bằng hoàn toàn), queue có thể chứa đến n/2 nút (ở tầng cuối cùng).
  - Vector `levelNodes` tạm thời có thể lưu tối đa số nút ở tầng lớn nhất, cũng là O(n).

### 4. Đối với ví dụ trong đề bài:
- Tầng 0 (chẵn): duyệt từ trái sang phải, thu được [3]
- Tầng 1 (lẻ): duyệt từ phải sang trái, thu được [4, 0]
- Tầng 2 (chẵn): duyệt từ trái sang phải, thu được [2, 1]
- Kết quả cuối cùng: [3, 4, 0, 2, 1]

Như vậy, hàm đã thực hiện đúng yêu cầu của đề bài là duyệt cây theo từng tầng với hướng duyệt xen kẽ giữa từ trái sang phải và từ phải sang trái.



*/