#include "sqlite.hpp"
#include <locale>
#include <string>
#include <codecvt>

namespace sqlitelib
{
    using std::pair;
    using std::string;
    using std::vector;
    using std::wstring;

    namespace SQLite3
    {
        sqlite::sqlite(STRING dbFilePath, int flags)
            :   _dbObject(nullptr)
        {
            // Pointer to the SQLite database object
            sqlite3* dbPtr;

            // Function call result.
            int rc;

            #ifdef _WIN32
                rc = sqlite3_open_v2(sqlite::Utf16ToUtf8String(dbFilePath).c_str(), &dbPtr, flags, nullptr);
            #elif __gnu_linux
                rc = sqlite3_open_v2(dbFilePath.c_str(), &dbPtr, flags, nullptr);
            #endif //

            if (rc != SQLITE_OK)
            {
                sqlite3_close(dbPtr);
                dbPtr = nullptr;

                throw sqlite_exception(rc, ROUTINE_NAME);
            }

            _dbObject = dbPtr;
        }

        sqlite::sqlite(sqlite&& src)
            :   _dbObject(src._dbObject)
        {
            src._dbObject = nullptr;
        }

        sqlite& sqlite::operator=(sqlite&& src)
        {
            this->_dbObject = src._dbObject;
            src._dbObject = nullptr;
            return *this;
        }

        sqlite::~sqlite()
        {
            if (this->_dbObject != nullptr)
            {
                int rc = sqlite3_close_v2(_dbObject);
                _dbObject = nullptr;
            }
        }

        bool sqlite::DbFileName(const string& dbName, string& fileNameOut)
        {
            const char* filePath = sqlite3_db_filename(this->_dbObject, dbName.c_str());
            if (nullptr == filePath)
            {
                fileNameOut.clear();
                return false;
            }

            fileNameOut.assign(filePath);
            return true;
        }

        void sqlite::Exec(const string& sql)
        {
            sqlite_object<char*> error;
            int rc = sqlite3_exec(this->_dbObject, sql.c_str(), nullptr, nullptr, &((char*)error));

            if (SQLITE_OK != rc)
            {
                throw sqlite_exception(rc, (char*)error);
            }
        }

        void sqlite::Exec(const string& sql, exec_result& resultProcessor)
        {
            sqlite_object<char*> error;
            int rc = sqlite3_exec(this->_dbObject, sql.c_str(), sqlite::ExecCallback, (void*)&resultProcessor, &((char*)error));

            if (SQLITE_OK != rc)
            {
                throw sqlite_exception(rc, (char*)error);
            }
        }

        int sqlite::ExecCallback(void* userData, int numFields, char** fieldValues, char** fieldNames)
        {
            exec_result* resultProcessorPtr = (exec_result*)userData;
            if (resultProcessorPtr->ReturnFieldNames())
            {
                return resultProcessorPtr->RowData(StringsArrayToVector((size_t)numFields, fieldNames, fieldValues)) ? 0 : 1;
            }

            return resultProcessorPtr->RowData(StringsArrayToVector((size_t)numFields, fieldValues)) ? 0 : 1;
        }

        string sqlite::Utf16ToUtf8String(const wstring& utf16String)
        {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> conversion;
            return conversion.to_bytes(utf16String.c_str());
        }

        std::vector<string> sqlite::StringsArrayToVector(size_t fieldCount, char** fieldValues)
        {
            vector<string> result;
            result.reserve(fieldCount);

            for (size_t index = 0u; index < fieldCount; ++index)
            {
                result.push_back(fieldValues[index]);
            }

            return std::move(result);
        }

        vector< pair< string, string > > sqlite::StringsArrayToVector(size_t fieldCount, char** fieldNames, char** fieldValues)
        {
            vector< pair< string, string > > result;
            result.reserve(fieldCount);

            for (size_t index = 0u; index < fieldCount; ++index)
            {
                result.push_back(pair< string, string >(fieldNames[index], fieldValues[index]));
            }

            return std::move(result);
        }

        int sqlite::Changes()
        {
            return sqlite3_changes(this->_dbObject);
        }

        bool sqlite::Complete(const std::string& sqlStatement)
        {
            return sqlite3_complete(sqlStatement.c_str()) == 0 ? false : true;
        }

        bool sqlite::Complete(const std::wstring& sqlStatement)
        {
            return sqlite3_complete16(sqlStatement.c_str()) == 0 ? false : true;
        }

        void sqlite::CacheFlush()
        {
            int rc = sqlite3_db_cacheflush(this->_dbObject);
            if (rc != SQLITE_OK)
            {
                throw sqlite_exception(rc, ROUTINE_NAME);
            }
        }

        int64_t sqlite::LastInsertRowID()
        {
            return (int64_t)sqlite3_last_insert_rowid(this->_dbObject);
        }

    } // namespace SQLite3
} // namespace sqlitelib
