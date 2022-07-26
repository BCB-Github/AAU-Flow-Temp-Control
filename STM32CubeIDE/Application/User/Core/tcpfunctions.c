/*
 * tcpfunctions.c
 *
 *  Created on: Jul 25, 2022
 *      Author: Jakob
 *   The function reads the message sent from the client as a command and executes accordingly
 */

#include "stdio.h"
#include "ctype.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "lwip/opt.h"

#include "lwip/api.h"
#include "lwip/sys.h"

#include "string.h"
#include "tcpfunctions.h"

extern int tempSetValue;
extern int flowSetValue;
extern int tempStartState;
extern int tempStopState;
extern int flowStartState;
extern int flowStopState;
extern int plimit;
extern xQueueHandle motorSwitchQ;

extern int len, sendingFlowState, sendingTempState;
extern char smsg[500];


void checkCommand(char input[])
{
	char firstChar = tolower(input[0]);
	char secondChar = tolower(input[1]);
	char fourthChar = tolower(input[3]);
	char fifthChar = tolower(input[4]);
	char sixthChar = tolower(input[5]);
	switch (firstChar) {
	case ('g'):
		switch (fourthChar) {   // Assumes a 'get' is followed by either temp or flow
		case ('f'):
			len = sprintf (smsg, "Sending flow rate continuously\n");
			sendingFlowState = 1;
			break;
		case ('t'):
			len = sprintf (smsg, "Sending temperature continuously\n");
			sendingTempState = 1;
			break;
		default:
			len = sprintf (smsg, "Unknown command. Type help for a list of commands\n");
			break;
		}

		break;

	case ('s'): ;
		if (secondChar == 't') {
			switch (fourthChar) {
			case ('p'):
				switch (fifthChar) {
					case ('d'):
						sendingFlowState = 0;
						sendingTempState = 0;
						len = sprintf (smsg, "Data transmission stopped\n");
						break;
					case ('f'):
						flowStartState = 0;
						flowStopState = 0;
						xQueueSend(motorSwitchQ, 0, 0);
						len = sprintf (smsg, "Flow rate control stopped\n");
						break;
					case ('t'):
						tempStartState = 0;
						tempStopState = 0;
						len = sprintf (smsg, "Temperature control stopped\n");
						break;
					default:
						len = sprintf (smsg, "Unknown command. Type help for a list of commands\n");
						break;
				}
				break;
			case ('r'):
				switch (sixthChar) {
					case ('f'):
						flowStartState = 1;
						flowStopState = 1;
						xQueueSend(motorSwitchQ, 1, 0);
						len = sprintf (smsg, "Flow rate control started\n");
						break;
					case ('t'):
						tempStartState = 1;
						tempStopState = 1;
						len = sprintf (smsg, "Temperature control started\n");
						break;
					default:
						len = sprintf (smsg, "Unknown command. Type help for a list of commands\n");
						break;
				}
				break;
			}
		} else {
			int index = 4;
			while (input[index] > 64) {
				index++;
				if (index > 20) goto error;
			}

			int setpoint = atoi(&input[index]);

			switch (fourthChar) {	// Assumes a 'set' is followed by either temp or flow
			case ('f'):
				flowSetValue = setpoint;
				len = sprintf (smsg, "Flow rate set to %d [ul/min]\n", setpoint);
				break;
			case ('t'):
				tempSetValue = setpoint;
				len = sprintf (smsg, "Temperature set to %d [C]\n", setpoint);
				break;
			case ('p'):
				plimit = setpoint;
				len = sprintf (smsg, "Pressure limit set to %d [bar]\n", setpoint);
				break;
			default:
				len = sprintf (smsg, "Unknown command. Type h for a list of commands\n");
				break;
			}
			break;
			error: ; // Jumps here if no number is found following the command
			len = sprintf (smsg, "Read command as setpoint but no number could be found\n"
					"Example forms: \"setflow750\" or \"settemp 42\"\n");
			break;
		}



	case ('h'):
		len = sprintf (smsg, "List of commands:\n"
				"gettemp/getflow: Starts sending current measured values every second\n"
				"stopdata: Stops the transmission of all measured values\n"
				"settemp/setflow: Followed by a whole number, the Set Points are changed to the number\n"
				"setplimit: Follow by a whole number in bar, the limit is changed to the number\n"
				"start or stop, followed by temp or flow: Starts or stops the control loops\n"
				"help: You're here right now.\n");
		break;

	default:
		len = sprintf (smsg, "Unknown command. Type help for a list of commands\n");
		break;
	}

}

