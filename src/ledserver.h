/*
 * Файл ledserver.h
 * содержит описание класс cLedServer
 *
 * cLedServer
 * назначение: интерфейс между клиентским приложением и оборудованием
 *
 * после создания объекта вызвать:
 * Init
 * при этом создаются два канала для приема и передачи сообщений
 * NAMEDPIPE_IN
 * NAMEDPIPE_OUT
 * производится инициализация оборудования.
 *
 * Если после инициализации нет ошибок можно запустить процесс обработки:
 * Run
 * Процесс производит чтение входного канала, передачу полученной команды оборудованию и
 * передача полученного ответа клиенту по выходному каналу
 *
 * Прерывание процесса отбработки по сигналу INT системы
 *
 * Завершение работы с оборудованием метод:
 * Done
 *
 */

#ifndef LEDSERVER_H
#define LEDSERVER_H

#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <csignal>


//
#include "cled.h"

//
#define NAMEDPIPE_IN    "/tmp/LedServer_in"
#define NAMEDPIPE_OUT   "/tmp/LedServer_out"

// ошибки инициализации сервера, можно было с перечеслением и не мудрить
enum eLS_Error {NO_ERROR=0, PIPE_EXIST=1, PIPE_ERROR=2, HW_ERROR=3, GEN_ERROR=4 };

/*
 * класс cLedServer
 */
class cLedServer
{
public:
    cLedServer();
    ~cLedServer();

    /*
     * Init(void)
     */
    eLS_Error Init(void);

    /*
     * Run(void)
     */
    void Run(void);

    /*
     * Done(void)
     */
    void Done(void);


protected:

    eLS_Error errinit;
    cLed *led;

    /*
     * ProcessCom(char *com)
     * функция предварительной обработки команд и обмена данными с оборудованием
     * вход/выход com - на входе строка содержит команду от клиента, на выходе отвер оборудования
     */
    void ProcessCom(char *com);

};

#endif // LEDSERVER_H
