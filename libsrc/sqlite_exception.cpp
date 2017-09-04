#include "sqlite_exception.hpp"

namespace sqlitelib
{
    using std::runtime_error;
    using std::string;

    sqlite_exception::sqlite_exception(int returnCode)
        :   runtime_error(nullptr),
            _returnCode(returnCode)
    {
    }

    sqlite_exception::sqlite_exception(int returnCode, const std::string& what)
        :   runtime_error(what),
            _returnCode(returnCode)
    {
    }

    sqlite_exception::sqlite_exception(int returnCode, const char* what)
        :   runtime_error(what),
            _returnCode(returnCode)
    {
    }

    string sqlite_exception::GetErrorMessage() const
    {
        return string(sqlite3_errstr(this->_returnCode));
    }
} // namespace sqlitelib
