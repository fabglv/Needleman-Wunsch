#include <stdio.h>
#include <string.h>

// FUNCTIONS
void print_matrix(int rows, int columns, int matrix[rows][columns])
{
    int i,j;
    for (i=0; i<rows; i++){
        for (j=0; j<columns; j++){
            printf("%d  ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_matrix_char(int rows, int columns, char matrix[rows][columns])
{
    int i,j;
    for (i=0; i<rows; i++){
        for (j=0; j<columns; j++){
            printf("%c  ", matrix[i][j]);
        }
        printf("\n");
    }
}

int min(int x, int y, int z)
{
    int min = x;
    if (y < min) {min = y;}
    if (z < min) {min = z;}
    return min;
}

int w(char x, char y)
{
    if (x==y) {return 0;}
    return 1;
}

void reverse_string(char str[])
{
    int i, j;
    j = strlen(str)-1;
    for(i=0; i<j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

void print_spaced(char str[])
{
    int i;
    for (i=0; i<strlen(str); i++){
        printf("%c  ", str[i]);
    }
}
void print_alignment(char str1[], char str2[])
{
    int len = strlen(str1);
    char bar_str[len];
    int i;
    for (i=0; i<len; i++){
        bar_str[i] = '|';
    }
    bar_str[len]='\0';
    print_spaced(str1); printf("\n");
    print_spaced(bar_str); printf("\n");
    print_spaced(str2);
    
}

// MAIN
int main()
{
    printf("__Needleman–Wunsch Algorithm__\n");

    // char a[100] = "AT";
    // char b[100] = "AGGT";
    
    char a[100];
    char b[100];
    printf("\nEnter string 1: "); 
    scanf("%s", a);
    printf("Enter string 2: "); 
    scanf("%s", b);

    printf("\nSequences: \n");
    printf("%s\n", a);
    printf("%s\n", b);

    int m = strlen(a) + 1;
    int n = strlen(b) + 1;

    int D[m][n];
    D[0][0] = 0;
    int i,j;

    // First Row
    for (j=0; j<n-1; j++){
        D[0][j+1] = D[0][j] + w('-', b[j]);
    }

    // First Column
    for (i=0; i<m-1; i++){
        D[i+1][0] = D[i][0] + w(a[i], '-');
    }

    // Remainder of the matrix
    int x,y,z;
    for (i=0; i<m-1; i++ ){
        for (j=0; j<n-1; j++){
            x = D[i][j+1] + w(a[i], '-');
            y = D[i][j] + w(a[i], b[j]);
            z = D[i+1][j] + w('-', b[j]);
            D[i+1][j+1] = min(x, y, z);
        }
    }

    printf("\nD matrix:\n");
    print_matrix(m, n, D);

    // Alignment reconstruction
    char a_aligned[100];
    char b_aligned[100];
    i = m-1; j = n-1;
    int k = 0;

    char H[m][n];
    for (i=0; i<m; i++){
        for (j=0; j<n; j++){
            H[i][j] = '.';
        }
    }

    i = m-1; j=n-1; k=0;
    while (i>0 || j>0){

        // Deletion
        if (j == 0 || D[i][j] == D[i-1][j] + w(a[i-1], '-')) {
            H[i][j] = '^';
            a_aligned[k] = a[i-1];
            b_aligned[k] = '-';
            i--;
        }
        // Substitution
        else if (D[i][j] == D[i-1][j-1] + w(a[i-1], b[j-1])) {
            H[i][j] = '\\';
            a_aligned[k] = a[i-1];
            b_aligned[k] = b[j-1];
            i--; j--;
        }
        // Insertion
        else if (i == 0 || D[i][j] == D[i][j-1] + w('-', b[j-1])) {
            H[i][j] = '<';
            a_aligned[k] = '-';
            b_aligned[k] = b[j-1];
            j--;
        }

        k++;
        if (k>1000) {break;}
    }

    printf("\nT matrix:\n");
    print_matrix_char(m,n,H);

    a_aligned[k] = '\0';
    b_aligned[k] = '\0';

    reverse_string(a_aligned);
    reverse_string(b_aligned);

    printf("\nOptimal alignment:\n");
    print_alignment(a_aligned, b_aligned);
    printf("\n");

}