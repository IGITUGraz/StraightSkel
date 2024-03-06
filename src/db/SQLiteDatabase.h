/**
 * @file   db/SQLiteDatabase.h
 * @author Gernot Walzl
 * @date   2012-01-25
 */

#ifndef DB_SQLITEDATABASE_H
#define	DB_SQLITEDATABASE_H

#include <string>
#include <iostream>
#include <sqlite3.h>
#include "debug.h"
#include "db/ptrs.h"
#include "db/SQLiteStmt.h"
#include "util/StringFactory.h"

namespace db {

using std::string;
using util::StringFactory;

class SQLiteDatabase {
public:
    SQLiteDatabase();
    virtual ~SQLiteDatabase();

    bool open(string &filename);
    bool close();
    bool isOpened();

    SQLiteStmtSPtr prepare(string& sql_query);

    bool beginTransaction();
    bool endTransaction();

protected:
    void printError();

    sqlite3* db_;
    bool transaction_;
};

}

#endif	/* DB_SQLITEDATABASE_H */

