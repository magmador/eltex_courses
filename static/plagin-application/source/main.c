#include <stdio.h>
#include "headerlib.h"
#include <dlfcn.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	struct complexNumber first;
	struct complexNumber second;
        first.realPart=-2;
        first.phantomPart=1;
        second.realPart=1;
        second.phantomPart=-1;
	void *lib_handler;
	char* funcName=(char*)malloc(10*sizeof(char));
	struct complexNumber (*ptrfunc[argc-1])(struct complexNumber, struct complexNumber); //функции для расчётов
	struct complexNumber (*readFunc[argc-1])(); //read функции
	void (*outFunc[argc-1])(struct complexNumber); //out функции
	char* (*retNameFunc)(); //получение имени функции для ldsym
	void (*funcFinish)(); //очищение памяти для имени
	int vart, firSec;
	printf("enter -1 for exit\n");
	for(int i=1;i<argc;++i)
        {
		if(argv[i][14]=='R')
		{
                	lib_handler = dlopen(argv[i], RTLD_NOW);
	                if(!lib_handler){
	                        fprintf(stderr, "dlopen() error: %s\n", dlerror());
	                        return 1;
        	        }
               		 else {
                        	retNameFunc = dlsym(lib_handler, "funcNameReturn");
	                        funcName = (*retNameFunc)();
	                        funcFinish = dlsym(lib_handler, "funcFinish");
        	                (*funcFinish)();
	                        if(funcName[0]=='R'){
                                	readFunc[i] = dlsym(lib_handler, funcName);
                                	printf("press %d to use %s\n", i, funcName);
                       		}
			}
		}
	}
	printf(">");
	scanf("%d", &vart);
	do{
		if(vart==-1) continue;
		printf("enter 1 for first and 2 for second>");
		scanf("%d", &firSec);
		if (firSec==1) 
			first=(*readFunc[vart])();
		else if (firSec==2) 
			second=(*readFunc[vart])();
		else {
			printf("input error. exit\n");
			return 1;
		}
		printf(">");
		scanf("%d", &vart);
	}while(vart!=-1);
        for(int i=1;i<argc;++i)
        {
                if(argv[i][14]=='O')
                {
                        lib_handler = dlopen(argv[i], RTLD_NOW);
                        if(!lib_handler){
                                fprintf(stderr, "dlopen() error: %s\n", dlerror());
                                return 1;
                        }
                         else {
                                retNameFunc = dlsym(lib_handler, "funcNameReturn");
                                funcName = (*retNameFunc)();
                                funcFinish = dlsym(lib_handler, "funcFinish");
                                (*funcFinish)();
                                if(funcName[0]=='O'){
        	                        outFunc[i] = dlsym(lib_handler, funcName);
	                                printf("press %d to use %s\n", i, funcName);
                                }
                        }
                }
        }
        printf(">");
        scanf("%d", &vart);
        do{
		if(vart==-1) continue;
                printf("enter 1 for first and 2 for second>");
                scanf("%d", &firSec);
                if (firSec==1) 
			(*outFunc[vart])(first);
		else if (firSec==2)
			(*outFunc[vart])(second);
                else {
                        printf("input error. exit\n");
                        return 1;
                }
                printf(">");
                scanf("%d", &vart);
        }while(vart!=-1);
        for(int i=1;i<argc;++i)
        {
                if(argv[i][14]!='O' && argv[i][14]!='R')
                {
                        lib_handler = dlopen(argv[i], RTLD_NOW);
                        if(!lib_handler){
                                fprintf(stderr, "dlopen() error: %s\n", dlerror());
                                return 1;
                        }
                        else {
                                retNameFunc = dlsym(lib_handler, "funcNameReturn");
                                funcName = (*retNameFunc)();
                                funcFinish = dlsym(lib_handler, "funcFinish");
                                (*funcFinish)();
                                if(funcName[0]!='O' && funcName[0]!='R'){
					ptrfunc[i] = dlsym(lib_handler, funcName);
	                                printf("press %d to use %s\n", i, funcName);
                                }
                        }
                }
        }
        printf(">");
        scanf("%d", &vart);
        do{
		if(vart==-1) continue;
		struct complexNumber result= (*ptrfunc[vart])(first,second);
		printf("(%d|%d, %d|%d) = %d|%d\n", first.realPart, first.phantomPart, second.realPart, second.phantomPart, result.realPart, result.phantomPart);
                printf(">");
                scanf("%d", &vart);
        }while(vart!=-1);
	dlclose(lib_handler);
	return 0;
}
