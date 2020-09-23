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
  int seq_server = 0;
  int received_seq;
  int expected = 0;

  // mensagem a ser recebida
  string raw_msg;

  vector<string> parsed_input;

  // mensagem divida
  vector<string> divided_msg;

  string received_type;


  while(1){

    // espera o cliente
    do{
      raw_msg = receive_message(socket, true);
      cout << raw_msg << endl;
    }while(raw_msg == "timeout");
    divided_msg = divide_msg(raw_msg);
    received_seq = get_received_seq(divided_msg);
    received_type = divided_msg[3];

    if(received_type != "0001" && received_seq == expected){
      cout << raw_msg << endl;
      // a mensagem é do cliente
      //interpret_msg(divided_msg, received_type, curr_dir);

      string response = wrap_msg(seq_server, END_OF_TRANSMISSION, "00001111", "");
      send_message(response, socket);
      execute(received_type, divided_msg, curr_dir);
      expected++;
      seq_server++;
    }
  }
}
