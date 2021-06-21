# Bomberman Dev Basic doc

Can output multiple strings on stderr via my_putCharArray function.
Cast the expression is the following way: (char const *[]){"string1", "string2", "string3", NULL}
Be sure to add a NULL at the end of the array.
Only send file descriptor for stdout and stderr for now (1 and 2).

Animation is handlded through sheet. Whole sheet is loaded in character structure.
Source rectangle is adjusted depending on loop status. very rough and dirty for now.

Controls:
Arrows for moving, escape for closing game.