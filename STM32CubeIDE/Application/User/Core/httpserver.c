
/* Includes ------------------------------------------------------------------*/
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/apps/fs.h"
#include "string.h"
#include <stdio.h>
#include "httpserver.h"
#include "cmsis_os.h"
#include "userStructs.h"
#include "lwip/apps/httpd.h"

#include <math.h>
#include <stdio.h>




extern PassDataMeas modelMeasPassData;
int indx = 0;
/* we will use character "x", "y","z" as tag for SSI */
char const* TAGCHAR[]={"sF", "sT", "sP"};
char const** TAGS=TAGCHAR;


/* CGI Defines */
tCGI CGI_TAB[2];
const char *CGIForm_Handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);
const char *CGILED_Handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

const tCGI FORM_CGI = {"/form.cgi", CGIForm_Handler};
const tCGI LED_CGI = {"/led.cgi", CGILED_Handler};

char name[30];
char colour;
char * colour2;

int testInt = 0;
int testInt1 = 0;



uint16_t ssi_handler (int iIndex, char *pcInsert, int iInsertLen)
{

	switch (iIndex) {
		case 0:
			indx+=1;
			sprintf(pcInsert, "%d", (int)modelMeasPassData.flowMeas[modelMeasPassData.newestMeasIndex]);
			return strlen(pcInsert);
			break;
		case 1:
			indx+=1;
			//char* number[10];

			//char* numberInsert = gcvt(modelMeasPassData.tempMeas[modelMeasPassData.newestMeasIndex], 3, number);
			sprintf(pcInsert, "%d", (int)modelMeasPassData.tempMeas[modelMeasPassData.newestMeasIndex]);
			//sprintf(pcInsert, numberInsert);
			return strlen(pcInsert);
			break;
		case 2:
			indx+=1;
			sprintf(pcInsert, name);// "%d", modelMeasPassData.presMeas[modelMeasPassData.newestMeasIndex]);
			return strlen(pcInsert);
			break;
		default :
			break;
	}

	return 0;
}



static void http_server(struct netconn *conn)
{
	struct netbuf *inbuf;
	err_t recv_err;
	char* buf;
	u16_t buflen;
	struct fs_file file;

	/* Read the data from the port, blocking if nothing yet there */
	recv_err = netconn_recv(conn, &inbuf);

	if (recv_err == ERR_OK)
	{
		if (netconn_err(conn) == ERR_OK)
		{
			netbuf_data(inbuf, (void**)&buf, &buflen);

			/* Get the data pointer and length of the data inside a netbuf */
			/* Check if request to get the index.html */
			if (strncmp((char const *)buf,"GET /index.html",15)==0)
			{
				fs_open(&file, "/index.html");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			if (strncmp((char const *)buf,"GET /dataPlotter.html",15)==0)
			{
				fs_open(&file, "/dataPlotter.html");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			if (strncmp((char const *)buf,"GET /js/dataPlotter.js",15)==0)
			{
				fs_open(&file, "/js/dataPlotter.js");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			if (strncmp((char const *)buf,"GET /js/plottly.js",15)==0)
			{
				fs_open(&file, "/js/plottly.js");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			/*
			if (strncmp((char const *)buf, "GET /ssipage.shtml", 18) == 0) {
				fs_open(&file, "/ssipage.shtml");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			if (strncmp((char const *)buf, "GET /cgiform.html", 17) == 0) {
				fs_open(&file, "/cgiform.shtml");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}*/
			if (strncmp((char const *)buf,"GET /img/ST.gif",15)==0)
			{
				fs_open(&file, "/img/ST.gif");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			if (strncmp((char const *)buf,"GET /img/stm32.jpg",18)==0)
			{
				fs_open(&file, "/img/stm32.jpg");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			if (strncmp((char const *)buf,"GET /img/logo.jpg",17)==0)
			{
				fs_open(&file, "/img/logo.jpg");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			if (strncmp((char const *)buf,"GET /buttoncolor=",17)==0)
			{
				colour = buf[17];
			}
			if (strncmp((char const *)buf, "GET /getvalue", 13) == 0)
			{
				char* pageData;
				pageData = pvPortMalloc(10);
				int len = sprintf (pageData, "%d", indx++);
				netconn_write(conn, (const unsigned char*) pageData, (size_t) len, NETCONN_NOCOPY);
				vPortFree(pageData);
			}
			else
			{
				/* Load Error page */
				fs_open(&file, "/404.html");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}

			/*
			 * 			netbuf_data(inbuf, (void**)&buf, &buflen);
			 *
			 */
			/* Check if request to get the index.html
			if (strncmp((char const *)buf,"GET /index.html",15)==0)
			{
				testInt = 1;
				fs_open(&file, "/index.html");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			else if (strncmp((char const *)buf, "GET /ssipage.shtml", 18) == 0) {
				fs_open(&file, "/ssipage.shtml");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			else if (strncmp((char const *)buf, "GET /cgiform.html", 17) == 0) {
				fs_open(&file, "/cgiform.shtml");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			if (strncmp((char const *)buf,"GET /buttoncolor=", 17)==0)
			{
				testInt = 2;
				colour2 = (char const *) buf;
				//memset(colour, '\0', 30);
				strcpy(colour, "Color Has been Updated -G");
			}
			if (strncmp((char const *)buf,"GET /B",6)==0)
			{
				testInt = 3;
				colour2 = (char const *) buf;

				//memset(colour, '\0', 30);
				strcpy(colour, "Color Has been Updated - B");

			}
			else
			{
				testInt = 4;
				 Load Error page
				fs_open(&file, "/404.html");
				netconn_write(conn, (const unsigned char*)(file.data), (size_t)file.len, NETCONN_NOCOPY);
				fs_close(&file);
			}
			*/
		}
	}
	/* Close the connection (server closes in HTTP) */
	netconn_close(conn);

	/* Delete the buffer (netconn_recv gives us ownership,
   so we have to make sure to deallocate the buffer) */
	netbuf_delete(inbuf);
}


static void http_thread(void *arg)
{
  struct netconn *conn, *newconn;
  err_t err, accept_err;

  /* Create a new TCP connection handle */
  conn = netconn_new(NETCONN_TCP);

  if (conn!= NULL)
  {
    /* Bind to port 80 (HTTP) with default IP address */
    err = netconn_bind(conn, IP_ADDR_ANY, 80);

    if (err == ERR_OK)
    {
      /* Put the connection into LISTEN state */
      netconn_listen(conn);

      while(1)
      {
        /* accept any incoming connection */
        accept_err = netconn_accept(conn, &newconn);
        if(accept_err == ERR_OK)
        {
          /* serve connection */
          http_server(newconn);

          /* delete connection */
          netconn_delete(newconn);
        }
      }
    }
  }
}

/*
void http_server_init()
{
  sys_thread_new("http_thread", http_thread, NULL, DEFAULT_THREAD_STACKSIZE, osPriorityNormal);
}
*/









const char *CGIForm_Handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
	testInt = testInt;
	if (iIndex == 0)
	{
		for (int i=0; i<iNumParams; i++)
		{
			if (strcmp(pcParam[i], "fname") == 0)  // if the fname string is found
			{
				memset(name, '\0', 30);
				strcpy(name, colour);
				//strcpy(name, pcValue[i]);
			}/*

			else if (strcmp(pcParam[i], "lname") == 0)  // if the lname string is found
			{
				strcat(name, " ");
				strcat(name, pcValue[i]);
			}
			*/
		}
	}

	return "/ssipage.shtml";
}


const char *CGILED_Handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
	if (iIndex == 1)
	{
		for (int i=0; i<iNumParams; i++)
		{
			if (strcmp(pcParam[i], "fname") == 0)  // if the fname string is found
			{
				memset(name, '\0', 30);
				strcpy(name, pcValue[i]);
			}

			else if (strcmp(pcParam[i], "lname") == 0)  // if the fname string is found
			{
				strcat(name, " ");
				strcat(name, pcValue[i]);
			}
		}
	}

	return "/cgiled.html";
}



void http_server_init (void)
{
	//httpd_init();
	sys_thread_new("http_thread", http_thread, NULL, DEFAULT_THREAD_STACKSIZE, osPriorityNormal);


	http_set_ssi_handler(ssi_handler, (char const**) TAGS, 3);
/*
	CGI_TAB[0] = FORM_CGI;
	CGI_TAB[1] = LED_CGI;

	http_set_cgi_handlers (&FORM_CGI, 1);
	http_set_cgi_handlers (CGI_TAB, 2);
*/


}
