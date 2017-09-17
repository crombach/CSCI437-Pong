/**
 * Pong game for CSCI 437.
 *
 * Created by Cullen Rombach (cmrombach@email.wm.edu).
 */

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ScoreLabel.h>
#include <GC.h>
#include <Paddle.h>
#include <Ball.h>
#include <TextUtils.h>
using namespace std;

void placeHeaders(sf::Text &header, sf::Text &subheader);

// Main function containing game loop.
int main(int argc, char** argv) {
    // Define window constants.
    const uint COLOR_DEPTH = 32;
    const string WINDOW_TITLE = "Pong - Cullen Rombach";
    const uint WINDOW_STYLE = sf::Style::Close;

    // Create main window with vsync enabled. Screen tearing sucks.
    sf::RenderWindow window(sf::VideoMode(GC::WIDTH, GC::HEIGHT, COLOR_DEPTH), WINDOW_TITLE, WINDOW_STYLE);
    window.setVerticalSyncEnabled(true);

    // Load in sounds.
    // Left hit.
    sf::SoundBuffer leftHitSoundBuffer;
    string leftHitLocation = "resources/leftHit.wav";
    if (!leftHitSoundBuffer.loadFromFile(leftHitLocation)) {
        throw runtime_error("Failed to load sound from " + leftHitLocation);
    }
    auto leftHit = make_shared<sf::Sound>(leftHitSoundBuffer);
    // Right hit.
    sf::SoundBuffer rightHitSoundBuffer;
    string rightHitLocation = "resources/rightHit.wav";
    if (!rightHitSoundBuffer.loadFromFile(rightHitLocation)) {
        throw runtime_error("Failed to load sound from " + rightHitLocation);
    }
    auto rightHit = make_shared<sf::Sound>(rightHitSoundBuffer);
    // Wall hit.
    sf::SoundBuffer wallHitSoundBuffer;
    string wallHitLocation = "resources/wallHit.wav";
    if (!wallHitSoundBuffer.loadFromFile(wallHitLocation)) {
        throw runtime_error("Failed to load sound from " + wallHitLocation);
    }
    auto wallHit = make_shared<sf::Sound>(wallHitSoundBuffer);
    // Player score.
    sf::SoundBuffer playerScoreSoundBuffer;
    string playerScoreLocation = "resources/playerScore.wav";
    if (!playerScoreSoundBuffer.loadFromFile(playerScoreLocation)) {
        throw runtime_error("Failed to load sound from " + playerScoreLocation);
    }
    sf::Sound playerScoreSound(playerScoreSoundBuffer);
    // AI score.
    sf::SoundBuffer aiScoreSoundBuffer;
    string aiScoreLocation = "resources/aiScore.wav";
    if (!aiScoreSoundBuffer.loadFromFile(aiScoreLocation)) {
        throw runtime_error("Failed to load sound from " + aiScoreLocation);
    }
    sf::Sound aiScoreSound(aiScoreSoundBuffer);
    // Menu blip.
    sf::SoundBuffer blipSoundBuffer;
    string blipLocation = "resources/blip.wav";
    if (!blipSoundBuffer.loadFromFile(blipLocation)) {
        throw runtime_error("Failed to load sound from " + blipLocation);
    }
    sf::Sound blip(blipSoundBuffer);

    // Load in fonts.
    // Wargames
    sf::Font wargames;
    string wargamesLocation = "resources/wargames.ttf";
    if (!wargames.loadFromFile(wargamesLocation)) {
        throw runtime_error("Failed to load font from " + wargamesLocation);
    }
    // Autobus
    sf::Font autobus;
    string autobusLocation = "resources/autobus.ttf";
    if (!autobus.loadFromFile(autobusLocation)) {
        throw runtime_error("Failed to load font from " + autobusLocation);
    }

    // Store some messages to use when the game is paused.
    string mainMenuHeader = "MAIN MENU";
    string mainMenuSubheader = "[1] SINGLE PLAYER\n[2] MULTI-PLAYER\n[C]\t\tCONTROLS";
    string controlsHeader = "CONTROLS";
    string controlsSubheader = "[SPACE]\t\t\t\t\tPAUSE\n"
                               "[UP]\t\t\t   P1 PADDLE UP\n"
                               "[DOWN]\tP1 PADDLE DOWN\n"
                               "[W]\t\t\t  P2 PADDLE UP\n"
                               "[S]\t\t  P2 PADDLE DOWN\n\n"
                               "[M]  RETURN TO MAIN MENU";
    string pauseHeader = "GAME PAUSED";
    string pauseSubheader = "[SPACE] CONTINUE\n[M]\t   MAIN MENU\n[ESC]\t\t\t QUIT";
    string singlePlayerWinHeader = "YOU WIN!";
    string singlePlayerLossHeader = "YOU LOSE!";
    string leftPlayerWinHeader = "LEFT PLAYER WINS!";
    string rightPlayerWinHeader = "RIGHT PLAYER WINS!";
    string endGameSubheader = "[SPACE]\t  RETRY\n[M]\t   MAIN MENU\n[ESC]\t\t\t QUIT";

    // Create a header Text object for use during game pauses.
    sf::Text header;
    header.setFont(wargames);
    header.setCharacterSize(GC::HEIGHT / 16);
    header.setString(mainMenuHeader);
    header.setColor(sf::Color::White);

    // Create a subheader Text object for use during game pauses.
    sf::Text subheader;
    subheader.setFont(autobus);
    subheader.setCharacterSize(GC::HEIGHT / 18);
    subheader.setString(mainMenuSubheader);
    subheader.setColor(sf::Color(100, 100, 100));

    // Place headers.
    placeHeaders(header, subheader);

    // Create score labels.
    ScoreLabel leftScore = ScoreLabel(GC::WIDTH / 3.f, GC::HEIGHT / 2.f, wargames);
    ScoreLabel rightScore = ScoreLabel((GC::WIDTH / 3.f) * 2.f, GC::HEIGHT / 2.f, wargames);

    // Create paddles.
    Paddle leftPaddle = Paddle(GC::WIDTH / 80.f, GC::HEIGHT / 2.f);
    Paddle rightPaddle = Paddle(GC::WIDTH - (GC::WIDTH / 80.f), GC::HEIGHT / 2.f);

    // Create ball.
    Ball ball = Ball(GC::WIDTH / 2.f, GC::HEIGHT / 2.f, leftHit, rightHit, wallHit);

    // Ghost ball variables for the AI to calculate moves.
    float lastBallDx = 0.f;
    auto nullSound = shared_ptr<sf::Sound>(nullptr);
    Ball ghostBall = Ball(ball.getPosition().x, ball.getPosition().y, nullSound, nullSound, nullSound);
    ghostBall.setDx(ball.getDx());
    ghostBall.setDy(ball.getDy());
    ghostBall.setFillColor(sf::Color::Green); // Relevant when testing the ghost ball's behavior.

    // Game state flags.
    bool isMainMenu = true;
    bool isControls = false;
    bool isPaused = true;
    bool isGameOver = false;
    bool isMultiplayer = false;
    bool holdState = true;

    // Timer things.
    sf::Clock clock;
    float dTime;
    float secondsSinceStateHeld = 0.f;

    // Start main loop
    while(window.isOpen()) {
        // Process events
        sf::Event event;
        while(window.pollEvent(event)) {
            // Exit when the window is closed.
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Allow the player to quit (at any time) with the escape button.
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            // If the player pressed 1 from the main menu, start the game as single player.
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num1 && isMainMenu && !isControls) {
                // Play sound.
                blip.play();
                // Set game state flags.
                isMainMenu = false;
                isMultiplayer = false;
                isPaused = false;
                holdState = true;
                // Reset game actors and scores.
                ball.reset();
                ghostBall.reset();
                rightPaddle.reset(false);
                leftPaddle.reset(true);
                leftScore.reset();
                rightScore.reset();
                // Update header text.
                header.setString(pauseHeader);
                subheader.setString(pauseSubheader);
                // Reposition headers.
                placeHeaders(header, subheader);
                // Reset game clock.
                clock.restart();
            }
            // If the player pressed 2 from the main menu, start the game as multiplayer.
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num2 && isMainMenu && !isControls) {
                // Play sound.
                blip.play();
                // Set game state flags.
                isMainMenu = false;
                isMultiplayer = true;
                isPaused = false;
                holdState = true;
                // Reset game actors and scores.
                ball.reset();
                ghostBall.reset();
                rightPaddle.reset(false);
                leftPaddle.reset(true);
                leftScore.reset();
                rightScore.reset();
                // Update header text.
                header.setString(pauseHeader);
                subheader.setString(pauseSubheader);
                // Reposition headers.
                placeHeaders(header, subheader);
                // Reset game clock.
                clock.restart();
            }
            // If the player pressed C from the main menu, show them the controls.
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::C && isMainMenu) {
                // Play sound.
                blip.play();
                // Set game state flags.
                isControls = true;
                // Update header text.
                header.setString(controlsHeader);
                subheader.setString(controlsSubheader);
                // Reposition headers.
                placeHeaders(header, subheader);
            }
            // Control pausing with the space bar.
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space && !isMainMenu) {
                // Play sound.
                blip.play();
                // If the game is over, mark it as not over and reset the text labels.
                if (isGameOver) {
                    isGameOver = false;
                    // Update text headers.
                    header.setString(pauseHeader);
                    subheader.setString(pauseSubheader);
                    // Update the text origins and positioning.
                    placeHeaders(header, subheader);
                }
                // Pause/unpause only if the game has started.
                isPaused = !isPaused;
                // If unpausing, restart the clock to avoid unwanted ball/paddle movement.
                // Also, mark that the game has just started to give the player some breathing room.
                if (!isPaused) {
                    clock.restart();
                    holdState = true;
                }
            }
            // The M key takes the player back to the main menu if the game is currently paused.
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::M && isPaused) {
                // Play sound.
                blip.play();
                // Set game state flags.
                isMainMenu = true;
                isControls = false;
                // Update header text.
                header.setString(mainMenuHeader);
                subheader.setString(mainMenuSubheader);
                // Reposition headers.
                placeHeaders(header, subheader);
            }
            // Pause if the game loses focus.
            else if (event.type == sf::Event::LostFocus) {
                isPaused = true;
            }
        }

        // Handle game events if we are in-game.
        if (!isPaused) {
            /*
             * If the "holdState" flag is set, give the player a brief time before the game state changes again.
             * This is done by preventing dTime (the change in time) from incrementing.
             * */
            if (holdState) {
                secondsSinceStateHeld += clock.restart().asSeconds();
                dTime = 0.f;
                // Give the player a brief time to get ready.
                if (secondsSinceStateHeld >= 0.75f) {
                    holdState = false;
                    secondsSinceStateHeld = 0.f;
                }
            } else {
                // Store time passed since the last frame.
                dTime = clock.restart().asSeconds();
            }

            // Move the ball. This also checks for collisions.
            ball.move(dTime, leftPaddle, rightPaddle);

            // Handle AI movements in single player.
            if (!isMultiplayer) {
                // Move the ghost ball used to calculate AI movements.
                ghostBall.moveAsGhostBall(dTime, leftPaddle, rightPaddle, ball, lastBallDx);
                // Store the real ball's last speed. Used for the Ghost Ball.
                lastBallDx = ball.getDx();
                // Move the AI paddle.
                leftPaddle.moveAsAI(dTime, ghostBall.getDy(), ghostBall.getPosition());
            }

            // Look for up/down inputs to move right paddle.
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                rightPaddle.moveUp(dTime);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                rightPaddle.moveDown(dTime);
            }
            else {
                rightPaddle.noMove();
            }

            // If we're in multiplayer, look for W/S inputs to control left paddle.
            if (isMultiplayer) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    leftPaddle.moveUp(dTime);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    leftPaddle.moveDown(dTime);
                }
                else {
                    leftPaddle.noMove();
                }
            }

            // Check for left point.
            if ((ball.getPosition().x - ball.getRadius()) >= GC::WIDTH) {
                // Increase left score.
                leftScore.increment();
                // Reset UI elements.
                leftPaddle.reset(true);
                rightPaddle.reset(false);
                ball.reset();
                ghostBall.reset();
                // Flag that the game just started again.
                holdState = true;
                // Reset ball speed for AI.
                lastBallDx = 0.f;
                // Play sound.
                if (isMultiplayer) {
                    playerScoreSound.play();
                } else {
                    aiScoreSound.play();
                }
            }
            // Check for right point.
            else if ((ball.getPosition().x + ball.getRadius()) <= 0) {
                // Increase right score.
                rightScore.increment();
                // Reset UI elements.
                leftPaddle.reset(true);
                rightPaddle.reset(false);
                ball.reset();
                ghostBall.reset();
                // Flag that the game just started again.
                holdState = true;
                // Reset ball speed for AI.
                lastBallDx = 0.f;
                // Play sound.
                playerScoreSound.play();
            }

            // Check for win/loss.
            if (leftScore.getScore() == 11 || rightScore.getScore() == 11) {
                // If the left won...
                if (leftScore.getScore() == 11) {
                    if (isMultiplayer) {
                        // Give left player win for multiplayer.
                        header.setString(leftPlayerWinHeader);
                    } else {
                        // Give a loss for single player.
                        header.setString(singlePlayerLossHeader);
                    }
                }
                // If the right won...
                else if (rightScore.getScore() == 11) {
                    if (isMultiplayer) {
                        // Give right player win for multiplayer.
                        header.setString(rightPlayerWinHeader);
                    } else {
                        // Give a win for single player.
                        header.setString(singlePlayerWinHeader);
                    }
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
