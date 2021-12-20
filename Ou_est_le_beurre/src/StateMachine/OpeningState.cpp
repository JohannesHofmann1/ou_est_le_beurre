//
// Created by paddy on 20.12.21.
//

#include "ou_est_le_beurre/OpeningState.hpp"


OpeningState::OpeningState(Game const *game) : State(game){
    pTextbox = game->getPTextbox();
    pFade = game->getPFade();

    // TODO initialize scene
    pFade->startFade();
    // TODO momy at door
    // TODO lock player control
}

bool OpeningState::goalReached() {
    if(state == FINISHED){
        return true;
    }
    return false;
}

void OpeningState::prepareEpilog(){
    pTextbox->set_text(L"Spielemacher", L"Das hier ist der Beginn von einem großartigem Spiel!");
    pTextbox->set_enabled(true);
}

void OpeningState::processState() {
    switch(state){
        case FADE_IN:
            if(!pFade->get_enabled()){
                prepareEpilog();
                state = EPILOG;
            }
            break;
        case EPILOG:
            if(!pTextbox->get_enabled()){
                state = FINISHED;
            }
            break;
    }
}
