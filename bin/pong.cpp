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
#include <unistd.h>
#include <TextUtils.h>

// Main function containing game loop.
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
    std::string pauseHeader = "PRESS SPACE TO CONTINUE";
    std::string winHeader = "YOU WIN";
    std::string lossHeader = "YOU LOSE";
    std::string pauseSubheader = "PRESS [SPACE] AT ANY TIME TO PAUSE";
    std::string endGameSubheader = "PRESS [SPACE] TO RETRY OR [ESC] TO QUIT";

    // Create a header Text object for use during game pauses.
    sf::Text header;
    header.setFont(wargames);
    header.setCharacterSize(GC::HEIGHT / 16);
    header.setString(pauseHeader);
    header.setColor(sf::Color::White);
    TextUtils::centerTextOrigin(&header);

    // Create a subheader Text object for use during game pauses.
    sf::Text subheader;
    subheader.setFont(autobus);
    subheader.setCharacterSize(GC::HEIGHT / 18);
    subheader.setString(pauseSubheader);
    subheader.setColor(sf::Color(60, 60, 60));
    TextUtils::centerTextOrigin(&subheader);

    // Set message and reminder position.
    TextUtils::centerTwoTexts(&header, &subheader);

    // Create score labels.
    ScoreLabel playerScore = ScoreLabel(GC::WIDTH / 3.f, GC::HEIGHT / 2.f, &wargames);
    ScoreLabel aiScore = ScoreLabel((GC::WIDTH / 3.f) * 2.f, GC::HEIGHT / 2.f, &wargames);

    // Create paddles.
    Paddle playerPaddle = Paddle(GC::WIDTH / 80.f, GC::HEIGHT / 2.f);
    Paddle aiPaddle = Paddle(GC::WIDTH - (GC::WIDTH / 80.f), GC::HEIGHT / 2.f);

    // Create ball.
    Ball ball = Ball(GC::WIDTH / 2.f, GC::HEIGHT / 2.f);

    // Game state flags.
    bool paused = true;
    bool gameOver = false;

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

            // Allow the player to quit with the escape button.
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }

            // Control pausing with the space bar.
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
                // If the game is over, mark it as not over and reset the text labels.
                if (gameOver) {
                    gameOver = false;
                    header.setString(pauseHeader);
                    subheader.setString(pauseSubheader);
                }
                // Pause/unpause.
                paused = !paused;
                // Give the player a small amount of time to prepare.
                if (!paused) {
                    usleep(50000);
                }
            }

            // Pause if the game loses focus.
            if (event.type == sf::Event::LostFocus) {
                paused = true;
            }
        }

        // Handle game events if we are in-game.
        if (!paused) {
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

            // Move the ball. This also checks for collisions.
            ball.move(dTime, &playerPaddle, &aiPaddle);

            // Check for a player point.
            if (ball.getPosition().x + ball.getRadius() >= GC::WIDTH) {
                playerScore.increment();
                playerPaddle.reset(true);
                aiPaddle.reset(false);
                ball.reset();
            }

            // Check for an AI point.
            if (ball.getPosition().x - ball.getRadius() <= 0) {
                aiScore.increment();
                playerPaddle.reset(true);
                aiPaddle.reset(false);
                ball.reset();
            }

            // Check for win/loss.
            if (playerScore.getScore() == 11 || aiScore.getScore() == 11) {
                // If the player won, give then the winner text.
                if (playerScore.getScore() == 11) {
                    header.setString(winHeader);
                }
                // If they lost, given them the loser text.
                if (aiScore.getScore() == 11) {
                    header.setString(lossHeader);
                }

                // Set subheader text.
                subheader.setString(endGameSubheader);

                // Update the text origins and positioning.
                TextUtils::centerTextOrigin(&header);
                TextUtils::centerTextOrigin(&subheader);
                TextUtils::centerTwoTexts(&header, &subheader);

                // Reset game elements.
                playerScore.reset();
                aiScore.reset();
                playerPaddle.reset(true);
                aiPaddle.reset(false);
                ball.reset();

                // Pause the game on the end screen.
                paused = true;
                gameOver = true;
            }
        }

        // Clear screen and fill with black
        window.clear(sf::Color::Black);

        // If paused, draw pause messages.
        if (paused) {
            window.draw(header);
            window.draw(subheader);
        }
        // Draw game components if not paused or game over.
        else {
            window.draw(playerScore);
            window.draw(aiScore);
            window.draw(playerPaddle);
            window.draw(aiPaddle);
            window.draw(ball);
        }

        // Display rendered image.
        window.display();
    }

    // Done.
    return 0;
}
