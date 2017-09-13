/**
 * Pong game for CSCI 437.
 *
 * Created by Cullen Rombach (cmrombach@email.wm.edu).
 */

#include <SFML/Graphics.hpp>
#include <ScoreLabel.h>
#include <GC.h>
#include <Paddle.h>
#include <Ball.h>

int main(int argc, char** argv)
{
    // Define window constants.
    const uint COLOR_DEPTH = 32;
    const std::string WINDOW_TITLE = "Pong - Cullen Rombach";
    const uint WINDOW_STYLE = sf::Style::Close;

    // Create main window with vsync enabled. Screen tearing sucks.
    sf::RenderWindow window(sf::VideoMode(GC::WIDTH, GC::HEIGHT, COLOR_DEPTH), WINDOW_TITLE, WINDOW_STYLE);
    window.setVerticalSyncEnabled(true);

    // Load in fonts.
    sf::Font scoreFont;
    std::string scoreFontLocation = "resources/wargames.ttf";
    if (!scoreFont.loadFromFile(scoreFontLocation)) {
        throw std::runtime_error("Failed to load font from " + scoreFontLocation);
    }

    // Create Score Labels.
    ScoreLabel playerScore = ScoreLabel(GC::WIDTH / 3.f, GC::HEIGHT / 2.f, &scoreFont);
    ScoreLabel aiScore = ScoreLabel((GC::WIDTH / 3.f) * 2.f, GC::HEIGHT / 2.f, &scoreFont);

    // Create actors.
    Paddle playerPaddle = Paddle(GC::WIDTH / 40.f, GC::HEIGHT / 2.f);
    Paddle aiPaddle = Paddle(GC::WIDTH - (GC::WIDTH / 40.f), GC::HEIGHT / 2.f);
    Ball ball = Ball(GC::WIDTH / 2.f, GC::HEIGHT / 2.f);

    // Start main loop
    while(window.isOpen())
    {
        // Process events
        sf::Event Event;
        while(window.pollEvent(Event))
        {
            // Exit
            if(Event.type == sf::Event::Closed)
                window.close();
        }

        // Clear screen and fill with black
        window.clear(sf::Color::Black);

        // Draw actors and labels.
        window.draw(playerScore);
        window.draw(aiScore);
        window.draw(playerPaddle);
        window.draw(aiPaddle);
        window.draw(ball);

        // Display rendered image.
        window.display();
    }

    // Done.
    return 0;
}
