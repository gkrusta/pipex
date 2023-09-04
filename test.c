#include <unistd.h>
#include <stdio.h>
int main (int argc, char * argv[], char *envp[]) {
	char* arguments[] = {"/bin/ls", "-l", NULL};
	int ret_val = execve (arguments[0], arguments, envp);
	printf("ret value ->%i", ret_val); 
}
