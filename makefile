.PHONY: BUILD TEST
.SILENT:

all: compile check

compile:
	cmake -S . -B build
	cmake --build build

check:
	cd build/test && ctest

run:
	cd build/example && ./main

clean:
	rm -r build/
