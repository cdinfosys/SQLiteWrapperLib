#include "StepStatementProcessing.hpp"
#include "sqlite_exception.hpp"

namespace sqlitelib
{
    namespace SQLite3
    {
        void StepStatementProcessing::Error(prepared_statement& /*statement*/, int errorCode)
        {
            throw sqlite_exception(errorCode);
        }
    } // namespace SQLite3
} // namespace sqlitelib
