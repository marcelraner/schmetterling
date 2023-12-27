# Project: Schmetterling

## Preparation

### Windows

Install the following applications:

- vscode
- cmake
- msys2

Then in the msys2 cli install the following packages:

```bash
Update MSYS2:
$ pacman -Syuu
$ pacman -S git
$ pacman -S make
$ pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
```

Add the following paths need to be added to the `Path` environment variable:
- `C:\msys64\usr\bin`
- `C:\msys64\ucrt64\bin`


## Modular architecture

Application {
    RenderTriggerer
    UpdateTriggerer
    EventLoop
    RenderEventHandler -> Render e.g. curser and spaceship
    UpdateEventHandler
}
