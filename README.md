# ChamberCrawler3000

A terminal based Dungeon Crawler made using C++, Object Oriented Programming, and Design Patterns. Advanced C++ material, such as smart pointers, and RAII was used for memory management and ensuring no memory leaks. Visitor, Observer (Publisher-Subscriber), and Model-View-Controller design patterns were used to simulate the combat between the player and enemies, movement of player and enemies, as well as the separation of a Display, Command Interpreter, and Gameplay Model. Using these design patterns, combined with Object Oriented Programming principles allowed for the implementation of many S.O.L.I.D design principles.

Game play is as follows.

Open a terminal and input the command "make" to compile the program and create an executable. The executable is named cc3k.
Your next input dictates your Player Race: (s)hade, (d)row, (v)ampire, (t)roll, or (g)oblin. Each has a set of abilities that can be found in the documents folder outlining game rules.

The player (represented by "@") has the following options:

- <no, so, ea, we, ne, nw, se, sw> as direction inputs for movement.
- u <direction> to use a potion in the direction specified.
- a <direction> to attack in the direction specified.
- r to restart the game.
- q to quit the game.
  
  Potions are represented by ? until consumed, after which they reveal themselves. Gold is represented by G. Enemies are repsented by the following letters:
  - "H" are Humans.
  - "W" are dwarfs.
  - "E" are elves.
  - "O" are orcs.
  - "M" are merchants.
  - "D" are dragons.
  - "L" are halflings.
  
  
  If you wish to implmenent your own map of chambers, you can do so by using the following tile representations:
  - "." for a floor tile that is free and unoccupied.
  - "|" and "-" for wall tiles.
  - "#" for passage tiles.
  - "+" for door tiles.
  - " " (space) for inaccessible locations, such as in between chambers.
  - "\" for exits (to the next floor).
  
  Create a text file with the above tile representations and when executing the game, add in the following command line flag: -f <File>
  
  If you wish to replay certain game states, you can input integer seeds using the flag: -s <Integer>
