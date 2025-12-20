# Mini-project-ALGO

A small C project implementing the Wordle game and two solver strategies.

## Project Structure

- `main.c` – Main program with menu  
- `the_game.c` – Game logic  
- `solver.c` – Solver 1 (frequency-based)  
- `solver2.c` – Solver 2 (unique-letter strategy)  
- `wordle.h` – Header file  
- `data.txt` – Dictionary file  

## How to Build and Run

```sh
git clone https://github.com/zakariamadi652/Mini-project-ALGO
cd Mini-project-ALGO
gcc main.c the_game.c solver.c solver2.c -o game
./game
