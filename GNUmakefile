 # $Id: GNUmakefile 22 2009-12-22 12:36:46Z schaelic $
 # --------------------------------------------------------------
 # GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
 # --------------------------------------------------------------
 
 name := exl_v2
 G4TARGET := $(name)
 G4EXLIB := true
 
 .PHONY: all
 all: lib bin
 
 include $(G4INSTALL)/config/architecture.gmk
 
 #Add ROOT options for compilation
# CPPFLAGS += `root-config --cflags` $(shell $(CLHEPSYS)/bin/clhep-config --include)
# LDFLAGS  += `root-config --libs` $(shell $(CLHEPSYS)/bin/clhep-config --libs)
# CPPFLAGS  += $(shell $(ROOTSYS)/bin/root-config --cflags) $(shell $(CLHEPSYS)/bin/clhep-config --include)
# EXTRALIBS += $(shell $(ROOTSYS)/bin/root-config --glibs) $(shell $(CLHEPSYS)/bin/clhep-config --libs)
 CPPFLAGS  += $(shell $(ROOTSYS)/bin/root-config --cflags)
 EXTRALIBS += $(shell $(ROOTSYS)/bin/root-config --glibs)

 include $(G4INSTALL)/config/binmake.gmk
CXXFLAGS  += -fPIC 
