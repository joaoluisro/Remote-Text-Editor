#ifndef CLIENTE_H
#define CLIENTE_H
void cd(string nome_dir);
void ls();
void ver(string nome_arq);
vpod linha(string num_linha, string nome_arq);
void linhas(string num_linha_inicial, string num_linha_inicial, string nome_arq);
void edit(string num_linha, string nome_arq, string novo_texto);
void parse_command(string input);

#endif /* CLIENTE_H*/
