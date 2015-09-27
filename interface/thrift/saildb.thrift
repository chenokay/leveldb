# vi: filetype=cpp

namespace cpp saildb
namespace py saildb
namespace php saildb

enum Status {
	SUCC = 0
	FAILURE = 1,
}

exception SailException {
	1: Status errCode,                                                                                                                                                                                                            
	2: string msg,
}

struct Reponse {
	1: string value,
	2: Status errCode,
}

service SailDb {
	Status Put(1:string key, 2:string value) throws (1:SailException se),
	Reponse Get(1:string key) throws (1:SailException se),
	Status Delete(1:string key) throws (1:SailException se),
}

