.PHONY: all
all: clean configure build test

.PHONY: clean
clean:
	rm -rf ./build/

.PHONY: configure
configure: clean
	cmake --preset=debug

.PHONY: build
build:
	cmake --build --preset=debug

.PHONY: test
test:
	ctest --preset=debug

.PHONY: test_renderer
test_renderer:
	ctest --preset=debug -R test_renderer

.PHONY: build_again
build_again:
	cmake --build --preset=debug --target client

.PHONY: samples
samples: configure
	cmake --build --preset=debug --target sample_event_trigger_listener_threads

.PHONY: run_again
run_again:
	cp ./extern/SDL2-2.28.5/x86_64-w64-mingw32/bin/SDL2.dll ./build/debug/and_again
	cp ./extern/SDL2_net-2.2.0/x86_64-w64-mingw32/bin/SDL2_net.dll ./build/debug/and_again
	./build/debug/and_again/client

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

.PHONY: run_wait_for_events_sample
run_wait_for_events_sample:
	cp ./extern/SDL2-2.28.5/x86_64-w64-mingw32/bin/SDL2.dll ./build/debug/samples/wait_for_events_sample
	cp ./extern/SDL2_net-2.2.0/x86_64-w64-mingw32/bin/SDL2_net.dll ./build/debug/samples/wait_for_events_sample
	./build/debug/samples/wait_for_events_sample/wait_for_events_sample

.PHONY: run_client2
run_client2:
	cp ./extern/SDL2-2.28.5/x86_64-w64-mingw32/bin/SDL2.dll ./build/debug/client2
	cp ./extern/SDL2_net-2.2.0/x86_64-w64-mingw32/bin/SDL2_net.dll ./build/debug/client2
	./build/debug/client2/client2
