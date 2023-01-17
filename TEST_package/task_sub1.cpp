#include"main.h"
#include"task_sub1.h"


//サブタスク1
void* task_sub1(void *global)
{
   struct Common *g_task = (Common*)global;
   while(1)
   {
       if(g_task->fin >= 1)break;
       sleep(0.1);
   }
   pthread_exit((void*)0);
}
