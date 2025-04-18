#include <iostream>
using namespace std;

// Định nghĩa cấu trúc của node trong danh sách liên kết
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class LinkedListMergeSort
{
public:
    // Hàm trộn hai danh sách liên kết đã sắp xếp
    // Lưu ý: Phải sử dụng các node trong danh sách gốc và không được thay đổi giá trị val của ListNode
    static ListNode *mergeLists(ListNode *a, ListNode *b)
    {
        if (!a)
            return b; // Nếu danh sách a rỗng, trả về danh sách b
        if (!b)
            return a; // Nếu danh sách b rỗng, trả về danh sách a

        // So sánh giá trị của node đầu tiên và nối đệ quy
        if (a->val <= b->val)
        {
            a->next = mergeLists(a->next, b); // Lấy node a và nối với kết quả trộn của phần còn lại
            return a;                         // Trả về node a làm node đầu tiên của danh sách đã trộn
        }
        else
        {
            b->next = mergeLists(a, b->next); // Lấy node b và nối với kết quả trộn của phần còn lại
            return b;                         // Trả về node b làm node đầu tiên của danh sách đã trộn
        }
    }

    // Hàm tìm điểm giữa của danh sách liên kết
    // Sử dụng thuật toán "Tortoise and Hare" (Rùa và Thỏ)
    static ListNode *getMiddle(ListNode *head)
    {
        if (!head || !head->next)
            return head; // Kiểm tra danh sách rỗng hoặc chỉ có 1 node

        ListNode *slow = head;       // Con trỏ "rùa" di chuyển 1 bước mỗi lần
        ListNode *fast = head->next; // Con trỏ "thỏ" di chuyển 2 bước mỗi lần

        // Di chuyển fast gấp đôi tốc độ của slow
        while (fast && fast->next)
        {
            slow = slow->next;       // Rùa đi 1 bước
            fast = fast->next->next; // Thỏ đi 2 bước
        }

        return slow; // Khi thỏ đến cuối, rùa sẽ ở giữa danh sách
    }

    // Hàm Merge Sort cho danh sách liên kết
    static ListNode *mergeSortList(ListNode *head)
    {
        // Điều kiện dừng: danh sách rỗng hoặc chỉ có 1 node
        if (!head || !head->next)
            return head;

        // Bước 1: Tìm điểm giữa của danh sách
        ListNode *middle = getMiddle(head);
        ListNode *rightHalf = middle->next; // Phần bên phải bắt đầu từ node sau middle

        // Cắt danh sách làm đôi bằng cách đặt next của middle thành nullptr
        middle->next = nullptr;

        // Bước 2: Đệ quy sắp xếp hai nửa
        ListNode *leftSorted = mergeSortList(head);       // Sắp xếp nửa trái
        ListNode *rightSorted = mergeSortList(rightHalf); // Sắp xếp nửa phải

        // Bước 3: Trộn hai nửa đã sắp xếp
        return mergeLists(leftSorted, rightSorted);
    }

    // Hàm tiện ích để in danh sách liên kết
    static void printList(ListNode *head)
    {
        while (head)
        {
            cout << head->val;
            if (head->next)
                cout << " -> ";
            head = head->next;
        }
        cout << endl;
    }

    // Hàm tiện ích để tạo danh sách liên kết từ mảng
    static ListNode *createList(int arr[], int n)
    {
        if (n == 0)
            return nullptr;

        ListNode *head = new ListNode(arr[0]);
        ListNode *current = head;

        for (int i = 1; i < n; i++)
        {
            current->next = new ListNode(arr[i]);
            current = current->next;
        }

        return head;
    }

    // Hàm tiện ích để giải phóng bộ nhớ
    static void freeList(ListNode *head)
    {
        ListNode *temp;
        while (head)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main()
{
    // Ví dụ 1: Danh sách có thứ tự ngẫu nhiên
    int arr1[] = {4, 2, 1, 3, 5};
    ListNode *list1 = LinkedListMergeSort::createList(arr1, 5);

    cout << "Danh sách 1 trước khi sắp xếp: ";
    LinkedListMergeSort::printList(list1);

    list1 = LinkedListMergeSort::mergeSortList(list1);

    cout << "Danh sách 1 sau khi sắp xếp: ";
    LinkedListMergeSort::printList(list1);

    // Giải phóng bộ nhớ
    LinkedListMergeSort::freeList(list1);

    // Ví dụ 2: Danh sách đã sắp xếp ngược
    int arr2[] = {5, 4, 3, 2, 1};
    ListNode *list2 = LinkedListMergeSort::createList(arr2, 5);

    cout << "\nDanh sách 2 trước khi sắp xếp: ";
    LinkedListMergeSort::printList(list2);

    list2 = LinkedListMergeSort::mergeSortList(list2);

    cout << "Danh sách 2 sau khi sắp xếp: ";
    LinkedListMergeSort::printList(list2);

    // Giải phóng bộ nhớ
    LinkedListMergeSort::freeList(list2);

    return 0;
}