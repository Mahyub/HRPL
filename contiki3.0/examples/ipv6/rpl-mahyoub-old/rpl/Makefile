CONTIKI=../../../..
CONTIKI_PROJECT = app-any-to-any #app-collect-only app-down-only app-any-to-any
CFLAGS += -DPROJECT_CONF_H=\"project-conf.h\"
TARGET=sky

WITH_UIP6=1
UIP_CONF_IPV6=1
CFLAGS+= -DUIP_CONF_IPV6_RPL
PROJECTDIRS += ../common ../common/tools 
PROJECT_SOURCEFILES += rpl-tools.c node-id.c

ifdef NO_WARNINGS
	CFLAGS += -w
endif

CYCLE_TIME ?= 500
CFLAGS += -DCMD_CYCLE_TIME=$(CYCLE_TIME)

PHASE_LOCK ?= 1
CFLAGS += -DCMD_PHASE_LOCK=$(PHASE_LOCK)


all: $(CONTIKI_PROJECT) 
include $(CONTIKI)/Makefile.include

%.exe: %.sky
	cp $< $@
