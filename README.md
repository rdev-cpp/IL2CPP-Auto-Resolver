# IL2CPP Auto

C++ library for automatic discovery and caching of IL2CPP function addresses in Unity games.

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)](https://windows.com/)

## Features

- **Automatic IL2CPP module detection** - Finds GameAssembly.dll or UnityPlayer.dll
- **Smart function caching** - Caches all IL2CPP function addresses on initialization  
- **Template-based API** - Type-safe function access with simple templates
- **Zero manual work** - No more pattern scanning or address hunting
- **Broad compatibility** - Works with most IL2CPP Unity versions
- **Lightning fast** - Instant function lookup after initialization

## Quick Start

```cpp
#include "il2cpp_auto.hpp"

// Initialize library (does all the heavy lifting)
if (IL2CPP_Auto::CAutoIL2CPP::Initialize()) {
    // Get any IL2CPP function with full type safety
    auto class_from_name = IL2CPP_Auto::CAutoIL2CPP::GetFunction<
        void*(*)(const char*, const char*)>("il2cpp_class_from_name");
    
    auto resolve_icall = IL2CPP_Auto::CAutoIL2CPP::GetFunction<
        void*(*)(const char*)>("il2cpp_resolve_icall");
    
    // Use the functions immediately
    if (class_from_name && resolve_icall) {
        void* camera_class = class_from_name("UnityEngine", "Camera");
        void* get_main = resolve_icall("UnityEngine.Camera::get_main");
    }
}
