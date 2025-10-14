#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Caminhos dos módulos
#define BANNER_PATH "Source/banner/enzo-banner.txt"
#define MODULE_EXEC "./Source/3D\\ UI/module"
#define UI_EXEC "./Source/3D\\ UI/3d_ui_logic"

// Função para exibir banner
void show_banner() {
    FILE *fp = fopen(BANNER_PATH, "r");
    if (!fp) {
        printf("[FreeSystem] ERRO: Banner não encontrado em %s\n", BANNER_PATH);
        return;
    }
    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
        usleep(50000); // efeito de digitação
    }
    fclose(fp);
    printf("\n>>> Enzo Linux (FreeSystem) iniciado!\n");
}

// Função para rodar módulo externo via system()
void run_module(const char *module_path) {
    printf("[FreeSystem] Inicializando módulo: %s\n", module_path);
    int ret = system(module_path);
    if (ret != 0) {
        printf("[FreeSystem] ATENÇÃO: módulo retornou código %d\n", ret);
    } else {
        printf("[FreeSystem] Módulo finalizado com sucesso.\n");
    }
}

// Prompt simples
void prompt() {
    char command[256];
    while (1) {
        printf("[EnzoOS]:~$ ");
        if (!fgets(command, sizeof(command), stdin)) break;

        // remover \n
        command[strcspn(command, "\n")] = 0;

        // sair
        if (strcmp(command, "exit") == 0) {
            printf("Saindo do Enzo Linux...\n");
            break;
        }

        // help
        if (strcmp(command, "help") == 0) {
            printf("Comandos disponíveis:\n");
            printf("  help       - mostra esta mensagem\n");
            printf("  module     - roda módulo 3D UI\n");
            printf("  free       - reinicia o sistema FreeSystem\n");
            printf("  exit       - sair do sistema\n");
            continue;
        }

        // rodar módulo
        if (strcmp(command, "module") == 0) {
            run_module(MODULE_EXEC);
            continue;
        }

        // rodar 3D UI
        if (strcmp(command, "3d") == 0) {
            run_module(UI_EXEC);
            continue;
        }

        // reiniciar
        if (strcmp(command, "free") == 0) {
            printf("[FreeSystem] Reiniciando sistema...\n");
            execv("./free_system", NULL); // reinicia o próprio binário
            perror("[FreeSystem] ERRO ao reiniciar");
            continue;
        }

        // se não reconhece, executa comando no shell
        int ret = system(command);
        if (ret != 0) printf("[FreeSystem] Comando retornou código %d\n", ret);
    }
}

int main() {
    show_banner();

    // inicializar módulos básicos (opcional)
    run_module(MODULE_EXEC);

    // iniciar prompt interativo
    prompt();

    printf("[FreeSystem] Sistema finalizado. Até mais!\n");
    return 0;
}
