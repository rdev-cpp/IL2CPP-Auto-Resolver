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

// Check if GameAssembly.dll is loaded (Optional but recommended)
if (IL2CPP_Auto::Resolver::Initialize()) {

    // 1. Get functions using Lazy Loading (Resolved & Cached on first call)
    // You can define the function type for safety:
    using il2cpp_domain_get_t = void* (*)();

    auto domain_get = IL2CPP_Auto::Resolver::GetFunction<il2cpp_domain_get_t>("il2cpp_domain_get");

    // 2. Or cast directly inline:
    auto thread_attach = IL2CPP_Auto::Resolver::GetFunction<void*(*)(void*)>("il2cpp_thread_attach");

    // 3. Use functions securely (Thread-Safe)
    if (domain_get && thread_attach) {
        void* domain = domain_get();
        void* thread = thread_attach(domain);
    }
}

