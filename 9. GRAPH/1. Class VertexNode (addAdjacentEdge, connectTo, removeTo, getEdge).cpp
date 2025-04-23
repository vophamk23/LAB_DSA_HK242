#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;
// Khai báo lớp DGraph có tham số template T (kiểu dữ liệu của đỉnh)
// Lớp này đại diện cho một đồ thị có hướng với các đỉnh có thể là bất kỳ kiểu dữ liệu nào
// Lớp này sử dụng danh sách liên kết đơn để lưu trữ các đỉnh và các cạnh kề của chúng
// Lớp này có các phương thức để thêm, xóa đỉnh và cạnh, kiểm tra đồ thị rỗng, in đồ thị ra console hoặc file
// và các phương thức khác để thao tác với đồ thị
// Lớp này cũng định nghĩa các lớp con VertexNode và Edge để đại diện cho các đỉnh và cạnh trong đồ thị
// Lớp VertexNode đại diện cho một đỉnh trong đồ thị và có các phương thức để thêm, xóa cạnh kề của nó
// Lớp Edge đại diện cho một cạnh trong đồ thị và có các thuộc tính như đỉnh đầu, đỉnh cuối và trọng số của cạnh
template <class T>
class DGraph
{
public:
    class VertexNode; // Khai báo trước lớp VertexNode - Đỉnh (để các hàm trong DGraph có thể sử dụng)
    class Edge;       // Khai báo trước lớp Edge - Cạnh (để các hàm trong DGraph có thể sử dụng)
protected:
    VertexNode *nodeList; // Con trỏ đến đầu danh sách đỉnh (danh sách liên kết đơn)
    int countVertex;      // Số lượng đỉnh trong đồ thị
    int countEdge;        // Số lượng cạnh trong đồ thị
public:
    DGraph()
    {                             // Hàm khởi tạo không tham số - ĐỒ THỊ RỖNG
        this->nodeList = nullptr; // Khởi tạo danh sách đỉnh rỗng
        this->countEdge = 0;      // Chưa có cạnh nào
        this->countVertex = 0;    // Chưa có đỉnh nào
    }
    ~DGraph() {};                //  Hàm hủy - Không làm gì đặc biệt
    DGraph(const DGraph &other); // Hàm sao chép - Tạo một đồ thị mới từ đồ thị khác

    VertexNode *getVertexNode(T vertex); // Tìm đỉnh có giá trị vertex trong đồ thị

    void add(T vertex);                           // Thêm một đỉnh mới có giá trị vertex vào đồ thị
    void connect(T from, T to, float weight = 0); // Tạo cạnh có hướng từ đỉnh from đến đỉnh to với trọng số weight

    void removeVertex(T removeVertex); // Xóa đỉnh có giá trị removeVertex khỏi đồ thị
    bool removeEdge(T from, T to);     // Xóa cạnh từ đỉnh from đến đỉnh to

    string shape();    // Trả về chuỗi mô tả hình dạng đồ thị
    bool empty();      // Kiểm tra đồ thị rỗng
    void clear();      // Xóa toàn bộ đồ thị
    void printGraph(); // In đồ thị ra console

    void printGraph(ofstream &out);               // In đồ thị ra file
    void printGraph(ofstream &out, string title); // In đồ thị ra file với tiêu đề

public:
    // Định nghĩa lớp VertexNode (đại diện cho một ĐỈNH trong đồ thị)
    // Lớp này được định nghĩa bên trong lớp DGraph để có thể truy cập các thành phần private của lớp DGraph
    // và ngược lại. Điều này giúp cho việc quản lý và thao tác với các đỉnh và cạnh trong đồ thị trở nên dễ dàng hơn.
    // Lớp VertexNode có thể được sử dụng độc lập, nhưng thường được sử dụng trong ngữ cảnh của lớp DGraph.
    class VertexNode
    {
    private:
        T vertex;            // Giá trị của đỉnh
        Edge *adList;        // Con trỏ đến đầu danh sách cạnh kề của đỉnh này
        VertexNode *next;    // Con trỏ đến đỉnh tiếp theo trong danh sách đỉnh
        friend class Edge;   // Cho phép lớp Edge truy cập các thành phần private của VertexNode
        friend class DGraph; // Cho phép lớp DGraph truy cập các thành phần private của VertexNode
    public:
        VertexNode(T vertex, Edge *adList = nullptr, VertexNode *next = nullptr)
        {                          // Hàm khởi tạo
            this->vertex = vertex; // Gán giá trị cho đỉnh
            this->adList = adList; // Gán danh sách cạnh kề (mặc định là rỗng)
            this->next = next;     // Gán đỉnh tiếp theo (mặc định là không có)
        }
        ~VertexNode() {};                // Hàm hủy - Không làm gì đặc biệt
        T getVertex() { return vertex; } // Trả về giá trị của đỉnh
        string toString();               // Trả về chuỗi mô tả đỉnh

        void addAdjacentEdge(Edge *newEdge);                  // Thêm một cạnh mới vào danh sách cạnh kề của đỉnh
        bool connectTo(VertexNode *toNode, float weight = 0); // Tạo cạnh từ đỉnh này đến đỉnh toNode
        bool removeTo(VertexNode *toNode);                    // Xóa cạnh từ đỉnh này đến đỉnh toNode
        Edge *getEdge(VertexNode *toNode);                    // Tìm cạnh từ đỉnh này đến đỉnh toNode
    };

    // Định nghĩa lớp Edge (đại diện cho một cạnh có hướng)
    // Lớp này được định nghĩa bên trong lớp DGraph để có thể truy cập các thành phần private của lớp DGraph
    // và ngược lại. Điều này giúp cho việc quản lý và thao tác với các đỉnh và cạnh trong đồ thị trở nên dễ dàng hơn.
    // Lớp Edge có thể được sử dụng độc lập, nhưng thường được sử dụng trong ngữ cảnh của lớp DGraph.
    // Lớp Edge đại diện cho một cạnh có hướng giữa hai đỉnh trong đồ thị.
    // Mỗi cạnh có một đỉnh đầu (fromNode), một đỉnh cuối (toNode) và một trọng số (weight).
    class Edge
    {
    private:
        VertexNode *fromNode;    // Đỉnh đầu của cạnh (từ đâu)
        VertexNode *toNode;      // Đỉnh cuối của cạnh (đến đâu)
        float weight;            // Trọng số của cạnh
        Edge *next;              // Con trỏ đến cạnh tiếp theo trong danh sách cạnh kề
        friend class VertexNode; // Cho phép lớp VertexNode truy cập các thành phần private của Edge
        friend class DGraph;     // Cho phép lớp DGraph truy cập các thành phần private của Edge
    public:
        Edge(VertexNode *fromNode, VertexNode *toNode, float weight = 0.0, Edge *next = nullptr)
        {                              // Hàm khởi tạo
            this->fromNode = fromNode; // Gán đỉnh đầu
            this->toNode = toNode;     // Gán đỉnh cuối
            this->weight = weight;     // Gán trọng số
            this->next = next;         // Gán cạnh tiếp theo (mặc định là không có)
        }
        string toString(); // Trả về chuỗi mô tả cạnh
    };
};
// Định nghĩa các phương thức của lớp VertexNode bên ngoài lớp DGraph
// Các phương thức này được định nghĩa bên ngoài lớp DGraph để tách biệt mã nguồn và dễ dàng quản lý

// 1. Tìm kiếm cạnh từ đỉnh hiện tại đến đỉnh toNode
/**
 * @brief Tìm kiếm cạnh từ đỉnh hiện tại đến đỉnh đích
 * @param toNode Con trỏ đến đỉnh đích cần tìm
 * @return Con trỏ đến cạnh nếu tìm thấy, nullptr nếu không tồn tại
 * @complexity O(n) với n là số cạnh kề của đỉnh hiện tại
 *
 * Thuật toán:
 * - Duyệt tuần tự qua danh sách kề (adjacency list)
 * - Kiểm tra đỉnh đích của mỗi cạnh
 * - Trả về cạnh đầu tiên thỏa điều kiện hoặc nullptr nếu không tìm thấy
 */
template <class T>
typename DGraph<T>::Edge *DGraph<T>::VertexNode::getEdge(VertexNode *toNode)
{
    // Duyệt qua danh sách kề của đỉnh hiện tại để tìm cạnh
    Edge *current = this->adList;

    while (current != nullptr)
    {
        // Kiểm tra xem cạnh hiện tại có đến đỉnh toNode không
        if (current->toNode == toNode)
        {
            return current; // Trả về cạnh nếu tìm thấy
        }
        current = current->next; // Chuyển sang cạnh tiếp theo trong danh sách
    }
    // Nếu không tìm thấy cạnh nào, trả về nullptr
    return nullptr;
}

// 2. Thêm một cạnh mới vào danh sách kề của đỉnh hiện tại
/**
 * @brief Thêm một cạnh mới vào danh sách kề của đỉnh hiện tại
 * @param newEdge Con trỏ đến cạnh mới cần thêm vào
 * @complexity O(1) - thao tác chèn đầu danh sách
 *
 * Thuật toán:
 * - Sử dụng phương pháp chèn đầu cho danh sách liên kết đơn
 * - Xử lý riêng trường hợp danh sách rỗng
 * - Không kiểm tra tính duy nhất của cạnh (được xử lý ở connectTo)
 */
template <class T>
void DGraph<T>::VertexNode::addAdjacentEdge(Edge *newEdge)
{
    // Sử dụng phương pháp thêm vào đầu danh sách liên kết đơn
    if (this->adList == nullptr)
    {
        // Nếu danh sách kề rỗng, đặt newEdge làm phần tử đầu tiên
        this->adList = newEdge;
    }
    else
    {
        // Ngược lại, chèn newEdge vào đầu danh sách
        newEdge->next = this->adList;
        this->adList = newEdge;
    }
}

// 3. Tạo kết nối từ đỉnh hiện tại đến đỉnh toNode với trọng số weight
/**
 * @brief Tạo kết nối từ đỉnh hiện tại đến đỉnh đích với trọng số xác định
 * @param toNode Con trỏ đến đỉnh đích cần kết nối
 * @param weight Trọng số của cạnh, mặc định là 0
 * @return true nếu tạo cạnh mới, false nếu chỉ cập nhật cạnh hiện có
 * @complexity O(n) với n là số cạnh kề của đỉnh hiện tại
 *
 * Thuật toán:
 * - Kiểm tra sự tồn tại của cạnh thông qua phương thức getEdge
 * - Nếu đã tồn tại, cập nhật trọng số
 * - Nếu chưa tồn tại, tạo cạnh mới và thêm vào danh sách kề
 * - Đảm bảo tính duy nhất của mỗi cặp đỉnh trong đồ thị có hướng
 */
template <class T>
bool DGraph<T>::VertexNode::connectTo(VertexNode *toNode, float weight)
{
    // Đầu tiên, kiểm tra xem cạnh này đã tồn tại chưa
    Edge *existingEdge = getEdge(toNode);

    if (existingEdge != nullptr)
    {
        // Nếu cạnh đã tồn tại, chỉ cập nhật trọng số
        existingEdge->weight = weight;
        return false; // Không có cạnh mới được tạo
    }
    else
    {
        // Nếu cạnh chưa tồn tại, tạo cạnh mới và thêm vào danh sách kề
        // Cạnh chưa tồn tại, khởi tạo cạnh mới
        Edge *newEdge = new Edge(this, toNode, weight);
        // Thêm vào danh sách kề
        addAdjacentEdge(newEdge);
        return true; // Đã tạo cạnh mới
    }
}

// 4. Xóa cạnh từ đỉnh hiện tại đến đỉnh toNode
/**
 * @brief Xóa cạnh từ đỉnh hiện tại đến đỉnh đích
 * @param toNode Con trỏ đến đỉnh đích của cạnh cần xóa
 * @return true nếu xóa thành công, false nếu không tìm thấy cạnh
 * @complexity O(n) với n là số cạnh kề của đỉnh hiện tại
 *
 * Thuật toán:
 * - Xử lý các trường hợp đặc biệt: danh sách rỗng và cạnh ở đầu danh sách
 * - Duyệt danh sách để tìm vị trí của cạnh cần xóa
 * - Cập nhật con trỏ next và giải phóng bộ nhớ
 * - Xử lý đúng để tránh memory leak
 */
template <class T>
bool DGraph<T>::VertexNode::removeTo(VertexNode *toNode)
{
    // Kiểm tra trường hợp đặc biệt: danh sách kề rỗng
    if (this->adList == nullptr)
    {
        return false; // Không có cạnh nào để xóa
    }

    // Trường hợp đặc biệt: cạnh cần xóa ở đầu danh sách
    if (this->adList->toNode == toNode)
    {
        Edge *temp = this->adList;
        this->adList = this->adList->next; // Cập nhật đầu danh sách
        delete temp;                       // Giải phóng bộ nhớ
        return true;
    }

    // Trường hợp tổng quát: tìm cạnh trong danh sách
    Edge *current = this->adList;
    while (current->next != nullptr)
    {
        if (current->next->toNode == toNode)
        {
            // Tìm thấy cạnh cần xóa (current->next)
            Edge *temp = current->next;
            current->next = current->next->next; // Bỏ qua cạnh cần xóa
            delete temp;                         // Giải phóng bộ nhớ
            return true;
        }
        current = current->next;
    }
    // Không tìm thấy cạnh cần xóa
    return false;
}