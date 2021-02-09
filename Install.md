Win10 Build

In Developer PowerShell for VS 2019
```
cd Build
cmake -G "Visual Studio 16 2019" ..
MSBuild.exe .\Glitter.sln
```

Linux Build

```
mkdir build
cd build
cmake ..
make -j7
cd gl_renderer
./gl_renderer
```