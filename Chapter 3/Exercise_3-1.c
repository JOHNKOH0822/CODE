#include <stdio.h>
#include <time.h>
int binsearch(int x, int v[], int n);
int binsearch_pro(int x, int v[], int n);
int main() {
    int v[1000];
    int x, n, i;
    int result;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter %d sorted elements:\n", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }
    printf("Enter value to search: ");
    scanf("%d", &x);
    result = binsearch(x, v, n);
    if(result == - 1)
    {
        printf("Element %d not found\n", x);
    }
    else 
    {
        printf("Element %d found at %d\n", x, result);
    }
    clock_t start = clock();
    for (int i = 0; i < 1000000; i++)
    {
        binsearch(x, v, n);
    }
    clock_t end = clock();
    printf("Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}
int binsearch(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid; /* found */ 
    }
    return -1; /* not found */
}
int binsearch_pro(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    high = n - 1;
    while(low < high)
    {
        mid = (high + low) / 2;
        if(x <= v[mid])
        {
            high = mid ;
        }
        else
        {
            low = mid + 1;
        }
    }
    if(v[low] == x)
    {
        return low;
    }
    return -1;
}
