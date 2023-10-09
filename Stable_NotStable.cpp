#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

vector<vector<int>> generate_array(int n, int m) {
    vector<vector<int>> array(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            array[i][j] = rand() % 15;
        }
    }
    return array;
}

void print_array(const vector<vector<int>>& array) {
    int n = array.size();
    int m = array[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

void bubble_sort(vector<vector<int>>& array, int column) {
    for (int i = 0; i < array.size() - 1; ++i) {
        for (int j = 0; j < array.size() - i - 1; ++j) {
            if (array[j][column] > array[j + 1][column] ||
                (array[j][column] == array[j + 1][column] && array[j] > array[j + 1])) {
                swap(array[j], array[j + 1]);
            }
        }
    }
}

void insertion_sort(vector<vector<int>>& array, int column) {
    int n = array.size();
    for (int i = 1; i < n; ++i) {
        vector<int> key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j][column] > key[column]) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

void selection_sort(vector<vector<int>>& array, int column) {
    int n = array.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < n; ++j) {
            if (array[j][column] < array[min_index][column]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(array[i], array[min_index]);
        }
    }
}

void merge(vector<vector<int>>& array, int column, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    vector<vector<int>> left_array(n1, vector<int>(array[0].size()));
    vector<vector<int>> right_array(n2, vector<int>(array[0].size()));

    for (int i = 0; i < n1; i++) {
        left_array[i] = array[left + i];
    }
    for (int i = 0; i < n2; i++) {
        right_array[i] = array[middle + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (left_array[i][column] <= right_array[j][column]) {
            array[k] = left_array[i];
            i++;
        }
        else {
            array[k] = right_array[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = left_array[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = right_array[j];
        j++;
        k++;
    }
}

void merge_sort(vector<vector<int>>& array, int column, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        merge_sort(array, column, left, middle);
        merge_sort(array, column, middle + 1, right);

        merge(array, column, left, middle, right);
    }
}

void quick_sort(vector<vector<int>>& array, int column, int left, int right) {
    if (left < right) {
        int pivot_index = left + rand() % (right - left + 1);
        vector<int> pivot = array[pivot_index];
        int i = left;
        int j = right;

        while (i <= j) {
            while (array[i][column] < pivot[column]) {
                i++;
            }
            while (array[j][column] > pivot[column]) {
                j--;
            }
            if (i <= j) {
                swap(array[i], array[j]);
                i++;
                j--;
            }
        }

        if (left < j) {
            quick_sort(array, column, left, j);
        }
        if (i < right) {
            quick_sort(array, column, i, right);
        }
    }
}

int main() {
    int n, m;
    cout << "Enter the number of rows: ";
    cin >> n;
    cout << "Enter the number of columns: ";
    cin >> m;

    vector<vector<int>> array = generate_array(n, m);
    vector<vector<int>> array_copy = array;  // Копія масиву для сортування

    bool stable;

    cout << "Original array:" << endl;
    print_array(array);

    cout << "Sorting by the first column using bubble sort:" << endl;
    bubble_sort(array_copy, 0);
    print_array(array_copy);

   
    stable = true;
    for (int i = 1; i < n; ++i) {
        if (array_copy[i][0] == array_copy[i - 1][0] && array_copy[i][1] < array_copy[i - 1][1]) {
            stable = false;
            break;
        }
    }

    if (stable) {
        cout << "Sorting by the first column using bubble sort is stable." << endl;
    }
    else {
        cout << "Sorting by the first column using bubble sort is not stable." << endl;
    }

    
    array_copy = array; // Повернення масиву до початкового стану
    cout << "Sorting by the second column using bubble sort:" << endl;
    bubble_sort(array_copy, 1);
    print_array(array_copy);

    // Перевірка стабільності сортування за другим стовпцем
    stable = true;
    for (int i = 1; i < n; ++i) {
        if (array_copy[i][1] == array_copy[i - 1][1] && array_copy[i][0] < array_copy[i - 1][0]) {
            stable = false;
            break;
        }
    }

    if (stable) {
        cout << "Sorting by the second column using bubble sort is stable." << endl;
    }
    else {
        cout << "Sorting by the second column using bubble sort is not stable." << endl;
    }

    array_copy = array; // Повернення масиву до початкового стану
    cout << "Sorting by the first column using insertion sort:" << endl;
    insertion_sort(array_copy, 0);
    print_array(array_copy);

    // Перевірка стабільності сортування за першим стовпцем
    stable = true;
    for (int i = 1; i < n; ++i) {
        if (array_copy[i][0] == array_copy[i - 1][0] && array_copy[i][1] < array_copy[i - 1][1]) {
            stable = false;
            break;
        }
    }

    if (stable) {
        cout << "Sorting by the first column using insertion sort is stable." << endl;
    }
    else {
        cout << "Sorting by the first column using insertion sort is not stable." << endl;
    }

    // Сортування методом сортування вставками за другим стовпцем
    array_copy = array; // Повернення масиву до початкового стану
    cout << "Sorting by the second column using insertion sort:" << endl;
    insertion_sort(array_copy, 1);
    print_array(array_copy);

    // Перевірка стабільності сортування за другим стовпцем
    stable = true;
    for (int i = 1; i < n; ++i) {
        if (array_copy[i][1] == array_copy[i - 1][1] && array_copy[i][0] < array_copy[i - 1][0]) {
            stable = false;
            break;
        }
    }

    if (stable) {
        cout << "Sorting by the second column using insertion sort is stable." << endl;
    }
    else {
        cout << "Sorting by the second column using insertion sort is not stable." << endl;
    }

    // Сортування методом сортування вибором за першим стовпцем
    array_copy = array; // Повернення масиву до початкового стану
    cout << "Sorting by the first column using selection sort:" << endl;
    selection_sort(array_copy, 0);
    print_array(array_copy);

    // Перевірка стабільності сортування за першим стовпцем
    stable = true;
    for (int i = 1; i < n; ++i) {
        if (array_copy[i][0] == array_copy[i - 1][0] && array_copy[i][1] < array_copy[i - 1][1]) {
            stable = false;
            break;
        }
    }

    if (stable) {
        cout << "Sorting by the first column using selection sort is stable." << endl;
    }
    else {
        cout << "Sorting by the first column using selection sort is not stable." << endl;
    }

    // Сортування методом сортування вибором за другим стовпцем
    array_copy = array; // Повернення масиву до початкового стану
    cout << "Sorting by the second column using selection sort:" << endl;
    selection_sort(array_copy, 1);
    print_array(array_copy);

    // Перевірка стабільності сортування за другим стовпцем
    stable = true;
    for (int i = 1; i < n; ++i) {
        if (array_copy[i][1] == array_copy[i - 1][1] && array_copy[i][0] < array_copy[i - 1][0]) {
            stable = false;
            break;
        }
    }

    if (stable) {
        cout << "Sorting by the second column using selection sort is stable." << endl;
    }
    else {
        cout << "Sorting by the second column using selection sort is not stable." << endl;
    }

    // Сортування методом злиття за першим стовпцем
    array_copy = array; // Повернення масиву до початкового стану
    cout << "Sorting by the first column using merge sort:" << endl;
    merge_sort(array_copy, 0, 0, n - 1);
    print_array(array_copy);

    // Перевірка стабільності сортування за першим стовпцем
    stable = true;
    for (int i = 1; i < n; ++i) {
        if (array_copy[i][0] == array_copy[i - 1][0] && array_copy[i][1] < array_copy[i - 1][1]) {
            stable = false;
            break;
        }
    }

    if (stable) {
        cout << "Sorting by the first column using merge sort is stable." << endl;
    }
    else {
        cout << "Sorting by the first column using merge sort is not stable." << endl;
    }

    // Сортування методом злиття за другим стовпцем
    array_copy = array; // Повернення масиву до початкового стану
    cout << "Sorting by the second column using merge sort:" << endl;
    merge_sort(array_copy, 1, 0, n - 1);
    print_array(array_copy);

    // Перевірка стабільності сортування за другим стовпцем
    stable = true;
    for (int i = 1; i < n; ++i) {
        if (array_copy[i][1] == array_copy[i - 1][1] && array_copy[i][0] < array_copy[i - 1][0]) {
            stable = false;
            break;
        }
    }

    if (stable) {
        cout << "Sorting by the second column using merge sort is stable." << endl;
    }
    else {
        cout << "Sorting by the second column using merge sort is not stable." << endl;
    }

    // Сортування методом швидкого сортування за першим стовпцем
    array_copy = array; // Повернення масиву до початкового стану
    cout << "Sorting by the first column using quick sort:" << endl;
    quick_sort(array_copy, 0, 0, n - 1);
    print_array(array_copy);

    // Перевірка стабільності сортування за першим стовпцем
    stable = true;
    for (int i = 1; i < n; ++i) {
        if (array_copy[i][0] == array_copy[i - 1][0] && array_copy[i][1] < array_copy[i - 1][1]) {
            stable = false;
            break;
        }
    }

    if (stable) {
        cout << "Sorting by the first column using quick sort is stable." << endl;
    }
    else {
        cout << "Sorting by the first column using quick sort is not stable." << endl;
    }

    // Сортування методом швидкого сортування за другим стовпцем
    array_copy = array; // Повернення масиву до початкового стану
    cout << "Sorting by the second column using quick sort:" << endl;
    quick_sort(array_copy, 1, 0, n - 1);
    print_array(array_copy);

    // Перевірка стабільності сортування за другим стовпцем
    stable = true;
    for (int i = 1; i < n; ++i) {
        if (array_copy[i][1] == array_copy[i - 1][1] && array_copy[i][0] < array_copy[i - 1][0]) {
            stable = false;
            break;
        }
    }

    if (stable) {
        cout << "Sorting by the second column using quick sort is stable." << endl;
    }
    else {
        cout << "Sorting by the second column using quick sort is not stable." << endl;
    }

    return 0;
}
