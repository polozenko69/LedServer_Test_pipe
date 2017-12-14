/*
 * Фаил cled.h
 *
 * Описание класса cLed
 * управление светодиодом
 *
 * обрабатыввает команды вида:
 * COMMAND [argument]\n
 *
 * возвращает результат вида:
 * STATUS [result]\n
 *
 */

#ifndef CLED_H
#define CLED_H

#include <cstring>
#include <cstdlib>
#include <cstdio>


// максимальная длина команды
#define MAX_LENGHT_COMMAND  100

// максимальная длина атрибута
#define MAX_LENGHT_VALUE    20

// строки для ответа InCommand
#define RETURN_FAILED "FAILED\n"
#define RETURN_OK "OK"

// разделители для командной строки
#define STRING_SEPARATOR    " \n"

// коды возвратов функций
#define FUNC_RET_ERROR  -1
#define FUNC_RET_OK     0
#define FUNC_RET_SET    1
#define FUNC_RET_GET    2

// максимально разрешенная частота мерцания светодиода
#define LED_MAX_RATE    5

/*
 * класс cLed
 */
class cLed
{
public:
    cLed();
    ~cLed();

    /*
     * int Init(void)
     * первоначальная настройка аппаратуры
     * возвращает:
     * FUNC_RET_OK - нет ошибки
     * FUNC_RET_ERROR - ошибка
     */
    int Init(void);

    /*
     * void Done(void)
     * функция завершения работы аппаратной части
     */
    void Done(void);

    /*
     * void InCommand(char* com)
     * функция обработки входящей команды
     * вход: com - указатель на строку команды
     * выход: com - результат помещается в ту же строку com
     */
    void InCommand(char* com);


protected:
    // атрибуты состояние, цвет, частоты мерцания
    int state;
    char color[MAX_LENGHT_VALUE];
    int rate;

    /*
     * int getIndexCommand(char* str)
     * функция возвращает номер команды, используется в InCommand
     * вход: str указатель на строку команды, не должнобыть доп. символов в начале и конце строки
     * выход номер команды (см. led_command) или FUNC_RET_ERROR
     */
    int getIndexCommand(char* str);

    /* Функции setLed*
     * предназначены для изменения атрибутов: состояние, цвкта и частоты светодиода
     * вход: inval указатель на текстовое значение атрибута, не должнобыть доп. символов в начале и конце строки
     * выход:
     * FUNC_RET_SET - нет ошибки
     * FUNC_RET_ERROR - ошибка
     */
    int setLedState(char* inval);
    int setLedColor(char* inval);
    int setLedRate(char* inval);

    /* Функции getLed*
     * возвращают текстовое значение атрибутов: состояние, цвкта и частоты светодиода
     * вход: outval - указатель на строку для текстого значения атрибута,
     *       должна быть создана и иметь длинну не менее MAX_LENGHT_VALUE
     * выход: в outval - значение атрибута
     * FUNC_RET_GET - нет ошибки
     * FUNC_RET_ERROR - ошибка
     */
    int getLedState(char* outval);
    int getLedColor(char* outval);
    int getLedRate(char* outval);
};

#endif // CLED_H
