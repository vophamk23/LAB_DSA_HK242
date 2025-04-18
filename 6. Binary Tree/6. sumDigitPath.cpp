#include <iostream>
#include <string>
using namespace std;
#include <queue>
#include <utility> // for std::pair

class BTNode
{
public:
    int val;
    BTNode *left;
    BTNode *right;
    BTNode()
    {
        this->left = this->right = NULL;
    }
    BTNode(int val)
    {
        this->val = val;
        this->left = this->right = NULL;
    }
    BTNode(int val, BTNode *&left, BTNode *&right)
    {
        this->val = val;
        this->left = left;
        this->right = right;
    }
};
// Hàm trợ giúp tính tổng các đường đi một cách đệ quy
void calculatePathSum(BTNode *node, long long currentNumber, long long &totalSum, const int MOD)
{
    // Nếu nút là NULL, trả về ngay (điều kiện dừng)
    if (node == NULL)
        return;

    // Cập nhật số hiện tại cho đường đi này (nhân với 10 và cộng thêm chữ số hiện tại) xe VD
    // Cập nhật số hiện tại: currentNumber = (currentNumber * 10 + node->val) % MOD
    // Nhân với 10 để dịch chữ số sang trái
    // Cộng thêm giá trị của nút hiện tại vào hàng đơn vị
    // Lấy dư theo MOD để tránh tràn số
    currentNumber = (currentNumber * 10 + node->val) % MOD;

    // Kiểm tra xem đây có phải là nút lá không, Nếu đây là nút lá thì:
    if (node->left == NULL && node->right == NULL)
    {
        // Đã đến cuối đường đi, thêm số vào tổng
        totalSum = (totalSum + currentNumber) % MOD;
        return;
    }
    // Tiếp tục duyệt xuống cây, Nếu không phải nút lá, tiếp tục đệ quy:
    calculatePathSum(node->left, currentNumber, totalSum, MOD);
    calculatePathSum(node->right, currentNumber, totalSum, MOD);
}
int sumDigitPath(BTNode *root)
{
    if (root == NULL)
        return 0;

    const int MOD = 27022001;
    long long totalSum = 0;
    // Bắt đầu tính toán đệ quy từ gốc với số ban đầu là 0
    calculatePathSum(root, 0, totalSum, MOD);
    return totalSum;
}
/*
1.Ý tưởng tổng quát:
- Dùng thuật toán duyệt cây theo chiều sâu (DFS) để đi từ gốc đến các nút lá
- Khi đi xuống từng nút, ta xây dựng số bằng cách nhân số hiện tại với 10
và cộng thêm giá trị của nút hiện tại
- Khi đến nút lá, ta có một số hoàn chỉnh và cộng nó vào tổng kết quả
2. Hàm calculatePathSum:
- node: Con trỏ đến nút hiện tại đang xét
- currentNumber: Số được tạo ra từ đường đi từ gốc đến nút hiện tại
- totalSum: Tổng của tất cả các số từ các đường đi (truyền bằng tham chiếu)
- MOD: Số chia lấy dư để tránh tràn số
3. Hàm sumDigitPath:
Kiểm tra nếu cây rỗng (root == NULL), trả về 0
Khởi tạo giá trị MOD = 27022001 (theo yêu cầu bài toán)
Khởi tạo tổng = 0
Gọi hàm đệ quy để tính toán: calculatePathSum(root, 0, totalSum, MOD)
Trả về kết quả tổng
*/