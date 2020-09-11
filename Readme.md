# Conway's Game of Life

### By: Kaan Sinar

**The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves. It is Turing complete and can simulate a universal constructor or any other Turing machine.**

### Rules:

At each step in time(or tick), the following transitions occur:

1.Any live cell with fewer than two live neighbours dies, as if by underpopulation.

2.Any live cell with two or three live neighbours lives on to the next generation.

3.Any live cell with more than three live neighbours dies, as if by overpopulation.

4.Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

**compiling: make all**

**usage: "./cgol (seed) (ticks)"**
