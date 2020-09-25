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

vector<string> response(vector<string> d_msg, string type, string &curr_dir, int &count){
  vector<string> msg_set;
  // se "lcd", mude o diretório
  if(type == "0000"){
    cd(d_msg[4], curr_dir);
  }

  // se "lls", envie o conteudo do ls no diretorio atual
  else if(type == "0001"){
    string ls_content = ls(curr_dir);
    int content_size = ls_content.size();
    int remainder = content_size % 15;
    for(int i = 0; i < content_size/15; i++){
      string ls_i = ls_content.substr(i * 15, 15);
      msg_set.push_back(wrap_msg(count,MARKER, "1011", ls_i));
      count += 2;
    }
    if(remainder != 0){
      string ls_i = ls_content.substr((content_size/15) * 15, remainder);
      msg_set.push_back(wrap_msg(count, MARKER, "1011", ls_i));
      count += 2;
    }
  }

  else if(type == "0010"){
    string ver_content = ver(d_msg[4]);
    int content_size = ver_content.size();
    int remainder = content_size % 15;
    for(int i = 0; i < content_size/15; i++){
      string ver_i = ver_content.substr(i * 15, 15);
      msg_set.push_back(wrap_msg(count,MARKER, "1100", ver_i));
      count += 2;
    }
    if(remainder != 0){
      string ver_i = ver_content.substr((content_size/15) * 15, remainder);
      msg_set.push_back(wrap_msg(count, MARKER, "1100", ver_i));
      count += 2;
    }
  }

  // adicione um fim de transmissão
  msg_set.push_back(wrap_msg(count, MARKER, END_OF_TRANSMISSION, ""));
  count += 2;
  return msg_set;
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

  vector<string> msg_set;

  string received_type;
  int i = 0;

  while(1){
    //  espera a mensagem do cliente
    do{
      buffer = receive_message(socket, false);

      // divide a mensagem em campos
      divided_msg = divide_msg(buffer);
      received_seq = get_received_seq(divided_msg);
      received_type = divided_msg[3];

      // checa a paridade e o marcador, envia um NACK caso hajam erros
      if(!check_parity(divided_msg) || divided_msg[0] != MARKER){
        send_message(wrap_msg(seq_server, MARKER, NACK, ""), socket);
        seq_server += 2;
        continue;
      }

    // condição do loop : sequencia esperada = sequencia recebida
    }while(received_seq != expected);
    expected += 2;

    // se recebeu ACK e chegou no final das mensagens do servidor, repita o processo
    if(received_type == ACK && i == msg_set.size()){
      i = 0;
      continue;
    }

    // se recebeu um comando do cliente, construa as mensagens
    if(received_type != ACK) msg_set = response(divided_msg, received_type, curr_dir, seq_server);

    // envie todas as mensagens
    if(i < msg_set.size()){
      send_message(msg_set[i], socket);
      i++;
    }
  }

}
