#include <iostream>
#include "../headers/ConexaoRawSocket.h"
#include <bits/stdc++.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <unistd.h>

int binary_char_to_int(const char *binary_num);
void substring(char s[], char sub[], int p, int l);
void send_message(std::string msg, int socket);
std::string receive_message(int socket);
std::vector<std::string> parse_command(std::string command);
void cd(std::string nome_dir);
void ls();
void ver(std::string nome_arq);
void linha(std::string num_linha, std::string nome_arq);
void linhas(std::string num_linha_inicial, std::string num_linha_final, std::string nome_arq);
void edit(std::string num_linha, std::string nome_arq, std::string novo_texto);
std::string convert_command(std::vector<std::string> args, int count, int tam, std::string parity, std::string data);
