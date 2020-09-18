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
    string mensagem = convert_command(parsed_command, 13, tam, parity, data);

    // envia a mensagem
    send_message(mensagem, socket);
  }
}
