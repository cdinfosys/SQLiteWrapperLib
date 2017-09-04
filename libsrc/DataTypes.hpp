#if !defined DATA_TYPES_B883AC42085D4E83850CF8EF2F265B14
#define DATA_TYPES_B883AC42085D4E83850CF8EF2F265B14 1

#include <cstdint>
#include <string>
#include <sqlite3.h>

namespace sqlitelib
{
    namespace SQLite3
    {
        enum class sqlite_data_type
        {
            unknown = 0,
            integer = SQLITE_INTEGER,
            floating_point = SQLITE_FLOAT,
            text = SQLITE3_TEXT,
            blob = SQLITE_BLOB,
            null = SQLITE_NULL
        }; // enum class sqlite_data_type
    } // namespace SQLite3

    using UINT8 = std::uint8_t;
    using UINT16 = std::uint16_t;
    using UINT32 = std::uint32_t;
    using UINT64 = std::uint64_t;

    using INT8 = std::int8_t;
    using INT16 = std::int16_t;
    using INT32 = std::int32_t;
    using INT64 = std::int64_t;

    #ifdef _WIN32
        using STRING = std::wstring;
        #define ROUTINE_NAME __FUNCSIG__
    #elif __gnu_linux
        using STRING = std::string;
        #define ROUTINE_NAME __PRETTY_FUNCTION__
    #endif

} // namespace sqlitelib

#endif // DATA_TYPES_B883AC42085D4E83850CF8EF2F265B14
