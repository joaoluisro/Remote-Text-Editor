#include <iostream>
#include "../headers/ConexaoRawSocket.h"
#include <bits/stdc++.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <unistd.h>

int binary_char_to_int(const char *binary_num);
std::string int_to_binary_char(int n, int size);
void substring(char s[], char sub[], int p, int l);
void send_message(std::string msg, int socket);
std::string receive_message(int socket);
std::vector<std::string> parse_input(std::string input);
void cd(std::string nome_dir, std::string &home_dir);
void ls();
void ver(std::string nome_arq);
void linha(std::string num_linha, std::string nome_arq);
void linhas(std::string num_linha_inicial, std::string num_linha_final, std::string nome_arq);
void edit(std::string num_linha, std::string nome_arq, std::string novo_texto);
std::string input_to_msg(std::vector<std::string> args, int count, int tam, std::string parity, std::string data);
std::vector<std::string> divide_msg(std::string msg);
int get_received_seq(std::vector<std::string> interpreted_msg);
bool wait_message(int socket);
bool is_from_client(std::vector<std::string> d_msg);
bool is_from_server(std::vector<std::string> d_msg);
std::string get_dir();
