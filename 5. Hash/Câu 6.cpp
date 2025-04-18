#include <iostream>
#include <vector>
#include <map>

using namespace std;

int pairMatching(vector<int> &nums, int target)
{
    map<int, int> m;

    // Đếm số lần xuất hiện của từng số
    for (int i : nums)
        m[i]++;

    int count = 0;

    for (auto it = m.begin(); it != m.end(); ++it)
    {
        int num = it->first;
        int freq = it->second;

        // Trường hợp num + num == target
        if (num * 2 == target)
        {
            count += freq / 2;
            m[num] = 0; // Đánh dấu là đã sử dụng hết số này
        }
        // Trường hợp tìm thấy cặp (num, target - num)
        else if (m.find(target - num) != m.end() && m[target - num] > 0)
        {
            int pair_count = min(freq, m[target - num]);
            count += pair_count;
            m[num] = 0;
            m[target - num] = 0; // Đánh dấu cả hai số là đã sử dụng
        }
    }
    return count;
}

int main()
{
    vector<int> nums = {1, 5, 7, -1, 5, 10, 3, 2, 2, -1, 7};
    int target = 6;

    cout << "Số cặp thỏa mãn: " << pairMatching(nums, target) << endl;

    return 0;
}
