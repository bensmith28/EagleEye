DEFCONFIG:=            freebsd.mk
BUILD_RULES:=          unix.mk
INSTALL_RULES:=        unix.mk

AS=                    $(CROSS_COMPILE)as
GCC=                   $(CROSS_COMPILE)gcc
LD=                    $(CROSS_COMPILE)ld
OBJCOPY=               $(CROSS_COMPILE)objcopy
AR=                    $(CROSS_COMPILE)ar
DEFLATE:=              gzip
SYMLINK:=              ln
MKDIR=                 @if [ ! -d $* ]; then echo "mkdir -p $*"; mkdir -p $*; else echo "!mkdir $*"; fi
RM:=                   rm -f
RMDIR:=                rm -rf
INSTALL=               install -g $(SYS_GROUP) -o $(SYS_USER)

DEBUG:=                -g
CFLAGS+=               -Wall -c -fPIC $(DEBUG) $(addprefix -D,$(OPTIONS))
#CFLAGS+=              -pedantic
CFLAGS+=               -fvisibility=hidden
CPPFLAGS:=             $(CFLAGS)
CFLAGS+=               -Wstrict-prototypes -Wno-variadic-macros
CLINKS+=               $(addprefix -l,$(LIBS)) $(DEBUG)

LIB_OUT:=              $(DESTDIR)/$(LIBNAME).so \
                       $(DESTDIR)/$(LIBNAME).a

INSTALL_FILES=         $(SYS_LIBDIR)/$(LIBNAME).so.$(LIBFULLREV)                    \
                       $(SYS_LIBDIR)/$(LIBNAME).so.$(LIBFULLREV).dbg                \
                       $(SYS_LIBDIR)/$(LIBNAME).so                                  \
                       $(SYS_LIBDIR)/$(LIBNAME).a.$(LIBFULLREV)                     \
                       $(SYS_LIBDIR)/$(LIBNAME).a                                   \
                       $(addprefix $(SYS_MANDIR)/,$(addsuffix .gz,$(SYS_MANPAGES))) \
                       $(SYS_INCDIR)/xbee.h

RELEASE_FILES=         $(DESTDIR)/$(LIBNAME).so.$(LIBFULLREV)     \
                       $(DESTDIR)/$(LIBNAME).so.$(LIBFULLREV).dbg \
                       $(DESTDIR)/$(LIBNAME).so                   \
                       $(DESTDIR)/$(LIBNAME).a.$(LIBFULLREV)      \
                       $(DESTDIR)/$(LIBNAME).a                    \
                       $(addprefix $(MANDIR)/,$(SYS_MANPAGES))    \
                       xbee.h                                     \
                       README HISTORY COPYING COPYING.LESSER

CLEAN_FILES=           $(BUILDDIR)/*.o \
                       $(BUILDDIR)/*.d

VER_DEFINES=           -DLIB_REVISION="\"$(LIBFULLREV)\""                             \
                       -DLIB_COMMIT="\"$(shell git log -1 --format="%H")\""           \
                       -DLIB_COMMITTER="\"$(shell git log -1 --format="%cn <%ce>")\"" \
                       -DLIB_BUILDTIME="\"$(shell date)\""
