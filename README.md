Right now there are three benchmarks:

* Cache effects via POPCNT in `opt/cache.cpp`
* Superscalar execution via double sum in `noopt/superscalar.cpp`
* Branch Prediction/Misprediction in `noopt/branches.cpp`

Use CMake to build this.
Google benchmark is included as submodule.
So, use `git submodule init && git submodule update` after initial clone.

CMake is invoked like `cmake -DBUILD_TYPE=Release ../cpu-effects-bench` from 
a directory that lies on the same level with the cloned repository.
CMake do not support in source builds.
After that just do `make` and run benchmarks.

`opt` contains example that can be compiled with optimizer, `noopt` contains examples that
are more visible when compiled without optimizer.

[Presentation](https://drive.google.com/file/d/0B6lLc0s9k8GyVTFxSkZLUkw2MkE/view?usp=sharing)
