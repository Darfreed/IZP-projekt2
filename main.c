#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAXLENGTH 30

typedef struct
{
    char *c;
    int val;
} type_t;

typedef struct
{
    char **elem;
    unsigned int count;
    unsigned int rowNum;
} Set_t;

typedef struct
{
    char ***elem;
    unsigned int count;
    unsigned int rowNum;
} Relation_t;

typedef struct
{
    char *oper;
    unsigned int *arg;
    unsigned int count;
} Command_t;

typedef struct
{
    char *row_type;
    Set_t U;
    Set_t *S;
    Relation_t *R;
    Command_t *C;
    unsigned int sCounter;
    unsigned int rCounter;
    unsigned int cCounter;
    unsigned int rows;
} row_t;

//set default value
void row_default(row_t *row)
{
    row->row_type = NULL;
    row->U.elem = NULL;
    row->S = NULL;
    row->R = NULL;
    row->C = NULL;
    row->sCounter = 0;
    row->rCounter = 0;
    row->cCounter = 0;
    row->rows = 0;
    row->U.count = 0;
    row->U.rowNum=0;
}



void row_dtor(row_t *row)
{
    //destructor for allocated univers
    if (row->U.elem != NULL)
    {
        for (unsigned int i = 0; i < row->U.count; i++)
        {
            if (row->U.elem[i] != NULL)
            {
                free(row->U.elem[i]);
                row->U.elem[i] = NULL;
            }
        }
        free(row->U.elem);
        row->U.elem = NULL;
    }

    //destructor for each allocated set
    if (row->S != NULL)
    {
        for (unsigned int i = 0; i < row->sCounter; i++)
        {
            for (unsigned int e = 0; e < row->S[i].count; e++)
            {

                free(row->S[i].elem[e]);
                row->S[i].elem[e] = NULL;
            }
            free(row->S[i].elem);
            row->S[i].elem = NULL;
        }
        free(row->S);
        row->S = NULL;
    }

    //destructor for all relations
    if (row->R != NULL)
    {
        for (unsigned int i = 0; i < row->rCounter; i++)
        {
            for (unsigned int e = 0; e < row->R[i].count; e++)
            {
                for (unsigned t = 0; t < 2; t++)
                {
                    free(row->R[i].elem[e][t]);
                    row->R[i].elem[e][t] = NULL;
                }
                free(row->R[i].elem[e]);
                row->R[i].elem[e] = NULL;
            }
        }
        free(row->R);
        row->R = NULL;
    }

    //destructor for each allocated command
    if (row->C != NULL)
    {
        for (unsigned int i = 0; i < row->cCounter; i++)
        {
            free(row->C[i].arg);
            row->C[i].arg = NULL;
        }
        free(row->C);
        row->C = NULL;
    }

    //destructor for allocated characters inside row_type
    free(row->row_type);
    row->row_type = NULL;
}


int find_set(row_t *row,unsigned int row_to_find)
{
    for(unsigned int i = 0;i < row->sCounter;i++){
        if(row->S[i].rowNum==(row_to_find)){
            return i;
        }
    }
    return -1;
}

int find_relation(row_t *row,unsigned int row_to_find)
{
    for(unsigned int i = 0;i < row->rCounter;i++){
        if(row->R[i].rowNum==(row_to_find)){
            return i;
        }
    }
    return -1;
}

bool Reflexive(char **u,int u_len, char ***r, int r_count)
{
    bool reflexive = false;
    for(int i = 0; u_len>i;i++){
        for(int j = 0; r_count>j;j++){
            if((strcmp(u[i],r[j][0])==0)&&(strcmp(u[i],r[j][1])==0)){
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

bool Symmetric(char ***r, int r_count)
{
    bool symmetric = false;
    for(int i = 0; i < r_count;i++){
        for(int j = 0; j < r_count;j++){
            if((strcmp(r[i][0],r[j][1])==0)&&(strcmp(r[i][1],r[j][0])==0)){
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

bool Antisymmetric(char ***r, int r_count)
{
    bool antisymmetric = true;
    for(int i = 0; i < r_count;i++){
        if(strcmp(r[i][0],r[i][1])!=0){
            for(int j = 0; j < r_count;j++){
                if((strcmp(r[i][0],r[j][1])==0)&&(strcmp(r[i][1],r[j][0])==0)){
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

bool Transitive(char ***r, int r_count)
{
    bool transitive = true;
    for(int i = 0; i<r_count; i++){
        for(int j = i+1; j<r_count; j++){
            if(strcmp(r[i][1],r[j][0])==0){
                for(int k = 0; k<r_count; k++){
                    if((strcmp(r[i][0],r[k][0])==0)&&(strcmp(r[j][1],r[k][1])==0)){
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

<<<<<<< HEAD
bool Function(char ***r, int r_count)
{
    bool function = true;
=======
bool Function(char r[5][2][30], int r_count){
>>>>>>> 13d511ae77ccf16deed27b65f375d10c1ce3771e
    for(int i = 0; i<r_count; i++){
        for(int j = i+1; j<r_count; j++){
            if(strcmp(r[i][0],r[j][0])==0){
                return false;
            }
        }
    }
    return true;
}

void Domain(char ***r, int r_count)
{
    printf("S");
    bool unique = true;
    for(int i=0;i<r_count;i++){
        for(int j=0;j<i;j++){
            if(strcmp(r[i][0],r[j][0])==0){
                unique = false;
                break;
            }
        }
        if(unique){
            printf(" %s", r[i][0]);
        }
        unique = true;
    }
    printf("\n");
}

void Codomain(char ***r, int r_count)
{
    printf("S");
    bool unique = true;
    for(int i=0;i<r_count;i++){
        for(int j=0;j<i;j++){
            if(strcmp(r[i][1],r[j][1])==0){
                unique = false;
                break;
            }
        }
        if(unique){
            printf(" %s", r[i][1]);
        }
        unique = true;
    }
    printf("\n");
}

bool Injective(char ***r, int r_count,char **a,int a_count,char **b,int b_count)
{
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

bool Surjective(char ***r, int r_count,char **a,int a_count,char **b,int b_count)
{
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

bool Bijective(char ***r, int r_count,char **a,int a_count,char **b,int b_count)
{
    if(Injective(r,r_count,a,a_count,b,b_count)&&Surjective(r,r_count,a,a_count,b,b_count)){
        return true;
    }
    return false;
}


int print(row_t *row)
{
    char c;
    unsigned int iS = 0, iR = 0, iC = 0;
    for (unsigned int i = 0; i < row->rows; i++)
    {
        c = row->row_type[i];
        switch (c)
        {
        case 'U':
            printf("%c ", c);
            for (unsigned int e = 0; e < row->U.count; e++)
            {
                printf("%s ", row->U.elem[e]);
            }

            printf("\n");
            break;
        case 'S':
            printf("%c ", c);
            for (unsigned int e = 0; e < row->S[iS].count; e++)
            {
                printf("%s ", row->S[iS].elem[e]);
            }
            iS++;
            printf("\n");
            break;
        case 'R':
            printf("%c ", c);
            for (unsigned int e = 0; e < row->R[iR].count; e++)
            {
                printf("(");
                for (unsigned int t = 0; t < 2; t++)
                {
                    if (t == 1)
                    {
                        printf("%s", row->R[iR].elem[e][t]);
                    }
                    else
                    {
                        printf("%s ", row->R[iR].elem[e][t]);
                    }
                }
                printf(") ");
            }
            iR++;
            printf("\n");
            break;
        case 'C':;
            char operands[10][20] = {"reflexive","symmetric","antisymmetric","transitive","function","domain","codomain","injective","surjective","bijective"};
            int operands_count = 10;
            int index=0;
            while(index<operands_count&&(strcmp(operands[index],row->C[iC].oper))){
                index++;
            }
            switch(index+1){
                case 1:
                    printf("%s\n",Reflexive(row->U.elem,row->U.count,row->R[find_relation(row,row->C[iC].arg[0])].elem,row->R[find_relation(row,row->C[iC].arg[0])].count)?"true":"false");
                    break;
                case 2:
                    printf("%s\n",Symmetric(row->R[find_relation(row,row->C[iC].arg[0])].elem,row->R[find_relation(row,row->C[iC].arg[0])].count)?"true":"false");
                    break;
                case 3:
                    printf("%s\n",Antisymmetric(row->R[find_relation(row,row->C[iC].arg[0])].elem,row->R[find_relation(row,row->C[iC].arg[0])].count)?"true":"false");
                    break;
                case 4:
                    printf("%s\n",Transitive(row->R[find_relation(row,row->C[iC].arg[0])].elem,row->R[find_relation(row,row->C[iC].arg[0])].count)?"true":"false");
                    break;
                case 5:
                    printf("%s\n",Function(row->R[find_relation(row,row->C[iC].arg[0])].elem,row->R[find_relation(row,row->C[iC].arg[0])].count)?"true":"false");
                    break;
                case 6:
                    Domain(row->R[find_relation(row,row->C[iC].arg[0])].elem,row->R[find_relation(row,row->C[iC].arg[0])].count);
                    break;
                case 7:
                    Codomain(row->R[find_relation(row,row->C[iC].arg[0])].elem,row->R[find_relation(row,row->C[iC].arg[0])].count);
                    break;
                case 8:
                    printf("%s\n",Injective(row->R[find_relation(row,row->C[iC].arg[0])].elem,row->R[find_relation(row,row->C[iC].arg[0])].count,row->S[find_set(row,row->C[iC].arg[1])].elem,row->S[find_set(row,row->C[iC].arg[1])].count,row->S[find_set(row,row->C[iC].arg[2])].elem,row->S[find_set(row,row->C[iC].arg[2])].count)?"true":"false");
                    break;
                case 9:
                    printf("%s\n",Surjective(row->R[find_relation(row,row->C[iC].arg[0])].elem,row->R[find_relation(row,row->C[iC].arg[0])].count,row->S[find_set(row,row->C[iC].arg[1])].elem,row->S[find_set(row,row->C[iC].arg[1])].count,row->S[find_set(row,row->C[iC].arg[2])].elem,row->S[find_set(row,row->C[iC].arg[2])].count)?"true":"false");
                    break;
                case 10:
                    printf("%s\n",Bijective(row->R[find_relation(row,row->C[iC].arg[0])].elem,row->R[find_relation(row,row->C[iC].arg[0])].count,row->S[find_set(row,row->C[iC].arg[1])].elem,row->S[find_set(row,row->C[iC].arg[1])].count,row->S[find_set(row,row->C[iC].arg[2])].elem,row->S[find_set(row,row->C[iC].arg[2])].count)?"true":"false");
                    break;
            }
            iC++;
            break;
        default:
            break;
        }
    }
    return 0;
}

int typeFromStr(char *str)
{
    type_t types[] = {{"U", 'U'}, {"S", 'S'}, {"R", 'R'}, {"C", 'C'}};
    for (unsigned int i = 0; i < sizeof(types) / sizeof(type_t); i++)
    {
        if (strcmp(types[i].c, str) == 0)
        {
            return types[i].val;
        }
    }
    return 0;
}

int saveInStruct(const char *fileName, row_t *row)
{
    //set default row
    row_default(row);
    FILE *fp;
    int c, t, i = 0, elemCounter = 0;
    unsigned int rowElem = 0;
    bool type = false, univers = false, word = false, white = false, command = false, cOper = false, right = true, left = false, relation = false, cNum = false;
    char str[MAXLENGTH + 1];
    char *bannedWords[] = {"true", "false", "empty", "card", "complemen", "union", "intersect", "minus", "subseteq", "subset", "equals", "reflexive ", "symmetric", "antisymmetri", "transitive", "function", "domain", "codomain", "injective", "surjective", "bijective"};
    unsigned int sizeOfBannedWords = sizeof(bannedWords) / sizeof(bannedWords[0]);
    //read file
    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        return 1;
    }
    while ((c = fgetc(fp)) != EOF)
    {
        //control if are in R ()
        if (t == 'R')
        {
            if (c == '(' || c == ')')
            {
                if (!left && c == '(')
                {
                    left = true;
                    right = false;
                    c = fgetc(fp);
                    rowElem++;
                    if (relation)
                    {
                        elemCounter = 0;
                    }
                    relation = false;
                }
                else if (!right && c == ')')
                {
                    left = false;
                    right = true;
                    c = fgetc(fp);
                    if (c != ' ' && c != '\n' && c != 13)
                    {
                        return 10;
                    }
                }
                else
                {
                    return 10;
                }
            }
        }

        if (c==13)
            {
                c = fgetc(fp);
            }

        //if c==' ' or '\n' its probably end of word or type
        if (c == ' ' || c == '\n')
        {

            str[i] = '\0';

            //check if is string somewhere inside arrey
            if (type && t == 'U')
            {

                for (unsigned int e = 0; e < sizeOfBannedWords; e++)
                {
                    //strstr check for substring inside string
                    if (strstr(str, bannedWords[e]) != NULL)
                    {
                        return 6;
                    }
                }
            }


            if (!type)
            {
                t = typeFromStr(str);
                if (!univers && t != 'U')
                {
                    return 2;
                }
                else if (command && t != 'C')
                {
                    return 3;
                }
            }
            else
            {
                if (word && !white)
                {
                    elemCounter++;
                    if (t == 'R')
                    {
                        if (right)
                        {
                            if (elemCounter != 2)
                            {
                                return 7;
                            }
                            relation = true;
                        }
                        if (!right && elemCounter > 2)
                        {
                            return 7;
                        }
                    }
                }
            }
            //add elements inside structure
            switch (t)
            {
            case 'U':
                if (!type)
                {
                    row->U.rowNum=row->rows+1;
                    type = true;
                    if (univers)
                    {
                        return 5;
                    }
                    univers = true;
                }
                else if (!white)
                {
                    row->U.count = elemCounter;
                    char **pom = realloc(row->U.elem, sizeof(char *) * row->U.count);
                    if (pom == NULL)
                    {
                        return 8;
                    }
                    row->U.elem = pom;
                    row->U.elem[elemCounter - 1] = NULL;
                    char *elem = realloc(row->U.elem[elemCounter - 1], sizeof(char) * strlen(str));
                    if (elem == NULL)
                    {
                        return 8;
                    }
                    row->U.elem[elemCounter - 1] = elem;
                    strcpy(row->U.elem[elemCounter - 1], str);
                }

                break;
            case 'S':
                if (!type)
                {
                    type = true;
                    row->sCounter += 1;
                    Set_t *set = realloc(row->S, sizeof(Set_t) * row->sCounter);
                    if (set == NULL)
                    {
                        return 8;
                    }
                    row->S = set;
                    row->S[row->sCounter - 1].elem = NULL;
                    row->S[row->sCounter - 1].count = 0;
                    row->S[row->sCounter-1].rowNum=row->rows+1;
                }
                else if (!white)
                {
                    row->S[row->sCounter - 1].count = elemCounter;
                    char **pom = realloc(row->S[row->sCounter - 1].elem, sizeof(char *) * elemCounter);
                    if (pom == NULL)
                    {
                        return 8;
                    }
                    row->S[row->sCounter - 1].elem = pom;
                    row->S[row->sCounter - 1].elem[elemCounter - 1] = NULL;
                    char *nstr = realloc(row->S[row->sCounter - 1].elem[elemCounter - 1], strlen(str));
                    if (nstr == NULL)
                    {
                        return 8;
                    }
                    row->S[row->sCounter - 1].elem[elemCounter - 1] = nstr;
                    strcpy(row->S[row->sCounter - 1].elem[elemCounter - 1], str);
                }

                break;
            case 'R':
                if (!type)
                {
                    type = true;
                    row->rCounter += 1;
                    Relation_t *rel = realloc(row->R, sizeof(Relation_t) * row->rCounter);
                    if (rel == NULL)
                    {
                        return 8;
                    }
                    row->R = rel;
                    row->R[row->rCounter - 1].elem = NULL;
                    row->R[row->rCounter - 1].count = 0;
                    row->R[row->rCounter-1].rowNum=row->rows+1;
                }
                else if (!white)
                {
                    if (rowElem > row->R[row->rCounter - 1].count)
                    {
                        row->R[row->rCounter - 1].count = rowElem;
                        char ***relat = realloc(row->R[row->rCounter - 1].elem, sizeof(char *) * rowElem);
                        if (relat == NULL)
                        {
                            return 8;
                        }
                        row->R[row->rCounter - 1].elem = relat;
                        row->R[row->rCounter - 1].elem[rowElem - 1] = NULL;
                    }

                    char **elem = realloc(row->R[row->rCounter - 1].elem[rowElem - 1], sizeof(char *) * elemCounter);
                    if (elem == NULL)
                    {
                        return 8;
                    }
                    row->R[row->rCounter - 1].elem[rowElem - 1] = elem;
                    row->R[row->rCounter - 1].elem[rowElem - 1][elemCounter - 1] = NULL;
                    char *nstr = realloc(row->R[row->rCounter - 1].elem[rowElem - 1][elemCounter - 1], strlen(str));
                    if (nstr == NULL)
                    {
                        return 8;
                    }
                    row->R[row->rCounter - 1].elem[rowElem - 1][elemCounter - 1] = nstr;
                    strcpy(row->R[row->rCounter - 1].elem[rowElem - 1][elemCounter - 1], str);
                }
                break;
            case 'C':
                if (!type)
                {
                    type = true;
                    row->cCounter += 1;
                    command = true;
                    cOper = true;
                    Command_t *command = realloc(row->C, sizeof(Command_t) * row->cCounter);
                    if (command == NULL)
                    {
                        return 8;
                    }
                    row->C = command;
                    row->C[row->cCounter - 1].arg = NULL;
                    row->C[row->cCounter - 1].oper = NULL;
                    row->C[row->cCounter - 1].count = 0;
                }
                else if (!white)
                {
                    if (cOper)
                    {
                        char *oper = realloc(row->C[row->cCounter - 1].oper, strlen(str));
                        if (oper == NULL)
                        {
                            return 8;
                        }
                        row->C[row->cCounter - 1].oper = oper;
                        cOper = false;
                        cNum = true;
                        strcpy(row->C[row->cCounter - 1].oper, str);
                    }
                    else
                    {
                        row->C[row->cCounter - 1].count++;
                        unsigned int *arg = realloc(row->C[row->cCounter - 1].arg, sizeof(unsigned int *) * row->C[row->cCounter - 1].count);
                        if (arg == NULL)
                        {
                            return 8;
                        }
                        row->C[row->cCounter - 1].arg = arg;
                        row->C[row->cCounter - 1].arg[row->C[row->cCounter - 1].count - 1] = atoi(str);
                    }
                }

                break;

            default:
                return 4;
            }
            if (c == '\n'||c == 13)
            {
                if (t == 'S' && !word)
                {
                    row->S[row->sCounter - 1].count = 0;
                }
                else if (t != 'S' && !word)
                {
                    return 1;
                }
                row->rows++;
                char *type_row = realloc(row->row_type, row->rows + 1);
                if (type_row == NULL)
                {
                    return 8;
                }
                row->row_type = type_row;
                row->row_type[row->rows - 1] = t;
                row->row_type[row->rows] = '\0';
                type = false;
                elemCounter = 0;
                rowElem = 0;
                word = false;
                cNum = false;
            }
            white = true;
            i = 0;
        }
        else
        {
            white = false;
            if (type && !word)
            {
                word = true;
            }

            if (i >= MAXLENGTH)
            {
                return 11;
            }
            if (t != 'C' && ((c > 'Z' || c < 'A') && (c > 'z' || c < 'a')))
            {
                return 12;
            }
            if (cNum)
            {
                if (c > '9' || c < '0')
                {
                    return 13;
                }
            }
            str[i] = c;
            i++;
        }
    }
    fclose(fp);
    if ((row->sCounter==0&&row->rCounter==0)||row->cCounter==0)
    {
        return 9;
    }
    return 0;
}



int main(int argc, char const *argv[])
{
    char *errors[] = {"File not found.", "The file should start with U.", "After C there can't be anything than C.","Row type should be U, S, R or C.",
                        "Only one U is supported.", "There are some banned words or somothing that is not inside U.", "There should be exactly two elements inside R.",
                        "Memory error.","File should contain a line with U, S, or R and C.","After ( or ) in R there should be a space or the end of a line.","Too long a string.",
                        "String should contain onlz A-Z and a-z characters.","After the identifier should be a numeric value.","Bad number of arguments","Wrong type of row selected"};

    row_t r1;
    int err = saveInStruct(argv[1], &r1);
    if (err != 0)
    {
        fprintf(stderr, "%s", errors[err - 1]);
        row_dtor(&r1);
        return EXIT_FAILURE;
    }
    err = print(&r1);
    if (err != 0)
    {
        fprintf(stderr, "%s", errors[err - 1]);
        row_dtor(&r1);
        return EXIT_FAILURE;
    }
    row_dtor(&r1);

    return 0;
}
