#include "Robot.h"
#include <iostream>

int main(int argc, char *argv[])
{
	Robot r("603132548:AAH9RAl4fTiwi2-uxH-YJnzJlEqzC9rgjG8", "Pinky");
	r.setupTelegram();
	r.setRecivingStatus(true);
	r.receiveMessages();
	return 0;
}
