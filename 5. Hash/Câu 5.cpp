/* Implement function

int foldShift(long long key, int addressSize);
int rotation(long long key, int addressSize);
to hashing key using Fold shift or Rotation algorithm.

Review:

The folding method for constructing hash functions begins by dividing the item into equal-size pieces (the last piece may not be of equal size). These pieces are then added together to give the resulting hash value.

The rotation method rotates the last digit to the front, and apply foldShift.*/

using namespace std;
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

long int to_int(string s)
{
    long int base = 1;
    long int res = 0;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        res += (s[i] - '0') * base; // Chuyển đúng ký tự số thành số nguyên
        base *= 10;
    }
    return res;
}

int foldShift(long long key, int addressSize)
{
    string s = "";
    string num = to_string(key);
    long int sum = 0;

    for (int i = 0; i < int(num.size());)
    {
        s = "";
        for (int j = 0; j < addressSize && i + j < int(num.size()); j++)
        {
            s += num[i + j];
        }
        i += addressSize; // Cập nhật chỉ số `i` đúng cách
        sum += to_int(s);
    }

    long int mod = pow(10, addressSize);
    return sum % mod;
}

int rotation(long long key, int addressSize)
{
    string num = to_string(key);
    if (num.size() > 1) // Kiểm tra để tránh lỗi khi số chỉ có một chữ số
    {
        string s1 = num.substr(0, num.size() - 1);
        num = num[num.size() - 1] + s1;
    }

    long int n = to_int(num);
    return foldShift(n, addressSize);
}

int main()
{
    long long key = 123456789;
    int addressSize = 3;

    cout << "Fold Shift: " << foldShift(key, addressSize) << endl;
    cout << "Rotation: " << rotation(key, addressSize) << endl;

    return 0;
}
