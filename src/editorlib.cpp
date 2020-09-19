#include <iostream>
#include "../headers/ConexaoRawSocket.h"
#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
using namespace std;

string int_to_binary_char(int n, int size){
  int *binaryNum = new int[size];
  int i = 0;
  while (n > 0) {
    binaryNum[i] = n % 2;
    n = n / 2;
    i++;
  }
  char *binary_char = new char[size];
  if(size == 4) strcpy(binary_char, "0000");
  else strcpy(binary_char, "00000000");
  int k = size - 1;
  for(int j = i - 1; j >= 0 ; j--){
    char c = '0' + binaryNum[j];
    binary_char[k] = c;
    k--;
  }
  std::string str(binary_char);
  return binary_char;
}

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

bool wait_message(int socket){
  char buffer[1024] = {0};
  int val_read = read(socket, buffer, 1024);
  cout << val_read;
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

void cd(string nome_dir, string &home_dir){
  home_dir = nome_dir;
  //string shell_command = "cd " + nome_dir;
  //system(shell_command.c_str());
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
o 0000 – cd – nome do diretório viaja na área de dados
o 0001 – ls
o 0010 – ver – nome arquivo viaja na área de dados
o 0011 – linha – nome arquivo viaja na área de dados
o 0100 – linhas – nome arquivo viaja na área de dados
o 0101 – edit – nome arquivo viaja na área de dados
*/


string msg_type(string arg){

    string type;
    if(arg == "cd"){
      type = "0000";
    }else if(arg == "ls"){
      type = "0001";
    }else if(arg == "ver"){
      type = "0010";
    }else if(arg == "linha"){
      type = "0011";
    }else if(arg == "linhas"){
      type = "0100";
    }else if(arg == "edit"){
      type = "0101";
    }else if(arg == "ACK"){
      type = "1000";
    }else if(arg == "NACK"){
      type = "1001";
    }else if(arg == "lines"){
      type = "1010";
    }else if(arg == "c_ls"){
      type = "1011";
    }else if(arg == "c_arq"){
      type = "1100";
    }else if(arg == "end_t"){
      type = "1101";
    }else if(arg == "error"){
      type = "1111";
    }
    return type;
}

// envelopa a mensagem adicionando os campos de marcador, tamanho, tipo, sequencialização, e paridade.

string convert_command(vector<string> args,
                              int count,
                              int tam,
                              string parity,
                              string data){

  vector<string> converted_message;
  // adiciona o marcador
  converted_message.push_back("01111110");

  // adiciona o tamanho
  converted_message.push_back(int_to_binary_char(tam, 4));

  // adiciona a sequencialização
  converted_message.push_back(int_to_binary_char(count, 8));

  // adiciona o tipo
  converted_message.push_back(msg_type(args[0]));

  //adiciona os dados
  converted_message.push_back(data);

  // adiciona a paridade
  converted_message.push_back(parity);

  // junta tudo na mensagem
  string msg;
  for(int i = 0; i < converted_message.size(); i++) msg += converted_message[i];
  return msg;
}

// "separa" a mensagem recebida do cliente

vector<string> divide_msg(string msg){
  vector<string> divided_msg;

  // recebe a primeira string com 8 caracteres -> marcador
  divided_msg.push_back(msg.substr(0, 8));

  // recebe a segunda string com 4 caracteres -> tamanho
  divided_msg.push_back(msg.substr(8, 4));

  string tam_s = msg.substr(8,4);
  int tam = binary_char_to_int(tam_s.c_str());

  // recebe a terceira string com 8 caracteres -> sequencialização
  divided_msg.push_back(msg.substr(12, 8));

  // recebe a quarta string com 4 caracteres -> tipo
  divided_msg.push_back(msg.substr(20, 4));

  //recebe o campo de dados
  divided_msg.push_back(msg.substr(24, tam));

  // recebe a paridade
  divided_msg.push_back(msg.substr(24 + tam, 8));
  return divided_msg;
}
