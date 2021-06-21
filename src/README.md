# Bomberman Dev Basic doc

Can output multiple strings on stderr via my_putCharArray function.<br>
Cast the expression is the following way: (char const *[]){"string1", "string2", "string3", NULL}<br>
<b>Be sure to add a NULL at the end of the array.</b><br>
Only send file descriptor for stdout and stderr for now (1 and 2).<br>

Animation is handlded through sheet. Whole sheet is loaded in character structure.<br>
Source rectangle is adjusted depending on loop status. very rough and dirty for now.<br>
Will polish it up later on<br>

Moving and collisions are handled in game_move_player<br>
The calculus is ugly but it's basically a brancheless condition nested in the calculus (makes sure to no go over set bounds)<br>

Animation transition for bombs is handled in tick_bombs()(bombs.c)<br>
Whole sprite sheet is loaded upon game startup<br>
Is made so that a new frame is set only every 3 loops (about 3 * 16 ms <==> 3 frames at 60 fps)<br>
Every bomb queue interaction is handled via pointer to the linked list so we can standardize all list operations (save first element, do things, set queue back to first element)<br>
Bombs are placed on the same tile as character, character coordinates are passed to bomb adding function <br>
Bomb adding function also adds new node to Bomb queue (add_bomb (bombs.c))<br>
One pass through bomb queue at every graphical refresh to display all of them<br>


# Current state:

Should be good for submission of first step.<br>
Some things would be nice to add like bomb setting cooldown, or detection of already set bomb at current tile<br>
Not really a priority since not asked in the step goals for now.<br>

# Current work:

Adding bomb handling functions.

Goal:

- Add support for direction key holding, currently is done via default key repetition which is not good. See SDLKEY_Scancodes stuff<br>
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
Arrows for moving, B for setting a bomb on the ground, escape for closing game.
