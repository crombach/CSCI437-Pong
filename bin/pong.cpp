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
    sf::Font wargames;
    std::string wargamesLocation = "resources/wargames.ttf";
    if (!wargames.loadFromFile(wargamesLocation)) {
        throw std::runtime_error("Failed to load font from " + wargamesLocation);
    }
    sf::Font autobus;
    std::string autobusLocation = "resources/autobus.ttf";
    if (!autobus.loadFromFile(autobusLocation)) {
        throw std::runtime_error("Failed to load font from " + autobusLocation);
    }

    // Store some messages to use when the game is paused.
    std::string pauseText = "PRESS SPACE TO CONTINUE";
    std::string reminderText = "PRESS SPACE AT ANY TIME TO PAUSE";

    // Create a message Text object.
    sf::Text message;
    message.setFont(wargames);
    message.setString(pauseText);
    message.setColor(sf::Color::White);
    sf::FloatRect messageRect = message.getLocalBounds();
    message.setOrigin(messageRect.left + (messageRect.width / 2), messageRect.top + (messageRect.height / 2));

    // Create a reminder Text object.
    sf::Text reminder;
    reminder.setFont(autobus);
    reminder.setString(reminderText);
    reminder.setColor(sf::Color(60, 60, 60));
    sf::FloatRect reminderRect = reminder.getLocalBounds();
    reminder.setOrigin(reminderRect.left + (reminderRect.width / 2), reminderRect.top + (reminderRect.height / 2));

    // Set message and reminder position.
    message.setPosition(GC::WIDTH / 2, (GC::HEIGHT / 2) - messageRect.height);
    reminder.setPosition(GC::WIDTH / 2, (GC::HEIGHT / 2) + reminderRect.height);

    // Create score labels.
    ScoreLabel playerScore = ScoreLabel(GC::WIDTH / 3.f, GC::HEIGHT / 2.f, &wargames);
    ScoreLabel aiScore = ScoreLabel((GC::WIDTH / 3.f) * 2.f, GC::HEIGHT / 2.f, &wargames);

    // Create paddles.
    Paddle playerPaddle = Paddle(GC::WIDTH / 80.f, GC::HEIGHT / 2.f);
    Paddle aiPaddle = Paddle(GC::WIDTH - (GC::WIDTH / 80.f), GC::HEIGHT / 2.f);

    // Create ball.
    Ball ball = Ball(GC::WIDTH / 2.f, GC::HEIGHT / 2.f);

    // Game state flags.
    bool inGame = false;

    // Timer.
    sf::Clock clock;

    // Start main loop
    while(window.isOpen()) {
        // Process events
        sf::Event event;
        while(window.pollEvent(event)) {
            // Exit when the window is closed.
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Control pausing with the space bar.
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                inGame = !inGame;
            }
        }

        // Display a pause screen if we are paused.
        if (!inGame) {

        }

        // Handle game events if we are in-game.
        else {
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
        // If paused, draw pause messages.
        else {
            window.draw(message);
            window.draw(reminder);
        }

        // TODO: Otherwise, draw pause screen.

        // Display rendered image.
        window.display();
    }

    // Done.
    return 0;
}
