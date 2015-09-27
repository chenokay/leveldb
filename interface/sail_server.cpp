#include <stdio.h>
#include <pthread.h>
#include <protocol/TBinaryProtocol.h>
#include <protocol/TProtocol.h>
#include <server/TNonblockingServer.h>
#include <transport/TServerSocket.h>
#include <transport/TBufferTransports.h>
#include <concurrency/ThreadManager.h>
#include <concurrency/PosixThreadFactory.h>
#include "sail_server.h"
#include "sail_handler.h"
#include "leveldb/cache.h"
#include "leveldb/filter_policy.h"

using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using boost::shared_ptr;

namespace SailDb {


void SailDbServer::serve()
{
    int listen = 3909;
    int server_threads = 30;

    shared_ptr < TProtocolFactory > protocolFactory(
            new TBinaryProtocolFactory());
    shared_ptr<SailDbHandle> handler(new SailDbHandle(_db)); // 多线程共享此对象
    shared_ptr < TProcessor > processor(new SailDbProcessor(handler));

    shared_ptr < TServerTransport > serverTransport(new TServerSocket(listen));
    shared_ptr < TTransportFactory > transportFactory(
            new TBufferedTransportFactory());
            //new TFramedTransportFactory());

    shared_ptr < ThreadManager > threadManager
            = ThreadManager::newSimpleThreadManager(server_threads);
    shared_ptr < PosixThreadFactory > threadFactory = shared_ptr<
            PosixThreadFactory> (new PosixThreadFactory());
    threadManager->threadFactory(threadFactory);
    threadManager->start();
	/*TThreadPoolServer server(processor, serverTransport, transportFactory,
            protocolFactory, threadManager);*/
	TNonblockingServer server(processor, protocolFactory, listen, threadManager);
    //DOMOB_WRITE_LOG(LOG_NOTICE, "start server ...");
    server.serve();
}

int SailDbServer::init()
{
  leveldb::Options options;	
  // 10 MB cache
  options.block_cache = leveldb::NewLRUCache(10 * 1048576);
  // bloom filter 
  options.filter_policy = leveldb::NewBloomFilterPolicy(10);
  options.create_if_missing = true;

  leveldb::Status status = leveldb::DB::Open(options, "./data/testdb", &_db);

    if (NULL == _db) {
            printf("db is NULL; fail to open\n");
    }

  if (!status.ok()) {
        printf("fail to open database:%s", status.ToString().c_str());   
        return -1;
  }

  return 0;
}

} 
