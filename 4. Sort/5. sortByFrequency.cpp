#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

void sortByFrequency(int arr[], int n)
{
    // Map to store frequency of each element
    unordered_map<int, int> freq;
    // Vector to store original indices to maintain relative order
    vector<pair<int, int>> elements;

    // Count frequencies and store original indices
    for (int i = 0; i < n; ++i)
    {
        freq[arr[i]]++;
        elements.push_back({arr[i], i});
    }

    // Custom comparator for sorting
    stable_sort(elements.begin(), elements.end(),
                [&](const pair<int, int> &a, const pair<int, int> &b)
                {
                    // If frequencies are different, sort by frequency in descending order
                    if (freq[a.first] != freq[b.first])
                        return freq[a.first] > freq[b.first];

                    // If frequencies are same, maintain original order
                    return a.second < b.second;
                });

    // Modify the original array
    for (int i = 0; i < n; ++i)
    {
        arr[i] = elements[i].first;
    }
}

int main()
{
    // Test Case 1
    int arr1[] = {-4, 4, 1, 2, 2, -4, 9, 1, -1};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    sortByFrequency(arr1, n1);

    // Print result
    for (int i = 0; i < n1; ++i)
    {
        cout << arr1[i] << " ";
    }
    cout << endl;

    // Test Case 2
    int arr2[] = {-5, 3, 8, 1, -9, 3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    sortByFrequency(arr2, n2);

    // Print result
    for (int i = 0; i < n2; ++i)
    {
        cout << arr2[i] << " ";
    }
    cout << endl;

    return 0;
}