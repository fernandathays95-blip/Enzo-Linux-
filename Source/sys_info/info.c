#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Função para mostrar o Tux ASCII colorido
void show_error_logo() {
    const char *tux_ascii[] = {
        "        .--.",
        "       |o_o |",
        "       |:_/ |",
        "      //   \\ \\",
        "     (|     | )",
        "    /'\\_   _/`\\",
        "    \\___)=(___/",
        NULL
    };

    const char *colors[] = {
        "\033[1;30m", // cinza escuro
        "\033[1;37m", // branco
        "\033[1;33m", // amarelo
        "\033[1;31m", // vermelho
        "\033[1;34m", // azul
        "\033[1;36m", // ciano
        "\033[1;32m"  // verde
    };

    printf("\n\033[1;31m[Enzo Linux] Erro crítico! Não há dados a mostrar.\033[0m\n\n");

    for (int i = 0; tux_ascii[i] != NULL; i++) {
        printf("%s%s\033[0m\n", colors[i % 7], tux_ascii[i]);
        usleep(100000); // efeito linha por linha
    }
    printf("\n\033[1;33m>>> Sistema protegido. Reinicie ou use comandos de recuperação.\033[0m\n\n");
}

// Função para mostrar informações do sistema
void show_sys_info(int error_mode) {
    if (error_mode) {
        // Se houve erro, mostra logo do Tux
        show_error_logo();
        return;
    }

    printf("====================================\n");
    printf("       Enzo Linux - Sys Info        \n");
    printf("====================================\n");

    // Informações do sistema
    printf("Sistema: Enzo Linux (FreeSystem)\n");
    printf("Versão atual: v1.0 (Termux Ready)\n");
    printf("Kernel: GPT Core\n");
    printf("Shell: Custom SH + C modules\n");
    printf("Rootfs: Alpine Linux mínimo\n\n");

    // Módulos carregados
    printf("Módulos carregados:\n");
    printf("  - 3D UI Module (ASCII simulation)\n");
    printf("  - Banner / Boot animation\n");
    printf("  - Sys Info Module (você está aqui!)\n\n");

    // Recursos disponíveis atualmente
    printf("Funcionalidades atuais:\n");
    printf("  - Terminal interativo [EnzoOS]:~$\n");
    printf("  - Execução de módulos C / scripts SH\n");
    printf("  - Simulação de interface 3D ASCII\n\n");

    // Próxima atualização
    printf("====================================\n");
    printf("      Próxima atualização (v1.1)    \n");
    printf("====================================\n");
    printf("Novos recursos previstos:\n");
    printf("  - Interface gráfica completa (GUI)\n");
    printf("  - Reconhecimento de toque (Touch Screen)\n");
    printf("  - Sistema modular expandido\n");
    printf("  - Logs de Kernel GPT dinâmicos em tempo real\n");
    printf("  - Boot animado colorido com efeitos visuais\n");
    printf("  - Integração de módulos com interação direta\n\n");

    printf(">>> Para mais detalhes, continue acompanhando o projeto Enzo Linux.\n");
    printf(">>> GitHub / Site oficial: https://SEU_SITE_DO_ENZO_LINUX.com\n");
    printf("====================================\n");
}

int main(int argc, char *argv[]) {
    int error_mode = 0;

    // Se passar argumento "error", mostra o logo do Tux
    if (argc > 1 && strcmp(argv[1], "error") == 0) {
        error_mode = 1;
    }

    show_sys_info(error_mode);
    return 0;
}
