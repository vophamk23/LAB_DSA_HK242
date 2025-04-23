#include <iostream>
#include <list>
using namespace std;

/**
 * Lớp Adjacency - Quản lý danh sách kề của một đỉnh
 * Lưu trữ các đỉnh kề dưới dạng danh sách liên kết
 */
class Adjacency
{
private:
    list<int> adjList; // Danh sách liên kết chứa các đỉnh kề
    int size;          // Kích thước của danh sách kề
public:
    // Constructor mặc định
    Adjacency() {}

    /*
     * Constructor với tham số số đỉnh
     * @param V Số đỉnh trong đồ thị
     */
    Adjacency(int V) {}

    // Thêm một đỉnh vào danh sách kề
    void push(int data)
    {
        adjList.push_back(data);
        size++;
    }

    // In danh sách kề dưới dạng liên kết (-> node1 -> node2...)
    void print()
    {
        for (auto const &i : adjList)
            cout << " -> " << i;
    }

    // In danh sách kề dưới dạng mảng (node1 node2...)
    void printArray()
    {
        for (auto const &i : adjList)
            cout << i << " ";
    }

    /*
     * Lấy kích thước của danh sách kề
     * @return Số phần tử trong danh sách kề
     */
    int getSize() { return adjList.size(); }

    /*
     * Lấy phần tử tại vị trí chỉ định trong danh sách kề
     * @param idx Vị trí cần lấy phần tử
     * @return Giá trị của phần tử tại vị trí idx
     */
    int getElement(int idx)
    {
        auto it = adjList.begin();
        advance(it, idx); // Di chuyển iterator đến vị trí idx
        return *it;       // Trả về giá trị tại vị trí đó
    }
};

/**
 * Lớp GRAPH - Biểu diễn đồ thị bằng danh sách kề
 */
class Graph
{
private:
    int V;          // Số đỉnh trong đồ thị
    Adjacency *adj; // Mảng các danh sách kề

public:
    /*
     * Constructor khởi tạo đồ thị với số đỉnh cho trước
     * @param V Số đỉnh trong đồ thị
     */
    Graph(int V)
    {
        this->V = V;
        adj = new Adjacency[V]; // Tạo mảng các danh sách kề
    }

    /*
     * Thêm một cạnh vào đồ thị (đồ thị vô hướng)
     * @param v Đỉnh thứ nhất
     * @param w Đỉnh thứ hai
     */
    void addEdge(int v, int w)
    {
        adj[v].push(w); // Thêm w vào danh sách kề của v
        adj[w].push(v); // Thêm v vào danh sách kề của w (đồ thị vô hướng)
    }

    // In đồ thị dưới dạng danh sách kề
    void printGraph()
    {
        for (int v = 0; v < V; ++v)
        {
            cout << "\nAdjacency list of vertex " << v << "\nhead ";
            adj[v].print();
        }
    }

    /**
     * Thuật toán Breadth-First Search (BFS) - Tìm kiếm theo chiều rộng
     * @param v Đỉnh bắt đầu
     * @return Danh sách các đỉnh theo thứ tự duyệt BFS
     */
    Adjacency *BFS(int v)
    {
        // Khởi tạo mảng đánh dấu các đỉnh đã được thăm
        bool *visited = new bool[V];
        for (int i = 0; i < V; i++)
            visited[i] = false; // Khởi tạo tất cả các đỉnh là chưa thăm

        // Khởi tạo danh sách kết quả để lưu trữ thứ tự thăm BFS
        Adjacency *result = new Adjacency(V);

        // Khởi tạo hàng đợi (queue) cho BFS
        list<int> queue;

        // Đánh dấu đỉnh xuất phát đã được thăm và thêm vào hàng đợi
        visited[v] = true;
        queue.push_back(v);

        // Thêm đỉnh xuất phát vào kết quả
        result->push(v);

        // Lặp cho đến khi hàng đợi rỗng
        while (!queue.empty())
        {
            // Lấy đỉnh đầu tiên từ hàng đợi
            int currentVertex = queue.front();
            queue.pop_front();

            // Duyệt qua tất cả các đỉnh kề với đỉnh hiện tại
            for (int i = 0; i < adj[currentVertex].getSize(); i++)
            {
                int adjacentVertex = adj[currentVertex].getElement(i);

                // Nếu đỉnh kề chưa được thăm
                if (!visited[adjacentVertex])
                {
                    // Đánh dấu đã thăm, thêm vào hàng đợi và kết quả
                    visited[adjacentVertex] = true;
                    queue.push_back(adjacentVertex);
                    result->push(adjacentVertex);
                }
            }
        }
        // Giải phóng bộ nhớ
        delete[] visited;

        // Trả về danh sách các đỉnh theo thứ tự BFS
        return result;
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

    /*
    // Thực hiện DFS bắt đầu từ đỉnh 0
     cout << "\n\nKết quả DFS bắt đầu từ đỉnh 0: ";
     Adjacency* dfsResult = g.DFS(0);
     dfsResult->printArray();
     */

    // Thực hiện BFS bắt đầu từ đỉnh 0
    cout << "\n\nKết quả BFS bắt đầu từ đỉnh 0: ";
    Adjacency *bfsResult = g.BFS(0);
    bfsResult->printArray();

    // Giải phóng bộ nhớ
    // delete dfsResult;
    delete bfsResult;

    return 0;
}