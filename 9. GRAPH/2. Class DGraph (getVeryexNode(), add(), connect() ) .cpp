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

// 1. Phương thức tìm kiếm đỉnh trong đồ thị
template <class T>
typename DGraph<T>::VertexNode *DGraph<T>::getVertexNode(T vertex)
{
    // Duyệt qua danh sách liên kết các đỉnh bắt đầu từ nodeList
    VertexNode *current = nodeList;
    while (current != nullptr)
    {
        // Kiểm tra nếu đỉnh hiện tại chứa giá trị vertex cần tìm
        if (current->vertex == vertex)
        {
            return current; // Trả về con trỏ đến đỉnh nếu tìm thấy
        }
        // Di chuyển đến đỉnh tiếp theo trong danh sách
        current = current->next;
    }
    return nullptr; // Trả về nullptr nếu không tìm thấy vertex
}

// 2. Phương thức thêm một đỉnh mới vào đồ thị
template <class T>
void DGraph<T>::add(T vertex)
{
    // Tạo một đỉnh mới với giá trị vertex
    VertexNode *newNode = new VertexNode(vertex);

    // Thêm đỉnh mới vào cuối danh sách các đỉnh
    if (nodeList == nullptr)
    {
        // Nếu danh sách rỗng, đỉnh mới trở thành đỉnh đầu tiên
        nodeList = newNode;
    }
    else
    {
        // Tìm đỉnh cuối cùng trong danh sách
        VertexNode *current = nodeList;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        // Thêm đỉnh mới vào sau đỉnh cuối cùng
        current->next = newNode;
    }

    // Tăng số lượng đỉnh
    countVertex++;
}

// 3. Phương thức tạo kết nối từ đỉnh "from" đến đỉnh "to" với trọng số weight
template <class T>
void DGraph<T>::connect(T from, T to, float weight)
{
    // Tìm đỉnh chứa giá trị "from" và đỉnh chứa giá trị "to"
    VertexNode *fromNode = getVertexNode(from);
    VertexNode *toNode = getVertexNode(to);

    // Nếu một trong hai đỉnh không tồn tại, ném ngoại lệ
    if (fromNode == nullptr || toNode == nullptr)
    {
        throw VertexNotFoundException("Vertex doesn't exist!");
    }

    // Kết nối đỉnh "from" đến đỉnh "to"
    bool isNewEdge = fromNode->connectTo(toNode, weight);

    // Nếu tạo cạnh mới, tăng biến đếm số cạnh
    if (isNewEdge)
    {
        countEdge++;
    }
}