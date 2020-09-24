#include "../headers/ConexaoRawSocket.h"
#include "../headers/editorlib.h"
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>
#define PORT 8081

using namespace std;


int main(){

  // diretório inicial
  string curr_dir = get_dir();

  // conecta a interface de loopback
  int socket = ConexaoRawSocket("lo");

  // inicia a sequencialização
  int client_seq = 0;
  int received_seq;
  int seq_server = 0;
  int expected = 1;

  // entrada parsado
  vector<string> parsed_input;

  // mensagem a ser enviada
  string raw_msg, buffer;

  // mensagem divida
  vector<string> divided_msg;

  // conjunto de mensagens
  vector<string> msg_set;
  string received_type;
  while(1){
    // recebe os comandos de entrada do usuário, linha inteira
    string input, curr_type;
    getline(cin, input);
    if(input == "halt") break;

    // parsa a entrada : retorna o comando e seus argumentos
    parsed_input = parse_input(input);

    if(parsed_input[0] == "cd"){
      cd(parsed_input[1], curr_dir);
      continue;
    }else if(parsed_input[0] == "ls"){
      cout << ls(curr_dir);
      continue;
    }
    if(parsed_input[0] == "lls") parsed_input.push_back("");

    curr_type = msg_type(parsed_input[0]);
    // adiciona os campos da mensagem: envelopa a entrada em uma mensagem
    raw_msg = wrap_msg(client_seq, curr_type, "00001111", parsed_input[1]);



    // envia a mensagem
    send_message(raw_msg, socket);
    client_seq += 2;

    // aguarda resposta
    do{
      buffer = receive_message(socket, true);
      if(buffer == "timeout") continue;
      divided_msg = divide_msg(buffer);
      received_seq = get_received_seq(divided_msg );
      received_type = divided_msg[3];
    }while(received_seq != expected);

    cout << buffer << endl;
    expected += 2;
    parsed_input.clear();
  }

}
