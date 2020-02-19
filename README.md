# C++ Codebase Build Instruction

## Dependencies
* CMake >= 3.13
* Flex >= ???
* Bison >= ???
* git >= ???

## Arch Linux/Manjaro Linux
`sudo pacman -S flex bison cmake git`

`cd ~`

`git clone https://github.com/lnikon/zsim ~/`

`cd zsim`

`mkdir build && cd build`

For Debug Build Use

`cmake -DCMAKE_BUILD_TYPE=Debug ..`

Otherwise

`cmake ..`

`make`

## Debian
`sudo apt-get update`

`sudo apt-get install git cmake build-essential flex bison`

`cd ~`

`git clone https://github.com/lnikon/zsim ~/`

`cd zsim`

`mkdir build && cd build`

For Debug Build Use

`cmake -DCMAKE_BUILD_TYPE=Debug ..`

Otherwise

`cmake ..`

`make`
