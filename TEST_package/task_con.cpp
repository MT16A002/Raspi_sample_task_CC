#include"main.h"
#include"task_con.h"

//TCP con task
void* task_con(void* global)
{
  struct Common* g_task = (Common*)global;
  int sock = -1, i = 0;
  while (1)
  {
    i++;
    // connction check
    if (sock == -1)
    {
      sock = establishConnection();
      std::cout << "Failed to establish connection." << std::endl;
      continue;
    }
    // Send a message to the server
    char message[MAX_SIZE];
    sprintf(message, "%d\n", i);
    int messageSize = strlen(message);
    if (send(sock, message, messageSize, 0) != messageSize)
    {
      sock = -1;
      std::cout << "Failed to send the message." << std::endl;
      close(sock);
      continue;
    }

    // Receive a response from the server
    char buffer[MAX_SIZE];
    int bytesRead = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead < 0)
    {
      std::cout << "Failed to receive data." << std::endl;
      close(sock);
      continue;
    }
    buffer[bytesRead] = '\0';
    std::cout << "Received response from server: " << buffer << std::endl;

    // Fin  
    if (g_task->fin >= 1)
    {
      close(sock);
      break;
    }
    sleep(0.1);
  }
  pthread_exit((void*)0);
}


int establishConnection() {

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
  {
    std::cout << "Failed to create socket." << std::endl;
    return -1;
  }

  sockaddr_in serverAddress{};
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(SERVER_PORT);

  if (inet_pton(AF_INET, SERVER_IP, &(serverAddress.sin_addr)) <= 0)
  {
    std::cout << "Invalid address or address not supported." << std::endl;
    return -1;
  }


  timeval timeout{};
  timeout.tv_sec = TIMEOUT_SECONDS;
  timeout.tv_usec = 0;

  if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&timeout), sizeof(timeout)) < 0)
  {
    std::cout << "Failed to set receive timeout." << std::endl;
  }
  if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<char*>(&timeout), sizeof(timeout)) < 0)
  {
    std::cout << "Failed to set send timeout." << std::endl;
  }

  int connectResult = connect(sock, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress));
  if (connectResult < 0)
  {
    std::cout << "Failed to connect to the server." << std::endl;
    close(sock);
    return -1;
  }
  else
  {
    std::cout << "Success." << std::endl;
  }
  return sock;

}

