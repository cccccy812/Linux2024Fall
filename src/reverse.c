#include "../include/reverse.h"

char *reverse(char *dest,const char *src){
int len=0;

while (src[len] !='\0'){
	len++;
}
for(int i=0;i<len;i++){
dest[i]=src[len-1-i];
}
dest[len]='\0';
return dest;
}
