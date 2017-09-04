#if !defined SQL_LITE_BB0AB32CCFEF460D816674433F5C255D
#define SQL_LITE_BB0AB32CCFEF460D816674433F5C255D

#include <string>
#include <sqlite3.h>
#include "DataTypes.hpp"
#include "exec_result.hpp"
#include "sqlite_exception.hpp"
#include "sqlite_object.hpp"

namespace sqlitelib
{
    namespace SQLite3
    {
        class prepared_statement;

        /**
         * @brief Wrapper class for the sqlite3_open() and sqlite3_close() sequence
         */
        class sqlite
        {
            friend class prepared_statement;

            private:
                sqlite3* _dbObject; ///< Object for accessing the SQLite database.

            public:
                /**
                 * @brief Construct an object from a path to a file.
                 * @param dbFilePath String object containing the path to the database file.
                 * @param flags File open flags.
                 */
                sqlite(STRING dbFilePath, int flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

                /**
                 * @brief Copy constructor.
                 * @param src Reference to an existing instance of the class.
                 */
                sqlite(const sqlite& src) = delete;

                /**
                 * @brief Move constructor.
                 * @param src Reference to an existing instance of the class.
                 */
                sqlite(sqlite&& src);

                /**
                 * @brief Destructor.
                 */
                ~sqlite();

            public:
                /**
                 * @brief Assignment operator overload.
                 * @param src Reference to an existing instance of the class.
                 */
                sqlite& operator=(sqlite&& src);

                /**
                 * @brief Copy assignment operator.
                 * @param src Reference to an existing instance of the class.
                 */
                sqlite& operator=(const sqlite& src) = delete;

            public:
                /**
                 * @brief Gets the path to the main database.
                 * @param fileNameOut Reference to a string object that receives the file path.
                 * @retval false No database is attached, or an in-memory database is attached
                 * @retval true Database file name is returned.
                 */
                 inline bool DbFileName(std::string& fileNameOut);

                /**
                 * @brief Gets the path to the main database.
                 * @param dbName Name of the attached database.
                 * @param fileNameOut Reference to a string object that receives the file path.
                 * @retval false No database is attached, or an in-memory database is attached
                 * @retval true Database file name is returned.
                 */
                 bool DbFileName(const std::string& dbName, std::string& fileNameOut);

                /**
                 * @brief Execute SQL statements.
                 * @param sql Semicolon-separated SQL statements.
                 */
                 void Exec(const std::string& sql);

                /**
                 * @brief Execute SQL statements
                 * @param sql Semicolon-separated SQL statements.
                 * @param resultProcessor Object derived from exec_result that will be called to process the results from the query;
                 */
                 void Exec(const std::string& sql, exec_result& resultProcessor);

                /**
                 * @brief Gets the number of rows changed by the last \c INSERT, \c DELETE, or \c UPDATE statement.
                 * @returns Returns a count of the number of rows changed.
                 */
                 int Changes();

                 /**
                  * @brief Writes dirty pages to disk.
                  */
                 void CacheFlush();

                 /**
                  * @brief Get the row id of the last inserted row 
                  * @returns Returns the row id of the last inserted row.
                  */
                 int64_t LastInsertRowID();
            public:
                /**
                 * @brief Check if the \p sqlStatement is a complete SQL statement.
                 * @retval true The statement is a complete SQL statement.
                 * @retval false The statement is not a complete SQL statement.
                 */
                 static bool Complete(const std::string& sqlStatement);

                /**
                 * @brief Check if the \p sqlStatement is a complete SQL statement.
                 * @retval true The statement is a complete SQL statement.
                 * @retval false The statement is not a complete SQL statement.
                 */
                 static bool Complete(const std::wstring& sqlStatement);

            private:
                /**
                 * @brief Called by Exec() to return values obtained by a SELECT statement.
                 * @param userData Points to the instance of the \c sqlite class.
                 * @param numFields Number of fields in the return list.
                 * @param fieldValues Array of strings containing the values of the fields of a record that was returned.
                 * @param fieldNames Array of strings containing the names of the fields.
                 * @retval 0 Continue retrieving records.
                 * @ratval <>0 Abort retrieval.
                 */
                static int ExecCallback(void* userData, int numFields, char** fieldValues, char** fieldNames);

                static std::vector<std::string> StringsArrayToVector(size_t fieldCount, char** fieldValues);

                static std::vector< std::pair< std::string, std::string > > StringsArrayToVector(size_t fieldCount, char** fieldNames, char** fieldValues);

                static std::string sqlite::Utf16ToUtf8String(const std::wstring& utf16String);
        }; // class sqlite

        inline bool sqlite::DbFileName(std::string& fileNameOut)
        {
            return DbFileName("main", fileNameOut);
        }
    } // namespace SQLite3
} // namespace sqlitelib

#endif // SQL_LITE_BB0AB32CCFEF460D816674433F5C255D

