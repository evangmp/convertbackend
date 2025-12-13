<a id="readme-top"></a>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

Caution : i'm still working on it.
Create under Windows OS. 
It can be used as a backend to compile some `.tex` files into (cropped) `.png`  in a selected folder.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With

* [CMake][CMake-url]
* [vcpkg][vcpkg-url]
* [ImageMagick][ImageMagick-url]
* [MickTex][MickTex-url]


<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GETTING STARTED -->
## Getting Started

There is some things that needs to be dl.

### Prerequisites

* C++ (v. 17 on my computer, if it works with another version tell me)

* CMake (dl)

* vcpkg (in the folder where you want to install it)
  ```sh
  git clone https://github.com/Microsoft/vcpkg.git
  bootstrap-vcpkg.bat
  ```

* ImageMagick (dl)

* MikTeX (dl)

### Installation

All the installations

1. Clone the repo (on the folder) :
   ```sh
   git clone https://github.com/evangmp/convertbackend.git
   ```
2. Install vcpkg dependance :
   ```sh
   vcpkg install http-lib
   ```
2. (bonus) Check :
   ```sh
   vcpkg list
   ```
2. (not working) try : (and if it still doesn't work idk)
   ```sh
   vcpkg install cpp-http-lib
   ```
3. Create a build folder (for CMake)
4. In the folder : CHECK THE PATHS in the CMakeLists.txt file !!!
   ```sh
   cd build
   cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/your/path/vcpkg/scripts/buildsystems/vcpkg.cmake
   ```
5. Again go back on the folder, you can try to debug it:
   ```sh
   cmake --build build --target convertbackend --config Debug
   cd build && .\Debug\convertbackend.exe
   ```
6. Again go back on the folder, you can try to release it: 
   ```sh
   cmake --build build --target convertbackend --config Release
   cd build && .\Release\convertbackend.exe
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- USAGE EXAMPLES -->
## Usage

If you have a frontend, you can send an http request to the port 9001 (if you didn't change it) with a string in the body like :
`\\documentclass{article} \\usepackage{bbold} \\pagestyle{empty} \\begin{document} test \\end{document}`

For example with React and Axios :
```js
    const httpTex = axios.create ({
        baseURL: "http://localhost:9001",
        headers: {
            "Content-type": "text/plain",
        },
    });

    const TexCompilation = async (texText: string) => {
        return await httpTex.post<string>("/compile", texText);
    };
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>


[CMake-url]: https://cmake.org/download/
[vcpkg-url]: https://vcpkg.io/en/
[ImageMagick-url]: https://imagemagick.org/script/download.php
[MickTex-url]: https://miktex.org/download