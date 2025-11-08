.PHONY: BUILD TEST
.SILENT:

test: clean compile check

compile:
	cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build
	cmake --build build

check:
	cd build/test && ctest

main: clean compile
	cd build/example && ./main

debug: 
	cd build/example && gdb main

valgrind: 
	cd build/example && valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./main


clean:
	@if test -d build/; then \
        rm -rf build/; \
    fi
