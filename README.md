# Enemy Friendly Fire

SFSE plugin that enables friendly fire for NPCs

## Requirements
* [CMake](https://cmake.org/)
	* Add this to your `PATH`
* [PowerShell](https://github.com/PowerShell/PowerShell/releases/latest)
* [Vcpkg](https://github.com/microsoft/vcpkg)
	* Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
* [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
	* Desktop development with C++
* [CommonLibSF](https://github.com/Starfield-Reverse-Engineering/CommonLibSF)
	* Add this as as an environment variable `CommonLibSFPath`

## Register Visual Studio as a Generator
* Open `x64 Native Tools Command Prompt`
* Run `cmake`
* Close the cmd window

## Building
```
git clone https://github.com/powerof3/EnemyFriendlyFireSFSE.git
cd EnemyFriendlyFireSFSE
cmake --preset vs2022-windows-vcpkg-sf
cmake --build build --config Release
```

## License
[MIT](LICENSE)
