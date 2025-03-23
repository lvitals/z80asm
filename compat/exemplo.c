// ./exemplo -a -b valor_b -c valor_c 

#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "ab:c:")) != -1) {
        switch (opt) {
            case 'a':
                printf("Opção -a encontrada\n");
                break;
            case 'b':
                printf("Opção -b com valor: %s\n", optarg);
                break;
            case 'c':
                printf("Opção -c com valor: %s\n", optarg);
                break;
            case '?':
                printf("Opção desconhecida: %c\n", optopt);
                break;
        }
    }
    return 0;
}