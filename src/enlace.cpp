#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <string>
#include <unistd.h>
#include <stdio.h>


void substring(char s[], char sub[], int p, int l) {
   int c = 0;

   while (c < l) {
      sub[c] = s[p+c-1];
      c++;
   }
   sub[c] = '\0';
}

int main(){

}
