#include <iostream>
#include <conio.h>
#include "_7seg.h"
using namespace std;

int main() {
	_7seg obj(350, 450, "Code7Seg - John MacTavish");
	while(true) {
        	obj.typeDisp();
        	obj.ledDisp();
        	obj.codeDisp();
        	obj.mouseEvent();
		delay(10);
	}
}
