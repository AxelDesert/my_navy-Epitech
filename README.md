# User documentation of my_navy project

The my_navy project is a program that make two terminals communicate with signals to play the famous battleships game.

## Requirements

The two players need a .txt file which has 4 lines with : [boat_length]:[first_pos]:[last_pos]
Example :
```
2:C1:C2
3:D4:F4
4:B5:B8
5:D7:H7
```

## Installation

1) ```
   git clone git@github.com:EpitechPromo2028/B-PSU-100-LIL-1-1-navy-axel.desert.git
   ```
2) ```
   make
   ```
3) To start a game :
   ```
   ./my_navy navy_positions
   ```
4) To join a game, enter the pid display on the screen which created the game :
   ```
   ./my_navy [creator_pid] navy_positions
   ```
Then the game is launched. The two players need to enter positions to find the navies of the enemy (the position must be between A1 and H8).
If a player has sank every boats of his enemy, the program display "I won" and return 0, therefore the other player's screen display "Enemy won"
and return 1.
