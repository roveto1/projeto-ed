// reading a text file - gcc -o teste teste.cpp -lstdc++
#include "array_stack.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int Aninhamento (string arquivo, structures::ArrayStack<string>* pilha) {
  string line;
  string altura;
  string largura;
  int matriz = 1;

  
  //Matriz que armazena todas as dimensoes
  vector<vector<int>> dimensoes;
  //Vetor que armazena apenas as dimensoes do cenario atual
  vector<int> dimensao_local;


  string file = arquivo;
  ifstream myfile (file);
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      for (int i = 0; i < line.length(); i++){
        if (line[i] == '<') {
            int j = i;
            string palavra;
            if (line[i+1] != '/') {
                while (line[j] != '>') {
                    palavra.push_back(line[j]);
                    j++;
                }
                palavra.push_back(line[j]);
                pilha->push(palavra);

              
//Coletando tags de dimensao da matriz ----------------------------
              
            if (palavra == "<altura>"){
              
                  int k = j+1;
                  while (line[k] != '<'){
                    altura.push_back(line[k]);
                    ++k;
                    
                  }

                  //Converte a string para inetiro
                  int int_altura = stoi(altura);

                  //Guarda a altura no vetor de dimensao local
                  dimensao_local.push_back(int_altura);
              
                  altura = " ";
                }
              
                
            if (palavra == "<largura>"){
              matriz++;
              int k = j+1;
              while (line[k] != '<'){
                largura.push_back(line[k]);
                k++;
              }
              //Converte a string para inteiro
              int int_largura = stoi(largura);

              //Guarda a largura no vetor de dimensao local
              dimensao_local.push_back(int_largura);

              //Guarda as dimensoes do cenario atual na Matriz Geral
              dimensoes.push_back(dimensao_local);

              //Esvazia o vetor de dimensoes do cenario atual
              dimensao_local.clear();
              
              largura = " ";
              
            }
              
//----------------------------------------------------------------------



              
            } else {
                while (line[j] != '>') {
                    if (line[j] != '/') {
                    palavra.push_back(line[j]);
                    } 
                    j++;
                }
                palavra.push_back(line[j]);
              

              
                if (!pilha->empty()) {
                string temp = pilha->pop();
                if (temp != palavra) {
                    cout << file;
                    printf(": Erro de aninhamento\n");
                    return 0;
                }
                } else {
                    cout << file;
                    printf(": Erro de aninhamento\n");
                    return 0;
                }
            
      }
    }
      }
    }
    myfile.close();
    if (!pilha->empty()) {
        cout << file;
        printf(": Erro de aninhamento\n");
        return 0;
    }
  } else {
    cout << "Erro para abrir o arquivo" << endl;
    return 0;
  } 

  cout << file;
  printf(": Aninhamento Correto\n");


  
//----Printando as dimensoes------------------------------
  for (int i = 0; i < matriz-1; i++){
    for (int j = 0; j < 2; j++){
      cout << dimensoes[i][j] << endl;
    }
    cout << "\n";
  }
//---------------------------------------------------------


  
  return 0;
}


int main () {
    structures::ArrayStack<string> pilha(500);
    
    char xmlfilename[100];

    std::cin >> xmlfilename;  // entrada
    string xmlString = xmlfilename;
    Aninhamento(xmlString, &pilha);
    
    /*
     
       COLOQUE SEU CODIGO AQUI
    
    */

    return 0;
}