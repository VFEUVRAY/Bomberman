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
- Add sprite loop handling to bomb objects, each bomb object must have its own sprite looping handler <b>- DONE -</b><br>*
- Set a bomb limit for the player + put a bomb reloading cooldown<br>

Other goal:

- Clean up character sprite looping (no need for globals, add necessary variables to player object) <b>- DONE -</b><br>
- New "player_t" might be created to seperate in a clearer manner the player object and its necessities <b>- DONE -</b><br>
- player object needs a second rectangle as source for sheet sprite cutting, and a loop index <b>- DONE -</b><br>
- Work on a different looping mechanism for both bomb and player sprite: bomb should loop in a "boomerang" fashion, player should go back to idle frame before going to its second step frame (all this is pretty optional) <br>
- Refactor the game.c file, steer away from switch based input handling to while + function pointers maybe. Will probably need to move bomb list pointer to player structure instead of game structure, will see<br>
- Implement an explosion sprite + maybe start implementing explosion related interaction (first could be player dying when in explosion diameter)
- Probably add player HP in concordance to previous point (3 lives)<br>
- Begin network implementation<br>


# Controls:<br>
Arrows for moving, B for setting bomb, escape to close game.
<b>debug controls:</b><br>
D to display player coordinates in terminal, R to reset player to original position.<br>
(Will probably work on a solution to display coordinates in game later)
