#include "list.h"

using namespace g3;
int main()
{
    list<int> myList;

    // Push some elements to the list
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);

    // Print elements using an iterator
    std::cout << "List elements: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Use other list functionalities
    myList.pop_front();
    std::cout << "After pop_front, first element: " << myList.front() << std::endl;

    myList.push_front(5);
    std::cout << "After push_front(5), first element: " << myList.front() << std::endl;

    // Create a list using a range
    int arr[] = {1, 2, 3, 4, 5};
    g3::list<int, std::allocator<int>> rangeList(arr, arr + 5);
    std::cout << "Range list elements: ";
    for (auto it = rangeList.begin(); it != rangeList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Demonstrate other constructors
    g3::list<int, std::allocator<int>> copyList(rangeList);
    std::cout << "Copy list elements: ";
    for (auto it = copyList.begin(); it != copyList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    g3::list<int, std::allocator<int>> initList({7, 8, 9, 10});
    std::cout << "Initializer list elements: ";
    for (auto it = initList.begin(); it != initList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

}