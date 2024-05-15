.PHONY: BUILD TEST
.SILENT:

all:
	cmake -S . -B build
	cmake --build build
	cd build/test && ctest