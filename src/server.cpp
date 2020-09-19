#include "../headers/ConexaoRawSocket.h"
#include "../headers/editorlib.h"
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#define PORT 8081

using namespace std;
extern int errno;
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

  // indica o diretório raiz
  string home_dir;
  system("pwd > tmp.txt");
  ifstream tmpfile("tmp.txt");
  getline(tmpfile, home_dir);
  system("rm tmp.txt");

  // inicia a conexão, espera a mensagem do cliente
  bool close_connection = false;
  string raw_msg = receive_message(socket);
  vector<string> d_msg = divide_msg(raw_msg);
  for(int i = 0; i < d_msg.size(); i++){
    cout << d_msg[i] << "\n";
  }

  while(1){

    // responde
    send_message(raw_msg, socket);
    raw_msg = receive_message(socket);

    d_msg = divide_msg(raw_msg);
    for(int i = 0; i < d_msg.size(); i++){
      cout << d_msg[i] << "\n";
    }

  }
}
