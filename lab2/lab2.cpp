 
#include<iostream>

#include<string>
using namespace std;

int MinRunGet(int n)
{
    int r = 0;
    while (n >= 64)
    {
        r |= (n & 1);
        n >>= 1;
    }
    return n + r;
}


template <typename T>
class DynamicArray {
private:
    T* arr;
    int size;
    int capacity;

    bool AllowedIndex(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Index is not available!" << std::endl;
            return false;
        }

        return true;
    }


public:
    DynamicArray() {
        capacity = 10;
        size = 0;
        arr = new T[capacity];
    }

    DynamicArray(int size) {
        capacity = size * 2;
        size = size;
        arr = new T[capacity];
    }

    DynamicArray(std::initializer_list<T> list) {
        size_t i = 0;
        size = list.size();
        capacity = size * 2;
        arr = new T[capacity];
        for (const T& elem : list) {
            arr[i++] = elem;
        }
    }

    T& operator[](int index) {

        if (AllowedIndex(index))
            return arr[index];

        throw std::out_of_range("Error");

    }




    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }


    ~DynamicArray() {
        delete[] arr;
    }


    int getSize() {
        return size;
    }

    void insertAt(int index, T value) {
        if (AllowedIndex(index)) return;

        if (size == capacity) {
            resize();
        }

        for (int i = size; i > index; i--) {
            arr[i] = arr[i - 1];
        }

        arr[index] = value;
        size++;
    }

    void remove(T value) {
        int index = -1;

        for (int i = 0; i < size; i++) {
            if (arr[i] == value) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            removeAt(index);
        }
        else {
            std::cout << "Element is not found!" << std::endl;
        }
    }

    void removeAt(int index) {
        if (AllowedIndex(index)) return;

        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }

        size--;
    }

    void append(T value) {
        if (size == capacity) {
            resize();
        }

        arr[size] = value;
        size++;
    }

    T get(int index) {

        if (AllowedIndex(index)) return;
        return arr[index];
    }

    int getCapacity() {
        return capacity;
    }

private:
    void resize() {
        capacity *= 2;
        T* newArr = new T[capacity];

        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }

        delete[] arr;
        arr = newArr;
    }
};

class Exception : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
};




void Sort_ins(DynamicArray<int>& mass, int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        int max = mass[i];
        int g = i - 1;
        while (g >= left && max < mass[g])
        {
            mass[g + 1] = mass[g];
            mass[g] = max;
            g = g - 1;
        }
    }
}



void merge(DynamicArray<int>& mass, int l, int m, int r)
{
    int* Left = new int[m - l + 1];
    int* Right = new int[r - m];
    for (int i = 0; i < m - l + 1; i++)
        Left[i] = mass[l + i];
    for (int i = 0; i < r - m; i++)
        Right[i] = mass[m + 1 + i];
    int i = 0, j = 0, k = l, testL = 0, testR = 0;
    while (i < m - l + 1 && j < r - m)
    {
        if (Left[i] <= Right[j]) {
            mass[k] = Left[i];
            i++;
            testL++;
            testR = 0;
        }
        else {
            mass[k] = Right[j];
            j++;
            testR++;
            testL = 0;
        }
        k++;
    }

    if (testL >= 7)  //галоп начинается тут, после того как из массива Left были взяты 7 раз элементы
    {
        int gallopStep = 1;
        bool col_mass_bro = 1;
        for (int g = i; g < m - l + 1;)
        {
            if (Left[g] <= Right[j])
            {
                g += gallopStep;
                gallopStep *= 2;
            }
            else
            {
                col_mass_bro = 0;
                testL = 0;
                testR = 0;
            }
        }
        if (col_mass_bro)
        {
            for (int g = 0; g < m - l + 1; g++)
            {
                mass[k] = Left[g];
                k++;
                i++;
                testL = 0;
                testR = 0;
            }
        }
    }
    else if (testR >= 7) //галоп начинается тут, после того как из массива Right были взяты 7 раз элементы
    {
        int gallopStep = 1;
        bool col_mass_bro = 1;
        for (int g = i; g < r - m;)
        {
            if (Right[g] <= Left[i])
            {
                g += gallopStep;
                gallopStep *= 2;
            }
            else
            {
                col_mass_bro = 0;
                testL = 0;
                testR = 0;
            }
        }
        if (col_mass_bro)
        {
            for (int g = 0; g < r - m; g++)
            {
                mass[k] = Left[g];
                k++;
                j++;
                testL = 0;
                testR = 0;
            }
        }
    }



    while (i < m - l + 1)
    {
        mass[k] = Left[i];
        i++;
        k++;
    }

    while (j < r - m)
    {
        mass[k] = Right[j];
        j++;
        k++;
    }
}

int min(int x, int y)
{
    if (x > y)
        return y;
    else
        return x;
}

void swap(int& a, int& b)
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

void Timsort(DynamicArray<int>& mass, int n)
{
    int MinRun = MinRunGet(n);
    for (int i = 0; i < n; i += MinRun)
    {
        int min_num = min(i + MinRun - 1, n - 1);
        int min_num2 = min_num;
        for (int g = i; g < min_num2; g++)
        {
            if (mass[g] > mass[g + 1])
            {
                min_num--;
            }

        }
        if (min_num != 0)
            Sort_ins(mass, i, min_num2); // min тут для того, чтобы за границы массива не вылетить
        else
        {
            min_num = min(i + MinRun, n);
            for (int g = i; g < min_num / 2; g++)
            {
                swap(mass[g], mass[min_num2]);
                min_num2--;
            }
        }
    }
    for (int size = MinRun; size < n; size = 2 * size)
    {
        for (int left = 0; left < n - size; left += 2 * size)
        {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (n - 1));
            merge(mass, left, mid, right);
        }
    }
}

int interface_for_tim()
{
    cout << "Что делаем? (для выбора ввидите число)";
    cout << "\n1.Создать автоматически массив из рамндомных значений заданного размера";
    cout << "\n2.Ввести собственные значения (через пробел)";
    cout << "\nНомер варианта: ";
    int g;
    cin >> g;
    return g;
}

int main()
{

    setlocale(LC_CTYPE, "Russian");
    DynamicArray<int> lol;
    switch (interface_for_tim())
    {
    case 1:
    {
        cout << "Количество элементов массива: ";
        int k;
        cin >> k;
    

        for (int i = 0; i < k; i++)
        {
            lol.append(rand() % 400 + 1); 
        }
        break;
    }
    case 2:
    {
        cout << "Введите выражение: ";
        string expression;
        cin >> expression;
        getline(cin, expression);
     
        break;
    }
    default:
        break;
    }
    cout << "Готовый массив: ";
    Timsort(lol, lol.getSize());
    for (int i = 0; i < lol.getSize(); i++) {
        cout << lol[i] << " ";
    }
    return 0;
}




