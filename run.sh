COMPILER_PATH=./build/src/main/main
MAREX_FILE=./marex/Main.marex

ctest --build-and-test . build --build-generator=Ninja

cmake . -B build
cmake --build build

${COMPILER_PATH} ${MAREX_FILE}