# Bomberman Dev Basic doc

Can output multiple strings on stderr via my_putCharArray function.
Cast the expression is the following way: (char const *[]){"string1", "string2", "string3", NULL}
Be sure to add a NULL at the end of the array.
Only send file descriptor for stdout and stderr for now (1 and 2).

Animation is handlded through sheet. Whole sheet is loaded in character structure.
Source rectangle is adjusted depending on loop status. very rough and dirty for now.

Current work:

Adding bomb handling functions.

Goal:

- Initializing the bomb queue upon game startup (empty)<br>
- Implement bomb setting through button press<br>
- Calling a bomb creating function upon input, function has to get player coordinates, add bomb object to bomb queue, set appropriate timer<br>
- Add pass through bomb list at rendering, render bombs before player sprite, decrement each bomb's timer (do both at the same time to avoid multiple passes through)<br>
- Add sprite loop handling to bomb objects, each bomb object must have its own sprite looping handler<br>

Other goal:

- Clean up character sprite looping (no need for globals, add necessary variables to player object)<br>
- New "player_t" might be created to seperate in a clearer manner the player object and its necessities<br>
- player object needs a second rectangle as source for sheet sprite cutting, and a loop index<br>

Controls:
Arrows for moving, escape for closing game.