#include"main.h"
#include"task_sub2.h"


//サブタスク2
void* task_sub2(void* global)
{
  struct Common* g_task = (Common*)global;
  while (1)
  {
    if (g_task->fin >= 1)break;
    sleep(0.1);
  }
  pthread_exit((void*)0);
}
