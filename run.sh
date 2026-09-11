DIR=mrx

rm -rf build
rm -rf ${DIR}/main.c
cmake . -B build -GNinja
cmake --build build
cd ${DIR}
./../build/src/main/main main.mrx
clang main.c -o app
cd ..
chmod +x ${DIR}/app
./${DIR}/app
echo ""
