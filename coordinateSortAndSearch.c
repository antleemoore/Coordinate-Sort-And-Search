#include <stdio.h>
#include <stdlib.h>
/*
  The first integer that determines the amount of coordinates
  cannot be followed by a space
*/
typedef struct coord{
    int x;
    int y;
}Coor;

void merge(int l, int m, int r, Coor a[]){
    int i, j, k;
    int n1 = m-l +1;
    int n2 = r - m;

    Coor L[n1], R[n2];

    for(i = 0; i < n1; i++){
        L[i] = a[l+i];
    }
    for(i = 0; i < n1; i++){
        L[i] = a[l+i];
    }
    for(j = 0; j < n2; j++){
        R[j] = a[m+1 +j];
    }

    i = 0; j = 0; k = l;

    while(i < n1 && j < n2){
        if(L[i].x <= R[j].x){
            a[k] = L[i];
            i++;
        }
        else{
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        a[k] = L[i];
        i++;
        k++;
    }
    while(j < n2){
        a[k] = R[j];
        j++;
        k++;
    }

 }

void mergeSort(int l, int h, Coor arr[]){
    for(int j = l; j < h; j++){
    for(int i = l; i < h; i++){
        if(arr[i].x > arr[i+1].x){
            Coor temp = arr[i];
            arr[i] = arr[i+1];
            arr[i+1] = temp;
        }
        if(arr[i].x == arr[i+1].x){
            if(arr[i].y > arr[i+1].y){
                Coor temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
            }

        }
    }
    }
 }

int binSearch(Coor *array, int low, int high, int xsearchval, int ysearchval){
    int mid;
    if(low<=high){
        mid = (low+high)/2;
        if(xsearchval < array[mid].x)
            return binSearch(array, low, mid-1, xsearchval, ysearchval);
        if(xsearchval > array[mid].x)
            return binSearch(array, mid+1, high, xsearchval, ysearchval);
        if(xsearchval == array[mid].x){
            if(ysearchval < array[mid].y)
                return binSearch(array, low, mid-1, xsearchval, ysearchval);
            else if(ysearchval > array[mid].y)
                return binSearch(array, mid+1, high, xsearchval, ysearchval);
            else
                return 1;
        }
    }
    return 0;

}

int findPosition(Coor *arr, int x, int y, int size){
    int count = 1;
    for(int i = 0; i < size; i++){
        if(arr[i].x == x && arr[i].y == y)
            return count;
        else
            count++;
    }
    return 0;

}

int main()
{
    /*Variable Declarations*/
    FILE *inFile, *outFile;
    inFile = fopen("in.txt", "r");
    outFile = fopen("out.txt", "w");
    int size;

    /*Scan File and Input to Struct Array*/
    fscanf(inFile, "%d", &size);
    Coor arr[size];
    for(int i = 0; i < size; i++){
            fscanf(inFile, "%d", &(arr[i].x));
            fscanf(inFile, "%d", &(arr[i].y));
    }
    /*Merge Sort and Merge*/
    int mid = size/2;
    mergeSort(0,mid,arr);
    mergeSort(mid+1,size,arr);
    merge(0,mid, size,arr);

    /*Write to Output File*/
    for(int i = 0; i < size; i++){
            fprintf(outFile, " %d",arr[i].x);
            fprintf(outFile, " %d", arr[i].y);
            fprintf(outFile, "\n");
    }
    fclose(inFile);
    fclose(outFile);
    printf("\nSorted and Output Written\n");

    int x,y;
    do{
        printf("\nSearch Input (x y): ");
        scanf("%d %d",&x, &y); while((getchar()) != '\n');
        if(x == -999 && y == -999)
            break;
        if(binSearch(arr,0,size,x,y)){
            printf("\nOutput: Found at position %d\n", findPosition(arr,x,y,size));
        }
        else
            printf("\nOutput: Not Found\n");
    }while(x != -999 && y != -999);
    printf("\nOutput: exit\n");
    return 0;
}

