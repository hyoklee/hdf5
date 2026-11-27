# Running HDF5 tests in the iOS Simulator

`simrun.sh` runs an iOS Simulator program in a booted simulator, from the
caller's working directory, so it can be used as
`CMAKE_CROSSCOMPILING_EMULATOR`. `simlaunch.c` is a small helper it runs
inside the simulator to change to that directory before starting the program.
No code signing is needed for the simulator.

```sh
# 1. Boot a simulator
xcrun simctl boot "iPhone 16"

# 2. Build the helper for the simulator
xcrun -sdk iphonesimulator clang -target "$(uname -m)-apple-ios16.0-simulator" \
  config/ios/simlaunch.c -o /path/to/simlaunch
export SIMLAUNCH=/path/to/simlaunch

# 3. Configure, build and test
cmake -G Ninja -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_SYSROOT=iphonesimulator \
  -DCMAKE_OSX_ARCHITECTURES="$(uname -m)" -DCMAKE_OSX_DEPLOYMENT_TARGET=16.0 \
  -DCMAKE_CROSSCOMPILING_EMULATOR="$PWD/config/ios/simrun.sh" \
  -DBUILD_TESTING=ON -DTEST_SHELL_SCRIPTS=OFF -B build .
cmake --build build
cd build && ctest -j "$(sysctl -n hw.ncpu)"
```

`simrun.sh` reads these variables:

| Variable | Meaning | Default |
|---|---|---|
| `SIMLAUNCH` | Path to the `simlaunch` helper | `simlaunch` next to `simrun.sh` |
| `SIMRUN_DEVICE` | Simulator UDID or name | `booted` |
| `SIMRUN_LIBRARY_PATH` | `DYLD_LIBRARY_PATH` inside the simulator | the program's directory |

`HDF5_*`, `H5_*` and `srcdir` are passed to the program. `simctl` passes no
other host environment variables, and macOS removes `DYLD_*` variables before
the script runs, which is why `SIMRUN_LIBRARY_PATH` exists.

The CMake test definitions run every test program through
`CMAKE_CROSSCOMPILING_EMULATOR`, so other emulators (for example Wine or QEMU)
can be plugged in the same way. Only the iOS Simulator has been tested.
