#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/**
 * Hàm đếm số nhóm bạn bè trong mạng quan hệ
 *
 * @param friends Danh sách kề biểu diễn mối quan hệ bạn bè
 * @return Số nhóm bạn bè (số thành phần liên thông của đồ thị)
 */
int numberOfFriendGroups(vector<vector<int>> &friends)
{
    int n = friends.size();         // Số người trong mạng
    vector<bool> visited(n, false); // Mảng đánh dấu người đã được thăm
    int count = 0;                  // Biến đếm số nhóm bạn bè

    // Dùng BFS để duyệt từng thành phần liên thông
    for (int i = 0; i < n; i++)
    {
        // Nếu người này chưa được thăm, tức là thuộc nhóm bạn bè mới
        if (!visited[i])
        {
            count++; // Tăng số nhóm bạn bè

            // Sử dụng BFS để tìm tất cả các bạn trong cùng nhóm
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while (!q.empty())
            {
                int person = q.front();
                q.pop();

                // Duyệt qua danh sách bạn bè của person
                for (int friend_id : friends[person])
                {
                    // Nếu người bạn chưa được thăm, thêm vào hàng đợi
                    if (!visited[friend_id])
                    {
                        visited[friend_id] = true;
                        q.push(friend_id);
                    }
                }
            }
        }
    }

    return count; // Trả về tổng số nhóm bạn bè
}

/**
 * Hàm main để kiểm tra kết quả
 */
int main()
{
    // Tạo đồ thị theo ví dụ
    vector<vector<int>> graph{
        {1},    // 0 có bạn là 1
        {0, 2}, // 1 có bạn là 0 và 2
        {1},    // 2 có bạn là 1
        {4},    // 3 có bạn là 4
        {3},    // 4 có bạn là 3
        {}      // 5 không có bạn
    };

    // In kết quả
    cout << "Số nhóm bạn bè: " << numberOfFriendGroups(graph) << endl;

    return 0;
}