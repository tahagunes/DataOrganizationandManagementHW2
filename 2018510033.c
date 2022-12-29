#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//https://www.edureka.co/blog/merge-sort-in-c/ for merge-sort approach

struct Records
{
    int id;
    char name[15];
    char surname[15];
    char email[26];
    int grade;
};
typedef struct Records dataff;

// Merge Function
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Finding mid element
        int m = l + (r - l) / 2;
        // Recursively sorting both the halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the array
        merge(arr, l, m, r);
    }
}

int main(int argc,char *argv[])
{
    // Instruction : <input file> <outputfile>
    int maxline = 150, counter = 0, datacounter = 0, saveid = 0, savegrade = 0, misstep = 0;
    char satir[maxline], *savename, *savesurname, *saveemail;
    dataff *students = malloc(0);
    char *uiF = argv[1];
    FILE *iF = fopen(uiF, "r");
    char *uoF = argv[2];
    FILE *oF = fopen(uoF, "w+");
    while (fgets(satir, maxline, iF))
    {
        if (misstep != 0)
        {

            char *splitted = strtok(satir, ";");
            //printf("%c < %c < %c < %c < %c\n",splitted[0],splitted[1],splitted[2],splitted[3],splitted[4]);
            while (splitted != NULL)
            {
                if (counter == 0)
                    students[datacounter].id = atoi(splitted);//okunan line ın parçalarını gerekli struct elemanına atiyorum
                else if (counter == 1)
                    strcpy(students[datacounter].name, splitted);
                else if (counter == 2)
                    strcpy(students[datacounter].surname, splitted);
                else if (counter == 3)
                    strcpy(students[datacounter].email, splitted);
                else if (counter == 4)
                    students[datacounter].grade = atoi(splitted);
                splitted = strtok(NULL, ";");
                counter++;//kacinci struct elemani oldugunu anlamak icin kullanıyorum
            }
            //printf("%d %s\n",students[datacounter].id,students[datacounter].name);
            counter = 0;
            datacounter++;
        }
        //printf("satir: %s\n",satir);
        misstep = 1;
        students = realloc(students, (datacounter + 1) * sizeof(dataff));
    }





    int arr[datacounter];
    for (size_t i = 0; i < datacounter; i++)
    {
        arr[i] = students[i].id;//sort etmek icin IDleri ayiriyorum
        //printf("id: %d name: %s\n",arr[i],students[i].name);
    }
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    mergeSort(arr, 0, arr_size - 1);//idler siralaniyor

    
    printf("Write process starting...\n");
    for (size_t i = 0; i < datacounter; i++)//siralanmis idlere gore struct arrayden elemanları cekip dosyaya yazdiriyoruz
    {
        for (size_t k = 0; k < datacounter; k++)
        {
            if (arr[i] == students[k].id && students[k].id != -3)
            {
                fprintf(oF, "%d;%s;%s;%s;%d\n", students[k].id, students[k].name, students[k].surname, students[k].email, students[k].grade);
                students[k].id = -3;
                
            }
        }
    }
    
    printf("Write process completed...\n");
    fclose(iF);
    fclose(oF);
    return 0;
}
