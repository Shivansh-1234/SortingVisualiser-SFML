#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

void swapBars(sf::RectangleShape& r1, sf::RectangleShape& r2);

size_t i{};

bool bubbleSorting = false;
bool selectionSorting = false;

int main()
{
    srand(static_cast<unsigned>(time(NULL)));

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Sorting Visualiser By Shivyy");
    window.setFramerateLimit(20);

    std::vector<sf::RectangleShape> barVec;

    int count = 0;

    //ADDDING BARS OF RANDOM SIZE ON SCREEN
    for (size_t i{}; i < 300; i++) {
        sf::RectangleShape temp(sf::Vector2f(5, 1 + (rand() % 700)));
        temp.setPosition(0 + count, 720 - temp.getGlobalBounds().height);
        temp.setFillColor(sf::Color::White);

        barVec.push_back(temp);

        count += 5;
    }

    
    while (window.isOpen())
    {
        //INPUT
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            bubbleSorting = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            selectionSorting = true;
        }

        //Selection Sort
        if (i < barVec.size() && selectionSorting && !bubbleSorting) {
            int min_idx = i;
            for (int j = i + 1; j < barVec.size(); j++) {
                if (720 - barVec[j].getPosition().y < 720 - barVec[min_idx].getPosition().y) {
                    min_idx = j;
                }                  
            }
            swapBars(barVec[min_idx], barVec[i]);
            std::swap(barVec[min_idx], barVec[i]);
            i++;
;       }

        //Bubble Sort
        if (i < barVec.size() && bubbleSorting && !selectionSorting) {
            for (size_t j{}; j < barVec.size() - i - 1; j++) {
                if (720 - barVec[j].getPosition().y > 720 - barVec[j + 1].getPosition().y) {
                    swapBars(barVec[j], barVec[j + 1]);
                    std::swap(barVec[j], barVec[j + 1]);
                }
            }
            i++;
        }

        //RENDER
        window.clear();
        
        for (auto& b : barVec) {
            window.draw(b);
        }

        window.display();
    }

    return EXIT_SUCCESS;
}

void swapBars(sf::RectangleShape& r1, sf::RectangleShape& r2)
{
    float temp = r1.getPosition().x;
    r1.setPosition(sf::Vector2f(r2.getPosition().x, r1.getPosition().y));
    r2.setPosition(sf::Vector2f(temp, r2.getPosition().y));
}
