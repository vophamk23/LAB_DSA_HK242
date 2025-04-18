template <class T>
class ArrayList
{
protected:
    T *data;      // dynamic array to store the list's items
    int capacity; // size of the dynamic array
    int count;    // number of items stored in the array
public:
    ArrayList()
    {
        capacity = 5;
        count = 0;
        data = new T[5];
    }
    ~ArrayList() { delete[] data; }
    void add(T e);
    void add(int index, T e);
    int size();
    bool empty();
    void clear();
    T get(int index);
    void set(int index, T e);
    int indexOf(T item);
    bool contains(T item);
    T removeAt(int index);
    bool removeItem(T item);
    void ensureCapacity(int index);
};
template <class T>
T ArrayList<T>::removeAt(int index)
{
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("index is out of range");
    }

    T removedValue = data[index]; // Store the element to return it later
    // Shift elements to the left
    for (int i = index; i < count - 1; i++)
    {
        data[i] = data[i + 1];
    }
    count--; // Reduce the size of the list
    return removedValue;
}
template <class T>
bool ArrayList<T>::removeItem(T item)
{
    for (int i = 0; i < count; i++)
    {
        if (data[i] == item)
        {                // Found the first occurrence
            removeAt(i); // Reuse removeAt to delete it
            return true;
        }
    }
    return false; // Item not found
}
template <class T>
void ArrayList<T>::clear()
{
    delete[] data;          // Free the old memory
    capacity = 5;           // Reset capacity
    count = 0;              // Reset count
    data = new T[capacity]; // Allocate a new empty array
}