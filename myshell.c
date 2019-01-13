#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>


const int MAX = 1024;
const int NUM = 16;

//模拟实现简易shell 命令+参数
//进程的程序替换来实现想要运行的命令
int main()
{
  //要输入命令前提是要有一个缓冲区
  char cmd[MAX];
  char* myargv[NUM];
  while(1)
  {
    printf("[XJH@localhost myshell]# ");

   //将命令行上的内容读到缓冲区上
   //scanf("%s",cmd);
   fgets(cmd,sizeof(cmd),stdin);
   cmd[strlen(cmd)-1] = '\0';
   //尝试解析内容   exec函数族   带p的 execvp
   int i = 0;
   myargv[i++] = strtok(cmd," ");  //ls -a -b ...
   char* ret = NULL;
   
   while(ret = strtok(NULL," "))  //说明此时ret结果并不为空
   {
     myargv[i++] = ret;
   }
   myargv[i] = NULL;

   pid_t id = fork();
   if(id == 0)
   {
     execvp(myargv[0],myargv);
     exit(1);
   }
   else
   {
     //parent
     waitpid(id,NULL,0);
   }
  }
  return 0;
}




