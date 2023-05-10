rm build/ -rf
mkdir build
cd build
em++ ../src/tetris.cpp -std=c++11 -s WASM=1 -s USE_SDL=2  -o main.js || exit 1
mv main.js ../web/gen/
mv main.wasm ../web/gen/