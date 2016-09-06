
INCLUDES=-I.
bin_LDADD=$(ACE_LIB) -laibase -laiodbc -laiodbc_uac -laicdc -lailogger -laicrypto
bin_SOURCES=logtest.o 
bin_PROGRAMS=logtest

