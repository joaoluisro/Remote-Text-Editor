#include "../headers/ConexaoRawSocket.h"
#include "../headers/editorlib.h"
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#define PORT 8081

using namespace std;

void interpret_msg(vector<string> messages, string type, string curr_dir){
  // comando ls
  if(type == "0001"){
    string ls_content = ls(curr_dir);

  }
}

int main(){

  // diretório inicial
  string curr_dir = get_dir();

  // conecta ao cliente
  int socket = ConexaoRawSocket("lo");

  // inicia a sequencialização
  int seq_server = 1;
  int received_seq;
  int expected = 0;

  // mensagem a ser recebida
  string raw_msg, buffer;

  vector<string> parsed_input;

  // mensagem divida
  vector<string> divided_msg;

  string received_type;


  while(1){
    //  espera a primeira mensagem

    do{
      buffer = receive_message(socket, true);
      if(buffer == "timeout") continue;
      divided_msg = divide_msg(buffer);
      received_seq = get_received_seq(divided_msg);
      received_type = divided_msg[3];
    }while(received_seq != expected);
    expected += 2;

    // executa o comando
    execute(received_type, divided_msg, curr_dir);
    raw_msg = wrap_msg(seq_server, ACK, "00001111", "");
    send_message(raw_msg, socket);
    seq_server += 2;
  }

}
