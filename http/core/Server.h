#ifndef DISK_API_SERVER_SERVER_H_
#define DISK_API_SERVER_SERVER_H_

#include "net.h"
#include "beast.h"
#include "Listener.h"
#include "../../tools/Logger.h"

void server_run();
void signal_handler(int sig_num);

#endif //DISK_API_SERVER_SERVER_H_