
#include <map>
#include <list>
#include <vector>
#include <sys/time.h>
#include <aibase/compiler.h>
#include <ailogger/Log_Msg.h>
#include <ailogger/ailogger.h>

using namespace std;
using namespace ailogger;


int main () {

	string logFile = "log/cdc/ascheck_testzz_01.log";
	Logger logger("AIBDB", logFile);
    std::string tmp = "123456789012345678901234567890123456789012345678901234567890";
	OSS_DEBUG((LM_STARTUP, "ascheck startup ...\n"));
    while (1)
	    OSS_DEBUG((LM_INFO,"infinite loop log,%s \n",tmp.c_str()));
    return 0;
}


