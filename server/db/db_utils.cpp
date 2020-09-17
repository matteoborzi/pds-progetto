//
// Created by rober on 17/09/2020.
//

#include <stdexcept>
#include "db_utils.h"

sqlite3* getDB(){
    sqlite3 *db;
    int rc;
    /* Open database */
    rc = sqlite3_open("test.db", &db);

    if( rc )
        throw std::runtime_error( "Can't open database: "+ std::string{ sqlite3_errmsg(db)});

}