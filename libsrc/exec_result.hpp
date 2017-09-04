#if !defined EXEC_RESULT_BB0AB32CCFEF460D816674433F5C255D
#define EXEC_RESULT_BB0AB32CCFEF460D816674433F5C255D

#include <vector>
#include <string>

namespace sqlitelib
{
    namespace SQLite3
    {
        /**
         * @brief class to handle output from sqlite3_exec.
         */
        class exec_result
        {
            protected:
                bool _returnColumnNames; ///< Flag to control if column names must be returned

            public:
                /**
                 * @brief Default constructror.
                 */
                exec_result();

                /**
                 * @brief Destructor.
                 */
                virtual ~exec_result();

            public:
                /**
                 * @brief Must indicate if the callback function of sqlite3_exec() returns field names or not.
                 * @retval true Field names are returned.
                 * @retval false Only field values are returned.
                 */
                inline bool ReturnFieldNames() const;

                /**
                 * @brief This method is called when \c ReturnFieldNames() returns \c true. 
                 * 
                 */
                virtual bool RowData(const std::vector<std::pair<std::string,  std::string > >& values);

                /**
                 * @brief This method is called when \c ReturnFieldNames() returns \c false. 
                 * 
                 */
                virtual bool RowData(const std::vector<std::string>& values);
        };

        inline bool exec_result::ReturnFieldNames() const
        {
            return this->_returnColumnNames;
        }
    } // namespace SQLite3
} // namespace sqlitelib
#endif // EXEC_RESULT_BB0AB32CCFEF460D816674433F5C255D
