// Hàm băm (hash function) để tính chỉ số trong bảng băm
// Sử dụng phép chia lấy dư để ánh xạ khóa vào một chỉ số trong bảng
int hashFunction(int key, int capacity)
{
    return key % capacity;
}

template <class K, class V>
class XHashMap
{
public:
    // Lớp Entry đại diện cho một nút trong danh sách liên kết
    // Mỗi nút chứa một cặp khóa-giá trị và con trỏ tới nút tiếp theo
    class Entry
    {
    public:
        K key;       // Khóa của mục nhập
        V value;     // Giá trị tương ứng với khóa
        Entry *next; // Con trỏ tới nút tiếp theo trong danh sách liên kết

        // Hàm khởi tạo để tạo một mục nhập mới
        Entry(K key, V value, Entry *next = 0)
        {
            this->key = key;
            this->value = value;
            this->next = next;
        }
    };

private:
    Entry **table; // Bảng băm - mảng các con trỏ tới các danh sách liên kết
    int capacity;  // Dung lượng của bảng băm
    int count;     // Số lượng phần tử hiện tại trong bảng băm

public:
    // Hàm khởi tạo: Tạo bảng băm với dung lượng mặc định là 10
    XHashMap()
    {
        this->capacity = 10;
        this->count = 0;
        table = new Entry *[capacity];

        // Khởi tạo tất cả các con trỏ trong bảng thành null
        for (int i = 0; i < capacity; i++)
        {
            table[i] = 0;
        }
    }

    // Hàm hủy: Giải phóng bộ nhớ cho tất cả các mục nhập và bảng
    ~XHashMap()
    {
        // Xóa từng danh sách liên kết tại mỗi chỉ số
        for (int idx = 0; idx < this->capacity; idx++)
        {
            Entry *entry = this->table[idx];
            while (entry != 0)
            {
                Entry *next = entry->next;
                delete entry;
                entry = next;
            }
        }
        // Xóa mảng bảng băm
        delete[] table;
    }

    // Phương thức thêm/cập nhật một phần tử vào bảng băm
    void put(int key, int value)
    {
        // Tính chỉ số băm cho khóa
        int index = hashFunction(key, capacity);

        // Kiểm tra xem khóa đã tồn tại chưa
        Entry *current = table[index];
        while (current != 0)
        {
            // Nếu khóa đã tồn tại, cập nhật giá trị
            if (current->key == key)
            {
                current->value = value;
                return;
            }
            current = current->next;
        }

        // Nếu khóa chưa tồn tại, tạo một mục nhập mới
        Entry *newEntry = new Entry(key, value, table[index]);
        table[index] = newEntry;

        // Tăng số lượng phần tử và kiểm tra hệ số tải
        count++;
        ensureLoadFactor(count);
    }

    // Kiểm tra và đảm bảo hệ số tải không vượt quá 0.75
    void ensureLoadFactor(int current_size)
    {
        // Tính kích thước tối đa được phép (75% dung lượng)
        int maxAllowedSize = 0.75 * capacity;

        // Nếu kích thước hiện tại vượt quá, thực hiện rehash
        if (current_size >= maxAllowedSize)
        {
            // Tăng dung lượng lên 1.5 lần
            int newCapacity = capacity * 1.5;

            // Gọi phương thức rehash với dung lượng mới
            rehash(newCapacity);
        }
    }
    // Phương thức này thay đổi kích thước bảng băm khi nó trở nên quá đầy.
    void rehash(int newCapacity)
    {
        // Lưu trữ bảng hiện tại và dung lượng
        Entry **oldTable = table;
        int oldCapacity = capacity;

        // Tạo bảng mới với dung lượng mới và cập nhật dung lượng
        capacity = newCapacity;
        table = new Entry *[newCapacity];

        // Khởi tạo bảng mới với các giá trị nullptr
        for (int i = 0; i < newCapacity; i++)
        {
            table[i] = 0;
        }

        // Đặt lại số lượng vì chúng ta sẽ chèn lại tất cả các mục
        count = 0;

        // Với mỗi chỉ mục trong bảng cũ
        for (int i = 0; i < oldCapacity; i++)
        {
            Entry *current = oldTable[i];

            // Duyệt qua danh sách liên kết tại chỉ mục đó
            while (current != 0)
            {
                // Lưu trữ mục tiếp theo trước khi chúng ta sửa đổi mục hiện tại
                Entry *next = current->next;

                // Tính toán lại chỉ mục mới cho mỗi mục sử dụng dung lượng mới
                int newIndex = hashFunction(current->key, newCapacity);

                // Chèn mục vào bảng mới tại chỉ mục được tính toán lại
                current->next = table[newIndex];
                table[newIndex] = current;

                // Di chuyển đến mục tiếp theo trong danh sách cũ
                current = next;

                // Tăng số lượng
                count++;
            }
        }

        // Xóa mảng bảng cũ
        delete[] oldTable;
    }

    // Phương thức in bảng (phục vụ kiểm tra)
    void printTable() const
    {
        cout << "------------Bảng băm được hiển thị như sau------------\n";
        for (int i = 0; i < capacity; i++)
        {
            Entry *entry = table[i];
            cout << "Chỉ số " << i << ": ";
            while (entry != 0)
            {
                cout << "(" << entry->key << ", " << entry->value << ") ";
                entry = entry->next;
            }
            cout << endl;
        }
        cout << "-----------------------------------------------------\n";
    }
};