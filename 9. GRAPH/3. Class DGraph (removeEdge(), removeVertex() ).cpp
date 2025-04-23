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
// Định nghĩa các phương thức của lớp template DGraph bên ngoài lớp DGraph
// Các phương thức này được định nghĩa bên ngoài lớp DGraph để tách biệt mã nguồn và dễ dàng quản lý

// 4. Triển khai phương thức xóa cạnh trong đồ thị
template <class T>
bool DGraph<T>::removeEdge(T from, T to)
{
    // Bước 1: Tìm đỉnh chứa giá trị "from"
    // Sử dụng phương thức getVertexNode để tìm đỉnh chứa giá trị "from"
    VertexNode *fromNode = getVertexNode(from);

    // Bước 2: Tìm đỉnh chứa giá trị "to"
    // Sử dụng phương thức getVertexNode để tìm đỉnh chứa giá trị "to"
    VertexNode *toNode = getVertexNode(to);

    // Bước 3: Kiểm tra sự tồn tại của cả hai đỉnh
    if (fromNode == nullptr || toNode == nullptr)
    {
        // Nếu ít nhất một đỉnh không tồn tại, ném ngoại lệ
        throw VertexNotFoundException("Vertex doesn't exist!");
    }

    // Bước 4: Xóa cạnh từ fromNode đến toNode sử dụng phương thức removeTo
    bool success = fromNode->removeTo(toNode);

    // Bước 5: Xử lý kết quả sau khi xóa
    if (success)
    {
        // Nếu xóa thành công, giảm số lượng cạnh và trả về true
        countEdge--;
        return true;
    }
    else
    {
        // Nếu không tìm thấy cạnh để xóa, trả về false
        return false;
    }
}

// 5. Triển khai phương thức xóa đỉnh trong đồ thị
template <class T>
void DGraph<T>::removeVertex(T removeVertex)
{
    // Bước 1: Tìm đỉnh cần xóa
    VertexNode *removeNode = getVertexNode(removeVertex);

    // Bước 2: Kiểm tra sự tồn tại của đỉnh cần xóa
    if (removeNode == nullptr)
    {
        // Nếu đỉnh không tồn tại, ném ngoại lệ
        throw VertexNotFoundException("Vertex doesn't exist!");
    }

    // Bước 3: Xóa tất cả các cạnh đi đến đỉnh cần xóa
    VertexNode *current = nodeList;
    while (current != nullptr)
    {
        // Bỏ qua nếu current chính là đỉnh cần xóa
        if (current != removeNode)
        {
            // Thử xóa cạnh từ current đến removeNode
            if (current->removeTo(removeNode))
            {
                // Nếu xóa thành công, giảm số lượng cạnh
                countEdge--;
            }
        }
        // Chuyển sang đỉnh tiếp theo
        current = current->next;
    }

    // Bước 4: Xóa tất cả các cạnh xuất phát từ đỉnh cần xóa
    Edge *currentEdge = removeNode->adList;
    while (currentEdge != nullptr)
    {
        // Lưu lại con trỏ đến cạnh tiếp theo trước khi xóa cạnh hiện tại
        Edge *nextEdge = currentEdge->next;

        // Xóa cạnh hiện tại
        delete currentEdge;

        // Giảm số lượng cạnh
        countEdge--;

        // Chuyển sang cạnh tiếp theo
        currentEdge = nextEdge;
    }

    // Bước 5: Xóa đỉnh khỏi danh sách đỉnh
    if (nodeList == removeNode)
    {
        // Trường hợp 5.1: Nếu đỉnh cần xóa là đỉnh đầu tiên
        nodeList = removeNode->next;
    }
    else
    {
        // Trường hợp 5.2: Nếu đỉnh cần xóa không phải là đỉnh đầu tiên

        // Tìm đỉnh trước removeNode trong danh sách
        current = nodeList;
        while (current != nullptr && current->next != removeNode)
        {
            current = current->next;
        }

        // Nếu tìm thấy đỉnh trước removeNode
        if (current != nullptr)
        {
            // Cập nhật con trỏ next để bỏ qua removeNode
            current->next = removeNode->next;
        }
    }

    // Bước 6: Giải phóng bộ nhớ của removeNode
    delete removeNode;

    // Bước 7: Giảm số lượng đỉnh
    countVertex--;
}