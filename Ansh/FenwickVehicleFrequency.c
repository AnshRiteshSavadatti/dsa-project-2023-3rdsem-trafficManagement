#include "header_file.h"


// Function:     update
// Description:  Updates the Binary Indexed Tree (BIT) by adding a delta value to the element at index x.
// Input parameter: x - index to be updated, delta - value to be added, BIT - Binary Indexed Tree array, n - size of the array
// Return type: void;
void update(int x, int delta, int BIT[], int n)
{
    for(; x <= n; x += x&-x)
    {
        BIT[x] += delta;
    }
    return;
}

// Function:     query
// Description:  Computes the prefix sum of elements in the Binary Indexed Tree (BIT) up to index x.
// Input parameter: x - index for prefix sum calculation, BIT - Binary Indexed Tree array
// Return Type:  int - prefix sum value
int query(int x, int BIT[])
{
    int sum = 0;
    for(; x > 0; x -= x&-x)
        sum += BIT[x];
    return sum;
}

// Function:     createBit
// Description:  Initializes the Binary Indexed Tree (BIT) using elements from the input array.
// Input parameter: BIT - Binary Indexed Tree array, arr - input array, n - size of the array
// return type: void
void createBit(int BIT[], int arr[], int n)
{
    for(int i = 1; i<=n; i++)
    {
        // index, element, BIT array
        update(i, arr[i], BIT, n);
    }
    return;
}

// Function:     FillFenwickFile
// Description:  Fills a file named "FenwickValues.txt" with random integer values (range 1 to 10).
// Input params: fp - file pointer, n - number of values to generate
void FillFenwickFile(FILE * fp, int n)
{
    fp = fopen("FenwickValues.txt", "w");
    for(int i=0; i <= n; i++)
    {
        fprintf(fp, "%d\n", (rand() % 10 + 1));
    }
    fclose(fp);
    return;
}

// Function:     ReadFenwickValues
// Description:  Reads integer values from a file named "FenwickValues.txt" into the given array.
// Input params: fp - file pointer, arr - array to store values
void ReadFenwickValues(FILE * fp, int arr[])
{
    fp = fopen("FenwickValues.txt", "r");
    int i = 0;
    while(!feof(fp))
    {
        fscanf(fp, "%d\n",&arr[i]);
        i++;
    }
    fclose(fp);
    return;
}

// Function:     initilizeBit
// Description:  Initializes the Binary Indexed Tree (BIT) array with zero values.
// Input params: BIT - Binary Indexed Tree array, n - size of the array
void initilizeBit(int BIT[], int n)
{
    for(int i=0; i<=n; i++)
    {
        BIT[i] = 0;
    }
    return;
}

// Function:     displayBIT
// Description:  Displays the contents of the Binary Indexed Tree (BIT) array.
// Input parameter: arr - Binary Indexed Tree array, n - size of the array
// return type: void
void displayBIT(int arr[], int n)
{
    for(int i=1; i<=n; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    return;
}

// Function:     displayValues
// Description:  Displays the contents of an array.
// Input parameter: arr - input array, n - size of the array
// return type: void
void displayValues(int arr[], int n)
{
    for(int i=1; i<=n; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    return;
}
