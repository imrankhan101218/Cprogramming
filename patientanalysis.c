#include <stdio.h>
int main(){
    FILE *fp;
    char doc[50];
    int year, patientnum, n, i;
    
    fp = fopen("hasta_kayitlari.txt", "w");
    if(fp == NULL){
        printf("file can't be opened");
        return 1;
    }

    printf("enter the number of doctors");
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        printf("enter the name of doctor : ");
        scanf("%s", doc);
        
        printf("enter the year :");
        scanf("%d", &year);
        
        printf("enter the number of patient : ");
        scanf("%d", &patientnum);
        
        fprintf(fp, "%s %d %d\n", doc, year, patientnum);
    }
    fclose(fp);
    
    int a;
    printf("enter the year : ");
    scanf("%d", &a);
    fp = fopen("hasta_kayitlari.txt", "r");
    if(fp == NULL){
        printf("error");
        return 1;
    }
    int totaldoc = 0;
    int totalpatient = 0;
    char doctem[50];
    int yeartem, patientnumtem;
    printf("all the registered doctors are\n");
    while((fscanf(fp, "%s %d %d", doctem, &yeartem, &patientnumtem)) != EOF){
        totaldoc++;
        totalpatient+=patientnumtem;
        printf("%s\n", doctem);
    }
    printf("total number of doctors is %d\n", totaldoc);
    printf("total patients is %d\n", totalpatient);
    fclose(fp);
    
    fp = fopen("hasta_kayitlari.txt", "r");
    if(fp == NULL){
        printf("file cannot be opened");
        return 1;
    }
    int docnumi = 0;
    int allpatnum = 0;
    int min, max;
    
    while(fscanf(fp, "%s %d %d", doctem, &yeartem, &patientnumtem) != EOF){
        if(a == yeartem){
            docnumi++;
            allpatnum += patientnumtem;
            if(docnumi == 1){
                min = patientnumtem;
                max = patientnumtem;
            }else{
                if(min > patientnumtem)
                    min = patientnumtem;
                if(max < patientnumtem)
                    max = patientnumtem;
            }
        }
    }
    printf("the total doctor is %d\n", docnumi);
    if(docnumi > 0){
        float ratio = (float)allpatnum/totalpatient;
        printf("the ratio is %.2f\n", ratio);
        printf("the minimum is %d\n", min);
        printf("the maximum is %d\n", max);
    }else{
        printf("there is nothing in this year\n");
    }
    fclose(fp);
    return 0;
}