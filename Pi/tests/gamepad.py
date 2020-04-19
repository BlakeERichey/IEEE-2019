import time
import inputs
from victor import Brain

brain = Brain(2)

print(inputs.devices.gamepads)

pads = inputs.devices.gamepads

if len(pads) == 0:
    raise Exception("Couldn't find any Gamepads!")

action_space = {
    'ABS_HAT0X 0':  "STOP",
    'ABS_HAT0X -1': "TURN_LEFT",        #LEft  D Pad
    'ABS_HAT0X 1':  "TURN_RIGHT",       #Right D Pad
    'ABS_HAT0Y 1':  "MOVE_BACKWARD",    #Down  D Pad
    'ABS_HAT0Y -1': "MOVE_FORWARD",     #Up    D Pad
    'ABS_HAT0Y 0':  "STOP",
    'BTN_TL 1':     "OPEN_CLAW",        #RIGHT BUMPER
    'BTN_TR 1':     "CLOSE_CLAW",       #LEFT BUMPER
    'BTN_SOUTH 1':  "CLOSE_FLIPPERS",   #A
    'BTN_EAST 1':   "OPEN_FLIPPERS",    #B
    'BTN_NORTH 1':  "RAISE_ARM",        #X
    'BTN_WEST 1':   "LOWER_ARM",        #Y
}

print("Ready to receive")
while True:
    events = inputs.get_gamepad()
    for event in events:
        # print(event.ev_type, event.code, event.state)
        key = event.code + ' ' + str(event.state)
        action = action_space.get(key)
        print('key', key, 'Action', action)
        if action is not None:
            ard = "0"
            if "ABS" not in key:
                ard = "1"
            brain.send_act(action, ard)