#include <iostream>
#include <string>
#include <utility>


#define DEFAULT_HEAP_CAPACITY 256


/* Heap that stores elements in nonascending order from top to bottom (from
 * root to leaves).  */
class heap {
public:
    heap() {
        data = new int[DEFAULT_HEAP_CAPACITY];
        size = 0;
        capacity = DEFAULT_HEAP_CAPACITY;
    }

    ~heap() {
        delete [] data;
    }

    void insert(int value) {
        /* Resize if neccessary.  */
        if (size == capacity) {
            capacity *= 2;
            int * new_data = new int[capacity];
            for (int i = 0; i < size; ++i)
                new_data[i] = data[i];

            delete [] data;
            data = new_data;
        }

        data[size] = value;
        heapify(size++);
    }

    int extract() {
        int value = data[0];
        data[0] = data[--size];

        /* current, left, right and next are indexes.  */
        int current = 0, left, right, next = 0;
        /* While thar is at least one child (left).  */
        while (current * 2 + 1 < size) {
            left    = current * 2 + 1;
            right   = current * 2 + 2;

            if (data[next] < data[left])
                next = left;

            /* There is left child but there could not be the right one.  */
            if (next != size)
                if (data[next] < data[right])
                    next = right;

            if (next == current)
                break;

            std::swap(data[current], data[next]);
            current = next;
        }

        return value;
    }

    void heapify(int index) {
        int parent_index;

        do {
            parent_index = (index - 1) / 2;

            if (data[parent_index] < data[index])
                std::swap(data[parent_index], data[index]);
            else
                break;    

            index = parent_index;
        } while (parent_index != 0);
    }

protected:
    /* Current implementation uses 1d array to store values and resizes it 
     * if this is neccessary by allocating new array of size twice as much
     * as current size is and copying all values from old array to the new
     * one. This is not the optimal implementation - there is a better one
     * that uses 2d arrays and does not require copying values.  */
    int * data;
    int size, capacity;
};


int main(void) {
    int n;
    std::cin >> n;

    /* Getting rid of '\n' before calling std::getline.  */
    char c;
    while (std::cin.get(c) && c != '\n') {}

    heap h;    
    std::string command;
    for (int i = 0; i < n; ++i) {
        std::getline(std::cin, command);

        if (command[0] == '0') {
            h.insert(stoi(command.substr(2)));
        }

        else if (command[0] == '1')
            std::cout << h.extract() << std::endl;
    }

    return 0;
}
