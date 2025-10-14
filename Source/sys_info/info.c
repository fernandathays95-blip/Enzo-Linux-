#include <stdio.h>
#include <stdlib.h>

void show_sys_info() {
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
    printf(">>> GitHub / Site oficial: https://github.com/fernandathays95-blip/Enzo-Linux-/tree/main\n");
    printf("====================================\n");
}

int main() {
    show_sys_info();
    return 0;
}
