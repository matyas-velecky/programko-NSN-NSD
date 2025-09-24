#include <stdio.h>
#define INPUT_FILE "cisla.txt"
#define OUTPUT_FILE "output.txt"

void header(FILE *f) {
    fprintf(f,"Vypis cisel ze souboru %s\n", INPUT_FILE);
    fprintf(f,"--------------------------------\n");
    fprintf(f,"poradi  cislo1  cislo2    nsn     nsd\n");
}

int NSD(int a, int b) {

    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }

    if (a > b) {
        return NSD(a % b, b);
    }
    if (a < b) {
        return NSD(a, b % a);
    }
}

int NSN(int a, int b) {
    return (a * b) / NSD(a, b);
}

void printing(FILE * f, int order, int num1, int num2, int nsn, int nsd) {
    fprintf(f, "%6d.%7d%8d%7d%8d\n", order, num1, num2, nsn, nsd);
}
void footer(FILE * f, int sum, int order, const char * txt) {
    fprintf(f,"Prumer cisel v prvnim sloupci je %.2f\n",(float)sum /order);
    fprintf(f, "Soubor %s obsahuje %d dvojic cisel\n", txt, order);
}
int main(void) {
    FILE * input;
    FILE * output;

    int number1;
    int number2;
    int order = 0;
    int orderFile = 0;
    int sum = 0;
    int sumFile = 0;
    input = fopen(INPUT_FILE, "r");
    output = fopen(OUTPUT_FILE, "w");
    if (input == NULL) {
        printf("Error opening file named %s\n", INPUT_FILE);
        return -1;
    }
    if (output == NULL) {
        printf("Error opening file named %s\n", OUTPUT_FILE);
        return -1;
    }

    header(stdout);
    header(output);
    while (fscanf(input,"%d%d", &number1, &number2) == 2) {
        order ++;
        printing(stdout, order, number1, number2,
            NSN(number1, number2), NSD(number1, number2));
        sum += number1;
        if (NSD(number1, number2) > 1) {
            orderFile ++;
            printing(output, orderFile, number1, number2,
                NSN(number1, number2), NSD(number1, number2));
            sumFile += number1;
        }
    }
    footer(stdout, sum, order, INPUT_FILE);
    footer(output, sumFile, orderFile, OUTPUT_FILE);

    if (fclose(input) == EOF) {
        printf("Error closing file named %s\n", INPUT_FILE);
        return -1;
    }
    if (fclose(output) == EOF) {
        printf("Error closing file named %s\n", OUTPUT_FILE);
        return -1;
    }
    return 0;
}
