.PHONY: configure
configure:
	cmake --preset=debug

.PHONY: build
build:
	cmake --build --preset=debug

.PHONY: clean
clean:
	rm -rf ./build/

.PHONY: test
test:
	ctest --preset=test-all

.PHONY: run
run:
	cp ./extern/SDL2-2.28.5/x86_64-w64-mingw32/bin/SDL2.dll ./build/debug/
	./build/debug/sample
