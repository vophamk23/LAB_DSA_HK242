#include <iostream>
#include <list>
#include <vector>
#include <stack>
using namespace std;

/**
 * Lớp Adjacency để lưu trữ danh sách kề
 * Mỗi phần tử trong danh sách kề biểu diễn một đỉnh kề với đỉnh hiện tại
 */
class Adjacency
{
private:
    list<int> adjList; // Danh sách các đỉnh kề
    int size;          // Kích thước của danh sách
public:
    // Hàm khởi tạo mặc định
    Adjacency() {}

    // Hàm khởi tạo với số đỉnh ban đầu
    Adjacency(int V) {}

    /*
     * Thêm một đỉnh vào danh sách kề
     * @param data: Đỉnh cần thêm
     */
    void push(int data)
    {
        adjList.push_back(data);
        size++;
    }

    // In danh sách kề theo định dạng -> đỉnh
    void print()
    {
        for (auto const &i : adjList)
            cout << " -> " << i;
    }

    // In danh sách kề theo định dạng đỉnh đỉnh đỉnh
    void printArray()
    {
        for (auto const &i : adjList)
            cout << i << " ";
    }

    /*
     * Lấy kích thước của danh sách kề
     * @return: Số phần tử trong danh sách kề
     */
    int getSize() { return adjList.size(); }

    /*
     * Lấy giá trị của phần tử tại vị trí idx trong danh sách kề
     * @param idx: Chỉ số của phần tử cần lấy
     * @return: Giá trị của phần tử tại vị trí idx
     */
    int getElement(int idx)
    {
        auto it = adjList.begin();
        advance(it, idx);
        return *it;
    }
};

/**
 * Lớp Graph biểu diễn đồ thị có hướng
 */
class Graph
{
    int V;          // Số đỉnh trong đồ thị
    Adjacency *adj; // Mảng các danh sách kề

    /**
     * Hàm hỗ trợ đệ quy cho thuật toán sắp xếp tô pô
     * @param v: Đỉnh hiện tại đang xét
     * @param visited: Mảng đánh dấu các đỉnh đã thăm
     * @param Stack: Ngăn xếp lưu thứ tự tô pô
     */
    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack)
    {
        // Đánh dấu đỉnh hiện tại đã được thăm
        visited[v] = true;

        // Duyệt qua tất cả các đỉnh kề với đỉnh hiện tại
        for (int i = 0; i < adj[v].getSize(); i++)
        {
            int adjacentVertex = adj[v].getElement(i);
            // Nếu đỉnh kề chưa được thăm, gọi đệ quy để thăm nó
            if (!visited[adjacentVertex])
            {
                topologicalSortUtil(adjacentVertex, visited, Stack);
            }
        }

        // Sau khi duyệt hết tất cả các đỉnh kề, đẩy đỉnh hiện tại vào ngăn xếp
        // Đỉnh được thêm sau khi tất cả các đỉnh "con cháu" đã được thêm vào ngăn xếp
        Stack.push(v);
    }

public:
    /*
     * Hàm khởi tạo đồ thị với V đỉnh
     * @param V: Số đỉnh trong đồ thị
     */
    Graph(int V)
    {
        this->V = V;
        adj = new Adjacency[V];
    }

    /*
     * Thêm cạnh từ đỉnh v đến đỉnh w
     * @param v: Đỉnh nguồn
     * @param w: Đỉnh đích
     */
    void addEdge(int v, int w)
    {
        adj[v].push(w);
    }

    /**
     * Hàm thực hiện thuật toán sắp xếp tô pô và in kết quả
     * Sắp xếp tô pô sắp xếp các đỉnh sao cho nếu có cạnh (u,v),
     * thì u xuất hiện trước v trong kết quả sắp xếp
     */
    void topologicalSort()
    {
        // Tạo một ngăn xếp để lưu kết quả sắp xếp tô pô
        stack<int> Stack;

        // Đánh dấu tất cả các đỉnh là chưa được thăm
        bool *visited = new bool[V];
        for (int i = 0; i < V; i++)
        {
            visited[i] = false;
        }

        // Gọi hàm topologicalSortUtil cho từng đỉnh chưa thăm
        // Luôn bắt đầu từ đỉnh 0 theo yêu cầu để đảm bảo kết quả đúng
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                topologicalSortUtil(i, visited, Stack);
            }
        }

        // In thứ tự tô pô từ ngăn xếp
        while (!Stack.empty())
        {
            cout << Stack.top() << " ";
            Stack.pop();
        }

        // Giải phóng bộ nhớ đã cấp phát
        delete[] visited;
    }

    /**
     * Hàm hủy để giải phóng bộ nhớ
     */
    ~Graph()
    {
        delete[] adj;
    }
};

/**
 * Hàm main để kiểm tra thuật toán
 */
int main()
{
    // Tạo đồ thị với 6 đỉnh (đánh số từ 0 đến 5)
    Graph g(6);

    // Thêm các cạnh vào đồ thị theo ví dụ
    g.addEdge(5, 2); // Cạnh từ đỉnh 5 đến đỉnh 2
    g.addEdge(5, 0); // Cạnh từ đỉnh 5 đến đỉnh 0
    g.addEdge(4, 0); // Cạnh từ đỉnh 4 đến đỉnh 0
    g.addEdge(4, 1); // Cạnh từ đỉnh 4 đến đỉnh 1
    g.addEdge(2, 3); // Cạnh từ đỉnh 2 đến đỉnh 3
    g.addEdge(3, 1); // Cạnh từ đỉnh 3 đến đỉnh 1

    // Thực hiện và in kết quả sắp xếp tô pô
    cout << "Kết quả sắp xếp tô pô: ";
    g.topologicalSort();

    return 0;
}

/*
1. Giải thích thuật toán sắp xếp tô pô (Topological Sort)
- Thuật toán sắp xếp tô pô được sử dụng cho đồ thị có hướng không chu trình (DAG - Directed Acyclic Graph).
- Kết quả của thuật toán là một thứ tự tuyến tính của các đỉnh sao cho nếu có một cạnh từ đỉnh u đến đỉnh v,
thì đỉnh u sẽ xuất hiện trước đỉnh v trong thứ tự tô pô.

2. Cách thức hoạt động:
Thuật toán dựa trên DFS (Depth-First Search):
- Duyệt đồ thị theo chiều sâu
- Sau khi duyệt xong tất cả các đỉnh kề của một đỉnh, đẩy đỉnh đó vào ngăn xếp
- Thứ tự các phần tử trong ngăn xếp (từ đỉnh xuống đáy) chính là thứ tự tô pô

Cấu trúc dữ liệu sử dụng:
- Mảng visited[]: Đánh dấu các đỉnh đã thăm
- Ngăn xếp Stack: Lưu thứ tự tô pô

Quá trình thực hiện của hàm topologicalSortUtil():
- Đánh dấu đỉnh hiện tại là đã thăm
- Với mỗi đỉnh kề chưa thăm, gọi đệ quy để thăm nó
- Sau khi đã thăm hết tất cả các đỉnh kề, đẩy đỉnh hiện tại vào ngăn xếp

Hàm topologicalSort():
- Khởi tạo ngăn xếp và mảng đánh dấu
- Gọi topologicalSortUtil() cho mỗi đỉnh chưa thăm
- In thứ tự tô pô từ ngăn xếp
*/