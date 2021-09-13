CONTIKI=../../contiki3.0
CONTIKI_PROJECT=app-p2p-sim-root app-p2p-sim-node 

CFLAGS += -DPROJECT_CONF_H=\"project-conf.h\"
TARGET=wismote
CONTIKI_WITH_IPV6 = 1
CFLAGS += -DUIP_CONF_IPV6_RPL 
CFLAGS += -DROOT_ID=1
CFLAGS+= -DN_NODES=50
CFLAGS+= -DN_FLOWS=24
PROJECTDIRS += hrpl-tools
PROJECTDIRS += ../hrpl
PROJECT_SOURCEFILES +=  hrpl-tools.c simple-energest.c  hrpl.c hrpl-discovery-manager.c hrpl-links-manager.c hrpl-route-manager.c

all: $(CONTIKI_PROJECT)
include $(CONTIKI)/Makefile.include
