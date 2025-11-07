#include <stdio.h>

int main(void) {
    char nome[16];
    printf("Digite seu nome: ");
    gets(nome); // perigoso! NÃO usar em código real
    fgets(nome, sizeof(nome), stdin); // Versão segura para uso
    printf("Olá, %s!\n", nome);
    return 0;
}
