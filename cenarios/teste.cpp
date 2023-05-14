// reading a text file - gcc -o teste teste.cpp -lstdc++
#include "array_stack.h"
#include "array_queue.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define ARRAY_SIZE 500

using namespace std;

typedef struct matrizOriginal {
  int linha;
  int coluna;
  vector<int> robo;
  string nome;
  vector<vector<char>> matriz;
} matrizOriginal;

vector<matrizOriginal*> Aninhamento (string arquivo, structures::ArrayStack<string>* pilha) {
  string line;
  string altura;
  string largura;

  string x;
  string y;

  int matriz = 1;
  int leituraMatriz = 0;
  int linhaMatriz = 0;
  vector<vector<char>> matrizLocal;
  
  matrizOriginal* matrizErro = new matrizOriginal;
  matrizErro->nome = "erro";
  
  //Vetor que armazena apenas as dimensoes do cenario atual
  vector<int> dimensao_local;

  //Vetor que armazena apenas as dimensoes do cenario atual
  vector<int> posicao_local;

  string nome_local;

  vector<matrizOriginal*> vetor_matriz;
  vector<matrizOriginal*> vetor_matrizErro;


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
              
              largura.clear();

              }

              
            }

            if (palavra == "<x>") {
              posicao_local.clear();
              
              int k = j+1;
              while (line[k] != '<'){
                x.push_back(line[k]);
                k++;
              }

              int int_x = stoi(x);

              posicao_local.push_back(int_x);
              x.clear();
            }
            
            if (palavra == "<y>") {

              int k = j+1;
              while (line[k] != '<'){
                y.push_back(line[k]);
                k++;
              }

              int int_y = stoi(y);

              posicao_local.push_back(int_y);
              y.clear();
            }


            if (palavra == "<nome>"){
              nome_local.clear();
              int k = j+1;
              while (line[k] != '<') {
                nome_local.push_back(line[k]);
                k++;
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
                    vetor_matrizErro.push_back(matrizErro);
                    return vetor_matrizErro;
                }
                } else {
                    vetor_matrizErro.push_back(matrizErro);
                    return vetor_matrizErro;
                }
            
      }
    } else if (leituraMatriz) {
      vector<char> temp;
      int coluna = dimensao_local[1];
      int linha = dimensao_local[0];
      for (int j = 0; j < line.length(); j++) {
        temp.push_back(line[j]);
      }

      matrizLocal.push_back(temp);

      linhaMatriz++;
      if (linhaMatriz == linha) {
        matrizOriginal* matrizRetorno = new matrizOriginal;
        matrizRetorno->linha = linha;
        matrizRetorno->coluna = coluna;
        matrizRetorno->robo.push_back(posicao_local[0]);
        matrizRetorno->robo.push_back(posicao_local[1]);
        matrizRetorno->nome = nome_local;
        matrizRetorno->matriz = matrizLocal;

        vetor_matriz.push_back(matrizRetorno);
        leituraMatriz = 0;
        linhaMatriz = 0;
        matrizLocal.clear();
        break;
      } 
      break; // esse break é uma divindade, não perturbar!!!
    }
      }
    }
    myfile.close();
    if (!pilha->empty()) {
        vetor_matrizErro.push_back(matrizErro);
        return vetor_matrizErro;
    }
  } else {
    vetor_matrizErro.push_back(matrizErro);
    return vetor_matrizErro;
  } 

  return vetor_matriz;
}

void RoboInteligente (matrizOriginal* argumento, structures::ArrayQueue<vector<int>>* fila) {

  int linha = argumento->linha;
  int coluna = argumento->coluna;
  vector<int> robo_xy = argumento->robo;
  string nome = argumento->nome;
  vector<vector<char>> matrizBase = argumento->matriz;

  vector<vector<char>> matrizResposta(linha, vector<char>(coluna, 0));
  vector<int> vizinho;
  vector<int> coordenada_local;

  int soma = 0;

  //Criando matriz Nula
  for (int i = 0; i < linha; i++) {
    for (int j = 0; j < coluna; j++) {
      matrizResposta[i][j] = '0';
    }
  }



  int x = robo_xy[0];
  int y = robo_xy[1];
  
  if (matrizBase[x][y] != '1') {
    cout << nome << ' ' << soma << endl;
    return;
  }
    fila->enqueue(robo_xy);
    matrizResposta[x][y] = '0';



  while( !fila->empty() ) {
    coordenada_local.clear();
    coordenada_local = fila->dequeue();

    if (coordenada_local[0] > 0 && 
        matrizBase[coordenada_local[0]-1][coordenada_local[1]] == '1' &&
        matrizResposta[coordenada_local[0]-1][coordenada_local[1]] == '0') {

      vizinho.push_back(coordenada_local[0]-1);
      vizinho.push_back(coordenada_local[1]);
      fila->enqueue(vizinho);
      matrizResposta[coordenada_local[0]-1][coordenada_local[1]] = '1';
      soma++;
      vizinho.clear();
    }

    if (coordenada_local[0] < linha-1 &&
        matrizBase[coordenada_local[0]+1][coordenada_local[1]] == '1' &&
        matrizResposta[coordenada_local[0]+1][coordenada_local[1]] == '0') {
      

      vizinho.push_back(coordenada_local[0]+1);
      vizinho.push_back(coordenada_local[1]);
      fila->enqueue(vizinho);
      matrizResposta[coordenada_local[0]+1][coordenada_local[1]] = '1';
      soma++;
      vizinho.clear();
    }

    if (coordenada_local[1] > 0 && 
        matrizBase[coordenada_local[0]][coordenada_local[1]-1] == '1' &&
        matrizResposta[coordenada_local[0]][coordenada_local[1]-1] == '0') {


      vizinho.push_back(coordenada_local[0]);
      vizinho.push_back(coordenada_local[1]-1);
      fila->enqueue(vizinho);
      matrizResposta[coordenada_local[0]][coordenada_local[1]-1] = '1';
      soma++;
      vizinho.clear();
    }

    if (coordenada_local[1] < coluna-1 && 
        matrizBase[coordenada_local[0]][coordenada_local[1]+1] == '1' &&
        matrizResposta[coordenada_local[0]][coordenada_local[1]+1] == '0') {



      vizinho.push_back(coordenada_local[0]);
      vizinho.push_back(coordenada_local[1]+1);
      fila->enqueue(vizinho);
      matrizResposta[coordenada_local[0]][coordenada_local[1]+1] = '1';
      soma++;
      vizinho.clear();
    }
    
  }

  cout << nome << ' ' << soma << endl;
  return;

}


int main () {
    structures::ArrayStack<string> pilha(ARRAY_SIZE);
    structures::ArrayQueue<vector<int>> fila(ARRAY_SIZE);
    
    char xmlfilename[100];

    std::cin >> xmlfilename;  // entrada
    string xmlString = xmlfilename;
    vector<matrizOriginal*> matrizVec = Aninhamento(xmlString, &pilha);

    if (matrizVec[0]->nome == "erro") {
      printf("erro");
      return 0;
    } 

    for (int i = 0; i < matrizVec.size(); i++) {
      RoboInteligente(matrizVec[i], &fila);
    }


    return 0;
}
