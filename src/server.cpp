#include "../headers/ConexaoRawSocket.h"
#include "../headers/editorlib.h"
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#define PORT 8081

using namespace std;
void interpret_msg(vector<vector<string>> messages){

}

vector<vector<string>> read_msg(vector<string> args){
  // verifica a quantidade necessária de mensagens a serem enviadas
  int msg_n = 1;

  // cd -> nome do diretorio > 15 bytes

  // ls -> arquivos listados > 15 bytes

  // ver -> nome do arquivo > 15 bytes
}

int main(){


  // conecta ao cliente
  int socket = ConexaoRawSocket("lo");

  // inicia a sequencialização
  int seq_server = 0;
  int received_seq;
  int seq_client = 0;

  // mensagem a ser recebida
  string raw_msg;

  vector<string> parsed_input;

  // mensagem interpretada
  vector<string> interpreted_msg;

  string received_type;

  // recebe a primeira mensagem
  raw_msg = receive_message(socket);
  interpreted_msg = divide_msg(raw_msg);
  received_seq = get_received_seq(interpreted_msg);

  while(1){

    // prepara uma resposta
    parsed_input = parse_input("ls");
    raw_msg = input_to_msg(parsed_input, seq_server, 11, "00001111", "hello client");
    send_message(raw_msg, socket);

    // espera o cliente
    raw_msg = receive_message(socket);
    interpreted_msg = divide_msg(raw_msg);
    received_seq = get_received_seq(interpreted_msg);
    received_type = interpreted_msg[3];

    if(received_type != "0001" && received_seq >= seq_server){
      // a mensagem é do cliente
      cout << raw_msg << endl;
      seq_server++;
    }

  }
}
