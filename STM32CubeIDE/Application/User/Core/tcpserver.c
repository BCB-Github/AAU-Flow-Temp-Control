/*
 * tcpserver.c
 *
 *  Created on: Apr 20, 2022
 *      Author: controllerstech.com og Jakob
 */

#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "lwip/opt.h"

#include "lwip/api.h"
#include "lwip/sys.h"

#include "tcpserver.h"
#include "string.h"
//#include "tcpfunctions.h"
extern osSemaphoreId_t tcpsemHandle;

static struct netconn *conn, *newconn;
static struct netbuf *buf;
static ip_addr_t *addr;
static unsigned short port;
char msg[100];
char smsg[500];
int len;
int errorint;
int sendingFlowState = 0;
int sendingTempState = 0;
extern int minsDataCount;

extern int flowSetValue;
extern float avgFlow, avgTemp;



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
					// Release the semaphore once the connection is successful
					//sys_sem_signal(&tcpsem);
					while (1)
					{
						/* receive the data from the client */
						while (netconn_recv(newconn, &buf) == ERR_OK)
						{
							/* Extract the address and port in case they are required */
							addr = netbuf_fromaddr(buf);  // get the address of the client
							port = netbuf_fromport(buf);  // get the Port of the client

							/* If there is some data remaining to be sent, the following process will continue */
							do
							{
								// semaphore must be taken before accessing the tcpsend function
								osSemaphoreAcquire(tcpsemHandle,osWaitForever);
								if (strlen(buf->p->payload) > 100) {
									len = sprintf (smsg, "Input string too large, max input is 100 characters\n");
									// send the data to the server
									tcpsend(smsg);
								} else {
									strncpy (msg, buf->p->payload, buf->p->len);   // get the message from the client
									checkCommand(msg);
									// send the data to the server
									tcpsend(smsg);
									memset (msg, '\0', 100);  // clear the buffer
								}

							}
							while (netbuf_next(buf) >0);

							netbuf_delete(buf);
						}
						/*if (sendingState == 1) {
							len = sprintf (smsg, "The current flowrate is %d\n", (int)avgFlow);
							netconn_write(newconn, smsg, len, NETCONN_COPY);

						}*/
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

void tcpsend (char *data)
{
	// send the data to the connected connection
	netconn_write(newconn, smsg, strlen(smsg), NETCONN_COPY);
	memset (smsg, '\0', 500);  // clear the output buffer
	// release the semaphore
	osSemaphoreRelease(tcpsemHandle);
}


static void tcpsend_thread (void *arg)
{
	for (;;)
	{
		if (xQueueReceive(sendServerErrorQ, &errorint, 0)==pdTRUE) {
			osSemaphoreAcquire(tcpsemHandle,osWaitForever);
			if (errorint == 0) {
				len = sprintf(smsg, "Error: Flow control running at max\n");
			} else if (errorint == 1) {
				len = sprintf(smsg, "Error: Pressure limit reached, returning to standby\n");
			}
			tcpsend(smsg);
		}
		else if ((sendingFlowState == 1) | (sendingTempState == 1))
		{
			// semaphore must be taken before accessing the tcpsend function
			osSemaphoreAcquire(tcpsemHandle,osWaitForever);

			if (sendingFlowState == 1)
			{
				char flowmsg[100];
				sprintf(flowmsg, "Current flow rate is: %d [ul/min]\n", (int)avgFlow);
				strcat(smsg, flowmsg);
			}
			if (sendingTempState == 1)
			{
				char tempmsg[100];
				int B4point;
				float afterpoint;
				B4point = (int)avgTemp;
				afterpoint = ((avgTemp-B4point)*10);
				sprintf(tempmsg, "Current temperature is: %d.%d [C]\n", B4point, (int)afterpoint);
				strcat(smsg, tempmsg);
			}
			// send the data to the server
			tcpsend(smsg);
		}
		osDelay(1000);
	}
}

void tcpserver_init(void)
{
	//sys_sem_new(tcpsem, 0);  // the semaphore would prevent simultaneous access to tcpsend
	sys_thread_new("tcp_thread", tcp_thread, NULL, DEFAULT_THREAD_STACKSIZE,osPriorityNormal);
	sys_thread_new("tcpsend_thread", tcpsend_thread, NULL, DEFAULT_THREAD_STACKSIZE,osPriorityNormal);
}

