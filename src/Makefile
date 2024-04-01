##  Jaydip Singh // Developed for STT-ND group studies //
## Date : 20/03/2015
## Prof. Sanjib Mishra

 
SHELL = /bin/sh
NAME = all
MAKEFILE = Makefile

# Include machine specific flags and locations (inc. files & libs)
#
include $(GENIE)/src/make/Make.include

GENIE_LIBS  = $(shell $(GENIE)/src/scripts/setup/genie-config --libs)
LIBRARIES  := $(GENIE_LIBS) $(LIBRARIES) $(CERN_LIBRARIES)


TGT =	 Event_Ana_tool	 \
	 Event_NuInt_Ana_tool
all: $(TGT)

Event_Ana_tool: FORCE
	$(CXX) $(CXXFLAGS) -c Event_Ana_tool.cxx $(CPP_INCLUDES)
	$(LD) $(LDFLAGS) Event_Ana_tool.o $(LIBRARIES) -o $(PWD)/Event_Ana_tool

Event_NuInt_Ana_tool: FORCE
	$(CXX) $(CXXFLAGS) -c Event_NuInt_Ana_tool.cxx $(CPP_INCLUDES)
	$(LD) $(LDFLAGS) Event_NuInt_Ana_tool.o $(LIBRARIES) -o $(PWD)/Event_NuInt_Ana_tool

#################### CLEANING

purge: FORCE
	$(RM) *.o *~ core 

clean: FORCE
	$(RM) *.o *~ core 
	$(RM) Event_Ana_tool
	$(RM) Event_NuInt_Ana_tool
distclean: FORCE
	$(RM) $(GENIE_BIN_INSTALLATION_PATH)/Event_Ana_tool
	$(RM) $(GENIE_BIN_INSTALLATION_PATH)/Event_NuInt_Ana_tool

FORCE:

# DO NOT DELETE
