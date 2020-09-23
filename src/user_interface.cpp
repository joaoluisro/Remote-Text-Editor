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

/*
vector<string> convert_user_command(vector<string> parsed_input, int client_seq){
  // verifica a quantidade necessária de mensagens a serem enviadas
  int msg_n;
  vector<string> messages_to_send;

  string message = input_to_msg(parsed_input);
  if(parsed_input[0] == "cd" || parsed_input[0] == "ls"){
    int data_size = parsed_input[1].size();
    msg_n = data_size/15 + 1*(data_size % 15 > 0);

    for(int i = 0; i < msg_n; i++){
      messages_to_send.push_back(input_to_msg(parsed_input, client_seq, 15, "00001111", "hello server");)
    }
  }

  // cd -> nome do diretorio > 15 bytes

  // ls -> arquivos listados > 15 bytes

  // ver -> nome do arquivo > 15 bytes


}
*/

// define os protocolos para cada comando


int main(){

  // diretório inicial
  string curr_dir = get_dir();

  // conecta a interface de loopback
  int socket = ConexaoRawSocket("lo");

  // inicia a sequencialização
  int client_seq = 0;
  int received_seq;
  int seq_server = 0;

  // entrada parsado
  vector<string> parsed_input;

  // mensagem a ser enviada
  string raw_msg;

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

    // adiciona os campos da mensagem: envelopa a entrada em uma mensagem
    raw_msg = wrap_msg(client_seq, msg_type(parsed_input[0]), "00001111", parsed_input[1]);

    msg_set.push_back(raw_msg);

    while(1){

      // envia a mensagem
      for(int i = 0; i < msg_set.size(); i++) send_message(msg_set[i], socket);

      // espera a resposta
      do{
        raw_msg = receive_message(socket, true);
        cout << raw_msg << endl;
      }while(raw_msg == "timeout");

      divided_msg = divide_msg(raw_msg);
      received_seq = get_received_seq(divided_msg);
      received_type = divided_msg[3];

      // re-envia a mensagem
      if(received_type == NACK) continue;

      if(received_type != "0000" && received_seq >= client_seq){
        // a mensagem é do servidor
        cout << raw_msg << endl;

        // responde com um ACK
        string response = wrap_msg(client_seq + 1, ACK, "00001111", "");
        send_message(response, socket);
        client_seq += 2;
      }

      // fim da transmissão, processa a próxima mensagem
      if(received_type == END_OF_TRANSMISSION) break;
    }
    msg_set.clear();
  }

}
