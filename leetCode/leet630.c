# include <stdio.h>
# include <stdlib.h>
// # define swap(a,b) {int t; t = a; a = b; b = t;}

// #define swap(a, b) do { int t = (a); (a) = (b); (b) = t; } while (0)
// #define swap(a, b) { int *t = a; a = b; b = t; }

void swap(int *a, int *b) 
{
    int temp1 = a[0];
    int temp2 = a[1];
    a[0] = b[0];
    a[1] = b[1];
    b[0] = temp1;
    b[1] = temp2;
}

void insertionSort(int **v, int l, int r)
{
    int aux1,aux2,j;
    int i = l + 1;
    while(i <= r)
    {
        aux1 = v[i][1];
        aux2 = v[i][0];
        j = i;
        while(j  > 0 && aux2 < v[j - 1][0])
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
    int pivo = v[r][0];

    while (i < r)
    {
        if(v[i][0] < pivo)
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

        if(v[meio][0] > v[r][0]) swap(v[meio], v[r]);
        if(v[l][0] > v[meio][0]) swap(v[l], v[meio]);
        if(v[r][0] > v[meio][0]) swap(v[r],v[meio]);

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

void insertionSort1(int **v, int l, int r)
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

int partition1( int **v , int l , int r )
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

void quickSort1(int **v, int l, int r)
{
    if(l < r)
    {   
        // coloca a mediana na ultima posicao, mediana de 3
        int meio = (l + r)/2; 

        if(v[meio][1] > v[r][1]) swap(v[meio], v[r]);
        if(v[l][1] > v[meio][1]) swap(v[l], v[meio]);
        if(v[r][1] > v[meio][1]) swap(v[r],v[meio]);

        if(r - l + 1 <= 15 )
            insertionSort1(v, l, r);
        else
        {
            int p = partition1(v, l, r);
            quickSort1(v, l, p-1);
            quickSort1(v, p+1, r);
        }
    }
}

int scheduleCourse(int** courses, int coursesSize, int* coursesColSize) 
{
    int actual_day = 0;
    int res = 0;
    actual_day = 0;
    quickSort1(courses,0,coursesSize-1);

    int ver_first = 0;
    int first = 0 ;
    for(int i = 0; i < coursesSize; i++)
    {
        if(actual_day + courses[i][0] <= courses[i][1])
        {
            if(!ver_first)
            {
                first = courses[i][0];
                ver_first = 1;
            }
            else if(courses[i][0] < first)
            {
                first = courses[i][0];
            }
            //printf("%d %d\n",actual_day + courses[i][0], courses[i][1]);
            res++;
            actual_day += courses[i][0];
        }
        else if(courses[i][0] < first && courses[i][0] <= courses[i][1])
        {
            actual_day -= first;
            actual_day += courses[i][0];
            first = courses[i][0];
        }
    }

    return res;
    
}

int main()
{
    int **v = malloc(2 * sizeof(int*));
    v[0] = malloc(2 * sizeof(int));
    v[0][0] = 3;
    v[0][1] = 2;
    v[1] = malloc(2 * sizeof(int));
    v[1][0] = 4;
    v[1][1] = 3;

    int *coursesColSize = malloc(sizeof(int));
    *coursesColSize = 2;
    scheduleCourse(v,2,coursesColSize);

    return 0;
}
// int scheduleCourse(int** courses, int coursesSize, int* coursesColSize) 
// {
//     int actual_day = 0;
//     int courses_complete = 0;
//     quickSort(courses, 0, coursesColSize - 1);
//     int **courses_sorted = courses;
//     for(int i = 0; i < coursesSize; i++ )
//     {
//         // Consegue completar o curso ate o dia limite ?
//         if(actual_day + courses_sorted[i][0] <= courses_sorted[i][1])
//         {
//             courses_complete++;
//             actual_day += courses_sorted[i][0];
//         }
//     }
// }