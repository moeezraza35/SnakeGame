windres resource.rc -O coff -o resource.res
g++ snake.cpp -o snake.exe resource.res