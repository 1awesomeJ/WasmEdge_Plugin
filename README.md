# WasmEdge_ffmpeg_Plugin
## Overview
This repository contains a WasmEdge plugin that exposes a host function for interacting with FFmpeg.
The plugin is built as a shared library and can be dynamically loaded into WasmEdge.

## Prerequisites
### Tools required
* .Cmake
* . gcc

### Libraries required
* .WasmEdge('libwasmedge')
* .ffmpeg('libavformat')

## Building the plugin
### Linux

1. **Navigate to the host_function directory**

```cd host_function```

2. **Compile the host function into a shared library**

```gcc -shared -o wasmedge_ffmpeg_plugin.so -fPIC avformat_host_function.c -lavformat -lwasmedge```

This will generate a shared library named ```wasmedge_ffmpeg_plugin.so```

### Usage and Testing
To test this functionality of this plugin, you need to have WasmEdge installed.
The function will be called by a WasmEdge VM instance.
