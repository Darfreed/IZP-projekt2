#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool Reflexive(char A[5][30],int A_len, char relation[5][2][30], int relation_count){
    bool reflexive = false;
    for(int i = 0; A_len>i;i++){
        for(int j = 0; relation_count>j;j++){
            if((strcmp(A[i],relation[j][0])==0)&&(strcmp(A[i],relation[j][1])==0)){
                reflexive = true;
                break;
            }
        }
        if(!reflexive){
            return false;
        }
        reflexive = false;
    }
    return true;
}

bool Symmetric(char relation[5][2][30], int relation_count){
    bool symmetric = false;
    for(int i = 0; i < relation_count;i++){
        for(int j = 0; j < relation_count;j++){
            if((strcmp(relation[i][0],relation[j][1])==0)&&(strcmp(relation[i][1],relation[j][0])==0)){
                symmetric = true;
                break;
            }
        }
        if(!symmetric){
            return false;
        }
        symmetric = false;
    }
    return true;
}

bool Antisymmetric(char relation[5][2][30], int relation_count){
    bool antisymmetric = true;
    for(int i = 0; i < relation_count;i++){
        if(strcmp(relation[i][0],relation[i][1])!=0){
            for(int j = 0; j < relation_count;j++){
                if((strcmp(relation[i][0],relation[j][1])==0)&&(strcmp(relation[i][1],relation[j][0])==0)){
                    antisymmetric = false;
                    break;
                }
            }
            if(!antisymmetric){
                return false;
            }
            antisymmetric = true;
        }
    }
    return true;
}

bool Transitive(char relation[5][2][30], int relation_count){
    bool transitive = true;
    for(int i = 0; i<relation_count; i++){
        for(int j = i+1; j<relation_count; j++){
            if(strcmp(relation[i][1],relation[j][0])==0){
                for(int k = 0; k<relation_count; k++){
                    if((strcmp(relation[i][0],relation[k][0])==0)&&(strcmp(relation[j][1],relation[k][1])==0)){
                        transitive = true;
                        break;
                    }
                }
                if(!transitive){
                    return false;
                }
                transitive = false;
            }
        }
    }
    return true;
}

bool Function(char relation[5][2][30], int relation_count){
    bool function = true;
    for(int i = 0; i<relation_count; i++){
        for(int j = i+1; j<relation_count; j++){
            if(strcmp(relation[i][0],relation[j][0])==0){
                return false;
            }
        }
    }
    return true;
}

void Domain(char relation[5][2][30], int relation_count){
    printf("S");
    bool unique = true;
    for(int i=0;i<relation_count;i++){
        for(int j=0;j<i;j++){
            if(strcmp(relation[i][0],relation[j][0])==0){
                unique = false;
                break;
            }
        }
        if(unique){
            printf(" %s", relation[i][0]);
        }
        unique = true;
    }
    printf("\n");
}

void Codomain(char relation[5][2][30], int relation_count){
    printf("S");
    bool unique = true;
    for(int i=0;i<relation_count;i++){
        for(int j=0;j<i;j++){
            if(strcmp(relation[i][1],relation[j][1])==0){
                unique = false;
                break;
            }
        }
        if(unique){
            printf(" %s", relation[i][1]);
        }
        unique = true;
    }
    printf("\n");
}

bool Injective(char r[4][2][30], int r_count,char a[3][30],int a_count,char b[3][30],int b_count){
    int injective_for_b = 0;
    int all_injective = 0;
    if(Function(r,r_count)){
        for(int i = 0;i<b_count;i++){
            for(int j = 0;j<r_count;j++){
                if(strcmp(b[i],r[j][1])==0){
                    for(int k = 0;k<a_count;k++){
                        if(strcmp(a[k],r[j][0])==0){
                            injective_for_b++;
                            all_injective ++;
                        }
                    }
                }
            }
            if(injective_for_b>1){
                return false;
            }
            injective_for_b = 0;
        }
        if(all_injective==a_count)
            return true;
    }
    return false;
}

bool Surjective(char r[4][2][30], int r_count,char a[4][30],int a_count,char b[3][30],int b_count){
    int a_surjective = 0;
    bool b_surjective = false;
    if(Function(r,r_count)){
        for(int i = 0;i<b_count;i++){
            for(int j = 0;j<r_count;j++){
                if(strcmp(b[i],r[j][1])==0){
                    b_surjective = true;
                    for(int k = 0;k<a_count;k++){
                        if(strcmp(a[k],r[j][0])==0){
                            a_surjective++;
                        }
                    }
                }
            }
            if(!b_surjective){
                return false;
            }
            b_surjective = false;
        }
        if((a_surjective==a_count))
            return true;
    }
    return false;
}

bool Bijective(char r[4][2][30], int r_count,char a[4][30],int a_count,char b[3][30],int b_count){
    if(Injective(r,r_count,a,a_count,b,b_count)&&Surjective(r,r_count,a,a_count,b,b_count)){
        return true;
    }
    return false;
}


int main()
{
    char A[5][30] = {"a", "bc", "d", "e"};
    int A_len = 4;
    char operand[] = "codomain";
    char relation_count=4;
    char relation[5][2][30] ={{"bc","bc"},{"d","d"},{"a","a"},{"e","e"}};
    char set1[4][30] = {"bc","d","a","e"};
    int set1_count = 4;
    char set2[4][30] = {"e","d","a","bc"};
    int set2_count = 4;

    char operands[10][20] = {"reflexive","symmetric","antisymmetric","transitive","function","domain","codomain","injective","surjective","bijective"};
    int i=0;
    while(i<10&&(strcmp(operands[i],operand))){
        i++;
    }
    switch(i+1){
        case 1:
            printf("%s\n",Reflexive(A,A_len,relation,relation_count)?"true":"false");
            break;
        case 2:
            printf("%s\n",Symmetric(relation,relation_count)?"true":"false");
            break;
        case 3:
            printf("%s\n",Antisymmetric(relation,relation_count)?"true":"false");
            break;
        case 4:
            printf("%s\n",Transitive(relation,relation_count)?"true":"false");
            break;
        case 5:
            printf("%s\n",Function(relation,relation_count)?"true":"false");
            break;
        case 6:
            Domain(relation,relation_count);
            break;
        case 7:
            Codomain(relation,relation_count);
            break;
        case 8:
            printf("%s\n",Injective(relation,relation_count,set1,set1_count,set2,set2_count)?"true":"false");
            break;
        case 9:
            printf("%s\n",Surjective(relation,relation_count,set1,set1_count,set2,set2_count)?"true":"false");
            break;
        case 10:
            printf("%s\n",Bijective(relation,relation_count,set1,set1_count,set2,set2_count)?"true":"false");
            break;
        default:
            printf("neco se pokazilo");
    }
    return 0;
}
