/*************************************************
 * Designed to test communications with the xbee *
 * on ttyS0    aaaa                                  *
 ************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <xbee.h>

 
int main(int argc, char** argv)
{
	struct xbee *xbee;
	struct xbee_con *con;
	struct xbee_conAddress *add;
	struct xbee_pkt *pkt;
    int timeout = 0;
    xbee_err err = 0;

    /* setup libxbee */
	if ((xbee_setup(&xbee, "xbee1", "/dev/ttyS0", 9600)) != XBEE_ENONE) {
	/* or you can use the network! */
	//if ((ret = xbee_setup(&xbee, "net", "127.0.0.1", 27015)) != XBEE_ENONE) {
		exit(1);
	}
	
	if(NULL == (con = malloc(sizeof(con))))
	{
	    printf("Failure to allocate for xbee_con\n");
	    exit(1);
	}
    //con = NULL;
	
	if(NULL == (add = malloc(sizeof(add))))
	{
	    printf("Failure to allocate for xbee_conAddress\n");
	    exit(1);
	}
	
	if(NULL == (pkt = malloc(sizeof(pkt))))
	{
	    printf("Failure to allocate for xbee_pkt\n");
	    exit(1);
	}
	
	add->addr16_enabled = 1;
	add->addr16[0] = 0x00;
	add->addr16[1] = 0x01;
	

    if((err = xbee_validate(xbee)) != XBEE_ENONE)
    {
        printf("Invalid xbee handle.\n");
        printf("ERR: %s\n", xbee_errorToStr(err));
        exit(1);
    }
    
    {
        char **types;
        int i;

        /* initialize xbee, using xbee_setup() */

        if (xbee_conGetTypes(xbee, &types) != XBEE_ENONE) exit(1);

        for (i = 0; types[i]; i++) {
            printf("type %d: %s\n", i, types[i]);
        }

        free(types);
    }
	
	if((err = xbee_conNew(xbee, &con, "16-bit Data", add)) != XBEE_ENONE)
	{
	    printf("Failed to initiate connection\n");
        printf("Error Desc.: %s\n", xbee_errorToStr(err));
        exit(1);
	}

    do
    {
			printf("TEST");
        //if(xbee_conRx(
    } while(++timeout < 10);
    
    if(NULL != pkt)
    {
        xbee_pktFree(pkt);
    }

    printf("End of xbee test\n");
    return 0;
}
 
