#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include "../headers/utils.h"
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
void parse_command(string input){
  vector<string> command = split_string(input);
  string instruction = command[0];
  cout << instruction << "\n";
  /*
  switch (command) {
    case "cd":
      cd();
      break
    case "lcd":
      lcd();
      break
    case "lls":
      lls();
      break
    case "ver":
      ver();
      break
    case "linha":
      linha();
      break
    case "linhas":
      linhas();
      break
    case "edit":
      edit();
      break
    default:
      cout << "Instrução não suportada"
      break
  }
  */
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
