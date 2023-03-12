#include <iostream>


/* I decided to implement a stack using a sequence of individually allocated
 * arrays of fixed size, with additional bookkeeping.  */
class stack {
public:
    stack() : blocks_max_(BLOCKS_COUNT), blocks_allocated_(1),
            data_(new int*[BLOCKS_COUNT]), 
            capacity_(BLOCK_CAPACITY), size_(0) {
        data_[0] = new int[BLOCK_CAPACITY];
    }

    ~stack() {
        for (int i = 0; i < blocks_allocated_; ++i)
            delete [] data_[i];

        delete [] data_;
    }

    void push(int value) {
        if (size_ == capacity_) {
            if (capacity_ == blocks_max_ * BLOCK_CAPACITY) {
                blocks_max_ *= 2;
                int ** new_data_ = new int*[blocks_max_];
                for (int i = 0; i < blocks_allocated_; ++i)
                    new_data_[i] = data_[i];
                
                delete [] data_;
                data_ = new_data_;
            }

            data_[blocks_allocated_++] = new int[BLOCK_CAPACITY];
            capacity_ += BLOCK_CAPACITY;
        }

        data_[size_ / BLOCK_CAPACITY][size_ % BLOCK_CAPACITY] = value;
        ++size_;
    }

    void pop() {
        --size_;
    }

    int top() {
        int block = (size_ - 1) / BLOCK_CAPACITY;
        int index = (size_ - 1) % BLOCK_CAPACITY;
        return data_[block][index];
    }

    int size() noexcept {
        return size_;
    }

    void clear() noexcept {
        size_ = 0;
    }

private:
    /* Default stack parameters.  */
    static int const BLOCKS_COUNT   = 2;
    static int const BLOCK_CAPACITY = 4;

    int ** data_;
    /* blocks_max_
     * maximal number of blocks that can be allocated.

     * blocks_allocated_
     * number of allocated blocks.
     * 
     * capacity_
     * number of elements that can be stored in already allocated memory.
     * 
     * size_
     * number of valid elements in stack.  */
    int blocks_max_, blocks_allocated_;
    int capacity_, size_;

    stack(stack const &);
    stack & operator=(stack const &);
};


int main(void) {
    stack s;

    std::string command;
    while(true) {
        std::getline(std::cin, command);
        size_t pos = command.find(' ');

        /* This can only happen when push command has been prompted. */
        if (pos != std::string::npos) {
            int value = stoi(command.substr(pos + 1));
            s.push(value);
            std::cout << "ok\n";
        }

        else if (command == "pop") {
            if (s.size() == 0) {
                std::cout << "error\n";
                continue;
            }

            int value = s.top();
            s.pop();
            std::cout << value << std::endl;
        }

        else if (command == "back") {
            if (s.size() == 0) {
                std::cout << "error\n";
                continue;
            }

            std::cout << s.top() << std::endl;        
        }

        else if (command == "size") {
            std::cout << s.size() << std::endl;
        }

        else if (command == "clear") {
            s.clear();
            std::cout << "ok\n";
        }

        else if (command == "exit") {
            std::cout << "bye\n";
            break;
        }
    }

    return 0;
}
