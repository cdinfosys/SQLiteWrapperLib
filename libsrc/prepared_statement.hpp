#if !defined PREPARED_STATEMENT_BB0AB32CCFEF460D816674433F5C255D
#define PREPARED_STATEMENT_BB0AB32CCFEF460D816674433F5C255D

#include <cstdint>
#include <string>
#include <vector>
#include <sqlite3.h>
#include "sqlite.hpp"
#include "StepStatementProcessing.hpp"

namespace sqlitelib
{
    namespace SQLite3
    {
        class StepStatementProcessing;
        /**
         * @brief Wrapper for a SQLite prepared statement.
         */
        class prepared_statement
        {
            private:
                sqlite3_stmt* _statementPtr; ///< Handle of the prepared statement.

            public:
                /**
                 * @param Construct a prepared statement
                 * @param dbObject Reference to a \c sqlite object.
                 * @param sql SQL statement.
                 */
                prepared_statement(sqlite& dbObject, const std::string& sql);

                /**
                 * @brief Destructor.
                 */
                ~prepared_statement();

            public:
                /**
                 * @brief Bind a null value to the prepared statement.
                 * @brief paramIndex Index of the parameter. The left-most parameter has index 1.
                 */
                void Bind(int paramIndex);

                /**
                 * @brief Bind a BLOB to the prepared statement.
                 * @param paramIndex Index of the parameter. The left-most parameter has index 1.
                 * @param blob Vector object that holds the BLOB data.
                 */
                void Bind(int paramIndex, const std::vector<uint8_t>& blob);

                /**
                 * @brief Bind a text value to the prepared statement.
                 * @param paramIndex Index of the parameter. The left-most parameter has index 1.
                 * @param 
                 */
                void Bind(int paramIndex, const std::string& value);

                /**
                 * @brief Bind a UTF-16 text value to the prepared statement.
                 * @param paramIndex Index of the parameter. The left-most parameter has index 1.
                 * @param 
                 */
                void Bind(int paramIndex, const std::wstring& value);

                /**
                 * @brief Bind a double value to the prepared statement.
                 * @param paramIndex Index of the parameter. The left-most parameter has index 1.
                 * @param value Parameter value.
                 */
                void Bind(int paramIndex, double value);

                /**
                 * @brief Bind an integer value to the prepared statement.
                 * @param paramIndex Index of the parameter. The left-most parameter has index 1.
                 * @param value Parameter value.
                 */
                void Bind(int paramIndex, int value);

                /**
                 * @brief Bind an integer value to the prepared statement.
                 * @param paramIndex Index of the parameter. The left-most parameter has index 1.
                 * @param value Parameter value.
                 */
                void Bind(int paramIndex, int64_t value);

                /**
                 * @brief Bind a BLOB set to all zeroes to the prepared statement.
                 * @param paramIndex Index of the parameter. The left-most parameter has index 1.
                 * @param count Size of the BLOB to create.
                 */
                void BindZeroBlob(int paramIndex, size_t count);

                /**
                 * @brief Clear all previous bindings.
                 */
                void ClearBindings();

                /**
                 * @brief Resets the statement. This does not clear out the parameter values
                 */
                void Reset();

                /**
                 * @Brief Gets the number of parameters in the prepared statement.
                 * @returns Returns the index of the last parameter.
                 */
                int ParametersCount();

                /**
                 * @brief Returns the number of columns in a result set. 
                 * @returns The number of columns in the result set.
                 */
                int ColumnsCount();
 
                /**
                 * @brief Get the index of a named parameter.
                 * @param name Parameter name.
                 * @retval 0 Parameter not found.
                 * @retval >0 Index of the parameter.
                 */
                int ParameterIndex(const std::string& name);

                /**
                 * @brief Get the name of a parameter. 
                 * @param index Parameter index.
                 * @param nameOut Name of the parameter.
                 */
                bool ParameterName(int index, std::string& nameOut);

                /**
                 * @brief Get the name of a column.
                 * @param index Parameter index.
                 * @returns Returns a string containing the name of the column.
                 */
                std::string ColumnName(int index);

                /**
                 * @brief Get the name of a column as a UTF-16 string.
                 * @param index Parameter index.
                 * @returns Returns a string containing the name of the column.
                 */
                std::wstring ColumnNameW(int index);

                /**
                * @brief Retrieve the next record from the query.
                * @param processor Reference to a StepStatementProcessing-derived object that will process the records that are retrieved.
                */
                void Step(StepStatementProcessing& processor);

                /**
                 * @brief Get the value of an integer field
                 * @param index Field index.
                 * @returns Returns the value of an integer field.
                 */
                int GetInt(int index);

                /**
                 * @brief Get the value of a 64-bit integer field
                 * @param index Field index.
                 * @returns Returns the value of a 64-bit integer field.
                 */
                int64_t GetInt64(int index);

                /**
                 * @brief Get the value of a UTF-8 text field
                 * @param index Field index.
                 * @returns Returns the value of a UTF-8 text field.
                 */
                std::string GetString(int index);

                /**
                 * @brief Get the value of a UTF-16 text field
                 * @param index Field index.
                 * @returns Returns the value of a UTF-16 text field.
                 */
                std::wstring GetWString(int index);

                /**
                 * @brief Get the data in a BLOB field
                 * @param index Field index.
                 * @returns Returns a vector of 8-bit unsigned integer values.
                 */
                std::vector<uint8_t> GetBlob(int index);

                /**
                 * @brief Get the value of a \c double field.
                 * @param index Field index.
                 * @returns Returns the value of the field as a \c double.
                 */
                double GetDouble(int index);

                /**
                 * @brief Get the value of a \c double field.
                 * @param index Field index.
                 * @returns Returns the value of the field as a \c double.
                 */
                sqlite_data_type GetColumnType(int index);

                /**
                 * @brief Get the expanded SQL query.
                 * @returns Returns the expanded SQL query.
                 */
                std::string ExpandedSql();
        }; // class prepared_statement
    } // namespace SQLite3
} // namespace sqlitelib

#endif // PREPARED_STATEMENT_BB0AB32CCFEF460D816674433F5C255D
