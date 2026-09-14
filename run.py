from subprocess import run
from enum import Enum
import os

class BuildType(Enum):
    RELEASE = 0
    DEBUG = 1

def build_type_str(BUILD_TYPE: BuildType) -> str:
    match BUILD_TYPE:
        case BuildType.RELEASE:
            return "Release"
        case BuildType.DEBUG:
            return "Debug"

BUILD_TYPE=BuildType.RELEASE

BUILD_TYPE_STRING = build_type_str(BUILD_TYPE)

run(["cmake", ".", "-B", "build", f"-DCMAKE_BUILD_TYPE={BUILD_TYPE_STRING}"], check=True)
run(["cmake", "--build", "build"], check=True)

if os.name == 'nt': 
    run([f"./build/src/main/Debug/main.exe"])
else:
    run(["./build/src/main/main"])