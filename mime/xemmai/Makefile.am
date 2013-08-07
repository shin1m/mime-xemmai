xemmaidir = $(XEMMAI_MODULE_PATH)

xemmai_PROGRAMS = mime.so
AM_CPPFLAGS = $(XEMMAI_CFLAGS)
AM_CXXFLAGS = -std=c++11 -fPIC
AM_LDFLAGS = -shared
if DEBUG
AM_CXXFLAGS += -g
else
AM_CPPFLAGS += -DNDEBUG
AM_CXXFLAGS += -O3
endif
if PROFILE
AM_CXXFLAGS += -pg
AM_LDFLAGS += -pg
endif
mime_so_LDADD = $(XEMMAI_LIBS)
mime_so_SOURCES = \
	base64.h \
	base64.cc \
	quoted_printable.h \
	quoted_printable.cc \
	mime.h \
	mime.cc
