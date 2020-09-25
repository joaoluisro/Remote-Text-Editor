#include <iostream>
#include "../headers/ConexaoRawSocket.h"
#include <bits/stdc++.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <unistd.h>

#define NACK "1001"
#define ACK  "1000"
#define END_OF_TRANSMISSION "1101"
#define MARKER "01111110"

int binary_char_to_int(const char *binary_num);
std::string int_to_binary_char(int n, int size);
void substring(char s[], char sub[], int p, int l);
void send_message(std::string msg, int socket);
std::string receive_message(int socket, bool time_out);
std::vector<std::string> parse_input(std::string input);
void cd(std::string nome_dir, std::string &home_dir);
std::string ls(std::string curr_dir);
std::string msg_type(std::string arg);
std::string ver(std::string nome_arq);
void linha(std::string num_linha, std::string nome_arq);
void linhas(std::string num_linha_inicial, std::string num_linha_final, std::string nome_arq);
void edit(std::string num_linha, std::string nome_arq, std::string novo_texto);
std::string input_to_msg(std::vector<std::string> args, int count, int tam, std::string parity, std::string data);
std::vector<std::string> divide_msg(std::string msg);
int get_received_seq(std::vector<std::string> interpreted_msg);
bool wait_message(int socket);
std::string get_parity(std::string marker, std::string type, std::string tam, std::string seq);
bool check_parity(std::vector<std::string> d_msg);
std::string wrap_msg(int count, std::string marker, std::string type, std::string data);
std::string get_dir();
void execute(std::string type, std::vector<std::string> divided_msg, std::string &curr_dir);
