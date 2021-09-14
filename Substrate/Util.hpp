#include <string>

long getSoBase( const char *soname);

long getSoBase( const char *soname)  // credits to https://github.com/ikoz/AndroidSubstrate_hookingC_examples/blob/master/nativeHook3/jni/nativeHook3.cy.cpp
{
    if (soname == NULL)
        return 0;

    FILE *f = NULL;
    if ((f = fopen("/proc/self/maps", "r")) == NULL)
        return 0;

    char line[1024] = {0};
    char *tok = NULL;
    char *state = NULL;
    while ( fgets(line,sizeof(line),f) !=NULL){

        if (strstr(line,soname)!=NULL) //判断soname是否是line的子串
        {
            tok = strtok_r(line, "-", &state); //截取字符串
            fclose(f);
            long soBase = (long) strtoll(tok, NULL, 16); //将字符串转成16进制
            return  soBase;
        }
    }

    fclose(f);
    return 0;
}
