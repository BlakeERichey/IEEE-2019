import time
from victor import Brain

brain = Brain(1)

actions = [
  'MOVE_FORWARD',  'STOP',
  'MOVE_BACKWARD', 'STOP',
  'TURN_LEFT',     'STOP',
  'TURN_RIGHT',    'STOP',
]

for action in actions:
  brain.send_act(action)
  time.sleep(3)

print("Movement complete")