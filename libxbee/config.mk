### libxbee configuration options:

### system install directories
SYS_LIBDIR:=    /usr/lib
SYS_INCDIR:=    /usr/include
#SYS_MANDIR:=    /usr/share/man
SYS_MANDIR:=    ./tmp
SYS_GROUP:=     root
SYS_USER:=      root

### setup a cross-compile toolchain (either here, or in the environment)
#CROSS_COMPILE?= 
#CFLAGS+=        
#CLINKS+=        

### un-comment to remove ALL logging (smaller & faster binary)
#OPTIONS+=       XBEE_DISABLE_LOGGING

### use for more precise logging options
#OPTIONS+=       XBEE_LOG_LEVEL=100
#OPTIONS+=       XBEE_LOG_RX
#OPTIONS+=       XBEE_LOG_TX

### un-comment to disable strict objects (xbee/con/pkt pointers are usually checked inside functions)
### this may give increased execution speed, but will be more suseptible to incorrect parameters
#OPTIONS+=       XBEE_DISABLE_STRICT_OBJECTS

### un-comment to remove network server functionality
#OPTIONS+=       XBEE_NO_NET_SERVER
#OPTIONS+=       XBEE_NO_NET_STRICT_VERSIONS

### un-comment to turn off hardware flow control
#OPTIONS+=       XBEE_NO_RTSCTS

### un-comment to use API mode 2
#OPTIONS+=       XBEE_API2
#OPTIONS+=       XBEE_API2_DEBUG
#OPTIONS+=       XBEE_API2_IGNORE_CHKSUM
#OPTIONS+=       XBEE_API2_SAFE_ESCAPE

### useful for debugging the core of libxbee
#OPTIONS+=       XBEE_NO_FINI
