# MyCompressor

## Overview

MyCompressor is a simple command-line file compression tool built in C++ using miniz for ZIP file support.

## Features

- Compress files to ZIP format
- Decompress ZIP files
- Help command

## Usage

1. Run the application:	MyCompressor.exe

2. Type commands:
   - `compress <input_file> <output_file.zip>` - Compress a file to ZIP format.
   - `decompress <input_file.zip> <output_file>` - Decompress a ZIP file.
   - `help` - Display available commands.
   - `exit` - Exit the application.

## Build Instructions

To build the project using Makefile, run:
```
make
```
To clean up:
```
make clean
```
