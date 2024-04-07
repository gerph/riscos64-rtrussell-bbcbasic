#define YEAR    "2024"          // Copyright year
#define VERSION "1.39a"         // Version string
#define VER_RES 1,39,1,00       // For VERSIONINFO resource
#define DEFAULT_RAM PAGE_OFFSET+0x2000000 // Initial amount of RAM to allocate
#if defined __EMSCRIPTEN__
#define MAXIMUM_RAM 0x03000000  // Maximum amount of RAM to allocate
#elif UINTPTR_MAX == UINT32_MAX
#define MAXIMUM_RAM 0x10000000  // Maximum amount of RAM to allocate
#else
#define MAXIMUM_RAM 0x100000000LL // Maximum amount of RAM to allocate
#endif
