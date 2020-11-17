#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <ctime>

const int MAX_LINE_SIZE = 10; // Константа по заданию, максимальная длинна строки

int ctoi(char x)
{
    return x - 'a' + 1;
}

int strSum(char* str)
{
    int size = sizeof(str) - 1;
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += ctoi(str[i]) * std::pow(26, size-i-1);
    }
    return sum;
}

int sequentialSearch(char** data, int dataSize, char* keyword)
{
    for (int i = 0; i < dataSize; i++)
    {
        if (strcmp(keyword, data[i]) == 0)
            return i;
    }
    return -1; // Возвращает -1 если значение не найдено
}

int binarySearch(char** data, int dataSize, char* keyword)
{
    int left = 0;
    int right = dataSize - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (strcmp(keyword,data[mid]) == 0) {
            return mid;
        }
        if (strcmp(keyword, data[mid]) < 0)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}

int interpolatingSearch(char** data, int dataSize, char* keyword)
{
    int left = 0;
    int right = dataSize - 1;
    while (left <= right)
    {
        int mid = left + ((strSum(keyword) - strSum(data[left])) *
            (right - left)) / (strSum(data[right]) - strSum(data[left]));
        if (strcmp(keyword, data[mid]) == 0) {
            return mid;
        }
        if (strcmp(keyword, data[mid]) < 0)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}

template<typename T>
void selectionSort(T array[], const size_t size)
{
    for (size_t idx_i = 0; idx_i < size - 1; idx_i++)
    {
        size_t min_idx = idx_i;
        for (size_t idx_j = idx_i + 1; idx_j < size; idx_j++)
        {
            if (strcmp(array[idx_j], array[min_idx]) < 0)
            {
                min_idx = idx_j;
            }
        }
        if (min_idx != idx_i)
        {
            std::swap(array[idx_i], array[min_idx]);
        }
    }
}

void printCharArray(char** data, int dataSize)
{
    for (int i = 0; i < dataSize; i++)
    {
        std::cout << i << ": " << data[i] << std::endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int size;
    std::string filename;
    std::cout << "Расположение файла (вариант 4): ";
    std::cin >> filename;
    std::ifstream in(filename);
    if (in.is_open())
    {
        in >> size;
        char **data = new char* [size];
        for (int i = 0; i < size; i++)
        {
            char* line = new char[MAX_LINE_SIZE];
            in >> line;
            data[i] = line;
        }

        char keyword[MAX_LINE_SIZE];
        std::cout << "Введите ключевое слово для поиска: ";
        std::cin >> keyword;

        int findet_index;

        double start = clock();
        findet_index = sequentialSearch(data, size, keyword);
        printf("%.4lf\n", (clock() - start) / CLOCKS_PER_SEC);

        std::cout << "Индекс найденного элемента последовательным поиском: " << findet_index << std::endl;

        start = clock();
        selectionSort(data, size); // Сортируем массив перед двоичным и интерполирующим поиском
        printf("%.4lf\n", (clock() - start) / CLOCKS_PER_SEC);

        start = clock();
        findet_index = binarySearch(data, size, keyword);
        printf("%.4lf\n", (clock() - start) / CLOCKS_PER_SEC);

        std::cout << "Индекс найденного элемента двоичным поиском: " << findet_index << std::endl;

        start = clock();
        findet_index = interpolatingSearch(data, size, keyword);
        printf("%.4lf\n", (clock() - start) / CLOCKS_PER_SEC);

        std::cout << "Индекс найденного элемента интерполирующим поиском: " << findet_index << std::endl;
    }
    else
    {
        std::cout << "Ошибка чтения файла\n";
    }
    in.close();
    return 0;
}