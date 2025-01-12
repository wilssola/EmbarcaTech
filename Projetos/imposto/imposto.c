#include <stdio.h>

float calcular_imposto(int faixa, float salario_bruto) {
    float aliquota;

    switch (faixa) {
        case 1:
            aliquota = 0.05;
            break;
        case 2:
            aliquota = 0.10;
            break;
        case 3:
            aliquota = 0.15;
            break;
        default:
            return -1; 
    }
    return salario_bruto * aliquota;
}

int main() {
    int faixa_salarial;
    float salario_bruto, imposto;

    printf("Escolha a faixa salarial:\n");
    printf("1 - Até R$ 2.000\n");
    printf("2 - De R$ 2.000 a R$ 5.000\n");
    printf("3 - Acima de R$ 5.000\n");
    scanf("%d", &faixa_salarial);

    printf("Digite o seu salário bruto: R$ ");
    scanf("%f", &salario_bruto);

    imposto = calcular_imposto(faixa_salarial, salario_bruto);

    if (imposto >= 0) {
        printf("O valor do imposto a ser pago é: R$ %.2f\n", imposto);
    } else {
        printf("Faixa salarial inválida.\n");
    }
}
