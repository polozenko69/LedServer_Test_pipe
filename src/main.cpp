
#include <stdlib.h>
#include "ledserver.h"

int main (int argc, char ** argv)
{
    eLS_Error errout=NO_ERROR;

    cLedServer ls;

    errout=ls.Init();

    switch(errout)
    {
    case NO_ERROR:
        printf("Сервер запущен.\n");
        ls.Run();
        printf("Сервер остановлен.\n");
        ls.Done();
        break;
    case PIPE_EXIST:
        printf("Сервер уже запущен. Запуск более одной копии запрещен!\n");
        break;
    case PIPE_ERROR:
        printf("Ошибка создания каналов!\n");
        break;
    case HW_ERROR:
        printf("Ошибка оборудования!\n");
        break;
    default:
        printf("Ошибка!\n");
        break;
    }
    return errout;
}
