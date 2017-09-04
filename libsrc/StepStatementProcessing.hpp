#if !defined STEP_STMNT_PROC_BB0AB32CCFEF460D816674433F5C255D
#define STEP_STMNT_PROC_BB0AB32CCFEF460D816674433F5C255D

#include "prepared_statement.hpp"

namespace sqlitelib
{
    namespace SQLite3
    {
        class StepStatementProcessing
        {
            public:
                /**
                 * @brief Default constructor.
                 */
                inline StepStatementProcessing();

                /**
                 * @brief Destructor.
                 */
                inline virtual ~StepStatementProcessing();

            public:
                /**
                 * @brief Called when the response starts. Use this for tasks like to retrieve column indexes
                 * @param statement Reference to a prepared_statement object.
                 */
                inline virtual void ResponseStart(prepared_statement& statement); 

                /**
                 * @brief Called when processing ends.
                 * @param statement Reference to a prepared_statement object.
                 */
                inline virtual void Completed(prepared_statement& statement);

                /**
                 * @brief Called when an error is encountered.
                 * @param statement Reference to a prepared_statement object.
                 * @param errorCode Error code.
                 */
                virtual void Error(prepared_statement& statement, int errorCode);

                /**
                 * @brief Called when a row is retrieved.
                 * @param statement Reference to a prepared_statement object.
                 * @param continueProcessing Set this value to \c false to stop processing.
                 */
                virtual void RowRetrieved(prepared_statement& statement, bool& continueProcessing)= 0;
        };

        inline StepStatementProcessing::StepStatementProcessing()
        {
        }

        inline StepStatementProcessing::~StepStatementProcessing()
        {
        }

        inline void StepStatementProcessing::ResponseStart(prepared_statement& /*statement*/)
        {
            // Do nothing.
        } 

        inline void StepStatementProcessing::Completed(prepared_statement& /*statement*/)
        {
            // Do nothing.
        } 

    } // namespace SQLite3
} // namespace sqlitelib

#endif // STEP_STMNT_PROC_BB0AB32CCFEF460D816674433F5C255D