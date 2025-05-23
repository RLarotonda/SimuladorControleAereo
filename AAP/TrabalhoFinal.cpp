#include <iostream>
#include <ctime>
using namespace std;

#include "FilaPrioridadeAdap.h"

int main() {
    // Criacao das filas de prioridade
    no* fp1 = inicializaFP(fp1);    
    no* fp2 = inicializaFP(fp2);    

    no voo[50]; 
    int idVoo = 0; // info 
    bool continua = true;

    // Cores
    const string RESET = "\033[0m"; 
    const string VERMELHO = "\033[31m";
    const string VERDE = "\033[32m";
    const string AMARELO = "\033[33m";
    const string AZUL = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string CIANO = "\033[36m";

    srand(time(0));   

    for(int ut = 0; continua; ut++) {
        cout << VERMELHO << "\nUnidade de Tempo " << ut << RESET << endl; 
        if(idVoo <50){
            cout << MAGENTA << "\nChegada de 5 solicitacoes!" << RESET << endl;

            for (int i = 0; i < 5; i++) {
                voo[idVoo].info = idVoo;
                voo[idVoo].prior = (rand()%2) + 1;     // 1 = alta, 2 = media
                voo[idVoo].tipo = rand()%2;      

                if(voo[idVoo].tipo == 0) {
                    fp1 = insereFP(fp1, idVoo, voo[idVoo].prior);
                    cout << "\nVoo " << voo[idVoo].info << "(" << voo[idVoo].prior << ") entrou na fila de POUSO" << endl;
                    exibe(fp1);
                    cout << endl;
                } else {
                    fp2 = insereFP(fp2, idVoo, voo[idVoo].prior);
                    cout << "\nVoo " << voo[idVoo].info << " (" << voo[idVoo].prior << ") entrou na fila de DECOLAGEM" << endl;
                    exibe(fp2);
                    cout << endl;
                }
                idVoo++;
            }
        }else {
            cout << "\nNao chegam mais solicitacoes." << endl;
        }

        if (ut % 2 == 0 && fp1 != NULL) {
            int vooRemovido = 0, prioridadeRemovida = 0;
            fp1 = removeFP(fp1, &vooRemovido, &prioridadeRemovida);
            cout << AMARELO << "\nVoo " << vooRemovido << " (" << prioridadeRemovida << ") realizou POUSO" << RESET << endl;
        }

        

        if (ut % 3 == 0 && fp2 != NULL) {
            int vooRemovido = 0, prioridadeRemovida = 0;
            fp2 = removeFP(fp2, &vooRemovido, &prioridadeRemovida);
            cout << AZUL << "\nVoo " << vooRemovido << " (" << prioridadeRemovida << ") realizou DECOLAGEM" << RESET << endl;
        }
        cout << VERDE << "\n=== Status das filas ===" << RESET << endl;
        cout << VERDE << "\nPista de pouso liberada";
        exibe(fp1);
        cout << RESET << endl;

        cout << VERDE <<"\nPista de decolagem liberada";
        exibe(fp2);
        cout << RESET << endl;

         if (idVoo >= 50 && fp1 == NULL && fp2 == NULL) {
            cout << "=== Fim da simulacao: Todos os voos foram processados ===";
            continua = false;
        }
    }
    return 0;
}