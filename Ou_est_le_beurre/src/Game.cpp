//
// Created by paddy on 30.11.21.
//

#include "ou_est_le_beurre/Game.hpp"
#include "ou_est_le_beurre/StateMachine/TestState.hpp"
#include "ou_est_le_beurre/StateMachine/ExploringState.hpp"

#include <iostream>
#include <utility>

Game::Game()
{
    // Background Music
    // load something into the sound buffer...
    if (!soundBuffer.loadFromFile(AUDIO_PATH + "Background_Music.wav"))
        std::cerr << "Problems while loading background music" << std::endl;

    backgroundMusic.setBuffer(soundBuffer);
    backgroundMusic.setLoop(true);

    backgroundMusic.play();

    // background
    if(!tex_background.loadFromFile(TEXTURES_PATH + "kitchen.png")) {
        std::cerr << "Problems while loading baackground texture" << std::endl;
    }
    background.setTexture(tex_background);

    pTilemap = std::make_shared<Tilemap>(this);

    pPlayer = std::make_shared<Player>(this, "Muttern.png");
    pTextbox = std::make_shared<Textbox>("Simple_Textbox.png");
    pFade = std::make_shared<FadeObject>();
    pPapo = std::make_shared<Player>(this, "Papo.png");
    pPapo->set_enabled(false);

    pPlayer->set_enabled(true);

    gameObjects.push_back(pPlayer);
    gameObjects.push_back(pTextbox);
    gameObjects.push_back(pFade);
    gameObjects.push_back(pPapo);

    // TODO add all states to states vector
   states.push_back(std::make_shared<OpeningState>(this));
   states.push_back(std::make_shared<ExploringState>(this));
   //std::shared_ptr<TestState> pTestState = std::make_shared<TestState>(this);
   //states.push_back(pTestState);

    // start iterator
    stateIterator = states.begin();
    (*stateIterator)->initState();
}

void Game::updateStateMachine(float delta_t){
    if((*stateIterator)->goalReached()){
        if((*stateIterator) == states.back()){
            // TODO do something
            std::cout << "Game is over" << std::endl;
        }else{
            stateIterator = next(stateIterator);
            (*stateIterator)->initState();
        }
    }
    (*stateIterator)->update(delta_t);
}

void Game::update(float delta_t)
{
    updateStateMachine(delta_t);

    // update current event
    for(auto event : events){
        event->update(delta_t);
    }


    // TODO update all game objects general
    // update gameObjects
    for(const auto& object : gameObjects) {
    	object->update(delta_t);
	}
}

void Game::draw(sf::RenderWindow &window)
{
    window.clear(sf::Color::White);

    window.draw(background);

    // draw gameObjects
    for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
    	window.draw(*(*it));
	}

    window.display();
}

Game::~Game() {
}

const std::shared_ptr<Textbox> &Game::getPTextbox() const {
    return pTextbox;
}

const std::shared_ptr<FadeObject> &Game::getPFade() const {
    return pFade;
}

const std::shared_ptr<Player> &Game::getPlayer() const {
	return pPlayer;
}

std::vector<std::shared_ptr<Event>> &Game::getEvents() {
	return events;
}

void Game::triggerEvent(int eventIndex) {
    // skip uninitialized events (index = -1)
    if(eventIndex != -1){
        events[eventIndex]->init();
    }
}

void Game::setEvents(std::vector<std::shared_ptr<Event>> events) {
    Game::events = std::move(events);
}

const std::shared_ptr<Tilemap> &Game::getPTilemap() const {
    return pTilemap;
}

const std::shared_ptr<Player> &Game::getPPapo() const {
    return pPapo;
}

bool Game::isKeyReleased(sf::Keyboard::Key key) {
	return key == releasedKey;
}

void Game::setKeyReleased(sf::Keyboard::Key key) {
	releasedKey = key;
}
