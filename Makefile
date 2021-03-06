
# Makefile сборки сервера

SRCDIR = ./src
OBJDIR = ./bin
CLIENTDIR = ./client
INSTALLDIR =./ 

CPP = g++

all: LedServer

clean: 
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/LedServer

main.o: $(SRCDIR)/main.cpp 
	$(CPP) -c -I$(SRCDIR) -o $(OBJDIR)/main.o $(SRCDIR)/main.cpp

ledserver.o: $(SRCDIR)/ledserver.cpp
	$(CPP) -c -I$(SRCDIR) -o $(OBJDIR)/ledserver.o $(SRCDIR)/ledserver.cpp

cled.o: $(SRCDIR)/cled.cpp
	$(CPP) -c -I$(SRCDIR) -o $(OBJDIR)/cled.o $(SRCDIR)/cled.cpp

LedServer: main.o ledserver.o cled.o	
	$(CPP) -o $(OBJDIR)/LedServer $(OBJDIR)/main.o $(OBJDIR)/ledserver.o $(OBJDIR)/cled.o
	

install: 
	install $(OBJDIR)/LedServer $(CLIENTDIR)/clientLed $(CLIENTDIR)/serverLed /usr/local/bin

uninstall:
	rm -f /usr/local/bin/LedServer /usr/local/bin/clientLed /usr/local/bin/serverLed


