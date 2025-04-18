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
    void ensureCapacity(int index);
};
template <class T>
void ArrayList<T>::ensureCapacity(int cap)
{
    if (cap > capacity)
    {
        int newCapacity = static_cast<int>(capacity * 1.5);
        if (newCapacity < cap)
        {
            newCapacity = cap;
        }
        T *newData = new T[newCapacity];
        for (int i = 0; i < count; i++)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
}
template <class T>
void ArrayList<T>::add(T e)
{
    ensureCapacity(count + 1);
    data[count++] = e;
}
template <class T>
void ArrayList<T>::add(int index, T e)
{
    if (index < 0 || index > count)
    {
        throw std::out_of_range("the input index is out of range!");
    }
    ensureCapacity(count + 1);
    for (int i = count; i > index; i--)
    {
        data[i] = data[i - 1];
    }
    data[index] = e;
    count++;
}
template <class T>
int ArrayList<T>::size()
{
    return count;
}