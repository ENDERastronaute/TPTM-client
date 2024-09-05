# TPTM Client

TPTM is my 3rd year school project, it is a way for teachers to send and retrieve files from students.

This is the client socket, made to be installed on all students' workstation.

## Debug

Compile in debug mode using :

```shell
cmake.exe -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=E:/apps/jetbrains/CLion/bin/ninja/win/x64/ninja.exe -G Ninja -S E:\projects\tptm\backend -B E:\projects\tptm\backend\cmake-build-debug
```

## Release

Or in release mode using :

```shell
cmake.exe --build E:\projects\tptm\backend\cmake-build-release --target backend -j 6
```