
#ifndef SAIL_HANDLER_H
#define SAIL_HANDLER_H

#include <protocol/TBinaryProtocol.h>
#include <server/TSimpleServer.h>
#include <transport/TServerSocket.h>
#include <transport/TBufferTransports.h>
#include "thrift_inerface/SailDb.h"
#include "thrift_inerface/saildb_types.h"
#include "leveldb/db.h"
#include "timer.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace saildb;

class SailDbHandle : public SailDbIf {
 public:
     SailDbHandle(leveldb::DB * db) : _db(db) {}
     virtual ~SailDbHandle() {}
     Status::type Put(const std::string& key, const std::string& value)
     {

        DOMOB_STL_CPP::Timer timer;
        leveldb::Status s = _db->Put(leveldb::WriteOptions(), key, value);
        
        int us = timer.usec_elapsed();

        printf("put key:%s; time:%d\n", key.c_str(), us);

        if (s.ok()) {
            return Status::SUCC;
        }

        return Status::FAILURE;
     }

     void Get(Reponse& _return, const std::string& key)
     {
        DOMOB_STL_CPP::Timer timer;
        if (NULL == _db) {
            printf("db is NULL\n");
            _return.errCode = Status::FAILURE;
            return ;
        }
        leveldb::Status s = _db->Get(leveldb::ReadOptions(), key, &(_return.value));
        int us = timer.usec_elapsed();

        printf("get key:%s; time:%d\n", key.c_str(), us);
        
        if (s.ok()) {
            _return.errCode = Status::SUCC;
        } else {
            _return.errCode = Status::FAILURE;
        }
     }

     Status::type Delete(const std::string& key)
     {
         return Status::SUCC;
     }

 private:
     leveldb::DB * _db;
};

#endif
