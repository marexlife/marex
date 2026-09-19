from subprocess import run

run(["cmake", ".", "-B", "build"], check=True)
run(["cmake", "--build", "build"], check=True)

