#include "ledserver.h"

volatile int stop=0;

struct sigaction sa;


void int_handler(int i)
{
    printf("Ctrl-C\n");
    stop=1;
}



cLedServer::cLedServer()
{
    stop=0;
    sigset_t newset;
    sigemptyset(&newset);
    sigaddset(&newset, SIGHUP);
    sigprocmask(SIG_BLOCK, &newset, 0);
    sa.sa_handler = int_handler;
    sigaction(SIGINT, &sa, 0);

    fd_in=0;
    fd_out=0;

    led = new cLed();
}

eLS_Error cLedServer::Init(void)
{
    eLS_Error err=NO_ERROR;

    if ( mkfifo(NAMEDPIPE_IN, 0666) == -1 )
    {
        if(errno==EEXIST)
            err=PIPE_EXIST;
        else
            err=PIPE_ERROR;
    } else if ( mkfifo(NAMEDPIPE_OUT, 0666) == -1 )
    {
        if(errno==EEXIST)
            err=PIPE_EXIST;
        else
            err=PIPE_ERROR;
    } else if( led->Init() )
    {
        err=HW_ERROR;
    } else
        err=NO_ERROR;

    return err;
}

void cLedServer::Run()
{
    char buf[BUFSIZE];
    char bufout[BUFSIZE];
    int len=0;
    int ret=0;
    while(1)
    {
        if ( (fd_in = open(NAMEDPIPE_IN, O_RDONLY)) > 0 )
        {
            memset(buf, '\0', BUFSIZE);
            memset(bufout, '\0', BUFSIZE);

            len = read(fd_in, buf, BUFSIZE-1);
            close(fd_in);

            if (len > 0 )
            {

                printf("Команда: %s", buf);
                ret=ProcessCom(buf, bufout);
                if(ret==0)
                {
                    strcpy(bufout, RET_FAILED);
                    strcat(bufout, "\n");
                }
                if ( (fd_out = open(NAMEDPIPE_OUT, O_WRONLY)) > 0 )
                {
                    len=write(fd_out, bufout, strlen(bufout));
                    close(fd_out);
                    if(len>0) printf("Ответ: %s\n", bufout);
                    else perror("write");
                } else
                {
                    perror("open out_pipe");
                }

            } else
            {
                perror("read");
            }

        } else
        {
            perror("open in_pipe");
        }

        if(stop==1) return;
    }
}

void cLedServer::Done()
{
    led->Done();
    unlink(NAMEDPIPE_IN);
    unlink(NAMEDPIPE_OUT);
}

cLedServer::~cLedServer()
{
    delete led;
}

int cLedServer::ProcessCom(char *com, char *out)
{
    char *device=NULL;
    char *command=NULL;
    char *parametre=NULL;
    char *value=NULL;

    command=strtok(com, "- \n");
    device=strtok(NULL, "- \n");
    parametre=strtok(NULL, "- \n");
    value=strtok(NULL, "- \n");

    if(strcmp("led", device)==0)
        led->InCommand(command, parametre, value, out);


    return strlen(out);

}



