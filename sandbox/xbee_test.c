/*************************************************
 * Designed to test communications with the xbee
 * on ttyS0
 ************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <xbee.h>

 
int main(int argc, char** argv)
{
	struct xbee *xbee;
    int timeout = 0;

    /* setup libxbee */
	if ((xbee_setup(&xbee, "xbee1", "/dev/ttyS0", 9600)) != XBEE_ENONE) {
	/* or you can use the network! */
	//if ((ret = xbee_setup(&xbee, "net", "127.0.0.1", 27015)) != XBEE_ENONE) {
		exit(1);
	}

    do
    {

    } while(++timeout < 1000);

    printf("End of xbee test\n");
    return 0;
}
 
