#if !defined SQLITE_EXCEPION_BB0AB32CCFEF460D816674433F5C255D
#define SQLITE_EXCEPION_BB0AB32CCFEF460D816674433F5C255D

#include <stdexcept>
#include <string>
#include <sqlite3.h>

namespace sqlitelib
{
    /**
     * @brief Exception class for the SQLite wrapper.
     */
    class sqlite_exception : public std::runtime_error
    {
        private:
            int _returnCode; ///< Return code from a function call.

        public:
            /**
             * @brief Construct an object with an error code.
             * @param returnCode Error code returned by the SQLite engine.
             */
            sqlite_exception(int returnCode);

            /**
             * @brief Construct an object with an error code and a description of the problem.
             * @param returnCode Error code returned by the SQLite engine.
             * @param what Explanation of the error.
             */
            sqlite_exception(int returnCode, const std::string& what);

            /**
             * @brief Construct an object with an error code and a description of the problem.
             * @param returnCode Error code returned by the SQLite engine.
             * @param what Explanation of the error.
             */
            sqlite_exception(int returnCode, const char* what);

        public:
            /**
             * @brief Get a message explaining the error code that was passed to the constructor.
             * @returns Returns an error message.
             */
            std::string GetErrorMessage() const;

            /**
             * @brief Get the return code that was passed to the constructor.
             * @returns Returns the error code that was passed to the constructor.
             */
            inline int GetReturnCode() const;
    };

    inline int sqlite_exception::GetReturnCode() const
    {
        return this->_returnCode;
    }
} // namespace sqlitelib

#endif // SQLITE_EXCEPION_BB0AB32CCFEF460D816674433F5C255D
