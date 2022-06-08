#include <bits/stdc++.h>
#define MAXIMA_LONGITUD_CADENA 100
// La máxima cantidad de líneas que puede tener
#define CANTIDAD_LINEAS 1
#define NOMBRE_ARCHIVO "mensaje.txt"
const int maxsize = 100;

struct huff_node
{
    char symbol;
    int freq;
    huff_node *parent;
    char childtype;
};

typedef huff_node *ptr;
ptr node[maxsize];
typedef long long int ll;

void create(int k, char let, int freq);
void print(int k);
void twosmall(ptr &p, ptr &q, int numnode);
void printFrase(char palabras[CANTIDAD_LINEAS][MAXIMA_LONGITUD_CADENA], FILE *arch, int n);

using namespace std;

int main()
{

    // Arreglo de cadenas : aquí almacenamos todas las palabras char palabras[CANTIDAD_LINEAS][MAXIMA_LONGITUD_CADENA];
    char palabras[CANTIDAD_LINEAS][MAXIMA_LONGITUD_CADENA];
    // Útil para leer el archivo
    char buferArchivo[MAXIMA_LONGITUD_CADENA];
    // Abrir el archivo...
    FILE *archivo = fopen(NOMBRE_ARCHIVO, "r");
    if (archivo == NULL)
    {
        printf("No se puede abrir el archivo");
        return 0;
    }
    // Necesitamos este ayudante para saber en qué línea vamos
    int indice = 0;
    // Mientras podamos leer una línea del archivo
    while (fgets(buferArchivo, MAXIMA_LONGITUD_CADENA, archivo))
    {
        // Remover salto de línea
        strtok(buferArchivo, "\n");
        // Copiar la línea a nuestro arreglo, usando el índice
        memcpy(palabras[indice], buferArchivo, MAXIMA_LONGITUD_CADENA);
        // Aumentarlo en cada iteración
        indice++;
    }
    // Terminamos de leer
    fclose(archivo);

    // Ahora ya tenemos el arreglo. Podemos imprimirlo
    int i;
    for (i = 0; i < CANTIDAD_LINEAS; i++)
    {
        // printf("mensaje para algoritmo de huffman: %s\n", palabras[i]);
        cout << "Mensaje para algoritmo de huffman: " << palabras[i] << endl;
    }

    // Implementacion de huffman
    // 1.- Determinar la cantidad de letras y su frecuencia
    int n = strlen(*palabras), cont, aux = 1;
    // printf("\nnumero de palabras:  %d\n", n);
    cout << "\nnumero de palabras:  " << n << endl;
    char *array_letras;
    array_letras = (char *)malloc(sizeof(char) * 1); // array dinamico para almacenar letras aumentando 1 en 1
    // int *array_frecuencias;
    array_letras[0] = palabras[0][0];

    for (int j = 1; j < n; j++)
    {
        cont = 0;
        for (int i = 0; i < aux; i++)
        {
            if (array_letras[i] == palabras[0][j])
                cont++;
        }
        if (cont == 0)
        {
            array_letras[aux] = palabras[0][j];
            aux++;
        }
    }

    // int tamanio = strlen(array_letras);
    // printf("%d", tamanio);

    // detemina la frecuencia de cada letra
    int frecuencia[aux];
    for (int i = 0; i < aux; i++)
    {
        frecuencia[i] = 0;
    }
    for (int i = 0; i < aux; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (array_letras[i] == palabras[0][j])
            {
                frecuencia[i]++;
            }
        }
    }

    // Aux es el total de letras sin repetir
    for (int i = 0; i < aux; i++)
    {
        // printf("\n%d %c", i + 1, array_letras[i]);
        cout << endl
             << i + 1 << " " << array_letras[i];
        // printf("\tfrecuencia: %d", frecuencia[i]);
        cout << " "
             << "frecuencia: " << frecuencia[i];
    }
    // ORDENAMOS DE MENOR A MAYOR
    for (int i = 0; i < aux; i++)
    {
        for (int j = 0; j < aux - 1; j++)
        {
            if (frecuencia[j] > frecuencia[j + 1])
            {
                int aux = frecuencia[j];
                frecuencia[j] = frecuencia[j + 1];
                frecuencia[j + 1] = aux;

                char aux2 = array_letras[j];
                array_letras[j] = array_letras[j + 1];
                array_letras[j + 1] = aux2;
            }
        }
    }

    // printf("\n\n");
    cout << endl
         << endl;
    // Aux cantidad de palabras sin repetir, frecuencia cantidad de veces que aparece cada letra
    for (int i = 0; i < aux; i++)
    {
        // printf("\n%d %c", i + 1, array_letras[i]);
        cout << i + 1 << " " << array_letras[i] << " Frecuencia: " << frecuencia[i] << endl;
    }

    // creacion del archivo
    int numsymbols = aux;
    ptr p, q, r;
    for (int i = 0; i < numsymbols; i++)
        create(i, array_letras[i], frecuencia[i]);

    for (int j = numsymbols; j < 2 * numsymbols - 1; j++)
    {
        r = (huff_node *)malloc(sizeof(huff_node));
        node[j] = r;
        r->parent = NULL;
        twosmall(p, q, j);
        p->parent = r;
        q->parent = r;
        p->childtype = 'L';
        q->childtype = 'R';
        r->symbol = ' ';
        r->freq = p->freq + q->freq;
    }
    cout << endl
         << endl;
    cout << "simbolo <-------> codigo: " << endl;

        // archivos
    FILE *arch;
    arch = fopen("huffman.dat", "wb"); // crea el archivo.dat
    if (arch == NULL)
    {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    for (int k = 0; k < numsymbols; k++)
        print(k);

    // imprimimos la frase en binario
    printFrase(palabras, arch, aux);
    fclose(arch);

    // OBTENEMOS LA CADENA CODIFICADA

    char SCodi[CANTIDAD_LINEAS][MAXIMA_LONGITUD_CADENA];
    // Útil para leer el archivo
    char bufferArchivo[MAXIMA_LONGITUD_CADENA];
    // Abrir el archivo...
    FILE *coditext = fopen("huffman.dat", "r");
    if (coditext == NULL)
    {
        printf("No se puede abrir el archivo");
        return 0;
    }
    // Necesitamos este ayudante para saber en qué línea vamos
    indice = 0;
    // Mientras podamos leer una línea del archivo
    while (fgets(bufferArchivo, MAXIMA_LONGITUD_CADENA, coditext))
    {
        // Remover salto de línea
        strtok(buferArchivo, "\n");
        // Copiar la línea a nuestro arreglo, usando el índice
        memcpy(SCodi[indice], bufferArchivo, MAXIMA_LONGITUD_CADENA);
        // Aumentarlo en cada iteración
        indice++;
    }
    // Terminamos de leer
    fclose(coditext);

    // Ahora ya tenemos el arreglo. Podemos imprimirlo
    for (i = 0; i < CANTIDAD_LINEAS; i++)
    {
        cout << "Mensaje para algoritmo de huffman codificado: " << SCodi[i] << endl;
    }

    return 0;
}

void create(int k, char let, int freq)
{
    ptr t = (huff_node *)malloc(sizeof(huff_node));

    // cout << "introduce el simbolo numero " << k + 1 << ": ";
    t->symbol = let;
    // cout << "introduce su frecuencia: ";
    t->freq = freq;
    t->parent = NULL;
    node[k] = t;
}

void print(int k)
{

    ptr t = node[k];
    char code[10];
    int size = 0;
    cout << t->symbol << " - ";

    while (t->parent != NULL)
    {
        if (t->childtype == 'L')
            code[size] = '0';
        else
            code[size] = '1';
        t = t->parent;
        size++;
    }

    for (int j = size - 1; j >= 0; j--)
    {
        cout << code[j];
    }
    cout << endl;
}

void twosmall(ptr &p, ptr &q, int numnodes)
{
    int min1 = 9999;
    int min2 = 9999;
    p = NULL;
    q = NULL;

    for (int i = 0; i < numnodes; i++)
    {
        if (node[i]->parent == NULL)
        {
            if (node[i]->freq < min1)
            {
                min2 = min1;
                min1 = node[i]->freq;
                q = p;
                p = node[i];
            }
            else if (node[i]->freq < min2)
            {
                min2 = node[i]->freq;
                q = node[i];
            }
        }
    }
}

void printFrase(char palabras[CANTIDAD_LINEAS][MAXIMA_LONGITUD_CADENA], FILE *arch, int n)
{
    char aux;
    size_t tam = strlen(palabras[0]);
    for (int i = 0; i < tam; i++)
    {
        aux = palabras[0][i];
        for (int j = 0; j < n; j++)
        {
            ptr t = node[j];
            if (aux == t->symbol)
            {
                char code[10];
                int size = 0;

                while (t->parent != NULL)
                {
                    if (t->childtype == 'L')
                        code[size] = '0';
                    else
                        code[size] = '1';
                    t = t->parent;
                    size++;
                }

                for (int j = size - 1; j >= 0; j--)
                {
                    // cout << code[j];
                    fwrite(&code[j], sizeof(char), 1, arch);
                }
                cout << endl;
            }
        }
    }
}