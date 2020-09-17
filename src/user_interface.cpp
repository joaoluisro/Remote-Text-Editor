#include "../headers/ConexaoRawSocket.h"
#include "../headers/editorlib.h"
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <stdio.h>
#define PORT 8081
using namespace std;

int main(){
  // conecta a interface de loopback
  int socket = ConexaoRawSocket("lo");
  // comando parsado
  vector<string> parsed_command;
  string msg_to_server = "1011110101110101101101010100001111101101101101101101101010111101110";
  send_message(msg_to_server, socket);
  //send_message(msg, socket);
  //printf("%d\n", sizeof(msg));
  //string s = "abcdefgh";
  //char *c = "abcdefgh";
  //printf("%s\n", msg->marker);
  //printf("%d\n", sizeof(c));
  ///send_int(n, socket);
  //string message = "hello from receive";
  //send_message(message, socket);

  /*
  while(1){
    // recebe os comandos de entrada do usuário
    string input;
    getline(cin, input);
    if(input == "halt"){
      break;
    }

    // parsa em comandos e argumentos
    parsed_command = parse_command(input);

    // envia a mensagem
    message = parsed_command[0];
    send_message(message, socket);
  }

  */
}
