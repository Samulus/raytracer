# raytracer
![](images/rbg_mirror.png)

### Build Instructions with `vcpkg` / `cmake`
0. Setup [vcpkg](https://github.com/microsoft/vcpkg#quick-start)
1. `vcpkg install glfw3 glew opengl glm spdlog doctest --triplet x64-windows`
2. `vcpkg install lua lua[cpp] --recurse --triplet x64-windows-static`
2. `vcpkg integrate install`, save the toolchain file argument it spits out
3. `mkdir build && cmake .. -DCMAKE_TOOLCHAIN_FILE=…`
4. `make && ./raytrace_release`