#include<winbgim.h>

#ifndef _7SEG_H
#define _7SEG_H

class _7seg{
private:
    char led[8], type;
    char* hexa();
public:
    _7seg(int width, int height, char* title);
    void typeDisp();
    void ledDisp();
    void codeDisp();
    void mouseEvent();
};
#endif
