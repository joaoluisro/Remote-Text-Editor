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

    // comandos do próprio cliente
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
    raw_msg = wrap_msg(client_seq, MARKER, curr_type, parsed_input[1]);

    // envia a mensagem
    send:
    send_message(raw_msg, socket);
    client_seq += 2;

    // aguarda resposta
    do{
      buffer = receive_message(socket, true);

      // em caso de timeout, re-envie
      if(buffer == "timeout") goto send;

      // caso a mensagem tenha chegado, divida ela em campos
      divided_msg = divide_msg(buffer);
      received_seq = get_received_seq(divided_msg );
      received_type = divided_msg[3];

      // checa a paridade e o marcador, envia um NACK caso hajam erros
      if(!check_parity(divided_msg) || divided_msg[0] != MARKER){
        send_message(wrap_msg(client_seq, MARKER, NACK, ""), socket);
        client_seq += 2;
        continue;
      }

      // em caso de NACK, re-envie
      if(received_type == NACK) goto send;

      // condição do loop: sequencia esperada = sequencia recebida
    }while(received_seq != expected);
    expected += 2;

    // adiciona a mensagem no vetor de mensagens
    msg_set.push_back(divide_msg(buffer)[4]);

    // responde com um ACK caso não tenha chegado no final da transmissão
    raw_msg = wrap_msg(client_seq, MARKER, ACK, "");
    if(received_type != END_OF_TRANSMISSION) goto send;

    // chegou no final, responde com um ultimo ACK
    send_message(raw_msg, socket);
    client_seq += 2;

    // exibe o conteúdo das mensagens do servidor
    for(int i = 0 ; i < msg_set.size(); i++) cout << msg_set[i];
    msg_set.clear();
  }

}
