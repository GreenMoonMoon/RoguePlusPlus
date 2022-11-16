#ifndef SM64_CONTROLLER_H
#define SM64_CONTROLLER_H

#include "SDL_keyboard.h"
#include "SDL_gamecontroller.h"

#include <vector>
#include <string>

struct GamepadState {
    //DPad buttons
    uint8_t DPadUp = 0;
    uint8_t DPadDown = 0;
    uint8_t DPadLeft = 0;
    uint8_t DPadRight = 0;
    //Face Buttons (based on Xbox controller layout)
    uint8_t A = 0; // Nintendo B | PlayStation ✕
    uint8_t B = 0; // Nintendo A | PlayStation ◯
    uint8_t X = 0; // Nintendo Y | PlayStation ☐
    uint8_t Y = 0; // Nintendo X | PlayStation △
    // Start, Back, and Guide
    uint8_t Start = 0;
    uint8_t Back = 0;
    uint8_t Guide = 0;
    //Left Click and Right Click
    uint8_t LeftStickClick = 0;
    uint8_t RightStickClick = 0;
    //Paddles 1-4
    uint8_t Paddle1 = 0;
    uint8_t Paddle2 = 0;
    uint8_t Paddle3 = 0;
    uint8_t Paddle4 = 0;
    //Touchpad Button and Misc (Xbox Share button, Switch Pro Capture button, and Mic button for PS4/PS5 controllers)
    uint8_t Touchpad = 0;
    uint8_t Misc = 0;
    //Left and Right Shoulder
    uint8_t LeftShoulder = 0;
    uint8_t RightShoulder = 0;
    // Axis values for the left and right stick
    struct LeftStickAxis {float x= 0.0f; float y = 0.0f;} LeftStick; // -1.0f <=> 1.0f
    struct RightStickAxis {float x = 0.0f; float y = 0.0f;} RightStick; // -1.0f <=> 1.0f
    //Left and Right Trigger
    float LeftTrigger = 0.0f; // 0.0f <=> 1.0f
    float RightTrigger = 0.0f; // 0.0f <=> 1.0f
};

struct SDLGamepadSensorState {
    // Right hand coordinate
    float Accelerometer[3] = {0.0f, 0.0f, 0.0f};
    float Gyroscope[3] = {0.0f, 0.0f, 0.0f};
};

struct SDLGamepadTouchpadFinger{
    Uint8 state;
    float x = 0.0f;
    float y = 0.0f;
    float pressure = 0.0f;
};

struct SDLGamepadTouchpad {
    std::vector<SDLGamepadTouchpadFinger> fingers;
};

class Gamepad {
  public:
    std::string name = "";
    SDL_GameController *gamepad;
    int touchpadCount = 0;
    bool hapticsSupported = false;
    bool triggerHapticsSupported = false;
    bool sensorSupported = false;
    bool gyroSupported = false;
    bool accelSupported = false;
    bool touchpadSupported = false;

  public:
    SDL_JoystickID id;
    GamepadState previousState;
    GamepadState state;
    SDLGamepadSensorState previousSensorState;
    SDLGamepadSensorState sensorState;
    std::vector<SDLGamepadTouchpad> touchpads;
    bool sensorEnabled = false;
    bool gyroActive = false;
    bool accelActive = false;
    bool queryTouchpadsActive = false;

    Gamepad(int joystick_index){
        // Open a new game controller and retrieve its ID
        gamepad = SDL_GameControllerOpen(joystick_index);
        id = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gamepad));

        name = SDL_GameControllerName(gamepad);

        // Check if haptics are supported
        if (SDL_GameControllerRumble(gamepad, 0, 0, 0) == 0){
            hapticsSupported = true;
        }

        // Check if trigger haptics are supported
        if (SDL_GameControllerRumbleTriggers(gamepad, 0, 0, 0) == 0){
            triggerHapticsSupported = true;
        }

        // Check if Gyro is supported
        if (SDL_GameControllerHasSensor(gamepad, SDL_SENSOR_ACCEL) || SDL_GameControllerHasSensor(gamepad, SDL_SENSOR_GYRO)){
            sensorSupported = true;
            if (SDL_GameControllerHasSensor(gamepad, SDL_SENSOR_ACCEL)){
                accelSupported = true;
            }
            if (SDL_GameControllerHasSensor(gamepad, SDL_SENSOR_GYRO)){
                gyroSupported = true;
            }
        }

        // Check if touchpad is supported
        touchpadCount = SDL_GameControllerGetNumTouchpads(gamepad);
        if (touchpadCount){
            touchpadSupported = true;
            touchpads.resize(touchpadCount);
            for (int i = 0; i < touchpadCount; i++){
                touchpads[i].fingers.resize(SDL_GameControllerGetNumTouchpadFingers(gamepad, i));
            }
        }
    }

    ~Gamepad(){
        SDL_GameControllerClose(gamepad);
    }

    bool HasAccelerometer(){
        return sensorSupported && accelSupported;
    }

    bool HasGyroscope(){
        return sensorSupported && gyroSupported;
    }

    bool HasAllSensors(){
        return HasAccelerometer() && HasGyroscope();
    }

    bool HasLED(){
        return SDL_GameControllerHasLED(gamepad);
    }

    void SetSensor(SDL_SensorType type, SDL_bool active){
        if (type == SDL_SENSOR_GYRO){
            gyroActive = active;
        }
        if (type == SDL_SENSOR_ACCEL){
            accelActive = active;
        }
        sensorEnabled = (gyroActive || accelActive);
        SDL_GameControllerSetSensorEnabled(gamepad, type, active);
    }

    void SetTouchpadSensing(bool active){
        if (touchpadSupported){
            queryTouchpadsActive = active;
        }
    }

    void pollTouchpad(){
        if (queryTouchpadsActive){
            for (int index = 0; index < touchpadCount; index++){
                for (int finger = 0; finger < touchpads[index].fingers.size(); finger++){
                    SDL_GameControllerGetTouchpadFinger(gamepad, index, finger,
                                                        &touchpads[index].fingers[finger].state,
                                                        &touchpads[index].fingers[finger].x,
                                                        &touchpads[index].fingers[finger].y,
                                                        &touchpads[index].fingers[finger].pressure);
                }
            }
        }
    }

    void PollState(){
        previousState = state;

        previousSensorState = sensorState;
        sensorState = SDLGamepadSensorState();
        state = {
            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_DPAD_UP),
            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_DPAD_DOWN),
            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_DPAD_LEFT),
            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_DPAD_RIGHT),

            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_A),
            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_B),
            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_X),
            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_Y),

            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_START),
            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_BACK),
            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_GUIDE),

            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_LEFTSTICK),
            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_RIGHTSTICK),

            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_PADDLE1),
            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_PADDLE2),
            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_PADDLE3),
            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_PADDLE4),

            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_TOUCHPAD),
            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_MISC1),

            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_LEFTSHOULDER),
            SDL_GameControllerGetButton(gamepad, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER),

            {
                float(SDL_GameControllerGetAxis(gamepad, SDL_CONTROLLER_AXIS_LEFTX)) / float(SDL_JOYSTICK_AXIS_MAX),
                float(SDL_GameControllerGetAxis(gamepad, SDL_CONTROLLER_AXIS_LEFTY)) / float(SDL_JOYSTICK_AXIS_MAX)
            },
            {
                float(SDL_GameControllerGetAxis(gamepad, SDL_CONTROLLER_AXIS_RIGHTX)) / float(SDL_JOYSTICK_AXIS_MAX),
                float(SDL_GameControllerGetAxis(gamepad, SDL_CONTROLLER_AXIS_RIGHTY)) / float(SDL_JOYSTICK_AXIS_MAX)
            },

            float(SDL_GameControllerGetAxis(gamepad, SDL_CONTROLLER_AXIS_TRIGGERLEFT)) / float(SDL_JOYSTICK_AXIS_MAX),
            float(SDL_GameControllerGetAxis(gamepad, SDL_CONTROLLER_AXIS_TRIGGERRIGHT)) / float(SDL_JOYSTICK_AXIS_MAX)
        };

        if (sensorEnabled){
            if (accelActive){
                SDL_GameControllerGetSensorData(gamepad, SDL_SENSOR_ACCEL, sensorState.Accelerometer, 3);
            }
            if (gyroActive){
                SDL_GameControllerGetSensorData(gamepad, SDL_SENSOR_GYRO, sensorState.Gyroscope, 3);
            }
        }
        pollTouchpad();
    }

    /// Apply haptics to the controller
    /// \param left value between 0.0f and 1.0f
    /// \param right value between 0.0f and 1.0f
    /// \param durationMS Duration in milliseconds
    void Rumble(float left, float right, Uint32 durationMS){
        if (hapticsSupported){
            SDL_GameControllerRumble(gamepad, 0xFFFF*left, 0xFFFF*right, durationMS);
        }
    }

    /// Apply haptics to the triggers
    /// \param left value between 0.0f and 1.0f
    /// \param right value between 0.0f and 1.0f
    /// \param durationMS Duration in milliseconds
    void RumbleTriggers(float left_trigger, float right_trigger, Uint32 durationMS){
        if (triggerHapticsSupported){
            SDL_GameControllerRumbleTriggers(gamepad, 0xFFFF*left_trigger, 0xFFFF*right_trigger, durationMS);
        }
    }

    /// Sets the controller LED's rgb values
    void SetLED(Uint8 r, Uint8 g, Uint8 b){
        SDL_GameControllerSetLED(gamepad, r, g, b);
    }
};

#endif // SM64_CONTROLLER_H
