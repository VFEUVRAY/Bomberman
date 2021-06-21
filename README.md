# Bomberman
Bomberman backup and training files for school project

# DEVELOPPERS DOC

[Refer to the README in src folder for general informations about how the code works](./src/)

# Current state:

Should be good for submission of first step.<br>
Some things would be nice to add like bomb setting cooldown, or detection of already set bomb at current tile<br>
Not really a priority since not asked in the step goals for now.<br>

Should be no memory problems caused by our end, makefile is working<br>

# Current work:

Adding bomb handling functions.

Goal:

- Add support for direction key holding, currently is done via default key repetition which is not good. See SDLKEY_Scancodes stuff <b>- DONE with another method-</b><br>
- Initializing the bomb queue upon game startup (empty) <b>- DONE -</b><br>
- Implement bomb setting through button press <b>- DONE -</b><br>
- Calling a bomb creating function upon input, function has to get player coordinates, add bomb object to bomb queue, set appropriate timer <b>- DONE -</b><br>
- Add pass through bomb list at rendering, render bombs before player sprite, decrement each bomb's timer (do both at the same time to avoid multiple passes through) <b> - Partially done: 2 passes through per graphic refresh - </b><br>
- Add sprite loop handling to bomb objects, each bomb object must have its own sprite looping handler <b>- DONE -</b><br>

Other goal:

- Clean up character sprite looping (no need for globals, add necessary variables to player object) <b>- DONE -</b><br>
- New "player_t" might be created to seperate in a clearer manner the player object and its necessities <b>- DONE -</b><br>
- player object needs a second rectangle as source for sheet sprite cutting, and a loop index <b>- DONE -</b><br>

# Controls:<br>
Arrows for moving, B for setting bomb, escape for closing game.
