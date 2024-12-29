# Snake game
This is simple snake game as mostly found in old Nokia phones. This game is developed in C++ as a command line game.

**Note:** This game is only for Windows Operating System.

**Note:** Use `compile.bat` to re-compile the code.
### How to download
1. Click `<> Code` green button and then select `Download ZIP`.
2. Open file location from `Downloads` > `open file location`.
3. Extract the ZIP file by right click and select `Extract all`.
4. Click on `snake.exe` to run the game.
### How to play
1. This game is played using W,A,S and D keys where W is for top, A for left, S for bottom and D for right.
2. If snake hits itself game will over.
3. If snake eats points it will increase its size.
### Customization
If you want to change some configuration here are some points that will help you customizing the game.

**Game Area:**

13. >const static int vert=10, hori=50;

In line number 13. It is possible to change the size of game area. `vert` means _verticle_ and `hori` means _horizontal_.

**Speed:**

144. >Sleep(100);

In line number 144. It is possible to change the speed using the number of milliseconds .

**Icon:**

To change the icon simply get an icon file and rename it `snake.ico` and paste it with same files and run `compile.bat`.