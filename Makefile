.PHONY: all
all: clean configure build test

.PHONY: clean
clean:
	rm -rf ./build/

.PHONY: configure
configure:
	cmake --preset=debug

.PHONY: build
build:
	cmake --build --preset=debug

.PHONY: test
test:
	ctest --preset=debug

.PHONY: run_server
run_server:
	cp ./extern/SDL2-2.28.5/x86_64-w64-mingw32/bin/SDL2.dll ./build/debug/server
	cp ./extern/SDL2_net-2.2.0/x86_64-w64-mingw32/bin/SDL2_net.dll ./build/debug/server
	./build/debug/server/server

.PHONY: run_client
run_client:
	cp ./extern/SDL2-2.28.5/x86_64-w64-mingw32/bin/SDL2.dll ./build/debug/client
	cp ./extern/SDL2_net-2.2.0/x86_64-w64-mingw32/bin/SDL2_net.dll ./build/debug/client
	./build/debug/client/client
