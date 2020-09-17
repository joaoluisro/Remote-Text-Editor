#include "../headers/ConexaoRawSocket.h"
#include "../headers/editorlib.h"
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#define PORT 8081

using namespace std;

vector<string> divide_msg(string msg){
  vector<string> divided_msg;
  divided_msg.push_back(msg.substr(0, 8));
  divided_msg.push_back(msg.substr(8, 4));
  string tam_s = msg.substr(8,4);
  int tam = binary_char_to_int(tam_s.c_str());
  divided_msg.push_back(msg.substr(12, 8));
  divided_msg.push_back(msg.substr(20, 4));
  divided_msg.push_back(msg.substr(24, tam));
  divided_msg.push_back(msg.substr(24 + tam, 8));
  return divided_msg;
}

int main(){
  // conecta ao cliente
  int socket = ConexaoRawSocket("lo");
  // comando dado pelo usuário
  string msg = receive_message(socket);
  vector<string> d_msg = divide_msg(msg);

  for(int i = 0; i < d_msg.size(); i++){
    cout << d_msg[i] << "\n";
  }
  //cout << msg;
  //int received = receive_int(socket);
  //string received = receive_message(socket);
  //cout << buffer << "\n";

}
