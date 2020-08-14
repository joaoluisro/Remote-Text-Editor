#include <iostream>
#include <bits/stdc++.h>
#include "../utils/utils.h"
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
  cout << instruction;


}


int main(){

  string input = "cd nome_dir";
  parse_command(input);
  return 0;
}
