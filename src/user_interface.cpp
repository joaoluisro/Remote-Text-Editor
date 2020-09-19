#include "../headers/ConexaoRawSocket.h"
#include "../headers/editorlib.h"
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <errno.h>
#include <stdio.h>
#define PORT 8081

using namespace std;

extern int errno;
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
  int count = 0;

  // comando parsado
  vector<string> parsed_command;

  while(1){

    // recebe os comandos de entrada do usuário, linha inteira
    string input;
    getline(cin, input);
    if(input == "halt") break;

    // parsa em comandos e argumentos
    parsed_command = parse_command(input);

    // envelopa a mensagem
    // teste
    int tam = 5;
    string parity = "00001111";
    string data = "hello";
    string mensagem = convert_command(parsed_command, count, tam, parity, data);

    // envia a mensagem
    send_message(mensagem, socket);
    //string answer;
    //answer = receive_message(socket);
    // espera a resposta
    //string answer = receive_message(socket);
    //cout << answer << "\n";
    count++;
  }
}
