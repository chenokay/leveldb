#ifndef SAIL_SERVER_H
#define SAIL_SERVER_H

#include "leveldb/db.h"

namespace SailDb {

class SailDbServer 
{
public:
	SailDbServer():_db(NULL) {};
	virtual ~SailDbServer() 
    {
        delete _db;
    }
    void serve();

    int init();

private:
    leveldb::DB * _db;
};

} 

#endif 
