from subprocess import run

run(["rm", "-rf", "build"])
run(["cmake", ".", "-B", "build"])
run(["cmake", "--build", "build"])
run(["./build/src/main/main", "./marex/main.marex"])
