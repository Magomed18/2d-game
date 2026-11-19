# Carrot Garden

A small C++/SFML gardening game. Prepare soil, plant seeds, and harvest five carrots.


## Requirements

CMake 3.28+, Git, Ninja, and a C++17 compiler (GCC or Clang).
Internet access is required for the first configuration: CMake downloads SFML 3.1.0 automatically.

## Build and run

### Windows (PowerShell)

Run these commands from the project root:

```powershell
cmake -S . -B build/ninja -G Ninja -DCMAKE_CXX_COMPILER=g++
cmake --build build/ninja --target main
.\build\ninja\bin\main.exe
```

### Linux / macOS (Bash)

On Ubuntu/Debian, install the build tools and SFML dependencies first:

```bash
sudo apt update
sudo apt install build-essential cmake git ninja-build \
    libxrandr-dev libxcursor-dev libxi-dev libudev-dev \
    libfreetype-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev
```

Check `cmake --version`: if your distribution provides an older version, install CMake 3.28+ separately.
Other Linux distributions need equivalent packages; see the [SFML build guide](https://www.sfml-dev.org/tutorials/3.1/getting-started/cmake/).

On macOS, install Xcode Command Line Tools and, with [Homebrew](https://brew.sh/) installed, the build tools:

```bash
xcode-select --install
brew install cmake ninja git
```

Then, on either Linux or macOS, run from the project root:

```bash
cmake -S . -B build/native -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build/native --target main
./build/native/bin/main
```

Use a separate build folder for each OS/compiler. Linux/macOS instructions have not been tested on those systems yet.

After code changes, repeat only the build and run commands.
Keep the `assets` folder in the project: this build loads assets from its original source location.

## Controls

- WASD / arrow keys: move.
- E: prepare, plant, or harvest the plot under your character's feet.
- Q: toggle the inventory bar.
- Escape: quit.
