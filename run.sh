rm -rf build
rm -rf tests/main.c
cmake . -B build -GNinja
cmake --build build
cd examples
./../build/src/main/main main.mrx
clang main.c -o app
chmod +x app
./app
