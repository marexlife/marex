COMPILER_PATH=./build/src/main/main
MAREX_FILE=./marex/Main.marex

cmake . -B build
cmake --build build
cd build/src/lex/tests && ctest . --output-on-failure

${COMPILER_PATH} ${MAREX_FILE}