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

First build issues:

After git clone
```
git submodule update --init --recursive
```

For Ubuntu, please install the below things:
```
sudo apt-get update && sudo apt-get install build-essential
```

Cannot find X11
```
sudo apt-get install libx11-dev
```

RandR not found
```
sudo apt-get install xorg-dev libglu1-mesa-dev
```