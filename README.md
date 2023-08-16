# WasmEdge_ffmpeg_Plugin
This repository contains the definition of a host function that is built into a wasmedge plugin for a few ffmpeg functions.

## Build
This plugin will be built into a shared library(".so" in Linux), and it will be available as a loadable plugin for WasmEdge.

### Dependencies
The build depends on these tools:
```cmake```, ```gcc```

It depends on the availability of these shared libraries:
wasmedge: ```libwasmedge```
ffmpeg: ```libavformat```

### Usage and Testing
To test this functionality of this plugin, you need to have WasmEdge installed
