#include <iostream>
#include <ctime>
using namespace std;

#include "FilaPrioridadeAdaptada.h"

void tempoEspera(no *L, int espera) {
    no* aux = L;
    int posicao = 1;
    cout << endl;
    while (aux != NULL) {
        int tempoEspera = posicao * espera;
        cout << "Voo " << aux->info << " com espera aproximada de " << tempoEspera << " ut" << endl;
        aux = aux->link;
        posicao++;
    }
}

int main() {
    // Criacao das filas de prioridade
    no* fp1 = inicializaFP(fp1);    
    no* fp2 = inicializaFP(fp2);    

    no voo[50]; // vetor estatico
    int idVoo = 0; // int info
    bool continua = true;
    int esperaPouso = 2;
    int esperaDecolagem = 3;

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
        cout << endl;
        cout << VERMELHO << "Unidade de Tempo " << ut << RESET << endl; 
        if(idVoo < 50){ // Pelo menos 50 voos
            cout << MAGENTA << "Chegada de 5 solicitacoes!" << RESET << endl;

            for (int i = 0; i < 5; i++) {
                voo[idVoo].info = idVoo;
                voo[idVoo].prior = (rand()%2) + 1; // 1 = alta, 2 = media
                voo[idVoo].tipo = rand()%2; // 0 = pouso, 1 = decolagem

                if(voo[idVoo].tipo == 0) {
                    fp1 = insereFP(fp1, idVoo, voo[idVoo].prior);
                    cout << "Voo " << voo[idVoo].info << "(" << voo[idVoo].prior << ") entrou na fila de POUSO" << endl;
                    cout << "POUSO: ";
                    exibe(fp1);
                    tempoEspera(fp1, esperaPouso);
                    cout << endl;
                } else {
                    fp2 = insereFP(fp2, idVoo, voo[idVoo].prior);
                    cout << "Voo " << voo[idVoo].info << " (" << voo[idVoo].prior << ") entrou na fila de DECOLAGEM" << endl;
                    cout << "DECOLAGEM: ";
                    exibe(fp2);
                    tempoEspera(fp2, esperaDecolagem);
                    cout << endl;
                }
                idVoo++;
            }
        }else {
            cout << MAGENTA << "Nao chegaram mais solicitacoes." << RESET << endl;
        }

        if (ut % 2 == 0 && fp1 != NULL) { // A cada 2 ut
            cout << "Pista de POUSO liberada" << endl;
            int vooRemovido = 0, prioridadeRemovida = 0;
            fp1 = removeFP(fp1, &vooRemovido, &prioridadeRemovida); // Remove primeiro da fila
            cout << AMARELO << "Voo " << vooRemovido << " (" << prioridadeRemovida << ") esta realizando POUSO" << RESET << endl;
        }
        
        if (ut % 3 == 0 && fp2 != NULL) { // A cada 3 ut
            cout << "Pista de DECOLAGEM liberada" << endl;
            int vooRemovido = 0, prioridadeRemovida = 0;
            fp2 = removeFP(fp2, &vooRemovido, &prioridadeRemovida);
            cout << AZUL << "Voo " << vooRemovido << " (" << prioridadeRemovida << ") esta realizando DECOLAGEM" << RESET << endl;
        }

        cout << VERDE << "=== Status das filas ===" << RESET << endl;
        cout << CIANO << "Fila de POUSO:" << RESET;
        cout << VERDE;
        exibe(fp1);
        cout << RESET;
        tempoEspera(fp1, esperaPouso);
        cout << endl;

        cout << CIANO <<"Fila de DECOLAGEM:" << RESET;
        cout << VERDE;
        exibe(fp2);
        cout << RESET;
        tempoEspera(fp2, esperaDecolagem);
        cout << endl;

        if (idVoo >= 50 && fp1 == NULL && fp2 == NULL) { // Quando as filas estiverem vazias
            cout << "=== Fim da simulacao: Todos os voos foram processados ===";
            continua = false;
        }
    }
    return 0;
}
