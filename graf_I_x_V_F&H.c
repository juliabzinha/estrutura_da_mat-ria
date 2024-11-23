#include <stdio.h>
#include <stdlib.h>

#define MAX_LINHAS 1000 // M�ximo de linhas por arquivo

int main() {
    char nomearq[20], saidaarq[20];
    FILE *entrada[4][3], *saida[4];
    int i, j, idx_j, k;
    float t[4][3][MAX_LINHAS], I[4][3][MAX_LINHAS], U[4][3][MAX_LINHAS];

    // Loop para variar os nomes dos arquivos
    for (j = 150, idx_j = 0; j <= 180; j += 10, idx_j++) {
        // Inicializa contador para cada conjunto
        k = 0;

        for (i = 1; i <= 3; i++) {
            // Gera o nome do arquivo de entrada
            sprintf(nomearq, "%d(%d).txt", j, i);
            entrada[idx_j][i - 1] = fopen(nomearq, "r");

            if (entrada[idx_j][i - 1] == NULL) {
                printf("Erro ao abrir o arquivo de entrada: %s\n", nomearq);
                continue; // Pula para o pr�ximo arquivo
            } else {
                printf("Arquivo de entrada aberto com sucesso: %s\n", nomearq);
            }

            // Leitura dos dados
            int linha = 0;
            while (fscanf(entrada[idx_j][i - 1], "%f %f %f",&t[idx_j][i - 1][linha],&I[idx_j][i - 1][linha],&U[idx_j][i - 1][linha]) == 3) {
                linha++;
                if (linha >= MAX_LINHAS) {
                    printf("N�mero m�ximo de linhas atingido em %s\n", nomearq);
                    break;
                }
            }
            fclose(entrada[idx_j][i - 1]); // Fecha o arquivo ap�s a leitura
            printf("Arquivo %s lido com %d linhas.\n", nomearq, linha);
        }

        // Gera o nome do arquivo de sa�da
        sprintf(saidaarq, "t=%d_med.txt", j);
        saida[idx_j] = fopen(saidaarq, "w");

        if (saida[idx_j] == NULL) {
            printf("Erro ao criar o arquivo de sa�da: %s\n", saidaarq);
            continue; // Pula para o pr�ximo conjunto
        } else {
            printf("Arquivo de sa�da criado com sucesso: %s\n", saidaarq);
        }

        // C�lculo das m�dias e grava��o no arquivo de sa�da
        for (int linha = 0; linha < MAX_LINHAS; linha++) {
            float soma_t = 0, soma_I = 0, soma_U = 0;
            int contador = 0;

            for (i = 0; i < 3; i++) {
                if (t[idx_j][i][linha] == 0 && I[idx_j][i][linha] == 0 && U[idx_j][i][linha] == 0) {
                    continue; // Ignora entradas n�o preenchidas
                }
                soma_t += t[idx_j][i][linha];
                soma_I += I[idx_j][i][linha];
                soma_U += U[idx_j][i][linha];
                contador++;
            }

            if (contador > 0) {
                fprintf(saida[idx_j], "%.2f %.2f\n", 100*(soma_I / contador), (soma_U / contador));
            }
        }
        fclose(saida[idx_j]); // Fecha o arquivo de sa�da
        printf("Arquivo de sa�da %s criado.\n", saidaarq);
    }

    return 0;
}
