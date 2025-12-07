#pragma once
#include <Windows.h>
#include <string>
#include <unordered_map>
#include <shared_mutex>
#include <mutex>

namespace IL2CPP_Auto {
    class Resolver {
    private:
        inline static HMODULE m_IL2CPPModule = nullptr;
        inline static std::unordered_map<std::string, uintptr_t> m_Cache;
        inline static std::shared_mutex m_Mutex;

        static HMODULE GetModule() {
            if (m_IL2CPPModule) return m_IL2CPPModule;
            m_IL2CPPModule = GetModuleHandleA("GameAssembly.dll");
            return m_IL2CPPModule;
        }

        static uintptr_t ResolveExport(const std::string& name) {
            HMODULE mod = GetModule();
            if (!mod) return 0;
            return reinterpret_cast<uintptr_t>(GetProcAddress(mod, name.c_str()));
        }

    public:
        static bool Initialize() {
            return GetModule() != nullptr;
        }

        static uintptr_t GetAddress(const std::string& name) {
            {
                std::shared_lock<std::shared_mutex> lock(m_Mutex);
                auto it = m_Cache.find(name);
                if (it != m_Cache.end()) {
                    return it->second;
                }
            }

            uintptr_t addr = ResolveExport(name);
            if (addr == 0) return 0;

            {
                std::unique_lock<std::shared_mutex> lock(m_Mutex);
                m_Cache[name] = addr;
            }

            return addr;
        }

        template<typename T = void*>
        static T GetFunction(const std::string& name) {
            return reinterpret_cast<T>(GetAddress(name));
        }

        static void ClearCache() {
            std::unique_lock<std::shared_mutex> lock(m_Mutex);
            m_Cache.clear();
            m_IL2CPPModule = nullptr;
        }
    };
}