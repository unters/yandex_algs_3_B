/* At first I tried to implement a deque using array of fixed-size arrays,
 * but it didn't work properly - I was catching segfaults when working with
 * "big" input data. I decided to postpone this implementation for a while
 * and come back to it after the marathon. Current implementation uses one
 * dynamic array.  */

#include <iostream>


class deque {
public:
    deque() {
        front_      = DEFAULT_CAPACITY / 2;
        back_       = front_;
        capacity_   = DEFAULT_CAPACITY;
        data_       = new int[capacity_];
    }

    ~deque() {
        delete [] data_;
    }

    int empty() {
        return front_ == back_;
    }

    int size() {
        return back_ - front_;
    }

    void clear() {
        front_  = capacity_ / 3;
        back_   = front_;
    }

    int front() {
        return data_[front_];
    }

    int back() {
        return data_[back_ - 1];
    }

    void push_front(int value) {
        if (front_ == 0)
            resize();
        
        data_[--front_] = value;
    }

    void push_back(int value) {
        if (back_ == capacity_)
            resize();
        
        data_[back_++] = value;
    }

    void pop_front() {
        if (empty() == true)
            return;

        ++front_;
    }

    void pop_back() {
        if (empty() == true)
            return;

        --back_;
    }

private:
    static int const DEFAULT_CAPACITY = 64;

    int * data_;
    size_t front_, back_, capacity_;

    void resize() {
        capacity_ *= 2;
        int * new_data_ = new int[capacity_];

        int index = capacity_ / 3;
        for (int i = front_; i < back_; ++i)
            new_data_[index++] = data_[i];

        int indent = size();
        front_  = capacity_ / 3;
        back_   = front_ + indent;

        delete [] data_;
        data_ = new_data_;
    }
};


int main(void) {
    deque d;

    std::string command;
    while(true) {
        std::getline(std::cin, command);
        size_t pos = command.find(' ');

        /* This can only happen when push command has been prompted. */
        if (pos != std::string::npos) {
            int value = stoi(command.substr(pos + 1));
            if (command[pos - 1] == 't')
                d.push_front(value);
            else if (command[pos - 1] == 'k')
                d.push_back(value);
            std::cout << "ok\n";
        }

        else if (command == "pop_front") {
            if (d.empty() == true) {
                std::cout << "error\n";
                continue;
            }

            int value = d.front();
            d.pop_front();
            std::cout << value << std::endl;
        }

        else if (command == "pop_back") {
            if (d.empty() == true) {
                std::cout << "error\n";
                continue;
            }

            int value = d.back();
            d.pop_back();
            std::cout << value << std::endl;
        }

        else if (command == "front") {
            if (d.empty() == true) {
                std::cout << "error\n";
                continue;
            }

            std::cout << d.front() << std::endl;        
        }

        else if (command == "back") {
            if (d.empty() == true) {
                std::cout << "error\n";
                continue;
            }

            std::cout << d.back() << std::endl;        
        }

        else if (command == "size") {
            std::cout << d.size() << std::endl;
        }

        else if (command == "clear") {
            d.clear();
            std::cout << "ok\n";
        }

        else if (command == "exit") {
            std::cout << "bye\n";
            break;
        }
    }

    return 0;
}