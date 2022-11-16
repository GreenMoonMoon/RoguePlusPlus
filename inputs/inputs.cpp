#include "inputs.h"
#include "SDL.h"

#include <iostream>

Input::Input() {
    if (SDL_InitSubSystem(SDL_INIT_SENSOR|SDL_INIT_GAMECONTROLLER|SDL_INIT_HAPTIC) != 0) {
        std::cerr << "SDL2 Sensor, GameController and Haptic subsystem couldn't be initialized. Error: "
                  << SDL_GetError() << std::endl;
        return;
    }

//    // PS4 Controller with bluetooth
//    SDL_SetHint(SDL_HINT_JOYSTICK_HIDAPI_PS4_RUMBLE, "1");

//    // PS5 Controller with bluetooth
//    SDL_SetHint(SDL_HINT_JOYSTICK_HIDAPI_PS5_RUMBLE, "1");

//    // SDL2 maps Nintendo Switch Pro controllers to the layout that nintendo usually provides.
//    SDL_SetHint(SDL_HINT_GAMECONTROLLER_USE_BUTTON_LABELS, "1");
//
//    // SDL2 can actually access and use Nintendo Switch Joycons without a driver needed, and allows for them to be queried with full functionality
//    // regarding analog, gyro and accelerometer, and other functionality. This hint controls that.
//    SDL_SetHint(SDL_HINT_JOYSTICK_HIDAPI_JOY_CONS, "1");
}

void Input::ProcessEvents(bool &running) {
    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_CONTROLLERDEVICEADDED){
            bool add_device = true;
            for(const auto gamepad: gamepads){
                if (gamepad->id == event.cdevice.which){
                    add_device = false;
                    break;
                }
            }
            if (add_device){
                gamepads.push_back(new Gamepad(event.cdevice.which));
            }
        }

        if (event.type == SDL_CONTROLLERDEVICEREMOVED){
            for(auto it = gamepads.begin(); it != gamepads.end(); it++){
                if((*it)->id == event.cdevice.which) {
                    auto gamepad = *(it);
                    gamepads.erase(it);
                    delete gamepad;
                    break;
                }
            }
        }

        for (auto gamepad : gamepads){
            gamepad->PollState();
            if(gamepad->state.A != 0){
                std::cout << "Button A pressed! " << gamepad->state.A << std::endl;
            }
        }

        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                }
        }
    }
}
