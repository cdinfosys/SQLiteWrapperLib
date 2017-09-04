/**
 * Program entry point.
 */

#include "targetver.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

#include <sqlitelib.hpp>
#include <exec_result.hpp>

using std::cout;
using std::endl;
using std::exception;
using std::string;

using SQLite = sqlitelib::SQLite3::sqlite;
using sqlitelib::sqlite_exception;
using RowProcessor = sqlitelib::SQLite3::exec_result;
using PreparedStatement = sqlitelib::SQLite3::prepared_statement;
using StepStatementProcessing = sqlitelib::SQLite3::StepStatementProcessing;

class BoundResult : public StepStatementProcessing
{
    public:
        BoundResult();
        virtual ~BoundResult();
        virtual void RowRetrieved(PreparedStatement& statement, bool& continueProcessing);
};

BoundResult::BoundResult()
{
}

BoundResult::~BoundResult()
{
}

void BoundResult::RowRetrieved(PreparedStatement& statement, bool& continueProcessing)
{
    string foo = statement.GetString(0);
    int i = statement.GetInt(1);
    i = 0;
}

int main()
{

    try
    {
        SQLite sqliteDb(L"D:\\1\\sqlite_test.db");
        string dbPath;
        sqliteDb.DbFileName(dbPath);
        sqliteDb.Exec("CREATE TABLE IF NOT EXISTS MyTable (id INTEGER PRIMARY KEY, value STRING)");
        sqliteDb.Exec("INSERT OR REPLACE INTO MyTable(id, value) VALUES (1, 'Foo'), (3, 'Bar')");

        RowProcessor rowProcessor;
        sqliteDb.Exec("SELECT COUNT (*) AS RecCount FROM MyTable", rowProcessor);

        sqliteDb.Exec("SELECT value, id FROM MyTable", rowProcessor);

        PreparedStatement statement(sqliteDb, "SELECT value, id FROM MyTable WHERE id >= :id");
        int paramCount = statement.ParametersCount();
        statement.Bind(1, 1);

        BoundResult boundRes;
        statement.Step(boundRes);
    }
    catch (const sqlite_exception& ex)
    {
        cout << "sqlite_exception " << ex.GetReturnCode() << ": " << ex.what() << endl << ex.GetErrorMessage() << endl;
    }
    catch (const exception& ex)
    {
        cout << ex.what() << endl;
    }
    catch (...)
    {
        cout << "Unknown excpetion caught." << endl;
    }

    return 0;
}

