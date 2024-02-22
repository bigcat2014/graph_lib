# Template Graph Library
## Prerequisites
- cmake
- libgtest-dev

## Building
### Debug
From the root of the project, run the following command:
```bash
cmake --build build --config Debug --target all --
```

### Release
From the root of the project, run the following command:
```bash
cmake --build build --config Release --target all --
```

## Installing
### Debug
From the root of the project, run the following command:
```bash
cmake --build build --config Debug --target install --
```

### Release
From the root of the project, run the following command:
```bash
cmake --build build --config Release --target install --
```

## Running tests
From the root of the project, run the following commands:
```bash
cd build
ctest -V
```

## Running
From the root of the project, run the following command:
```bash
./install/bin/graph_lib
```