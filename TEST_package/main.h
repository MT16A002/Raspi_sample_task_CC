// TEST_package.h : 標準のシステム インクルード ファイル用のインクルード ファイル、
// または、プロジェクト専用のインクルード ファイル。
#define MAIN
#ifdef MAIN


//#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/select.h>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <chrono>


//タスク間で共通のグローバル
struct Common
{
  int init;
  int count;
  int fin;
};

void init(Common& global);


#endif //_H_MAIN

// TODO: プログラムに必要な追加ヘッダーをここで参照します。
