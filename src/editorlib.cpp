#include <iostream>
#include "../headers/ConexaoRawSocket.h"
#include <bits/stdc++.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
using namespace std;

int binary_char_to_int(const char *binary_num)
{
    int num = atoi(binary_num);
    int dec_value = 0;
    int base = 1;
    int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;

        dec_value += last_digit * base;

        base = base * 2;
    }
    return dec_value;
}

void substring(char s[], char sub[], int p, int l) {
   int c = 0;

   while (c < l) {
      sub[c] = s[p+c-1];
      c++;
   }
   sub[c] = '\0';
}

void send_message(string msg, int socket){
  const char *msg_c = msg.c_str();
  write(socket, msg_c, strlen(msg_c));
}

string receive_message(int socket){
  char buffer[1024] = {0};
  read(socket, buffer, 1024);
  std::string str(buffer);
  return buffer;
}

/*
  cd     <nome_dir>
  lcd    <nome-dir>
  ls
  lls
  ver    <nome_arq>
  linha  <num_linha> <nome_arq>
  linhas <num_linha_inicial> <num_linha_final> <nome_arq>
  edit   <num_linha> <nome_arq> <novo_texto>
*/

void cd(string nome_dir){
  string shell_command = "cd " + nome_dir;
  system(shell_command.c_str());
}

void ls(){
  string shell_command = "ls";
  system(shell_command.c_str());
}

void ver(string nome_arq){
  string shell_command = "cat " + nome_arq;
  system(shell_command.c_str());
}

void linha(string num_linha, string nome_arq){
  string shell_command = "sed -n " + num_linha + "p " + nome_arq;
  system(shell_command.c_str());
}

void linhas(string num_linha_inicial, string num_linha_final, string nome_arq){
  string shell_command = "sed -n " + num_linha_inicial + "," + num_linha_final + "p " + nome_arq;
  system(shell_command.c_str());
}

void edit(string num_linha, string nome_arq, string novo_texto){
  string shell_command = "sed -i \'" + num_linha + "i" + novo_texto + "\' " + novo_texto;
  system(shell_command.c_str());
}

vector<string> parse_command(string input){
  // args : guarda o comando e seus argumentos
  vector<string> args;
  int previous = 0;

  for(int i = 0; i < input.size(); i++){
    if(isblank(input[i])){
      args.push_back(string(input.begin() + previous, input.begin() + i));
      previous = i+1;
    }
    if(i == input.size() - 1) args.push_back(string(input.begin() + previous, input.begin() + i + 1));
  }
  return args;
}
/*
void send_message(string message, int socket){
  // converte pra string em formato char*
  const char *c_message = message.c_str();

  // envia a mensagem
  send(socket, c_message, strlen(c_message), 0);
}

string receive_message(int socket){
  // buffer de 1024 bytes
  char buffer[1024] = {0};

  // lê a mensagem a armazena no buffer
  int val_read = read(socket, buffer, 1024);
  string str(buffer);
  return buffer;
}
*/
