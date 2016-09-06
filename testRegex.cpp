#include <string>
#include <sys/types.h>
#include <regex.h>

using namespace std;
int main(int argc,char* argv[]) {
    //string pattern="DR_GPRS_[0-9]+_B-.*";
    string pattern="DR_GPRS_.*_A.*";
    string src="DR_GPRS_201605_A-160504194600-10941.dat";
    string matched_ = "";
    string error_ = "";
    // compile
    regex_t reg;
    int z = regcomp(&reg,pattern.c_str(),0);
    if(z != 0) {
        char ebuf[128],tmp[1024];
        regerror(z,&reg,ebuf,sizeof(ebuf));
        sprintf(tmp,"%s: regcomp('%s')\n",ebuf,pattern.c_str());
        error_ = string(tmp);
        printf("error_%s\n",error_.c_str() );
        return -1;
    }
    // execute
    const size_t nmatch = 10;
    regmatch_t pm[10];
    z = regexec(&reg,src.c_str(),nmatch,pm,0);
    if(z == REG_NOMATCH) {
        error_ = "no match";
        regfree(&reg);
        printf("error_%s\n",error_.c_str() );
        return 1;
    }
    else if(z != 0) {
        char ebuf[128],tmp[1024];
        regerror(z,&reg,ebuf,sizeof(ebuf));
        sprintf(tmp,"%s: regexec('%s')\n",ebuf,src.c_str());
        error_ = string(tmp);
        printf("error_%s\n",error_.c_str() );
        regfree(&reg);
        return 2;
    }
    // free
    printf("right\n");
    regfree(&reg);
    return 0;
}
