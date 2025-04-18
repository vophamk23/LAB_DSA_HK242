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
    /*    // Phương thức THÊM/CẬP NHẬT một phần tử mới vào bảng băm
        void put(int key, int value)
        {
            // Tính chỉ số băm cho khóa
            int index = hashFunction(key, capacity);

            // Duyệt từng nút trong danh sách liên kết tại chỉ số đã tính
            Entry *current = table[index];
            while (current != 0)
            {
                // Nếu tìm thấy khóa, cập nhật giá trị và kết thúc
                if (current->key == key)
                {
                    current->value = value;
                    return;
                }
                current = current->next;
            }

            // Nếu không tìm thấy khóa, thêm một mục mới vào đầu danh sách liên kết
            Entry *newEntry = new Entry(key, value);
            newEntry->next = table[index];
            table[index] = newEntry;

            // Tăng số lượng phần tử
            count++;

            // Kiểm tra xem bảng có cần mở rộng không
            if (count > capacity)
            {
                rehash(2 * capacity);
            }
        }
            */

    // Hàm lấy giá trị từ khóa
    // V& get (int key); có thê ghi vậy
    void get(int Key)
    {
        // Tính chỉ số băm cho khóa
        int index = hashFunction(key, capacity);

        // Duyệt từng nút trong danh sách liên kết tại chỉ số đã tính
        Entry *current = table[index];
        while (current != 0)
        {
            // Nếu tìm thấy khóa, trả về giá trị tương ứng
            if (current->key == key)
            {
                return current->value;
            }
            current = current->next;
        }

        // Nếu không tìm thấy khóa, ném ngoại lệ
        throw std::out_of_range("Key not found in XHashMap");
    }
};