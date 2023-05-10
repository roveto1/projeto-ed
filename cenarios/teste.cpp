// reading a text file
#include "array_stack.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int Aninhamento (string arquivo, structures::ArrayStack<string>* pilha) {
  string line;
  string altura;
  string largura;
  int matriz = 1;


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
                  cout << matriz << endl;
                  
              
                  int k = j+1;
                  while (line[k] != '<'){
                    altura.push_back(line[k]);
                    ++k;
                    
                  }
                  cout << altura << '\n';
                  altura = " ";
                }
              
                
            if (palavra == "<largura>"){
              matriz++;
              int k = j+1;
              while (line[k] != '<'){
                largura.push_back(line[k]);
                k++;
              }
              cout << largura << '\n';
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
                    //cout << line[j+8] << endl;
              
                
                

              
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