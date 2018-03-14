
//Commands:
//	w-Move forward
//	a-Move left
//	d-Move right
//	s-Move back
//	x-Stop

#include "BrickPi3.h"   // for BrickPi3
#include <iostream>      // for printf
#include <unistd.h>     // for usleep
#include <signal.h>     // for catching exit signals

using namespace std;

BrickPi3 BP;

void exit_signal_handler(int signo);

//Stop
void stop(void)
{
	 BP.set_motor_dps(PORT_B, 0);
	 BP.set_motor_dps(PORT_C, 0);
}

//Move Forward
void fwd(void)
{
	 BP.set_motor_power(PORT_B, 40);
	 BP.set_motor_power(PORT_C, 40);
	 sleep(3);
	 stop();

}
//Move Left
void left(void)
{
	 BP.set_motor_dps(PORT_B, 90);
	 BP.set_motor_dps(PORT_C, -90);
}
//Move Right
void right(void)
{
	 BP.set_motor_dps(PORT_B, -90);
	 BP.set_motor_dps(PORT_C, 90);
}
//Move backward
void back(void)
{
	 BP.set_motor_dps(PORT_B, -180);
	 BP.set_motor_dps(PORT_C, -180);
	 sleep(3);
	 stop();
}

int main()
{
	signal(SIGINT, exit_signal_handler); // register the exit function for Ctrl+C
  	BP.detect(); // Make sure that the BrickPi3 is communicating and that the firmware is compatible with the drivers.
  	char inp;

	while(true)
	{
		cout << "Press f (forward), b (backward), l(left), r (right), s (stop): " << endl;
		cin.get(inp);	//Take input from the terminal
		//Move the bot
		if(inp=='f') {
			  	BP.set_motor_power(PORT_B, 25);
			  	BP.set_motor_power(PORT_C, 25);
			}

		else if (inp=='b') {
			  	BP.set_motor_power(PORT_B, -25);
			  	BP.set_motor_power(PORT_C, -25);
			}

		else if (inp=='l'){
				BP.set_motor_power(PORT_B, -25);
			  	BP.set_motor_power(PORT_C, 25);
			}
		else if (inp=='r'){
				BP.set_motor_power(PORT_B, 25);
				BP.set_motor_power(PORT_C, -25);
			}
		else if (inp=='s'){
				BP.set_motor_power(PORT_B, 0);
				BP.set_motor_power(PORT_C, 0);
			}



		usleep(100000);			//sleep for 10 ms
	}

	return 0;
}

// Signal handler that will be called when Ctrl+C is pressed to stop the program
void exit_signal_handler(int signo){
  if(signo == SIGINT){
    BP.reset_all();    // Reset everything so there are no run-away motors
    exit(-2);
  }
}