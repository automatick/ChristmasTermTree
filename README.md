# Tree Animation with NCurses

This project is a simple implementation of a Christmas tree animation using the **ncurses** library in C++. The tree is drawn dynamically with random decorations (garlands) that light up and change colors.

## Features

- **Dynamic Christmas tree drawing**: A tree is drawn with a trunk, foliage, and a random pattern.
- **Garlands**: Lights randomly appear and disappear on the tree with different colors.
- **Adaptability**: Supports different terminal sizes and adjusts the tree's dimensions accordingly.
- **Color support**: Uses a wide range of colors, taking advantage of 256-color terminals if available.

## Requirements

- A system with `ncurses` library installed.
- A compiler with C++ support (e.g., `g++`).

## How to Compile

Run the following commands to build the program using CMake:

```bash
mkdir build
cd build
cmake ..
make
```

## How to Run

Run the compiled program in your terminal:

```bash
./tree
```

## Code Overview

### Functions

1. **`init()`**:
   - Initializes the `ncurses` environment.
   - Sets up colors for the terminal and determines compatibility.

2. **`end()`**:
   - Ends the `ncurses` session safely.

3. **`draw_rectangle()`**:
   - Draws a filled rectangle with specified dimensions and color pair.

4. **`draw_trunk()`**:
   - Draws the trunk of the tree.

5. **`draw_tree()`**:
   - Dynamically draws the tree foliage with randomized patterns.

6. **`draw_garland()`**:
   - Adds animated garlands to the tree. Lights appear and disappear randomly, changing colors dynamically.

7. **`main()`**:
   - Initializes the tree.
   - Prepares the symbols and colors for restoring the tree after garlands.
   - Handles memory allocation and cleanup.

### Key Features in Code

- **Tree Symbols**:
  - The tree's structure is stored in a 2D array to allow restoring the state after garland updates.

- **Garland Animation**:
  - Uses `napms()` to create a delay between frames.
  - Randomizes the positions and colors of lights for a dynamic effect.

## Terminal Compatibility

- The program dynamically adjusts to the terminal size, making it versatile.
- If your terminal supports 256 colors, the program uses an enhanced color palette. Otherwise, it falls back to standard colors.

## Troubleshooting

1. **Colors not working properly**:
   - Ensure your terminal supports 256 colors. Use a command like `echo $TERM` to verify. For full color support, use `xterm-256color`.

2. **Weird artifacts on the tree**:
   - Ensure you are using a modern terminal emulator.
   - If the issue persists, try reducing the randomness in `draw_tree()` or `draw_garland()`.

## Future Improvements

- Add more customizable decorations (e.g., stars or ornaments).
- Implement user input to control animation speed or tree size.
- Add snowfall animation.

## License

This project is licensed under the MIT License. Feel free to use, modify, and distribute the code.

---

Enjoy your animated Christmas tree! 🎄

