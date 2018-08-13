#include <iostream>
#include <string>
#include <vector>
#include <queue>


void merge(std::vector<int> &array, int low, int middle, int high)
{
    int i; // counter
    std::queue<int> buffer1;
    std::queue<int> buffer2;

    for (i = low; i <= middle; i++)
    {
        buffer1.push(array[i]);
    }
    for (i = middle + 1; i <= high; i++)
    {
        buffer2.push(array[i]);
    }

    i = low;

    while (!(buffer1.empty() || buffer2.empty()))
    {
        if (buffer1.front() <= buffer2.front())
        {
            array[i++] = buffer1.front();
            buffer1.pop();
        }
        else
        {
            array[i++] = buffer2.front();
            buffer2.pop();

        }
    }

    while (!buffer1.empty())
    {
        array[i++] = buffer1.front();
        buffer1.pop();
    }

    while (!buffer2.empty())
    {
        array[i++] = buffer2.front();
        buffer2.pop();
    }

};

void mergeSort(std::vector<int> &array, int low, int high)
{
    int middle;

    if (low < high)
    {
        middle = (low + high) / 2;
        mergeSort(array, low, middle);
        mergeSort(array, middle + 1, high);
        merge(array, low, middle, high);
    }
};

void printArray(std::vector<int> array)
{
    for (unsigned int i = 0; i < array.size(); i++)
    {
        std::cout << array[i];
        if (i < array.size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "\n";
};
    


int main(int argc, char* argv[])
{
    std::vector<int> intVec = {14, 23, 8, 1, 3, 13, 8, 99, 63, 52};
    //std::vector<int> intVec = {14, 23, 8, 1};
    std::cout << "The original array: " << "\n";
    printArray(intVec);
    int end = intVec.size() - 1;
    //std::cout << "end = " << end << "\n";
    mergeSort(intVec, 0, end);
    std::cout << "The sorted array: " << "\n";
    printArray(intVec);
    

    return 0;
}
