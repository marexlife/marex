rm -rf build
rm -rf tests/main.c
cmake . -B build -GNinja
cmake --build build
cd mrx
./../build/src/main/main main.mrx
clang main.c -o app
cd ..
chmod +x tests/app
./tests/app
echo ""
