#include <stdio.h>
#include <unistd.h>

void show_linux_logo() {
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

    printf("\n\033[1;32m[Enzo Linux] Tux Linux ASCII Logo:\033[0m\n\n");

    for (int i = 0; tux_ascii[i] != NULL; i++) {
        printf("%s%s\033[0m\n", colors[i % 7], tux_ascii[i]);
        usleep(100000); // efeito de animação linha por linha
    }

    printf("\n\033[1;33m>>> Enzo Linux pronto para uso! Digite 'help' para comandos.\033[0m\n\n");
}

int main() {
    show_linux_logo();
    return 0;
}
