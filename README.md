# IL2CPP Auto

C++ library for automatic discovery and caching of IL2CPP function addresses in Unity games.

## Features

- Automatic IL2CPP module detection
- Caches all IL2CPP function addresses on initialization
- Simple template-based API for function access
- No manual address hunting required
- Works with most IL2CPP Unity versions

## Usage

```cpp
#include "il2cpp_auto.hpp"

// Initialize library
if (IL2CPP_Auto::CAutoIL2CPP::Initialize()) {
    // Get any IL2CPP function
    auto class_from_name = IL2CPP_Auto::CAutoIL2CPP::GetFunction<
        void*(*)(const char*, const char*)>("il2cpp_class_from_name");
    
    auto resolve_icall = IL2CPP_Auto::CAutoIL2CPP::GetFunction<
        void*(*)(const char*)>("il2cpp_resolve_icall");
    
    // Use the functions
    if (class_from_name && resolve_icall) {
        void* camera_class = class_from_name("UnityEngine", "Camera");
        void* get_main = resolve_icall("UnityEngine.Camera::get_main");
    }
}
