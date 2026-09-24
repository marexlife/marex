COMPILER_PATH=./build/src/main/main
MAREX_FILE=./marex/Main.marex

ctest --build-and-test . build

cmake . -B build
cmake --build build

${COMPILER_PATH} ${MAREX_FILE}