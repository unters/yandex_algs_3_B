#include <iostream>
#include <string>


int convert_timestamp_to_seconds(std::string);

std::string convert_seconds_to_timestamp(int);


int main(void) {
    std::string a, b, c;
    std::getline(std::cin, a);
    std::getline(std::cin, b);
    std::getline(std::cin, c);
    int a_in_seconds = convert_timestamp_to_seconds(a);
    int b_in_seconds = convert_timestamp_to_seconds(b);
    int c_in_seconds = convert_timestamp_to_seconds(c);

    int diffirence_in_seconds;
    if (a_in_seconds <= c_in_seconds)
        diffirence_in_seconds = c_in_seconds - a_in_seconds;
    else
        diffirence_in_seconds = (86400 + c_in_seconds - a_in_seconds);

    double remain = (double)diffirence_in_seconds / 2 - \
        diffirence_in_seconds / 2;
    if (remain >= (double)1 / 2)
        diffirence_in_seconds = diffirence_in_seconds / 2 + 1;
    else
        diffirence_in_seconds /= 2;

    b_in_seconds = (b_in_seconds + diffirence_in_seconds) % 86400;
    std::cout << convert_seconds_to_timestamp(b_in_seconds) << std::endl;
    
    return 0;
}


int convert_timestamp_to_seconds(std::string s) {
    int s_in_seconds = \
        std::stoi(s.substr(0, 2)) * 3600 + \
        std::stoi(s.substr(3, 2)) * 60 + \
        std::stoi(s.substr(6, 2));
    return s_in_seconds;
}


std::string convert_seconds_to_timestamp(int s) { 
    int seconds = s % 60;
    int minutes = (s / 60) % 60;
    int hours   = s / 3600;

    std::string timestamp;
    timestamp.append(std::to_string(hours / 10));
    timestamp.append(std::to_string(hours % 10));
    timestamp.append(":");
    timestamp.append(std::to_string(minutes / 10));
    timestamp.append(std::to_string(minutes % 10));
    timestamp.append(":");
    timestamp.append(std::to_string(seconds / 10));
    timestamp.append(std::to_string(seconds % 10));

    return timestamp;
}