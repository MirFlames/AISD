#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

const int MAX_LINE_SIZE = 10; // Константа по заданию, максимальная длинна строки

int sequentialSearch(char** data, int dataSize, char* keyword)
{
    for (int i = 0; i < dataSize; i++)
    {
        //std::cout << "Слово: " << data[i] << " [ " << i << " ] | Сравниваемое: " << keyword << std::endl; // debug
        if (strcmp(keyword, data[i]) == 0)
            return i;
    }
    return -1; // Возвращает -1 если значение не найдено
}

int binarySearch(char** data, int dataSize, char* keyword)
{
    int left = 0; // задаем левую и правую границы поиска
    int right = dataSize - 1;
    while (left <= right) // пока левая граница не "перескочит" правую
    {
        int mid = (left + right) / 2; // ищем середину отрезка
        if (strcmp(keyword,data[mid]) == 0) {  // если ключевое поле равно искомому
            return mid;    // мы нашли требуемый элемент,
        }
        if (strcmp(keyword,data[mid]) < 0)     // если искомое ключевое поле меньше найденной середины
            right = mid - 1;  // смещаем правую границу, продолжим поиск в левой части
        else                  // иначе
            left = mid + 1;   // смещаем левую границу, продолжим поиск в правой части
    }
    return -1; // Возвращает -1 если значение не найдено
}

void sortCharArray(char** data, int dataSize)
{
    char* temp;
    int top, seek;
    for (top = 0; top < dataSize - 1; top++)
    {
        for (seek = top + 1; seek < dataSize; seek++)
        {
            if (strcmp(data[top], data[seek]) > 0)
            {
                std::swap(data[top], data[seek]);
            }
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
    // debug tupa
    std::cout << strcmp((char*)"a", (char*)"b") << std::endl;
    std::cout << strcmp((char*)"b", (char*)"a") << std::endl;
    std::cout << strcmp((char*)"a", (char*)"a") << std::endl;
    /* -------------------------------------------------------- */

    setlocale(LC_ALL, "Russian");
    int size;
    char line[MAX_LINE_SIZE];
 
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
            in >> line;
            data[i] = line;
            //std::cout << "Data: " << data[i] << " | Line: " << line << std::endl; // debug
        }

        std::cout << "Считанный массив строк:\n";
        printCharArray(data, size);

        char keyword[MAX_LINE_SIZE];
        std::cout << "Введите ключевое слово для поиска: ";
        std::cin >> keyword;

        std::cout << "Индекс найденного элемента последовательным поиском: " << sequentialSearch(data, size, keyword) << std::endl;

        sortCharArray(data, size); // Сортируем массив перед двоичным поиском
        std::cout << "Индекс найденного элемента двоичным поиском: " << binarySearch(data, size, keyword) << std::endl;
    }
    else
    {
        std::cout << "Ошибка чтения файла\n";
    }
    in.close();
    return 0;
}