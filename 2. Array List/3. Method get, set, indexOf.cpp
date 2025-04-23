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

    void set(int index, T e);                      // set the index position in the list with the value e
    T get(int index);                              // get the element at the index, if the index is out of range, "throw std::out_of_range("index
    is out of range ");" void set(int index, T e); // set the index position in the list with the value e
    int indexOf(T item);                           // get the first index of item in the list, else return -1
    bool contains(T item);                         // check if the item is in the list
    T removeAt(int index);
    bool removeItem(T item);
};

template <class T>
void ArrayList<T>::clear()
{
    delete[] data;          // Free the old array
    capacity = 5;           // Reset capacity to initial value
    count = 0;              // Reset count to 0
    data = new T[capacity]; // Create a new array with the initial capacity
}
template <class T>
T ArrayList<T>::get(int index)
{
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("index is out of range");
    }
    return data[index];
}

template <class T>
void ArrayList<T>::set(int index, T e)
{
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("index is out of range");
    }
    data[index] = e;
}
template <class T>
int ArrayList<T>::indexOf(T item)
{
    for (int i = 0; i < count; i++)
    {
        if (data[i] == item)
        {
            return i; // Return the index of the first occurrence
        }
    }
    return -1; // Item not found
}
template <class T>
bool ArrayList<T>::contains(T item)
{
    return indexOf(item) != -1; // Check if the item exists in the list
}
template <class T>
bool ArrayList<T>::empty()
{
    return count == 0; // Check if the list is empty
}
