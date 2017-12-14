#include "cled.h"

// список команд обрабатываемых классом cLed
const char led_command[][MAX_LENGHT_COMMAND]=
{
    "set-led-state\0", //0
    "get-led-state\0", //1
    "set-led-color\0", //2
    "get-led-color\0", //3
    "set-led-rate\0",  //4
    "get-led-rate\0",  //5
    "\0" // end
};


int cLed::getIndexCommand(char *str)
{
    int ret=FUNC_RET_ERROR;
    int i=0;
    while(led_command[i][0]!=0)
    {
        if(strcmp(led_command[i], str)==0)
        {
            ret=i;
            break;
        }
        i++;
    }
    return ret;
}


cLed::cLed()
{
    // заготовка
}

cLed::~cLed()
{
    // заготовка
}

int cLed::Init()
{
    /*
     * Здесь можно сделать что-то с аппаратурой
     */
    state=0;
    strcpy(color, "red");
    rate=0;
    return FUNC_RET_OK;
}

void cLed::Done()
{
    /*
     * Здесь можно сделать что-то с аппаратурой
     */
    state=0;
    strcpy(color, "red");
    rate=0;
}

void cLed::InCommand(char *com)
{
    char tmpstr[MAX_LENGHT_COMMAND]={0};
    char* in_com;
    char* in_val;
    int ret=FUNC_RET_ERROR;

    // скопируем чтоб не испортить
    strcpy(tmpstr, com);
    // выделим команду и значение(если есть)
    in_com=strtok(tmpstr, STRING_SEPARATOR);
    in_val=strtok(NULL, STRING_SEPARATOR);

    switch(getIndexCommand(in_com))
    {
    case 0: // set-led-state
        ret=setLedState(in_val);
        break;
    case 1: // get-led-state
        ret=getLedState(tmpstr);
        break;
    case 2: // set-led-color
        ret=setLedColor(in_val);
        break;
    case 3: // get-led-color
        ret=getLedColor(tmpstr);
        break;
    case 4: // set-led-rate
        ret=setLedRate(in_val);
        break;
    case 5: // get-led-rate
        ret=getLedRate(tmpstr);
        break;
    default: // нет такой команды
        ret=FUNC_RET_ERROR;
        break;
    }

    if(ret==FUNC_RET_SET)
    {   // формируем строку вида "OK\n"
        strcpy(com, RETURN_OK);
        strcat(com, "\n");
    } else if(ret==FUNC_RET_GET)
    {   // формируем строку вида "OK значение\n"
        strcpy(com, RETURN_OK);
        strcat(com, " ");
        strcat(com, tmpstr);
        strcat(com, "\n");
    } else
    {   // формируем строку вида "FAILED\n"
        strcpy(com, RETURN_FAILED);
    }

}

int cLed::setLedState(char *inval)
{
    int ret=FUNC_RET_ERROR;
    // проверим переданное значение
    if(strcmp(inval,"on")==0)
    {
        // все нормально, включаем

        /*
         * Здесь можно сделать что-то с аппаратурой
         */

        state=1;
        ret=FUNC_RET_SET;
    } else if(strcmp(inval,"off")==0)
    {
        // все нормально, выключаем

        /*
         * Здесь можно сделать что-то с аппаратурой
         */

        state=0;
        ret=FUNC_RET_SET;
    } else
        ret=FUNC_RET_ERROR;
    return ret;
}

int cLed::getLedState(char *outval)
{
    int ret=FUNC_RET_ERROR;

    /*
     * Здесь можно сделать что-то с аппаратурой
     */

    // вернем текущее значение
    if(state==0)
    {
        strcpy(outval, "off");
        ret=FUNC_RET_GET;
    } else if(state==1)
    {
        strcpy(outval, "on");
        ret=FUNC_RET_GET;
    } else
        ret=FUNC_RET_ERROR;

    return ret;
}

int cLed::setLedColor(char *inval)
{
    int ret=FUNC_RET_ERROR;
    // проверим переданное значение
    if( (strcmp(inval,"red")==0) || \
        (strcmp(inval,"green")==0) || \
        (strcmp(inval,"blue")==0) )
    {
        // все нормально, проводим замену значения

        /*
         * Здесь можно сделать что-то с аппаратурой
         */

        strcpy(color, inval);
        ret=FUNC_RET_SET;
    }
    return ret;

}

int cLed::getLedColor(char *outval)
{
    int ret=FUNC_RET_GET;

    /*
     * Здесь можно сделать что-то с аппаратурой
     */

    // вернем текущее значение
    strcpy(outval, color);
    return ret;

}

int cLed::setLedRate(char *inval)
{
    int ret=FUNC_RET_ERROR;
    // проверим переданное значение
    int newrate = atoi(inval);
    if( (newrate>=0)&&(newrate<=LED_MAX_RATE) )
    {
        // все нормально, проводим замену значения

        /*
         * Здесь можно сделать что-то с аппаратурой
         */

        rate=newrate;
        ret=FUNC_RET_SET;
    }
    return ret;
}

int cLed::getLedRate(char *outval)
{
    int ret=FUNC_RET_GET;

    /*
     * Здесь можно сделать что-то с аппаратурой
     */

    // вернем текущее значение
    sprintf(outval, "%u", rate);
    return ret;
}



