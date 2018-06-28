thrift -r --gen cpp  thrift/saildb.thrift 
mv gen-cpp thrift_inerface
rm thrift_inerface/SailDb_server.skeleton.cpp
make leveldb
cp ../include/leveldb/*.h leveldb/
cp ../libleveldb.a .
make clean
make

