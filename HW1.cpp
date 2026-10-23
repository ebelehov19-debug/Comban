#include <stdio.h>
#include <stdlib.h>

static void print_array(const int a[], int length)
{
    for (int i = 0; i < length; ++i)
    {
        printf("%d", a[i]);

        if (i + 1 < length)
        {
            printf(" ");
        }
    }

    printf("\n");
}

static void partitions_rec(int remaining, int minimum,
    int result[], int length)
{
    if (remaining == 0)
    {
        print_array(result, length);
        return;
    }

    for (int x = minimum; x <= remaining; ++x)
    {
        result[length] = x;
        partitions_rec(remaining - x, x, result, length + 1);
    }
}

void partitions(int number)
{
    if (number <= 0)
    {
        return;
    }
                  
    int* result = (int*)malloc((size_t)number * sizeof(*result));

    if (result == NULL)
    {
        return;
    }

    partitions_rec(number, 1, result, 0);

    free(result);
}

static void combinations_rec(const int set[], int n, int k,
    int start, int result[], int length)
{
    if (length == k)
    {
        print_array(result, length);
        return;
    }

    int needed = k - length;

    for (int i = start; i <= n - needed; ++i)
    {
        result[length] = set[i];
        combinations_rec(set, n, k, i + 1, result, length + 1);
    }
}

void combinations(const int set[], int n, int k)
{
    if (n < 0 || k < 0 || k > n)
    {
        return;
    }

    int capacity = k > 0 ? k : 1;
    int* result = (int*)malloc((size_t)capacity * sizeof(*result));

    if (result == NULL)
    {
        return;
    }

    combinations_rec(set, n, k, 0, result, 0);

    free(result);
}

static void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void permutations_rec(int set[], int n, int position)
{
    if (position == n)
    {
        print_array(set, n);
        return;
    }

    for (int i = position; i < n; ++i)
    {
        swap(&set[position], &set[i]);

        permutations_rec(set, n, position + 1);

        swap(&set[position], &set[i]);
    }
}

void permutations(int set[], int n)
{
    if (n < 0)
    {
        return;
    }

    permutations_rec(set, n, 0);
}

static void subsets_rec(const int set[], int n, int position,
    int result[], int length)
{
    if (position == n)
    {
        printf("{");

        for (int i = 0; i < length; ++i)
        {
            if (i > 0)
            {
                printf(", ");
            }

            printf("%d", result[i]);
        }

        printf("}\n");
        return;
    }

    subsets_rec(set, n, position + 1, result, length);

    result[length] = set[position];

    subsets_rec(set, n, position + 1, result, length + 1);
}

void subsets(const int set[], int n)
{
    if (n < 0)
    {
        return;
    }

    int capacity = n > 0 ? n : 1;
    int* result = (int*)malloc((size_t)capacity * sizeof(*result));

    if (result == NULL)
    {
        return;
    }

    subsets_rec(set, n, 0, result, 0);

    free(result);
}

static void brackets_rec(int n, int opened, int closed,
    char result[], size_t position)
{
    if (opened == n && closed == n)
    {
        result[position] = '\0';
        printf("%s\n", result);
        return;
    }

    if (opened < n)
    {
        result[position] = '(';

        brackets_rec(n, opened + 1, closed, result, position + 1);
    }

    if (closed < n)
    {
        result[position] = ')';

        brackets_rec(n, opened, closed + 1, result, position + 1);
    }
}

void brackets(int n)
{
    if (n < 0)
    {
        return;
    }

    char* result = (char*)malloc((size_t)n * 2 + 1);

    if (result == NULL)
    {
        return;
    }

    brackets_rec(n, 0, 0, result, 0);

    free(result);
} 

int main(void)
{
    int number = 5;

    int set[] =
    {
        2, 5, 7
    };

    int n = (int)(sizeof(set) / sizeof(set[0]));
    int k = 2;
    int pairs = 3;

    printf("Integer partitions of %d:\n", number);
    partitions(number);

    printf("\nCombinations of %d elements taken %d at a time:\n", n, k);
    combinations(set, n, k);

    printf("\nPermutations:\n");
    permutations(set, n);

    printf("\nSubsets:\n");
    subsets(set, n);

    printf("\nParenthesis sequences with %d pairs:\n", pairs);
    brackets(pairs);

    return 0;
}
