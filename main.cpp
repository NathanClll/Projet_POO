#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <ctime>
#include <cstdlib>
#include <iostream>

const int cellSize = 10;
const int gridWidth = 80;
const int gridHeight = 80;

std::vector<std::vector<int>> grid(gridWidth, std::vector<int>(gridHeight));

void initializeGrid() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grid[x][y] = std::rand() % 2;  // Randomly initialize cells as alive or dead
        }
    }
}

void renderGrid(sf::RenderWindow &window) {
    window.clear();
    sf::RectangleShape cell(sf::Vector2f(
        static_cast<float>(cellSize) - 1.0f,
        static_cast<float>(cellSize) - 1.0f
    ));

    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            if (grid[x][y] == 1) {
                cell.setPosition(sf::Vector2f(
                    static_cast<float>(x * cellSize),
                    static_cast<float>(y * cellSize)
                ));
                window.draw(cell);
            }
        }
    }
    window.display();
}

int main() {
    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(
            static_cast<unsigned int>(gridWidth * cellSize),
            static_cast<unsigned int>(gridHeight * cellSize)
        )),
        "Game of Life"
    );

    initializeGrid();

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        renderGrid(window);

        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}