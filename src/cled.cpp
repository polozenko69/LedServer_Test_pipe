#include "cled.h"


cLed::cLed()
{
    memset(state, '\0', MAXCHAR);
    memset(color, '\0', MAXCHAR);
    memset(rate, '\0', MAXCHAR);
}

cLed::~cLed()
{

}

int cLed::Init()
{
    strcpy(state, "off");
    strcpy(color, "red");
    strcpy(rate, "0");
    return 0;
}

void cLed::Done()
{

}

char *cLed::InCommand(char *com, char *par, char *val, char *out)
{

    if(strcmp("get", com)==0)
        getCommand(par, out);
    else if(strcmp("set", com)==0)
        setCommand(par, val, out);
    else strcpy(out, RET_FAILED);

    return out;
}

char *cLed::getCommand(char *par, char *out)
{
    strcpy(out, "OK ");
    if(strcmp("state", par)==0)
        strcat(out, state);
    else if(strcmp("color", par)==0)
        strcat(out, color);
    else if(strcmp("rate", par)==0)
        strcat(out, rate);
    else strcpy(out, RET_FAILED);

    strcat(out, "\n");

    return out;
}

char *cLed::setCommand(char *par, char *val, char *out)
{
    strcpy(out, "OK ");
    if(strcmp("state", par)==0)
        strcpy(state, val);
    else if(strcmp("color", par)==0)
        strcpy(color, val);
    else if(strcmp("rate", par)==0)
        strcpy(rate, val);
    else strcpy(out, RET_FAILED);

    strcat(out, "\n");

    return out;
}

