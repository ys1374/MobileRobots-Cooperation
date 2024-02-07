#include <SFML/Graphics.hpp>
#include <iostream>



int main() {
    const int gridSize = 50; // Grid size (4x4 in this case)
    const int squareSize = 20; // Size of each square in pixels
    const int borderSize = 1; // Size of the border in pixels

    // Calculate window size considering the borders
    int windowSize = gridSize * (squareSize + borderSize) + borderSize;

    sf::RenderWindow window(sf::VideoMode(windowSize, .6 * windowSize), "Msc Thesis");

    // Array to store the colors of each square
    sf::Color gridColors[gridSize][gridSize];

    // Initialize all squares with white color
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            gridColors[i][j] = sf::Color::White;
        }
    }

    // Change color of specific squares
    int iii[2]{ 1,2 };
    int jjj[2]{ 1,3 };
    gridColors[iii[0]][jjj[0]] = sf::Color::Red;
    gridColors[iii[1]][jjj[1]] = sf::Color::Blue;

    sf::Clock clock; // starts the clock
    double speedFactor = 20.0;

    while (window.isOpen()) {
        sf::Event event;
        //std::cout << window.pollEvent(event);/////////////////////////////////////////////////////////////

        while (window.pollEvent(event)) {

            //std::cout << window.pollEvent(event);/////////////////////////////////////////////////////////////

            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Check if one minute has passed
        sf::Time elapsed = clock.getElapsedTime();
        std::cout << speedFactor * elapsed.asSeconds() << "\n;"; /////////////////////////////////////////////////////;
        //double time = elapsed.asSeconds();

        if (speedFactor * elapsed.asSeconds() >= 10) {
            //std::cout << "o1\n"/////////////////////////////////////////////////////;
            // Reset the clock
            clock.restart();

            // Move squares to new positions
            //sf::Color tempColumn[gridSize];
            //for (int i = 0; i < gridSize; i++) {
            //    tempColumn[i] = gridColors[i][gridSize - 1];
            //}
            //for (int j = gridSize - 1; j > 0; j--) {
            //    for (int i = 0; i < gridSize; i++) {
            //        gridColors[i][j] = gridColors[i][j - 1];
            //    }
            //}
            //for (int i = 0; i < gridSize; i++) {
            //    gridColors[i][0] = tempColumn[i];
            //}
            gridColors[iii[0]][jjj[0]] = sf::Color::White;
            gridColors[iii[1]][jjj[1]] = sf::Color::White;

            iii[0] = iii[0] + 1; iii[1] = iii[1] + 1;

            gridColors[iii[0]][jjj[0]] = sf::Color::Red;
            gridColors[iii[1]][jjj[1]] = sf::Color::Blue;





        }

        window.clear(sf::Color::Black); // Set background to black which will serve as the border color

        // Draw the grid
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
                square.setPosition(i * (squareSize + borderSize) + borderSize, j * (squareSize + borderSize) + borderSize);
                square.setFillColor(gridColors[i][j]);
                window.draw(square);
            }
        }
        //std::cout << "oz\n";//////////////////////////////////////////////////////////////////////////
        window.display();
    }

    return 0;
}
