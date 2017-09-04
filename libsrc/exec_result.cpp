#include "exec_result.hpp"

namespace sqlitelib
{
    namespace SQLite3
    {
        using std::pair;
        using std::string;
        using std::vector;

        exec_result::exec_result()
            :   _returnColumnNames(true)
        {
        }

        exec_result::~exec_result()
        {
        }

        bool exec_result::RowData(const std::vector<std::pair<std::string,  std::string > >& values)
        {
            this->_returnColumnNames = false;
            return true;
        }

        bool exec_result::RowData(const std::vector<std::string>& values)
        {
            return true;
        }
    } // namespace SQLite3
} // namespace sqlitelib
