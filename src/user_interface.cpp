#include "../headers/ConexaoRawSocket.h"
#include "../headers/editorlib.h"
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <stdio.h>
#define PORT 8081

using namespace std;

vector<vector<string>> convert_user_command(vector<string> args){
  // verifica a quantidade necessária de mensagens a serem enviadas
  int msg_n = 1;

  // cd -> nome do diretorio > 15 bytes

  // ls -> arquivos listados > 15 bytes

  // ver -> nome do arquivo > 15 bytes


}

int main(){
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

  // mensagem interpretada
  vector<string> interpreted_msg;

  string received_type;
  while(1){
    // recebe os comandos de entrada do usuário, linha inteira
    string input;
    getline(cin, input);
    if(input == "halt") break;


    while(1){
      // parsa a entrada : retorna o comando e seus argumentos
      parsed_input = parse_input(input);

      // adiciona os campos da mensagem: envelopa a entrada em uma mensagem
      raw_msg = input_to_msg(parsed_input, client_seq, 12, "00001111", "hello server");

      // envia a mensagem
      send_message(raw_msg, socket);

      // espera a resposta
      raw_msg = receive_message(socket);
      interpreted_msg = divide_msg(raw_msg);
      received_seq = get_received_seq(interpreted_msg);
      received_type = interpreted_msg[3];

      if(received_type != "0000" && received_seq >= client_seq){
        // a mensagem é do server
        cout << raw_msg << endl;
        client_seq++;
        break;
      }

    }
  }

}
