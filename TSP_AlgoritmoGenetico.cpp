#include "graph.h"
#include <bits/stdc++.h>
#include <limits.h>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace Graph;

int **matrix;
int quantCidades = 3;
int distanciaMinima = INT_MAX;

vector<int> menorCaminho;
vector<int> times;

struct Caminho {
    vector<int> ordem;
    int distancia;
};

// verifica se uma ordem inclui uma cidade
bool inclui(vector<int> ordem, int x) {
    for (int i = 0; i < ordem.size(); i++) {
        if (ordem[i] == x)
            return true;
    }
    return false;
}

// gera uma ordem aleatoria
vector<int> gerarOrdem() {
    vector<int> ordem;
    
    while (ordem.size() != (quantCidades - 1)) {
        int num = (rand() % (quantCidades - 1) + 1);
        if (!inclui(ordem, num))
            ordem.push_back(num);
    }

    return ordem;
}

// calcula a distancia representada pela ordem
int calcularDistancia(vector<int> ordem) {
    int soma = 0;

    soma += matrix[0][ordem[0]]; // da cidade inicial ate a primeira cidade da ordem
    soma += matrix[ordem[ordem.size()-1]][0]; // da ultima cidade da ordem ate a cidade inicial

    for (int i = 0; i < ordem.size() - 1; i++)
        soma += matrix[ordem[i]][ordem[i+1]];

    return soma;
}

// mutacao em uma ordem para tentar gerar uma ordem melhor
vector<int> mutacao(vector<int> ordem, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        while (true) {
            int a = rand() % (quantCidades - 1);
            int b = rand() % (quantCidades - 1);
            if (a != b) {
                int temp = ordem[a];
                ordem[a] = ordem[b];
                ordem[b] = temp;
                break;
            }
        }
    }
    
    return ordem;
}

// cross-over em duas ordens para tentar gerar uma ordem melhor
vector<int> crossOver(vector<int> primeira, vector<int> segunda) {
    vector<int> novaOrdem;

    int inicio = rand() % (quantCidades - 1);
    int fim = inicio + rand() % (quantCidades - 1 - inicio);

    // seleciona uma parte da primeira ordem e coloca na nova ordem
    for (int i = inicio; i < fim; i++)
        novaOrdem.push_back(primeira[i]);

    // completa a nova ordem com o que falta da segunda
    for (int i = 0; i < (quantCidades - 1); i++) {
        if (!inclui(novaOrdem, segunda[i]))
            novaOrdem.push_back(segunda[i]);
    }
    
    return novaOrdem;
}

// funcao auxiliar para ordenar a populacao
bool menorQue(Caminho a, Caminho b) {
    return a.distancia < b.distancia;
}

// esfria a temperatura
int esfriar(int temperatura) {
    return (90 * temperatura) / 100;
}

// calcula a media de tempo
int avarageTime() {
    return accumulate(times.begin(), times.end(), 0) / 10;
}

void algoritmoGenetico(int tamanhoPopulacao, int quantGeracoes, int temperatura) {
    Caminho caminho;
    vector<Caminho> populacao;

    // criando a primeira geracao
    int geracaoAtual = 1;
    for (int i = 0; i < tamanhoPopulacao; i++) {
        caminho.ordem = gerarOrdem();
        caminho.distancia = calcularDistancia(caminho.ordem);
        populacao.push_back(caminho);

        // se encontrar um caminho melhor
        if (caminho.distancia < distanciaMinima) {
            distanciaMinima = caminho.distancia;
            menorCaminho = caminho.ordem;
        }
    }

    // realizar mutacoes e crossing-overs para tentar encontrar uma ordem melhor
    while (temperatura > 1000 && geracaoAtual <= quantGeracoes) {
        sort(populacao.begin(), populacao.end(), menorQue);
        vector<Caminho> novaPopulacao;
        Caminho novoCaminho;

        for (int i = 0; i < tamanhoPopulacao; i++) {
            while (true) {
                int sorte = (rand() % tamanhoPopulacao) - i;
                if (i < tamanhoPopulacao && sorte > 0) // realizar mais crossing-overs com ordens melhores
                    novoCaminho.ordem = crossOver(populacao[i].ordem, populacao[i+1].ordem);
                else // realizar mais mutacoes com ordens piores
                    novoCaminho.ordem = mutacao(populacao[i].ordem, (i/quantCidades) + 1);
                
                novoCaminho.distancia = calcularDistancia(novoCaminho.ordem);

                // se encontrar um caminho melhor
                if (novoCaminho.distancia < distanciaMinima) {
                    distanciaMinima = novoCaminho.distancia;
                    menorCaminho = novoCaminho.ordem;
                    temperatura = 10000 * quantCidades;
                }

                // adicionar na populacao
                if (novoCaminho.distancia <= populacao[i].distancia) { // caso haja uma melhora
                    novaPopulacao.push_back(novoCaminho);
                    break;
                }
                else { // aceitar com uma chance baseada na temperatura
                    float prob = pow(2.7, -1 * ((float)(novoCaminho.distancia - populacao[i].distancia) / temperatura));
                    if (prob > 0.5) {
                        novaPopulacao.push_back(novoCaminho);
                        break;
                    }
                }
            }
        }
  
        temperatura = esfriar(temperatura);
        populacao = novaPopulacao;
        geracaoAtual++;
    }
}

int main() {
    int tamanhoPopulacao, quantGeracoes, temperatura;
    clock_t end, start;

    while (quantCidades <= 100) {
        tamanhoPopulacao = quantCidades * quantCidades;
        quantGeracoes = tamanhoPopulacao * quantCidades;
        temperatura = 10000 * quantCidades;

        matrix = new int *[quantCidades];
        initMatrix(matrix, quantCidades);
        fillMatrix(matrix, quantCidades, x, y);

        algoritmoGenetico(tamanhoPopulacao, quantGeracoes, temperatura);

        // RESULTADOS
        cout << distanciaMinima << endl;

        cout << "1 "; // cidade inicial
        for (int i = 0; i < (quantCidades - 1); i++)
            cout << menorCaminho[i] + 1 << " ";
        cout << endl << endl;

        quantCidades++;
        menorCaminho.clear();
        times.clear();
        distanciaMinima = INT_MAX;
    }

    return 0;
}