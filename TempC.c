#include <stdio.h>

#define TEMPERATURAS_A_AVALIAR 7

short achar_temperatura_maxima(
    int temperaturas[TEMPERATURAS_A_AVALIAR],
    int *dia_da_temperatura_maxima,
    int *temperatura_maxima_na_semana,
    int *temperatura_minima_na_semana
);

void exibir_grafico_de_linhas(
    int temperaturas[TEMPERATURAS_A_AVALIAR],
    int temperatura_maxima,
    int temperatura_minima
);

void apresentar_programa(void);

int main(void) {
    // definindo variaveis principais do porgrama
    int usuario_digitou_um_numero; 
    int temperaturas_escritas = 0;
    int temperatura;
    int temperaturas[TEMPERATURAS_A_AVALIAR];
    int dia_da_temperatura_maxima;
    int temperatura_maxima_na_semana;
    int temperatura_minima_na_semana;

    // Apresentar programa
    apresentar_programa();

    do {
        printf("👉 Digite a temperatura da entrada %d de %d e aperte Enter: ", temperaturas_escritas + 1, TEMPERATURAS_A_AVALIAR);

        // scanf devolve 1 se ler corretamente a opcao_escolhida
        usuario_digitou_um_numero = scanf("%i", &temperatura);

        // Limpar buffer usando getchar.
        while ( getchar() != '\n' );

        // Usuário inseriu caracteres não numéricos.
        if (usuario_digitou_um_numero != 1) {
            printf("❌ ERRO: Só é possível utilizar números.\n");
            printf("⚠️ Por favor, digite um número inteiro\n");
            continue;
        }

        // armacenar temperatura
        temperaturas[temperaturas_escritas] = temperatura;
        
        // atualizar contagem do dia
        temperaturas_escritas++;
    } while(temperaturas_escritas < TEMPERATURAS_A_AVALIAR);

    // evaluar temperaturas
    short vezes_temperatura_maxima_atingida = achar_temperatura_maxima(
        temperaturas,
        &dia_da_temperatura_maxima,
        &temperatura_maxima_na_semana,
        &temperatura_minima_na_semana
    );

    // exibir análise de temperaturas
    printf("\n🌡️✨ Análise das Temperaturas da Semana ✨🌡️\n\n");
    printf("🔥 A temperatura mais alta da semana foi %d °C.\n", temperatura_maxima_na_semana);
  
    if (vezes_temperatura_maxima_atingida > 1) {
        printf("✨ Ela apareceu %d vezes ao longo da semana.\n", vezes_temperatura_maxima_atingida);
        printf("📅 A primeira vez aconteceu no dia %d.\n", dia_da_temperatura_maxima);
    } else {
        printf("📅 Ela ocorreu no dia %d.\n", dia_da_temperatura_maxima);
    }

    exibir_grafico_de_linhas(
        temperaturas,
        temperatura_maxima_na_semana,
        temperatura_minima_na_semana
    );

    // FIM
    return 0;
}

/* Percorre uma matriz de temperaturas e identifica:
    - A maior temperatura registrada na semana
    - O menor valor de temperatura
    - O primeiro dia em que a temperatura máxima foi atingida
    
    Return: Número de vezes que a temperatura máxima foi registrada
 */
short achar_temperatura_maxima(
    int temperaturas[TEMPERATURAS_A_AVALIAR],
    int *dia_da_temperatura_maxima,
    int *temperatura_maxima_na_semana,
    int *temperatura_minima_na_semana
) {
    // menor temperatura encontrada (inicializado no maior valor possível)
    int min = 2147483647;

    // maior temperatura do semana (inicializado no menor valor possível)
    int max_geral = -2147483647;

    // auxiliar para acompanhar a evolução do máximo
    int max_realtivo = -2147483647;
    
    // contador de ocorrências da temperatura máxima
    int vezes_temperatura_maxima_atingida = 0;

    // armazena o índice do primeiro dia da temperatura máxima
    int primeiro_dia_com_maxima_temperatura;

    // percorre todas as temperaturas fornecidas
    for (int i = 0; i < TEMPERATURAS_A_AVALIAR; i++) {

        // verifica se a temperatura atual é maior ou igual ao último máximo relativo
        if (max_realtivo <= temperaturas[i]) {
            max_realtivo = temperaturas[i];

            if (max_geral < max_realtivo) {
                // novo máximo encontrado
                max_geral = max_realtivo;
                vezes_temperatura_maxima_atingida = 1;
                primeiro_dia_com_maxima_temperatura = i;
            } else {
                // se for igual ao máximo atual, incrementa contador
                vezes_temperatura_maxima_atingida++;
            }
        } 

        // atualiza o valor mínimo
        if (temperaturas[i] < min) {
            min = temperaturas[i];
        } 
    }

    // atualiza valores de saída via ponteiros
    *temperatura_maxima_na_semana = max_geral;
    *temperatura_minima_na_semana = min;
    *dia_da_temperatura_maxima = primeiro_dia_com_maxima_temperatura + 1; 
    
    return vezes_temperatura_maxima_atingida;
}

/*  Desenha o gráfico de cima para baixo,
    mostrando todos os níveis de temperatura
    desde a máxima até a mínima.
*/
void exibir_grafico_de_linhas(
    int temperaturas[TEMPERATURAS_A_AVALIAR],
    int temperatura_maxima,
    int temperatura_minima
) {
    printf("\n📈 Gráfico das Temperaturas Máximas da Semana ✨\n\n");
    // Legenda do eixo Y (temperatura em °C)
    printf("°C\n"); 
    for (int nivel_atual = temperatura_maxima; nivel_atual >= temperatura_minima; nivel_atual--) {
        
        // Exibe o valor da temperatura atual (nível) alinhado ao eixo Y
        // Adiciona espaço extra para valores menores que 10, mantendo o alinhamento
        if (nivel_atual < 10) {
            printf(" ");
        } 
        printf("%d ", nivel_atual);
        printf("|  ");

        // Percorre todas as temperaturas registradas pelo usuário
        for (int i = 0; i < TEMPERATURAS_A_AVALIAR; i++) {
            // Se a temperatura do dia for exatamente igual ao nível, desenha um ponto
            if (temperaturas[i] == nivel_atual) {
                printf("●  ");
            } 
            // Se a temperatura for maior que o nível atual, desenha uma linha vertical
            else if (temperaturas[i] > nivel_atual) {
                printf("│  ");  
            } 
            // Caso contrário, apenas deixa o espaço em branco
            else {
                printf("   ");  
            }
        }

        // Depois de avaliar todas as temperaturas nesse nível, passa para o próximo (linha abaixo)
        printf("\n");
    }

    // Linha horizontal do eixo X (base do gráfico)
    printf("──────");  
    
    // Cada temperatura ocupa 3 espaços no eixo X
    for (int i = 0; i < TEMPERATURAS_A_AVALIAR; i++) {
        printf("───");
    }

    printf("\n");
    
    // Legenda do eixo X (dias)
    printf("dias  ");

    // Exibe os numeros dos dias alinhado ao eixo X
    // Adiciona espaço extra para valores menores que 10, mantendo o alinhamento
    for (int i = 0; i < TEMPERATURAS_A_AVALIAR; i++) {
        printf("%d ", i+1);
        if (i+1 < 10) {
            printf(" ");
        }
    }
    printf("\n");
}

/* gerado a partir do site https://patorjk.com/software/taag/
* ASCII Art Font: Big Money-nw
*/
void apresentar_programa(void) {
    printf("\n");
    printf("$$$$$$$$\\                                       $$$$$$\\  \n");
    printf("\\__$$  __|                                     $$  __$$\\ \n");
    printf("   $$ | $$$$$$\\  $$$$$$\\$$$$\\   $$$$$$\\        $$ /  \\__|\n");
    printf("   $$ |$$  __$$\\ $$  _$$  _$$\\ $$  __$$\\       $$ |      \n");
    printf("   $$ |$$$$$$$$ |$$ / $$ / $$ |$$ /  $$ |      $$ |      \n");
    printf("   $$ |$$   ____|$$ | $$ | $$ |$$ |  $$ |      $$ |  $$\\ \n");
    printf("   $$ |\\$$$$$$$\\ $$ | $$ | $$ |$$$$$$$  |      \\$$$$$$  |\n");
    printf("   \\__| \\_______|\\__| \\__| \\__|$$  ____/        \\______/ \n");
    printf("                               $$ |                      \n");
    printf("                               $$ |                      \n");
    printf("                              \\__|                      \n");
    printf("\n");
    printf("👋 Bem-vindo ao Temp C! Vamos descobrir a temperatura máxima da semana em graus Celsius 🔥\n");
    printf("\n");
}
