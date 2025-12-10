# IL2CPP Auto Resolver

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)](https://windows.com/)

**IL2CPP Auto Resolver** is a modern C++17 header-only library for automatic discovery and caching of IL2CPP function addresses in Unity games. Perfect for game modding without manual address hunting or pattern scanning.

## Features

- **Automatic IL2CPP Module Detection** - Finds GameAssembly.dll or UnityPlayer.dll
- **Smart Function Caching** - Addresses cached on first use, instant subsequent lookups
- **Thread-Safe Design** - Safe concurrent access from multiple threads
- **Template-Based API** - Type-safe function access with compile-time type checking
- **Zero Manual Work** - No pattern scanning or address hunting required
- **Lazy Loading** - Functions resolved only when requested
- **Broad Compatibility** - Works with most IL2CPP Unity versions
- **Header-Only** - Single file inclusion, no linking required

## Requirements

- C++17 or higher compiler (`/std:c++17` or higher)
- Windows platform
- Unity game built with IL2CPP backend

## Installation

Simply add `il2cpp_auto.hpp` to your project and include it:

```cpp
#include "il2cpp_auto.hpp"
```

## Quick Start

```cpp
#include "il2cpp_auto.hpp"

// Check if IL2CPP module is loaded (Optional but recommended)
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
```

## API Reference

### `static bool Initialize()`
Checks if an IL2CPP module is present in the process.  
**Returns:** `true` if GameAssembly.dll or UnityPlayer.dll is loaded, `false` otherwise.

### `static uintptr_t GetAddress(const std::string& name)`
Resolves the address of an exported IL2CPP function.  
**Parameters:**
- `name` - Name of the function (e.g., "il2cpp_domain_get")  
**Returns:** Function address or `0` if not found.

### `template<typename T = void*> static T GetFunction(const std::string& name)`
Gets a function pointer with type casting.  
**Template Parameter:**
- `T` - Function pointer type (default: `void*`)  
**Parameters:**
- `name` - Name of the function  
**Returns:** Function pointer cast to type `T` or `nullptr` if not found.

### `static void ClearCache()`
Clears all cached function addresses and resets the module handle.  
**Note:** After calling this, subsequent function calls will re-resolve addresses.
