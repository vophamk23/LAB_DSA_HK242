#include <iostream>
#include <list>
#include <vector>
using namespace std;

// Lớp Adjacency: Biểu diễn danh sách kề của một đỉnh trong đồ thị
class Adjacency
{
private:
    list<int> adjList; // Danh sách liên kết chứa các đỉnh kề
    int size;          // Kích thước của danh sách kề
public:
    // Hàm khởi tạo mặc định
    Adjacency()
    {
        size = 0; // Khởi tạo kích thước ban đầu là 0
    }

    // Hàm khởi tạo với tham số V (số đỉnh)
    Adjacency(int V)
    {
        size = 0; // Khởi tạo kích thước ban đầu là 0
    }

    // Thêm một đỉnh vào danh sách kề
    void push(int data)
    {
        adjList.push_back(data); // Thêm đỉnh vào cuối danh sách
        size++;                  // Tăng kích thước danh sách lên 1
    }

    // In danh sách kề theo định dạng: " -> đỉnh1 -> đỉnh2 -> ..."
    void print()
    {
        for (auto const &i : adjList)
            cout << " -> " << i;
    }

    // In danh sách kề theo định dạng mảng: "đỉnh1 đỉnh2 ..."
    void printArray()
    {
        for (auto const &i : adjList)
            cout << i << " ";
    }

    // Lấy kích thước của danh sách kề
    int getSize() { return adjList.size(); }

    // Lấy giá trị của đỉnh tại vị trí idx trong danh sách kề
    int getElement(int idx)
    {
        auto it = adjList.begin(); // Iterator trỏ đến phần tử đầu tiên
        advance(it, idx);          // Di chuyển iterator đến vị trí idx
        return *it;                // Trả về giá trị tại vị trí đó
    }
};

// Lớp Graph: Biểu diễn đồ thị
class Graph
{
private:
    int V;          // Số đỉnh trong đồ thị
    Adjacency *adj; // Mảng các danh sách kề
public:
    // Hàm khởi tạo với tham số V (số đỉnh)
    Graph(int V)
    {
        this->V = V;
        adj = new Adjacency[V]; // Cấp phát động mảng các danh sách kề
    }

    // Thêm cạnh vào đồ thị không hướng (thêm w vào danh sách kề của v và ngược lại)
    void addEdge(int v, int w)
    {
        adj[v].push(w); // Thêm w vào danh sách kề của v
        adj[w].push(v); // Thêm v vào danh sách kề của w
    }

    // In thông tin đồ thị ra màn hình
    void printGraph()
    {
        for (int v = 0; v < V; ++v)
        {
            cout << "\nAdjacency list of vertex " << v << "\nhead ";
            adj[v].print(); // In danh sách kề của đỉnh v
        }
    }

    // Thuật toán DFS (Depth-First Search): Tìm kiếm theo chiều sâu
    // Tham số startVertex: đỉnh bắt đầu cho việc duyệt DFS
    // Trả về: một danh sách các đỉnh theo thứ tự thăm DFS
    Adjacency *DFS(int startVertex)
    {
        // Tạo mảng để đánh dấu các đỉnh đã thăm
        // Mỗi phần tử trong mảng tương ứng với một đỉnh trong đồ thị
        // visited[i] = true nếu đỉnh i đã được thăm, ngược lại là false
        bool *visited = new bool[V];

        // Khởi tạo tất cả các đỉnh là chưa được thăm
        for (int i = 0; i < V; i++)
            visited[i] = false;

        // Tạo đối tượng Adjacency để lưu kết quả DFS (thứ tự thăm các đỉnh)
        Adjacency *result = new Adjacency();

        // Gọi hàm đệ quy DFS_Util để thực hiện thuật toán DFS
        // startVertex: đỉnh bắt đầu
        // visited: mảng đánh dấu các đỉnh đã thăm
        // result: danh sách kết quả các đỉnh theo thứ tự thăm
        DFS_Util(startVertex, visited, result);

        // Giải phóng bộ nhớ cho mảng visited khi không còn sử dụng
        delete[] visited;

        // Trả về danh sách các đỉnh theo thứ tự thăm DFS
        return result;
    }

private:
    // Hàm đệ quy hỗ trợ cho DFS
    // vertex: đỉnh đang xét hiện tại
    // visited[]: mảng đánh dấu các đỉnh đã thăm
    // result: danh sách lưu thứ tự thăm các đỉnh
    void DFS_Util(int vertex, bool visited[], Adjacency *result)
    {
        // Bước 1: Đánh dấu đỉnh hiện tại đã thăm
        visited[vertex] = true;

        // Bước 2: Thêm đỉnh hiện tại vào danh sách kết quả
        // Đây là bước quan trọng để ghi nhận thứ tự thăm các đỉnh
        result->push(vertex);

        // Bước 3: Duyệt qua tất cả các đỉnh kề của đỉnh hiện tại
        // Thuật toán sẽ ưu tiên đi sâu trước khi đi rộng
        for (int i = 0; i < adj[vertex].getSize(); i++)
        {
            // Lấy đỉnh kề thứ i của đỉnh hiện tại
            int adjacentVertex = adj[vertex].getElement(i);

            // Bước 4: Nếu đỉnh kề chưa được thăm, đệ quy để thăm nó và tất cả các đỉnh
            // có thể đi đến từ đỉnh kề đó (đi sâu) trước khi thăm đỉnh kề tiếp theo
            // Đây là đặc điểm quan trọng của DFS - đi sâu tối đa có thể trước khi quay lui
            if (!visited[adjacentVertex])
                DFS_Util(adjacentVertex, visited, result);
        }

        // Khi đã thăm hết tất cả các đỉnh kề và các đỉnh có thể đi được từ chúng,
        // thuật toán sẽ tự động quay lui đến đỉnh đã gọi nó trước đó (nhờ vào tính chất đệ quy)
        // Không cần mã hóa việc quay lui vì nó được xử lý tự động bởi cơ chế đệ quy
    }
};

// Hàm main để thử nghiệm đồ thị, DFS và BFS
int main()
{
    // Tạo đồ thị với 6 đỉnh (đánh số từ 0 đến 5)
    Graph g(6);

    // Thêm các cạnh vào đồ thị để tạo thành cấu trúc sau:
    //    0
    //   / \
    //  1   2
    //  |   |\ 
    //  |   | 4
    //  |   |/
    //  3---5
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    // In cấu trúc đồ thị
    cout << "Cấu trúc đồ thị:" << endl;
    g.printGraph();

    // Thực hiện DFS bắt đầu từ đỉnh 0
    cout << "\n\nKết quả DFS bắt đầu từ đỉnh 0: ";
    Adjacency *dfsResult = g.DFS(0);
    dfsResult->printArray();

    /*
    // Thực hiện BFS bắt đầu từ đỉnh 0
    cout << "\n\nKết quả BFS bắt đầu từ đỉnh 0: ";
    Adjacency* bfsResult = g.BFS(0);
    bfsResult->printArray();
    */

    // Giải phóng bộ nhớ
    delete dfsResult;
    // delete bfsResult;

    return 0;
}