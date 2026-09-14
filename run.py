from subprocess import run
import os

run(["cmake", ".", "-B", "build"], check=True)
run(["cmake", "--build", "build"], check=True)

if os.name == 'nt': 
    run(["./build/src/main/Debug/main.exe"])
else:
    run(["./build/src/main/main"])