from subprocess import run
import os

compiler_path="./build/src/main"
marex_file="marex/Main.marex"

run(["cmake", ".", "-B", "build"], check=True)
run(["cmake", "--build", "build"], check=True)

if os.name == 'nt':
    run([f"{compiler_path}/Debug/main.exe", marex_file])
else:
    run([f"{compiler_path}/main", marex_file])