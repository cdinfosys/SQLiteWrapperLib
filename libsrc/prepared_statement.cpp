#include "prepared_statement.hpp"
#include "sqlite_exception.hpp"

namespace sqlitelib
{
    namespace SQLite3
    {
        using std::string;
        using std::vector;
        using std::wstring;

        prepared_statement::prepared_statement(sqlite& dbObject, const string& sql)
            :   _statementPtr(nullptr)
        {
            sqlite3_stmt* statementPtr;
            int rc = sqlite3_prepare_v2
            (
                dbObject._dbObject,
                sql.c_str(),
                (int)(sql.size() + 1u),
                &statementPtr,
                nullptr
            );

            if (rc != SQLITE_OK)
            {
                sqlite3_finalize(statementPtr);
                throw sqlite_exception(rc, sql);
            }

            this->_statementPtr = statementPtr;
        }

        prepared_statement::~prepared_statement()
        {
            sqlite3_finalize(this->_statementPtr);
            this->_statementPtr = nullptr;
        }

        void prepared_statement::Bind(int paramIndex)
        {
            int rc = sqlite3_bind_null(this->_statementPtr, paramIndex);
            if (rc != SQLITE_OK)
            {
                throw sqlite_exception(rc);
            }
        }

        void prepared_statement::Bind(int paramIndex, const std::vector<uint8_t>& blob)
        {
            int rc = sqlite3_bind_blob64(this->_statementPtr, paramIndex, (const void*)blob.data(), (sqlite_int64)blob.size(), SQLITE_TRANSIENT);
            if (rc != SQLITE_OK)
            {
                throw sqlite_exception(rc);
            }
        }

        void prepared_statement::Bind(int paramIndex, double value)
        {
            int rc = sqlite3_bind_double(this->_statementPtr, paramIndex, value);
            if (rc != SQLITE_OK)
            {
                throw sqlite_exception(rc);
            }
        }

        void prepared_statement::Bind(int paramIndex, int value)
        {
            int rc = sqlite3_bind_int(this->_statementPtr, paramIndex, value);
            if (rc != SQLITE_OK)
            {
                throw sqlite_exception(rc);
            }
        }

        void prepared_statement::Bind(int paramIndex, int64_t value)
        {
            int rc = sqlite3_bind_int64(this->_statementPtr, paramIndex, (sqlite_int64)value);
            if (rc != SQLITE_OK)
            {
                throw sqlite_exception(rc);
            }
        }

        void prepared_statement::Bind(int paramIndex, const std::string& value)
        {
            int rc = sqlite3_bind_text64(this->_statementPtr, paramIndex, (const char*)value.c_str(), (sqlite_int64)value.size(), SQLITE_TRANSIENT, SQLITE_UTF8);
            if (rc != SQLITE_OK)
            {
                throw sqlite_exception(rc);
            }
        }

        void prepared_statement::Bind(int paramIndex, const std::wstring& value)
        {
            int rc = sqlite3_bind_text16
            (
                this->_statementPtr, 
                paramIndex, 
                (const void*)value.c_str(), 
                (int)(value.size() * sizeof(value[0])), 
                SQLITE_TRANSIENT
            );
            if (rc != SQLITE_OK)
            {
                throw sqlite_exception(rc);
            }
        }

        void prepared_statement::BindZeroBlob(int paramIndex, size_t count)
        {
            int rc = sqlite3_bind_zeroblob64(this->_statementPtr, paramIndex, (sqlite_int64)count);
            if (rc != SQLITE_OK)
            {
                throw sqlite_exception(rc);
            }
        }

        void prepared_statement::ClearBindings()
        {
            int rc = sqlite3_clear_bindings(this->_statementPtr);
            if (rc != SQLITE_OK)
            {
                throw sqlite_exception(rc);
            }
        }

        void prepared_statement::Reset()
        {
            int rc = sqlite3_reset(this->_statementPtr);
            if (rc != SQLITE_OK)
            {
                throw sqlite_exception(rc);
            }
        }

        int prepared_statement::ParametersCount()
        {
            return sqlite3_bind_parameter_count(this->_statementPtr);
        }

        int prepared_statement::ParameterIndex(const std::string& name)
        {
            return sqlite3_bind_parameter_index(this->_statementPtr, name.c_str());
        }

        bool prepared_statement::ParameterName(int index, std::string& nameOut)
        {
            const char* paramNamePtr = sqlite3_bind_parameter_name(this->_statementPtr, index);
            if (nullptr == paramNamePtr)
            {
                nameOut.clear();
                return false;
            }

            nameOut.assign(paramNamePtr);
            return true;
        }

        void prepared_statement::Step(StepStatementProcessing& processor)
        {
            int returnCode;
            bool firstRecord(true);
            bool continueProcessing(true);
            bool continueLoop(true);

            while (continueLoop)
            {
                returnCode = sqlite3_step(this->_statementPtr);
                switch (returnCode)
                {
                    case SQLITE_ROW:
                        {
                            if (firstRecord)
                            {
                                processor.ResponseStart(*this);
                                firstRecord = false;
                            }
                            processor.RowRetrieved(*this, continueProcessing);
                            if (!continueProcessing)
                            {
                                continueLoop = false;
                            }
                        }
                        break;

                    case SQLITE_DONE:
                        continueLoop = false;
                        break;

                    default:
                        processor.Error(*this, returnCode);
                        break;
                }
            }

            processor.Completed(*this);
        }

        int prepared_statement::GetInt(int index)
        {
            return sqlite3_column_int(this->_statementPtr, index);
        }

        int64_t prepared_statement::GetInt64(int index)
        {
            return (int64_t)sqlite3_column_int64(this->_statementPtr, index);
        }

        std::string prepared_statement::GetString(int index)
        {
            size_t resultLength = (size_t)(sqlite3_column_bytes(this->_statementPtr, index));
            return std::string((const char*)sqlite3_column_text(this->_statementPtr, index), resultLength);
        }

        std::wstring prepared_statement::GetWString(int index)
        {
            size_t resultLength = (size_t)(sqlite3_column_bytes16(this->_statementPtr, index));
            return std::wstring((const wchar_t*)sqlite3_column_text16(this->_statementPtr, index), resultLength);
        }

        vector<uint8_t> prepared_statement::GetBlob(int index)
        {
            vector<uint8_t> result;
            size_t resultLength = (size_t)(sqlite3_column_bytes(this->_statementPtr, index));
            result.reserve(resultLength);
            uint8_t* blobPtr = (uint8_t*)sqlite3_column_blob(this->_statementPtr, index);
            result.assign(blobPtr, blobPtr + resultLength);
            return std::move(result);
        }

        double prepared_statement::GetDouble(int index)
        {
            return sqlite3_column_double(this->_statementPtr, index);
        }

        sqlite_data_type prepared_statement::GetColumnType(int index)
        {
            switch (sqlite3_column_type(this->_statementPtr, index))
            {
                case SQLITE_INTEGER:
                    return sqlite_data_type::integer;

                case SQLITE_FLOAT:
                    return sqlite_data_type::floating_point;

                case SQLITE3_TEXT:
                    return sqlite_data_type::text;

                case SQLITE_BLOB:
                    return sqlite_data_type::blob;

                case SQLITE_NULL:
                    return sqlite_data_type::null;

                default:
                    return sqlite_data_type ::unknown;
            }
        }

        string prepared_statement::ColumnName(int index)
        {
            const char* colNamePtr = sqlite3_column_name(this->_statementPtr, index);
            return (nullptr == colNamePtr) ? string() : string(colNamePtr); 
        }

        wstring prepared_statement::ColumnNameW(int index)
        {
            const wchar_t* colNamePtr = (const wchar_t*)sqlite3_column_name16(this->_statementPtr, index);
            return (nullptr == colNamePtr) ? wstring() : wstring(colNamePtr); 
        }

        int prepared_statement::ColumnsCount()
        {
            return sqlite3_data_count(this->_statementPtr);
        }

        string prepared_statement::ExpandedSql()
        {
            return string(sqlite3_expanded_sql(this->_statementPtr));
        }
    } // namespace SQLite3
} // namespace sqlitelib
