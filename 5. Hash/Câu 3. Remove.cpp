// Description: Implement the remove method for the XHashMap class
int hashFunction(int key, int capacity)
{
    return key % capacity;
}

template <class K, class V>
class XHashMap
{
public:
    class Entry
    {
    public:
        K key;
        V value;
        Entry *next;

        Entry(K key, V value, Entry *next = 0)
        {
            this->key = key;
            this->value = value;
            this->next = next;
        }
    };

private:
    Entry **table; // hash table
    int capacity;  // size for the hash table
    int count;

public:
    // Constructor
    XHashMap()
    {
        this->capacity = 10;
        this->count = 0;
        table = new Entry *[capacity];
        // reset table to 0
        for (int i = 0; i < capacity; i++)
        {
            table[i] = 0;
        }
    }

    ~XHashMap()
    { // Destructor
        // Remove all entries in the current map
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
        // Remove table
        delete[] table;
    }

    // put method
    void put(int key, int value); // Already implemented
    V &get(int key);              // Already implemented

    // Xóa một cặp khóa-giá trị khỏi bảng băm và trả về giá trị đã bị xóa
    V remove(K key)
    {
        // Tính toán chỉ số index trong bảng băm cho khóa
        // Sử dụng hàm băm để ánh xạ khóa vào một vị trí trong bảng
        int index = hashFunction(key, capacity);

        // Bắt đầu từ đầu danh sách liên kết tại vị trí index
        // `current` trỏ tới nút đầu tiên của danh sách
        Entry *current = table[index];

        // `prev` dùng để theo dõi nút trước đó, ban đầu là null
        // Biến này giúp chúng ta điều chỉnh liên kết khi xóa nút
        Entry *prev = nullptr;

        // Duyệt qua toàn bộ danh sách liên kết tại vị trí index
        // Tìm kiếm nút có khóa khớp với khóa cần xóa
        while (current != nullptr)
        {
            // Kiểm tra xem khóa của nút hiện tại có trùng khóa cần xóa không
            if (current->key == key)
            {
                // Nếu tìm thấy, lưu lại giá trị để trả về sau khi xóa
                V value = current->value;

                // Xử lý hai trường hợp xóa khác nhau:

                // Trường hợp 1: Nếu nút cần xóa là nút đầu tiên trong danh sách
                if (prev == nullptr)
                {
                    // Cập nhật đầu danh sách trỏ tới nút tiếp theo
                    table[index] = current->next;
                }
                // Trường hợp 2: Nút cần xóa nằm ở giữa hoặc cuối danh sách
                else
                {
                    // Điều chỉnh con trỏ của nút trước để bỏ qua nút hiện tại
                    // Kết nối trực tiếp tới nút tiếp theo
                    prev->next = current->next;
                }

                // Giảm số lượng phần tử trong bảng băm
                count--;

                // Giải phóng bộ nhớ của nút được xóa
                delete current;

                // Trả về giá trị của nút đã xóa
                return value;
            }

            // Nếu chưa tìm thấy, di chuyển tới nút tiếp theo
            // Cập nhật `prev` thành nút hiện tại
            // Và `current` trỏ tới nút kế tiếp
            prev = current;
            current = current->next;
        }

        // Nếu duyệt hết danh sách mà không tìm thấy khóa
        // Ném ngoại lệ để thông báo khóa không tồn tại
        throw std::out_of_range("Không tìm thấy khóa");
    }
};