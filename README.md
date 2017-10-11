# cubetac: A 3D version of Tic-Tac-Toe

A very simple game I put together in a couple of weeks. It can be played with a friend over the internet, although you'll have to do the port forwarding yourself (port used is 53000). This is my first C++ project, so expect it to be buggy!

## How to play
If playing online, one of the players has to select SERVER and the other CLIENT. If playing offline, simply select OFFLINE.

When it's your turn, click on a cell to place your symbol in it; player 1 is circles and player 2 is crosses. The first player to form a line of 4 of their symbols wins.

The four grids represent the four layers of a 4x4x4 cube. Any line of four symbols counts, be it horizontal (all on one grid), vertical (same space in all four grids), or diagonal between two corners of the cube. So, for example, if there are circles on the bottom left corner of all four grids, that forms a vertical line on a side of the cube.

(For now, the only way to restart the game is to close it and open it again. To be implemented, maybe?)

## Download

Latest version can be found [here](https://github.com/HikaruAikawa/cubetac/releases).

## Credit

The person who told me about this game (in paper format) was [Sora Amano](https://twitter.com/soraamano_). There's probably another version of it somewhere, but I don't know of it.

This game was made with the [SFML](https://www.sfml-dev.org/) library.
