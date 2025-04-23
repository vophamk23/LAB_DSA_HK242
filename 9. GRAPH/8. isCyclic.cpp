#include <iostream>
#include <vector>
#include <list>
using namespace std;

// Lớp đồ thị có hướng
class DirectedGraph
{
private:
    int V;                 // Số đỉnh của đồ thị
    vector<list<int>> adj; // Danh sách kề

    // Hàm DFS đệ quy để kiểm tra chu trình
    bool isCyclicUtil(int v, vector<bool> &visited, vector<bool> &recStack)
    {
        // Đánh dấu đỉnh hiện tại là đã thăm và thêm vào ngăn xếp đệ quy
        visited[v] = true;
        recStack[v] = true;

        // Duyệt tất cả các đỉnh kề với đỉnh hiện tại
        for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            // Nếu đỉnh kề chưa được thăm, tiếp tục DFS từ đỉnh đó
            if (!visited[*i] && isCyclicUtil(*i, visited, recStack))
            {
                return true;
            }
            // Nếu đỉnh kề đã có trong ngăn xếp đệ quy, có chu trình
            else if (recStack[*i])
            {
                return true;
            }
        }

        // Xóa đỉnh khỏi ngăn xếp đệ quy khi quay lui
        recStack[v] = false;
        return false;
    }

public:
    // Hàm khởi tạo đồ thị với V đỉnh
    DirectedGraph(int V)
    {
        this->V = V;
        adj.resize(V);
    }

    // Thêm cạnh từ đỉnh u đến đỉnh v
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    // Kiểm tra xem đồ thị có chu trình hay không
    bool isCyclic()
    {
        // Khởi tạo mảng đánh dấu các đỉnh đã thăm
        vector<bool> visited(V, false);

        // Mảng đánh dấu các đỉnh đang nằm trong ngăn xếp đệ quy (đường đi hiện tại)
        vector<bool> recStack(V, false);

        // Gọi hàm DFS bắt đầu từ tất cả các đỉnh
        // để đảm bảo xét cả trường hợp đồ thị không liên thông
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                if (isCyclicUtil(i, visited, recStack))
                {
                    return true; // Nếu phát hiện chu trình, trả về true
                }
            }
        }

        return false; // Không có chu trình
    }
};

// Hàm main để kiểm tra
int main()
{
    DirectedGraph g(8);
    int edege[][2] = {{0, 6}, {1, 2}, {1, 4}, {1, 6}, {3, 0}, {3, 4}, {5, 1}, {7, 0}, {7, 1}};

    for (int i = 0; i < 9; i++)
        g.addEdge(edege[i][0], edege[i][1]);

    if (g.isCyclic())
        cout << "Graph contains cycle";
    else
        cout << "Graph doesn't contain cycle";

    return 0;
}

/*
Nguyên lý hoạt động:

Thuật toán DFS được sử dụng để duyệt đồ thị theo chiều sâu
Bắt đầu từ một đỉnh, ta đánh dấu nó là đã thăm và tiếp tục thăm các đỉnh kề chưa được thăm:

- Sử dụng thuật toán DFS (Depth-First Search) với hai mảng đánh dấu
    visited[]: đánh dấu các đỉnh đã được thăm
    recStack[]: đánh dấu các đỉnh đang nằm trong đường đi DFS hiện tại

- Phát hiện chu trình:
Một chu trình được phát hiện khi ta thăm một đỉnh đã nằm trong đường đi hiện tại
Khi đỉnh v được thăm, ta đánh dấu visited[v] = true và recStack[v] = true
Khi quay lui từ đỉnh v, ta đặt recStack[v] = false (đỉnh không còn trong đường đi hiện tại)
Nếu trong quá trình duyệt gặp đỉnh w với recStack[w] = true, nghĩa là có chu trình

- Xử lý đồ thị không liên thông:
Bắt đầu DFS từ mỗi đỉnh chưa được thăm
Đảm bảo kiểm tra toàn bộ đồ thị kể cả khi không liên thông
*/