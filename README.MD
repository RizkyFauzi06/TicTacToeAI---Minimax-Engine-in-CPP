# TicTacToeAI - Minimax Engine

A desktop-based Tic-Tac-Toe game developed in C++ using the Raylib graphics library. This project focuses on low-level matrix manipulation and features an unbeatable AI opponent powered by a custom-built Minimax algorithm. 

## Features
* **VS AI Mode:** Play against an intelligent computer opponent. The AI utilizes the Minimax decision rule to evaluate all possible future moves, ensuring it never loses.
* **2 Player Mode:** Standard local multiplayer functionality.
* **Data-Oriented Grid System:** Implements strict `[Row][Column]` memory addressing for accurate translation between Cartesian screen coordinates (X/Y) and the 2D memory array.
* **State Machine:** Clean separation of game states (Menu, Playing, Game Over) to manage the rendering and logic pipelines efficiently.

## Tech Stack
* **Language:** C++
* **Graphics & Input:** Raylib
* **AI Architecture:** Minimax Algorithm (Zero-Sum Game Theory)

## Asset Dependencies
To run this application successfully, the following media assets must be placed in the same root directory as the executable file. 

* **Textures:** * `X.png` (Player 1 symbol)
    * `O.png` (Player 2 / AI symbol)
* **Audio:**
    * `place.mp3` or `place.wav` (Sound effect for placing a mark)
    * `GameOver.mp3` or `GameOver.wav` (Sound effect triggered upon win/loss/draw)

*(Note: Ensure the audio extensions in your root folder match the extensions called inside the `LoadSound()` function in your source code).*

## Installation and Compilation

1.  **Prerequisites:** Ensure you have the [Raylib C++ Compiler environment](https://www.raylib.com/) installed and configured on your system (MinGW for Windows).
2.  **Setup Directory:**
    Create a project folder named `TicTacToeAI`. Place `TicTacToe.cpp` and all required asset dependencies (`.png` and audio files) into this folder.
3.  **Open Terminal:**
    Navigate to the project directory:
    ```bash
    cd path/to/your/TicTacToeAI
    ```
4.  **Compile the Source Code:**
    Run the following command to compile the C++ file into an executable binary:
    ```bash
    g++ TicTacToe.cpp -o TicTacToe.exe -O1 -Wall -std=c++11 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
    ```
    *(If you are using a configured VS Code environment, you can alternatively use your build task shortcut, e.g., `Ctrl+Shift+B`).*
5.  **Run the Game:**
    Execute the binary explicitly from the terminal to ensure relative paths for assets are loaded correctly into VRAM/RAM:
    ```bash
    .\TicTacToe.exe
    ```

## Controls
* **Mouse Left Click:** Navigate the menu and place the X/O symbols on the grid.

---
*Developed as an exercise in C++ matrix manipulation and AI logic implementation.*