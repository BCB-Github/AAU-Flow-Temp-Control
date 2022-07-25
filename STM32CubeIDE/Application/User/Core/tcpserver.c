/*
 * tcpserver.c
 *
 *  Created on: Apr 20, 2022
 *      Author: controllerstech.com
 */

#include "lwip/opt.h"

#include "lwip/api.h"
#include "lwip/sys.h"

#include "tcpserver.h"
#include "string.h"

static struct netconn *conn, *newconn;
static struct netbuf *buf;
static ip_addr_t *addr;
static unsigned short port;
char msg[100];
char smsg[200];
int len;
int sendingState = 0;
extern int minsDataCount;

extern int flowSetValue;
extern float avgFlow;



/**** Send RESPONSE every time the client sends some data ******/
static void tcp_thread(void *arg)
{
	err_t err, accept_err, recv_error;

	/* Create a new connection identifier. */
	conn = netconn_new(NETCONN_TCP);

	if (conn!=NULL)
	{
		/* Bind connection to the port number 7. */
		err = netconn_bind(conn, IP_ADDR_ANY, 7);

		if (err == ERR_OK)
		{
			/* Tell connection to go into listening mode. */
			netconn_listen(conn);

			while (1)
			{
				/* Grab new connection. */
				accept_err = netconn_accept(conn, &newconn);

				/* Process the new connection. */
				if (accept_err == ERR_OK)
				{

					/* receive the data from the client */
					while (netconn_recv(newconn, &buf) == ERR_OK)
					{
						/* Extrct the address and port in case they are required */
						addr = netbuf_fromaddr(buf);  // get the address of the client
						port = netbuf_fromport(buf);  // get the Port of the client

						/* If there is some data remaining to be sent, the following process will continue */
						do
						{

							strncpy (msg, buf->p->payload, buf->p->len);   // get the message from the client

							checkCommand(msg);

							netconn_write(newconn, smsg, len, NETCONN_COPY);  // send the message back to the client
							memset (msg, '\0', 100);  // clear the buffer
						}
						while (netbuf_next(buf) >0);

						if (sendingState == 0) {
							len = sprintf (smsg, "The current flowrate is %d\n", (int)avgFlow);
							netconn_write(newconn, smsg, len, NETCONN_COPY);
							osDelay(10);
						}
						netbuf_delete(buf);
					}


					/* Close connection and discard connection identifier. */
					netconn_close(newconn);
					netconn_delete(newconn);
				}
			}
		}
		else
		{
			netconn_delete(conn);
		}
	}
}


void tcpserver_init(void)
{
  sys_thread_new("tcp_thread", tcp_thread, NULL, DEFAULT_THREAD_STACKSIZE,osPriorityNormal);
}

void checkCommand(char input[])
{
	/*switch (input[0]) {
	case ('G' | 'g'):
		switch (input[3]) {
		case ('F' | 'f'):
			len = sprintf (smsg, "Received: \"%s\"\n Was the command \"getFlow\"?\n", input);
			break;
		}
		break;
	default:
		len = sprintf (smsg, "Received: \"%s\"\n Unknown command\n", input);
		break;
	} */
	if (input[0] == 'G' | input[0] == 'g') {
		len = sprintf (smsg, "Received: \"%s\"\n Was the command \"getFlow\"?\n", input);
		sendingState = 1;
	} else {
		len = sprintf (smsg, "Received: \"%s\"\n Unknown command\n", input);
	}
	/* Extract command */
	char cmdOnly[8] = {'\0'};
	int commandLength = 0;
	do {
		cmdOnly[commandLength] = input[commandLength];
		commandLength++;
		if (commandLength == 8) {break;}

	} while (input[commandLength] != ' ');
	char cmdOnly2[commandLength+1];
	for (int x = 0;x<commandLength+1;x++) {
		cmdOnly2[x] = cmdOnly[x];
	}
	char compare[8] = "getData";
	//for (int z = commandLength; z<10; z++) {
	//	cmdOnly[z] = '\0';
	//}
	if (cmdOnly==compare) {
		len = sprintf (smsg, "Received: \"%s\"\n Was the command \"%s\"?\n MinsDataCount: %d\n", compare, cmdOnly, minsDataCount);
	}
	if (input[0] == '1') {
		int newSetValue = atoi(&input[1]);
		flowSetValue = newSetValue;
		len = sprintf (smsg, "Received: \"%s\"\n Changed flowSetValue to: %d\n", input, newSetValue);
	}
	// Or modify the message received, so that we can send it back to the client
	//len = sprintf (smsg, "Received: \"%s\"\n Was the command \"%s\"?\n I reached index %d\n", command, cmdOnly2, commandLength);
	//}
}
