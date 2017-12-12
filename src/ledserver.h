#ifndef LEDSERVER_H
#define LEDSERVER_H

#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <csignal>

#include "cled.h"


#define NAMEDPIPE_IN    "/tmp/LedServer_in"
#define NAMEDPIPE_OUT   "/tmp/LedServer_out"




#define BUFSIZE        100

enum eLS_Error {NO_ERROR=0, PIPE_EXIST=1, PIPE_ERROR=2, HW_ERROR=3};


class cLedServer
{
public:
    cLedServer();
    eLS_Error Init(void);
    void Run(void);
    void Done(void);
    ~cLedServer();

protected:
    int fd_in;
    int fd_out;

    cLed *led;

    int ProcessCom(char *com, char *out);



};

#endif // LEDSERVER_H
