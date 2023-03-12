#include <iostream>
#include <queue>


int main(void) {
    std::queue<int> cards_1, cards_2;

    int card;
    for (int i = 0; i < 5; ++i) {
        std::cin >> card;
        cards_1.push(card);
    }

    for (int i = 0; i < 5; ++i) {
        std::cin >> card;
        cards_2.push(card);
    }

    uint count = 0;
    uint8_t card_1, card_2;
    while(count != 1000000) {
        if (cards_1.empty() == true) {
            std::cout << "second " << count << std::endl;
            return 0;
        }

        if (cards_2.empty() == true) {
            std::cout << "first " << count << std::endl;
            return 0;
        }

        card_1 = cards_1.front();
        card_2 = cards_2.front();
        cards_1.pop();
        cards_2.pop();

        if (card_1 == 0 && card_2 == 9) {
            cards_1.push(card_1);
            cards_1.push(card_2);
        }

        else if (card_1 == 9 && card_2 == 0) {
            cards_2.push(card_1);
            cards_2.push(card_2);
        }

        else if (card_1 > card_2) {
            cards_1.push(card_1);
            cards_1.push(card_2);
        }

        else {
            cards_2.push(card_1);
            cards_2.push(card_2);
        }

        ++count;
    }

    std::cout << "botva\n";
    
    return 0;
}
