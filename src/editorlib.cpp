#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <stdlib.h>

using namespace std;

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

void parse_command(string input){
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

  if(args[0] == "cd" || args[0] == "lcd") cd(args[1]);
  if(args[0] == "ls" || args[0] == "lls") ls();
  if(args[0] == "ver") ver(args[1]);
  if(args[0] == "linha") linha(args[1], args[2]);
  if(args[0] == "linhas") linhas(args[1], args[2], args[3]);
  if(args[0] == "edit") edit(args[1], args[2], args[3]);

}


int main(){

  while(1){
    string input;
    getline(cin, input);
    if(input == "halt"){
      break;
    }
    parse_command(input);
  }
  return 0;
}
