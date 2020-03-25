import time
import inputs
from victor import Brain

brain = Brain(1)

print(inputs.devices.gamepads)

pads = inputs.devices.gamepads

if len(pads) == 0:
    raise Exception("Couldn't find any Gamepads!")

action_space = {
    'ABS_HAT0X 0':  "STOP",
    'ABS_HAT0X -1': "TURN_LEFT",
    'ABS_HAT0X 1':  "TURN_RIGHT",
    'ABS_HAT0Y 1':  "MOVE_BACKWARD",
    'ABS_HAT0Y -1': "MOVE_FORWARD",
    'ABS_HAT0Y 0':  "STOP",
    'BTN_TL 1':     "OPEN_CLAW",
    'BTN_TR 1':     "CLOSE_CLAW",
    'BTN_Z 1':      "CLOSE_FLIPPERS",
    'BTN_WEST 1':   "OPEN_FLIPPERS",
    'BTN_EAST 1':   "RAISE_ARM",
    'BTN_C 1':      "LOWER_ARM",
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
            if 'EAST' in key or 'C' in key:
                ard = "0"
            brain.send_act(action, ard)