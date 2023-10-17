#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
void swap(int& num1, int& num2)
{
    int temp = num1;
    num1 = num2;
    num2 = temp;
}

void PrintArray(std::vector<int>& array) {
    for (int i = 0; i < array.size(); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void Heapify(vector<int>& array, int parent, int size)
{
    int lchild = 2 * parent + 1; //index
    int rchild = 2 * parent + 2; //index

    int largest = parent; //initialization

    if (lchild < size && array[lchild] > array[largest])
        largest = lchild;
    
    if (rchild < size && array[rchild] > array[largest])
        largest = rchild;

    if (largest != parent)
    {
        swap(array[parent], array[largest]);

        //heapify the subtree
        Heapify(array, largest, size);
    }
}


void HeapSort(vector<int>& array)
{
    int size = array.size();
    //build max heap
    for (int i = size / 2 - 1; i >= 0; i--) //從size / 2 - 1 開始是parent
        Heapify(array, i, size);

    for (int i = size - 1; i >= 0; i--)
    {
        //swap root and the last one
        swap(array[0], array[i]);

        //reheapify the tree
        //size would be gradually smaller
        Heapify(array, 0, i);
    }
}

int Partition(vector<int>& array, int left, int right, int pivot)
{
    int leftptr = left - 1;
    int rightptr = right;

    while (true)
    {
        while (array[++leftptr] < pivot)
        {
            //do nothing
        }

        while (rightptr > 0 && array[--rightptr] > pivot)
        {
            //do nothing
        }

        if (leftptr >= rightptr)
            break;
        else
            swap(array[leftptr], array[rightptr]);

    }
    swap(array[leftptr], array[right]);


    return leftptr;
}

void QuickRecur(vector<int>& array, int left, int right)
{
    if (left >= right)
        return;
    else
    {
        int pivot = array[right];
        int PartitionPoint = Partition(array, left, right, pivot);
        QuickRecur(array, left, PartitionPoint - 1);
        QuickRecur(array, PartitionPoint + 1, right);
    }
}

void QuickSort(vector<int>& array)
{
    int leftptr = 0;
    int rightptr = array.size() - 1;
    QuickRecur(array, leftptr, rightptr);
}


int main() {
    std::fstream file;
    file.open("input2.txt");

    int times = 0;
    file >> times;

    for (int t = 0; t < times; t++) {
        int size = 0;
        file >> size;

        std::vector<int> array1;
        std::vector<int> array2;

        for (int i = 0; i < size; i++) {
            int x;
            file >> x;
            array1.push_back(x);
            array2.push_back(x);
        }

        HeapSort(array1);
        cout << "Max Heap Sort : ";
        PrintArray(array1);

        QuickSort(array2);
        cout << "Quick Sort : ";
        PrintArray(array2);
    }
    system("pause");
    return 0;
}