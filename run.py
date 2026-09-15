from subprocess import run
import os

try:
    run(["cmake", ".", "-B", "build", "-GNinja"], check=True)
except:
    run(["cmake", ".", "-B", "build"], check=True)

run(["cmake", "--build", "build"], check=True)

ARGUMENTS=["./mrx/main.mrx"]

if os.name == 'nt': 
    run([f"./build/src/main/Debug/main.exe"] + ARGUMENTS)
else:
    run(["./build/src/main/main"] + ARGUMENTS)