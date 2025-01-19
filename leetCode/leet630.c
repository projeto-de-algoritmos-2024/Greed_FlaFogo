# include <stdio.h>
# include <stdlib.h>
# define swapHeap(a,b) {int t; t = a; a = b; b = t;}

typedef int Item;

void swap(int *a, int *b) 
{
    int temp1 = a[0];
    int temp2 = a[1];
    a[0] = b[0];
    a[1] = b[1];
    b[0] = temp1;
    b[1] = temp2;
}

// void swapHeap(int *a, int *b)
// {
//     int temp = *a;
//     *a = b;
//     *b = temp;
// }

void insertionSort(int **v, int l, int r)
{
    int aux1,aux2,j;
    int i = l + 1;
    while(i <= r)
    {
        aux1 = v[i][1];
        aux2 = v[i][0];
        j = i;
        while(j  > 0 && aux1 < v[j - 1][1])
        {
            v[j][1] = v[j - 1][1];
            v[j][0] = v[j - 1][0];
            j--;
        }

        v[j][1] = aux1;
        v[j][0] = aux2;
        i++;
    }
}

int partition( int **v , int l , int r )
{
    int i = l;
    int j = l ;
    int pivo = v[r][1];

    while (i < r)
    {
        if(v[i][1] < pivo)
        {   
            if(i != j)
                swap(v[i], v[j]);
            j++;
        }
        i++;
    }
    
    swap (v[j] ,v[r]);

    return j;
}

void quickSort(int **v, int l, int r)
{
    if(l < r)
    {   
        // coloca a mediana na ultima posicao, mediana de 3
        int meio = (l + r)/2; 

        if(v[meio][1] > v[r][1]) swap(v[meio], v[r]);
        if(v[l][1] > v[meio][1]) swap(v[l], v[meio]);
        if(v[r][1] > v[meio][1]) swap(v[r],v[meio]);

        if(r - l + 1 <= 15 )
            insertionSort(v, l, r);
        else
        {
            int p = partition(v, l, r);
            quickSort(v, l, p-1);
            quickSort(v, p+1, r);
        }
    }
}

void  fixUp(Item *heap, Item n)
{   
    // n é o índice no vetor
    while( n > 1 && heap[n/2] < heap[n])
    {
        swapHeap(heap[n/2],heap[n]);
        n = n/2;
    }
}

// k = índice do elemento em análise
void fixDown(Item k, Item n, Item *heap)
{   
    int j;

    // Tem filho?
    while(2*k <= n)
    {
        j = 2 * k; // recebe o índice do filho

        // Pega o maior filho
        if(j < n && heap[j] < heap[j + 1])
            j++;
        
        // Se o maior filho for menor que o pai ja pode parar
        if(heap[k] > heap[j])
            return;

        swapHeap(heap[k], heap[j]);
        k = j; // Atualiza o índice do elemento
    }
}

int scheduleCourse(int** courses, int coursesSize, int* coursesColSize) 
{
    int actual_day = 0;
    int res = 0;
    actual_day = 0;
    quickSort(courses,0,coursesSize-1);
    int n = 1;
    int *heap = malloc(sizeof(int) * (coursesSize + 1) );

    for(int i = 0; i < coursesSize; i++)
    {
        if(actual_day + courses[i][0] <= courses[i][1])
        {   
            printf("actual_day: %d dur: %d temp:%d",courses[i][0], courses[i][1]);

            heap[n] = courses[i][0];
            fixUp(heap, n);
            n++;
            res++;
            actual_day += courses[i][0];
        }
        else if(courses[i][0] < heap[1])
        {
            actual_day -= heap[1];
            actual_day += courses[i][0];
            heap[1] = courses[i][0];
            fixDown(1, n-1, heap);
        }
    }

    printf("%d\n", res);
    return res;
    
}
