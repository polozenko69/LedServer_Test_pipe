/*
 * Основная программа
 * Сервера управления светодиодом
 */

#include <stdlib.h>

// подключаем класс сервера
#include "ledserver.h"

int main (int argc, char ** argv)
{
    eLS_Error errout;
    // создаем объект сервера
    cLedServer ls;

    // инициализируем сервер и анализируем ошибки
    errout=ls.Init();

    switch(errout)
    {
    case NO_ERROR:
        // нет ошибок запускаем процесс обработки
        printf("Сервер запущен.\n");
        ls.Run();
        // завершаем работу сервера
        printf("Сервер остановлен.\n");
        ls.Done();
        break;
    // ошибки
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
    return (int)errout;
}
