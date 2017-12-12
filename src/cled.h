#ifndef CLED_H
#define CLED_H

#include <cstring>

#define MAXCHAR 50

#define RET_FAILED "FAILED"


class cLed
{
public:
    cLed();
    ~cLed();

    int Init(void);
    void Done(void);
    char *InCommand(char* com, char *par, char *val, char *out);


protected:
    char state[MAXCHAR];
    char color[MAXCHAR];
    char rate[MAXCHAR];


    char *getCommand(char *par, char *out);
    char *setCommand(char *par, char *val, char *out);

};

#endif // CLED_H
