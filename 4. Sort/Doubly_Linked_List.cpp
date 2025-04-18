template <class T>
class DLinkedList
{
public:
    class Node; // Forward declaration
protected:
    Node *head;
    Node *tail;
    int count;

public:
    DLinkedList();
    ~DLinkedList();
    void add(const T &e);
    void add(int index, const T &e);
    int size();

public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;

    public:
        Node()
        {
            this->previous = NULL;
            this->next = NULL;
        }

        Node(const T &data)
        {
            this->data = data;
            this->previous = NULL;
            this->next = NULL;
        }
    };
};

template <class T>
void DLinkedList<T>::add(const T &e)
{
    Node *newNode = new Node(e);
    if (!head)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->previous = tail;
        tail = newNode;
    }
    count++;
}

template <class T>
void DLinkedList<T>::add(int index, const T &e)
{
    if (index < 0 || index > count)
    {
        throw std::out_of_range("Index out of bounds");
    }

    Node *newNode = new Node(e);
    if (index == 0)
    {
        newNode->next = head;
        if (head)
            head->previous = newNode;
        head = newNode;
        if (!tail)
            tail = newNode;
    }
    else if (index == count)
    {
        add(e);
        return;
    }
    else
    {
        Node *current = head;
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->previous = current;
        if (current->next)
            current->next->previous = newNode;
        current->next = newNode;
    }
    count++;
}

template <class T>
int DLinkedList<T>::size()
{
    return count;
}
