/*Implement three following hashing function:

long int midSquare(long int seed);
long int moduloDivision(long int seed, long int mod);
long int digitExtraction(long int seed, int* extractDigits, int size);

Note that:

In midSquare function: we eliminate 2 last digits and get the 4 next digits.

In digitExtraction: extractDigits is a sorted array from smallest to largest index of digit in seed (index starts from 0). The array has size size.

 */

long int midSquare(long int seed)
{
    seed = seed * seed;  // Bình phương giá trị seed
    seed /= 100;         // Bỏ đi 2 chữ số cuối cùng bằng phép chia nguyên cho 100
    return seed % 10000; // Lấy 4 chữ số tiếp theo bằng phép chia lấy dư với 10000
}

long int moduloDivision(long int seed, long int mod)
{
    return seed % mod; // Lấy phần dư của seed khi chia cho mod (phép băm bằng phép chia)
}

long int digitExtraction(long int seed, int *extractDigits, int size)
{
    int tmp[1000]; // Mảng tạm thời để lưu các chữ số của seed
    for (int i = 0; i < 1000; i++)
        tmp[i] = -1; // Khởi tạo tất cả phần tử trong tmp với giá trị -1

    int i = 0;
    while (seed > 0)
    {
        tmp[i] = seed % 10; // Lấy chữ số cuối cùng của seed và lưu vào mảng tmp
        seed /= 10;         // Loại bỏ chữ số cuối cùng của seed
        i++;                // Tăng chỉ số mảng tmp
    }

    long int result = 0; // Kết quả số sau khi trích xuất các chữ số
    long int n = 1;      // Biến này không cần thiết ở đây, có thể bỏ

    int j = 0; // Chỉ mục của extractDigits
    while (size)
    {
        // Lấy chữ số tại vị trí được chỉ định bởi extractDigits[j]
        // Vì mảng tmp lưu chữ số theo thứ tự đảo ngược, ta cần truy cập tmp[i - extractDigits[j] - 1]
        result = result * 10 + tmp[i - extractDigits[j] - 1];
        j += 1;  // Tăng chỉ mục extractDigits
        n *= 10; // (Không cần thiết ở đây)
        size--;  // Giảm số lượng chữ số cần trích xuất
    }

    return result; // Trả về số được trích xuất
}
