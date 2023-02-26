#include <iostream>
#include <string>


#define DEFAULT_QUEUE_CAPACITY 256


class queue {
public:
    queue() {
        data = new int[DEFAULT_QUEUE_CAPACITY];
        head = -1, tail = -1, capacity = DEFAULT_QUEUE_CAPACITY;
        reversed = false;
    }

    ~queue() {
        delete [] data;
    }

    bool is_empty() {
        if (head == -1 && tail == -1)
            return true;    
        return false;
    }

    bool is_full() {
        if ((head == 0) && (tail == capacity - 1))
            return true;

        if (tail == head - 1 && reversed == true)
            return true;

        return false;
    }

    size_t size() {
        if (is_full())
            return capacity;

        if (is_empty())
            return 0;

        if (head <= tail)
            return tail - head + 1;

        return capacity - head + tail + 1;
    }

    void clear() {
        head = -1, tail = -1;
    }

    /* Returns true if queue is not empty (and sets copy_to equal to 
     * element of queue). Else returns false (copy_to remains unset).  */
    bool front(int & copy_to) {
        if (is_empty())
            return false;

        copy_to = data[head];
        return true;
    }

    void push(int value) {
        /* If queue is full: reallocate memory of double size.  */
        if (is_full()) {
            uint new_capacity = capacity * 2;
            int * new_data = new int[new_capacity];
            
            if (head < tail) {
                for (uint i = head; i <= tail; ++i)
                    new_data[i - head] = data[i];
                
                tail = tail - head;
                head = 0;
            }

            else if (head > tail) {
                for (uint i = head; i < capacity; ++i)
                    new_data[i - head] = data[i];
                
                for (uint i = 0; i <= tail; ++i)
                    new_data[capacity - head + i] = data[i];

                tail = capacity - head + tail + 1;
                head = 0;
            }

            delete [] data;
            data = new_data;
            capacity = new_capacity;
        }

        /* Add node.  */
        if (is_empty())
            head = 0, tail = 0;

        else if (tail == capacity - 1) {
            tail = 0;
            reversed = true;
        }
            
        else
            ++tail;

        data[tail] = value;
    }

    /* Returns true if element has been popped successfully. Else returns
     * false. Does not return an element being popped (obviously).  */
    bool pop() {
        if (is_empty())
            return false;

        if (head == capacity - 1) {
            head = 0;
            reversed = false;
        }

        else
            ++head;

        if (head > tail && reversed == false)
            head = -1, tail = -1;

        return true;
    }

protected:
    int * data;
    int head, tail, capacity;
    bool reversed;
};


int main(void) {
    queue q;

    std::string command;
    while(true) {
        std::getline(std::cin, command);
        size_t pos = command.find(' ');

        /* This can only happen when push command has been prompted. */
        if (pos != std::string::npos) {
            int value = stoi(command.substr(pos + 1));
            q.push(value);
            std::cout << "ok\n";
        }

        else if (command == "pop") {
            int front_value;
            bool result = q.front(front_value);

            if (result == true) {
                q.pop();
                std::cout << front_value << std::endl;;
            }

            else
                std::cout << "error\n";
        }

        else if (command == "front") {
            int front_value;
            bool result = q.front(front_value);
            if (result == true)
                std::cout << front_value << std::endl;
            else
                std::cout << "error\n";
        }

        else if (command == "size") {
            std::cout << q.size() << std::endl;
        }

        else if (command == "clear") {
            q.clear();
            std::cout << "ok\n";
        }

        else if (command == "exit") {
            std::cout << "bye\n";
            break;
        }
    }

    return 0;
}
