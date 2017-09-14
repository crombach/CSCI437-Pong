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
#include <TextUtils.h>

void placeHeaders(sf::Text *header, sf::Text *subheader);

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

    // Create a subheader Text object for use during game pauses.
    sf::Text subheader;
    subheader.setFont(autobus);
    subheader.setCharacterSize(GC::HEIGHT / 18);
    subheader.setString(pauseSubheader);
    subheader.setColor(sf::Color(80, 80, 80));

    // Place headers.
    placeHeaders(&header, &subheader);

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
    bool justStarted = true;
    bool gameOver = false;

    // Timer things.
    sf::Clock clock;
    float dTime;
    float secondsSinceStarted = 0.f;

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
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }

            // Control pausing with the space bar.
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
                // If the game is over, mark it as not over and reset the text labels.
                if (gameOver) {
                    gameOver = false;
                    // Update text headers.
                    header.setString(pauseHeader);
                    subheader.setString(pauseSubheader);
                    // Update the text origins and positioning.
                    placeHeaders(&header, &subheader);
                }
                // Pause/unpause.
                paused = !paused;
                // If unpausing, restart the clock to avoid unwanted ball/paddle movement.
                // Also, mark that the game has just started to give the player some breathing room.
                if (!paused) {
                    clock.restart();
                    justStarted = true;
                }
            }

            // Pause if the game loses focus.
            if (event.type == sf::Event::LostFocus) {
                paused = true;
            }
        }

        // Handle game events if we are in-game.
        if (!paused) {
            /*
             * Store time passed since last frame. If the game just started or just unpaused,
             * give the player a brief time before the ball starts moving. This is done by preventing
             * dTime (delta time, or the change in time) from incrementing.
             * */
            if (justStarted) {
                secondsSinceStarted += clock.restart().asSeconds();
                dTime = 0.f;
                // Give the play 0.6 seconds to get ready.
                if (secondsSinceStarted >= 0.6f) {
                    justStarted = false;
                    secondsSinceStarted = 0.f;
                }
            }
            else {
                dTime = clock.restart().asSeconds();
            }

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
                // Don't let the ball clip out of the screen.
                ball.setPosition(GC::WIDTH - ball.getRadius(), ball.getPosition().y);
                // Increase player score.
                playerScore.increment();
                // Reset UI elements.
                playerPaddle.reset(true);
                aiPaddle.reset(false);
                ball.reset();
                // Flag that the game just started again.
                justStarted = true;
            }

            // Check for an AI point.
            if (ball.getPosition().x - ball.getRadius() <= 0) {
                // Don't let the ball clip out of the screen.
                ball.setPosition(ball.getRadius(), ball.getPosition().y);
                // Increase AI score.
                aiScore.increment();
                // Reset UI elements.
                playerPaddle.reset(true);
                aiPaddle.reset(false);
                ball.reset();
                // Flag that the game just started again.
                justStarted = true;
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

                // Place headers.
                placeHeaders(&header, &subheader);

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

        // If paused, draw headers.
        if (paused) {
            window.draw(header);
            window.draw(subheader);
        }
        // Draw game components if not paused.
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

// Update the origins and positioning of the headers.
void placeHeaders(sf::Text *header, sf::Text *subheader) {
    TextUtils::centerTextOrigin(header);
    TextUtils::centerTextOrigin(subheader);
    TextUtils::centerTwoTexts(header, subheader);
}
