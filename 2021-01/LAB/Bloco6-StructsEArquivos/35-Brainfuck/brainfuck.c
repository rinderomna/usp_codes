#include <stdio.h>
#include <stdlib.h>

void indentar(FILE *file, int nivel_indentacao);

int main() {
    FILE *cfile;
    cfile = fopen("jit-gerado.c", "w");

    fprintf(cfile, "#include <stdio.h>\n\n");
    fprintf(cfile, "int main() {\n");
    fprintf(cfile, "\tchar mem[30000];\n");
    fprintf(cfile, "\tint i = 0;\n");
    fprintf(cfile, "\t// Seta todos os lugares da memória para 0.\n");
    fprintf(cfile, "\tfor (int j = 0; j < 30000; j++) {\n");
    fprintf(cfile, "\t\tmem[j] = 0;\n");
    fprintf(cfile, "\t}\n\n");

    fprintf(cfile, "\t/* Começo do código traduzido de BF */\n");

    char comando;
    int nivel_indentacao = 0;

    do {
        comando = getchar();
        
        switch (comando) {
            case '+':
                indentar(cfile, nivel_indentacao);
                fprintf(cfile, "\tmem[i]++;\n");
                break;
            case '-':
                indentar(cfile, nivel_indentacao);
                fprintf(cfile, "\tmem[i]--;\n");
                break;
            case '>':
                indentar(cfile, nivel_indentacao);
                fprintf(cfile, "\ti++;\n");
                break;
            case '<':
                indentar(cfile, nivel_indentacao);
                fprintf(cfile, "\ti--;\n");
                break;
            case '.':
                indentar(cfile, nivel_indentacao);
                fprintf(cfile, "\tputchar(mem[i]);\n");
                break;
            case '[':
                indentar(cfile, nivel_indentacao);
                fprintf(cfile, "\twhile (mem[i]) {\n");
                nivel_indentacao++;
                break;
            case ']':
                nivel_indentacao--;
                indentar(cfile, nivel_indentacao);
                fprintf(cfile, "\t}\n");
                break;
        }
    } while (comando != EOF);

    fprintf(cfile, "\t/* Fim do código traduzido de BF */\n\n");

    fprintf(cfile, "\tprintf(\"\\n\");\n");
    fprintf(cfile, "\tfor (int j = 0; j < 30000; j++) {\n");
    fprintf(cfile, "\t\tif (mem[j] != 0) {\n");
    fprintf(cfile, "\t\t\tprintf(\"%%d \", mem[j]);\n");
    fprintf(cfile, "\t\t}\n");
    fprintf(cfile, "\t}\n");
    fprintf(cfile, "\tprintf(\"\\n\");\n\n");
    fprintf(cfile, "\treturn 0;\n");
    fprintf(cfile, "}");

    fclose(cfile);

    system("gcc jit-gerado.c -o jit-exe");
    system("./jit-exe");

    return 0;
}

void indentar(FILE *file, int nivel_indentacao) {
    for (int i = 0; i < nivel_indentacao; i++) {
        fprintf(file, "\t");
    }
}