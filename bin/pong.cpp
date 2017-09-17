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

void placeHeaders(sf::Text &header, sf::Text &subheader);

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
    placeHeaders(header, subheader);

    // Create score labels.
    ScoreLabel leftScore = ScoreLabel(GC::WIDTH / 3.f, GC::HEIGHT / 2.f, wargames);
    ScoreLabel rightScore = ScoreLabel((GC::WIDTH / 3.f) * 2.f, GC::HEIGHT / 2.f, wargames);

    // Create paddles.
    Paddle leftPaddle = Paddle(GC::WIDTH / 80.f, GC::HEIGHT / 2.f);
    Paddle rightPaddle = Paddle(GC::WIDTH - (GC::WIDTH / 80.f), GC::HEIGHT / 2.f);

    // Create ball.
    Ball ball = Ball(GC::WIDTH / 2.f, GC::HEIGHT / 2.f);

    // Ghost ball variables for the AI to calculate moves.
    float lastBallDx = 0.f;
    Ball ghostBall = Ball(ball.getPosition().x, ball.getPosition().y);
    ghostBall.setDx(ball.getDx());
    ghostBall.setDy(ball.getDy());
    ghostBall.setFillColor(sf::Color::Green); // Relevant when testing the ghost ball's behavior.

    // Game state flags.
    bool isPaused = true;
    bool justStarted = true;
    bool isGameOver = false;

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
                if (isGameOver) {
                    isGameOver = false;
                    // Update text headers.
                    header.setString(pauseHeader);
                    subheader.setString(pauseSubheader);
                    // Update the text origins and positioning.
                    placeHeaders(header, subheader);
                }
                // Pause/unpause.
                isPaused = !isPaused;
                // If unpausing, restart the clock to avoid unwanted ball/paddle movement.
                // Also, mark that the game has just started to give the player some breathing room.
                if (!isPaused) {
                    clock.restart();
                    justStarted = true;
                }
            }
            // Pause if the game loses focus.
            else if (event.type == sf::Event::LostFocus) {
                isPaused = true;
            }
        }

        // Handle game events if we are in-game.
        if (!isPaused) {
            /*
             * Store time passed since last frame. If the game just started or just unpaused,
             * give the player a brief time before the ball starts moving. This is done by preventing
             * dTime (delta time, or the change in time) from incrementing.
             * */
            if (justStarted) {
                secondsSinceStarted += clock.restart().asSeconds();
                dTime = 0.f;
                // Give the player 0.75 seconds to get ready.
                if (secondsSinceStarted >= 0.75f) {
                    justStarted = false;
                    secondsSinceStarted = 0.f;
                }
            } else {
                dTime = clock.restart().asSeconds();
            }

            // Move the ball. This also checks for collisions.
            ball.move(dTime, leftPaddle, rightPaddle);
            // Move the ghost ball used to calculate AI movements.
            ghostBall.moveAsGhostBall(dTime, leftPaddle, rightPaddle, ball, lastBallDx);
            // Store the real ball's last speed. Used for the Ghost Ball.
            lastBallDx = ball.getDx();

            // Move the AI paddle.
            rightPaddle.moveAsAI(dTime, ghostBall.getDy(), ghostBall.getPosition());

            // Move the player's paddle if commanded.
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                leftPaddle.moveUp(dTime);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                leftPaddle.moveDown(dTime);
            }
            else {
                // This is just used to flag that the paddle shouldn't move.
                leftPaddle.noMove();
            }

            // Check for a player point.
            if ((ball.getPosition().x + ball.getRadius()) >= GC::WIDTH) {
                // Don't let the ball clip out of the screen.
                ball.setPosition(GC::WIDTH - ball.getRadius(), ball.getPosition().y);
                // Increase player score.
                leftScore.increment();
                // Reset UI elements.
                leftPaddle.reset(true);
                rightPaddle.reset(false);
                ball.reset();
                // Flag that the game just started again.
                justStarted = true;
                // Reset ball speed for AI.
                lastBallDx = 0.f;
            }

            // Check for an AI point.
            if ((ball.getPosition().x - ball.getRadius()) <= 0) {
                // Don't let the ball clip out of the screen.
                ball.setPosition(ball.getRadius(), ball.getPosition().y);
                // Increase AI score.
                rightScore.increment();
                // Reset UI elements.
                leftPaddle.reset(true);
                rightPaddle.reset(false);
                ball.reset();
                // Flag that the game just started again.
                justStarted = true;
                // Reset ball speed for AI.
                lastBallDx = 0.f;
            }

            // Check for win/loss.
            if (leftScore.getScore() == 11 || rightScore.getScore() == 11) {
                // If the player won, give then the winner text.
                if (leftScore.getScore() == 11) {
                    header.setString(winHeader);
                }
                // If they lost, given them the loser text.
                if (rightScore.getScore() == 11) {
                    header.setString(lossHeader);
                }

                // Set subheader text.
                subheader.setString(endGameSubheader);

                // Place headers.
                placeHeaders(header, subheader);

                // Reset game elements.
                leftScore.reset();
                rightScore.reset();
                leftPaddle.reset(true);
                rightPaddle.reset(false);
                ball.reset();

                // Pause the game on the end screen.
                isPaused = true;
                isGameOver = true;
            }
        }

        // Clear screen and fill with black
        window.clear(sf::Color::Black);

        // If paused, draw headers.
        if (isPaused) {
            window.draw(header);
            window.draw(subheader);
        }
        // Draw game components if not paused.
        else {
            window.draw(leftScore);
            window.draw(rightScore);
            window.draw(leftPaddle);
            window.draw(rightPaddle);
            //window.draw(ghostBall); // Uncomment this to see the ghost ball.
            window.draw(ball);
        }

        // Display rendered image.
        window.display();
    }

    // Done.
    return 0;
}

// Update the origins and positioning of the headers.
void placeHeaders(sf::Text &header, sf::Text &subheader) {
    TextUtils::centerTextOrigin(header);
    TextUtils::centerTextOrigin(subheader);
    TextUtils::centerTwoTexts(header, subheader);
}
