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

int main(int argc, char** argv) {
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

    // Game state flags.
    bool inGame = true;

    // Timer.
    sf::Clock clock;

    // Start main loop
    while(window.isOpen()) {
        // Process events
        sf::Event Event;
        while(window.pollEvent(Event)) {
            // Exit when the window is closed.
            if (Event.type == sf::Event::Closed) {
            window.close();
            }
        }

        // Handle game events if we are in-game.
        if (inGame) {
            // Store time passed since last frame.
            float dTime = clock.restart().asSeconds();

            // Move the player's paddle if commanded.
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                playerPaddle.moveUp(dTime);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                playerPaddle.moveDown(dTime);
            }

            // Move the AI paddle.
            aiPaddle.moveAsAI(ball.getPosition(), dTime);

            // Move the ball. This also checks for paddle hits.
            ball.move(dTime, &playerPaddle, &aiPaddle);

            // Check for a player point.
            if (ball.getPosition().x + ball.getRadius() >= GC::WIDTH) {
                playerScore.increment();
                // TODO: May want to pause the game here.
                playerPaddle.reset(true);
                aiPaddle.reset(false);
                ball.reset();
            }

            // Check for an AI point.
            if (ball.getPosition().x - ball.getRadius() <= 0) {
                aiScore.increment();
                // TODO: May want to pause the game here.
                playerPaddle.reset(true);
                aiPaddle.reset(false);
                ball.reset();
            }
        }

        // Clear screen and fill with black
        window.clear(sf::Color::Black);

        // Draw actors and scores if in-game.
        if (inGame) {
            window.draw(playerScore);
            window.draw(aiScore);
            window.draw(playerPaddle);
            window.draw(aiPaddle);
            window.draw(ball);
        }

        // TODO: Otherwise, draw pause screen.

        // Display rendered image.
        window.display();
    }

    // Done.
    return 0;
}
