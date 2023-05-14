// reading a text file - gcc -o teste teste.cpp -lstdc++
#include "array_stack.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef struct matrizOriginal {
  int linha;
  int coluna;
  vector<vector<char>> matriz;
} matrizOriginal;

vector<matrizOriginal*> Aninhamento (string arquivo, structures::ArrayStack<string>* pilha) {
  string line;
  string altura;
  string largura;
  int matriz = 1;
  int leituraMatriz = 0;
  int linhaMatriz = 0;
  vector<vector<char>> matrizLocal;
  string erro1 = ": Erro de aninhamento";
  string erro2 = ": Arquivo nao encontrado";

  
  //Matriz que armazena todas as dimensoes
  vector<vector<int>> dimensoes;
  //Vetor que armazena apenas as dimensoes do cenario atual
  vector<int> dimensao_local;

  vector<matrizOriginal*> vetor_matriz;


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
                //Esvazia o vetor de dimensoes do cenario atual
                dimensao_local.clear();
              
                  int k = j+1;
                  while (line[k] != '<'){
                    altura.push_back(line[k]);
                    ++k;
                    
                  }

                  if (altura.length() > 0) {

                  //Converte a string para inetiro
                  int int_altura = stoi(altura);

                  //Guarda a altura no vetor de dimensao local
                  dimensao_local.push_back(int_altura);
              
                  altura.clear();
                }
            }
              
                
            if (palavra == "<largura>"){
              matriz++;
              int k = j+1;
              while (line[k] != '<'){
                largura.push_back(line[k]);
                k++;
              }

              if (largura.length() > 0) {

              //Converte a string para inteiro
              int int_largura = stoi(largura);

              //Guarda a largura no vetor de dimensao local
              dimensao_local.push_back(int_largura);

              //Guarda as dimensoes do cenario atual na Matriz Geral
              dimensoes.push_back(dimensao_local);
              
              largura.clear();

              }

              
            }
              
//----------------------------------------------------------------------
            if (palavra == "<matriz>"){
              if (linhaMatriz == 0) {
                leituraMatriz = 1;
              }
              break;
            }



              
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
                    throw std::logic_error(file + erro1);
                }
                } else {
                    cout << file;
                    throw std::logic_error(file + erro1);
                }
            
      }
    } else if (leituraMatriz) {
      vector<char> temp;
      for (int j = 0; j < line.length(); j++) {
        temp.push_back(line[j]);
      }

      matrizLocal.push_back(temp);

      linhaMatriz++;
      int coluna = dimensao_local[1];
      int linha = dimensao_local[0];
      if (linhaMatriz == linha) {
        matrizOriginal* matrizRetorno = new matrizOriginal;
        matrizRetorno->linha = linha;
        matrizRetorno->coluna = coluna;
        matrizRetorno->matriz = matrizLocal;

        vetor_matriz.push_back(matrizRetorno);
        leituraMatriz = 0;
        linhaMatriz = 0;
        matrizLocal.clear();
        cout << endl;
        break;
      } 
      break; // esse break é um deus; não perturbar!!!
    }
      }
    }
    myfile.close();
    if (!pilha->empty()) {
        cout << file;
        throw std::logic_error( file + erro1);
    }
  } else {
    throw std::logic_error(file + erro2);
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
  return vetor_matriz;
}


int main () {
    structures::ArrayStack<string> pilha(500);
    
    char xmlfilename[100];

    std::cin >> xmlfilename;  // entrada
    string xmlString = xmlfilename;
    vector<matrizOriginal*> matrizVec = Aninhamento(xmlString, &pilha);

    for (int k = 0; k < matrizVec.size(); k++) {
      vector<vector<char>> matriz = matrizVec[k]->matriz;
      int linha = matrizVec[k]->linha;
      int coluna = matrizVec[k]->coluna;
      
      cout << '\n';
      for (int i = 0; i < linha; i++){
        for (int j = 0; j < coluna; j++){
          cout << matriz[i][j];
        }
        cout << endl;
      }
      
     }


    
    /*
     
       COLOQUE SEU CODIGO AQUI
    
    */

    return 0;
}
