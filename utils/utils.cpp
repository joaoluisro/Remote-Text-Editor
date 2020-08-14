#include <iostream>
#include <bits/stdc++.h>
using namespace std;


vector<string> split_string(string input){
  string aux = "";
  vector<string> final_str;
  int j = 0;

  for (int i = 0; i <= input.size(); i++){
    if (input[i] == ' ' || input[i] == '\0'){
      final_str.push_back(aux);
      aux = "";
      j++;
      continue;
    }
    aux += input[i];
  }
  return final_str;
}
