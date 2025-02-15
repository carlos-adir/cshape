.PHONY: BUILD TEST
.SILENT:

test: clean compile check

compile:
	cmake -S . -B build
	cmake --build build

check:
	cd build/test && ctest

run:
	cd build/example && ./main

main: clean compile run

clean:
	@if test -d build/; then \
        rm -rf build/; \
    fi
