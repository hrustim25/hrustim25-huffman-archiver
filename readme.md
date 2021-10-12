# Huffman Archiver

Last release version 1.0.0


## Description

Archiver is based on the [Huffman coding algorithm](https://en.wikipedia.org/wiki/Huffman_coding).
Algorithm provides compression and decompression of any kind of file,
but it is especially efficient with text file formats. For other types of
files (especially for large ones) compression could be inefficient
due to inner construction of the algorithm.

## Benchmarks

The benchmark uses compiler GCC v9.3.0 on Linux 64-bits (Ubuntu 20.04). The reference system uses a Core i3-8130U CPU @ 2.2GHz. All evaluations made in single-thread mode.
|  Compression type     | Ratio   | Compression | Decompression |
|  ----------           | -----   | ----------- | ------------- |
|  Text                 |  1.548  |   2.8 MB/s  |    1.1 MB/s   |
|  Video                |  1.001  |   3.2 MB/s  |    3.3 MB/s   |
|  Image                |  1.012  |   2.7 MB/s  |    1.0 MB/s   |
|  Text       (-O2)     |  1.548  |   3.2 MB/s  |    1.3 MB/s   |
|  Video      (-O2)     |  1.001  |     5 MB/s  |    6.5 MB/s   |
|  Image      (-O2)     |  1.012  |   2.9 MB/s  |    1.1 MB/s   |

## Installation

You need to install

[Cmake](https://en.wikipedia.org/wiki/CMake):
```
sudo apt install cmake
```

[Make](https://en.wikipedia.org/wiki/Make_(software)):
```
sudo apt install make
```

### Building
From the project directory run:
```
    mkdir build
    cd build
    cmake ..
    make
```

## Use guide
You can find command list and their description using:
```
./archiver -h
```
