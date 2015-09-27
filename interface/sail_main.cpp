#include <stdlib.h>
#include "sail_server.h"

int main(int argc, char **argv)
{
    SailDb::SailDbServer saildb_server;

    try {
        int ret = saildb_server.init();

        if (0 != ret) {
            printf("fail to startup");
            exit(1);
        }

        saildb_server.serve();
    }
	catch (std::exception &e) {
        return 1;
    }

    return 0;
}
