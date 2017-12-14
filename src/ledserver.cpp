#include "ledserver.h"


// обработка сигнала INT системы
volatile int stopServerFlag=0;

struct sigaction sa;


void int_handler(int i)
{
    printf("Ctrl-C\n");
    stopServerFlag=1;
}
// ----------------------------


cLedServer::cLedServer()
{
    // установим обработчик сигнала INT и заблокируем HUP
    stopServerFlag=0;
    sigset_t newset;
    sigemptyset(&newset);
    sigaddset(&newset, SIGHUP);
    sigprocmask(SIG_BLOCK, &newset, 0);
    sa.sa_handler = int_handler;
    sigaction(SIGINT, &sa, 0);

    // создадим объект светодиода
    led = new cLed();
    errinit=GEN_ERROR;
}

eLS_Error cLedServer::Init(void)
{
    // создадим входной канал
    if ( mkfifo(NAMEDPIPE_IN, 0666) == -1 )
    {
        if(errno==EEXIST)
            errinit=PIPE_EXIST;
        else
            errinit=PIPE_ERROR;
    //если нет ошибок создаем выходной канал
    } else if ( mkfifo(NAMEDPIPE_OUT, 0666) == -1 )
    {
        if(errno==EEXIST)
            errinit=PIPE_EXIST;
        else
            errinit=PIPE_ERROR;
    //если нет ошибок инициализируем аппаратуру светодиода
    } else if( led->Init()==-1 )
    {
        errinit=HW_ERROR;
    } else
        errinit=NO_ERROR;

    return errinit;
}

void cLedServer::Run()
{
    // входной/выходной буфер обмена
    char buf[MAX_LENGHT_COMMAND];

    int fd=0;

    int len=0;

    if(errinit!=NO_ERROR)
         return;

    //основной цикл обработки сообщений
    while(1)
    {
        // ожидаем открытия входного канала клиентом
        if ( (fd = open(NAMEDPIPE_IN, O_RDONLY)) > 0 )
        {
            memset(buf, '\0', MAX_LENGHT_COMMAND);


            len = read(fd, buf, MAX_LENGHT_COMMAND-1);
            close(fd);

            if (len > 0 )
            {

                printf("Команда: %s", buf);
                // передаем принятые данные на обработку
                ProcessCom(buf);
                // по завершению в buf выходные данные

                // ожидаем открытия клиентом на чтение выходношо канала
                if ( (fd = open(NAMEDPIPE_OUT, O_WRONLY)) > 0 )
                {
                    // отправляем результат
                    len=write(fd, buf, strlen(buf));
                    close(fd);
                    if(len>0) printf("Ответ: %s\n", buf);

         // в случае ошибок, сообщаем
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

        if(stopServerFlag==1)
            // если получен сигнал на завершение работы, выходим
            break;
    }
}

void cLedServer::Done()
{
    // завершаем работу с аппаратной частью
    led->Done();
    // удалим каналы
    unlink(NAMEDPIPE_IN);
    unlink(NAMEDPIPE_OUT);
}

cLedServer::~cLedServer()
{
    delete led;
}

void cLedServer::ProcessCom(char *com)
{
    char tmpstr[MAX_LENGHT_COMMAND];
    char *device=NULL;

    strcpy(tmpstr, com); // скопируем входную команду


    // вычислим название устройства оно у нас 1 после тире
    device=strtok(tmpstr, "-"); // холостой ход
    device=strtok(NULL, "-");

    // проверим для какого устройства
    // (вдруг захочется добавить еще устроиств - led2 или motor)
    // если устроиства нет - ошибка
    if(strcmp("led", device)==0)
        // передаем на обработку аппаратуре
        led->InCommand(com);
    else strcpy(com, RETURN_FAILED);
}



