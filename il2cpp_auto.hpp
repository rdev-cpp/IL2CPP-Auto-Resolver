#pragma once
#include <cstdint>
#include <unordered_map>
#include <string>
#include <Windows.h>

namespace IL2CPP_Auto {
    class CAutoIL2CPP {
    private:
        static std::unordered_map<std::string, uintptr_t> m_CachedAddresses;
        static HMODULE m_IL2CPPModule;

        static bool FindIL2CPPModule();
        static void CacheAllFunctions();

    public:
        static bool Initialize();

        template<typename T>
        static T GetFunction(const std::string& name) {
            auto it = m_CachedAddresses.find(name);
            if (it != m_CachedAddresses.end()) {
                return reinterpret_cast<T>(it->second);
            }
            return nullptr;
        }

        static uintptr_t GetAddress(const std::string& name) {
            auto it = m_CachedAddresses.find(name);
            return (it != m_CachedAddresses.end()) ? it->second : 0;
        }
    };
}