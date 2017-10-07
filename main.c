#include <stdio.h>
#include <string.h>

#define TAM 100
#define DIR '>'
#define ESQ '<'
#define INI '#'
#define ESP '_'

void inicializaFita(char fita[TAM]){//coloca o simbolo inicial no inicio da fita e coloca espaços no final
    int i;
    char aux[TAM]={INI,'\0'};
    strcpy(fita,strcat(aux,fita));
    fita[TAM]='\0';
    for(i=strlen(fita);i<TAM;i++)fita[i]=ESP;
}
int main(){
    char transicoes[TAM][8],estIni[2],estAtual[2],estFin[TAM][2],fita[TAM];
    int cabeca,i,qtdTra=0,qtdFin=0,op=1,flag;
    system("title Maquina Universal");
    printf("Maquina Universal\n\nSimbolos reservados para o sistema:\n\n> andar para a direita\n< andar para a esquerda\n# simbolo inicial\n_ espaco\n\n");
    inserirTuplas(transicoes,&qtdTra,estIni,estFin,&qtdFin);
    while(op==1){//permite verificar várias strings para a mesma máquina de turing
        strcpy(estAtual,estIni);
        system("cls");
        printf("String: ");
        scanf("%s",fita);
        printf("Posicao inicial da cabeca de leitura(a menor posicao e zero): ");
        scanf("%d",&cabeca);
        inicializaFita(fita);
        flag=1;
        while(flag==1)flag=simulaTransicao(estAtual,&fita[cabeca],transicoes,&qtdTra,&cabeca,fita);
        if(flag==0){
            if(estadoPertenceFin(estAtual,estFin,&qtdFin)==1)printf("Essa string e aceita por essa maquina de turing\n\n");
            else printf("Essa string NAO e aceita por essa maquina de turing\n\n");
        }
        printf("Cabeca: %d\nEstado atual: %s\nFita: %s\n\nVerificar outra palavra?\n1 - sim       2 - nao\n\n",cabeca,estAtual,fita);
        scanf("%d",&op);
    }
    system("pause");
    return 0;
}
int estadoPertenceFin(char estAtual[2],char estFin[TAM][2],int *qtdFin){//no momento em que a maquina pára, é verificado se o estado em que parou pertence ao conjunto de estados finais
    int i;
    for(i=0;i<=*qtdFin;i++)if(estFin[i][0]==estAtual[0])return 1;
    return 0;
}
int simulaTransicao(char estA[],char letra[],char transicoes[TAM][8],int *qtdTra,int *cabeca,char fita[TAM]){//verifica se existe transição para o estado atual da maquina e para a letra que a cabeça está apontando na fita
    int i;
    for(i=0;i<*qtdTra;i++){
        if(transicoes[i][0]==estA[0]&&transicoes[i][2]==letra[0]){
            estA[0]=transicoes[i][4];
            if(transicoes[i][6]==DIR) *cabeca = *cabeca + 1;
            else if(transicoes[i][6]==ESQ) *cabeca = *cabeca - 1;
            else fita[*cabeca]=transicoes[i][6];
            return 1;
        }
    }
    return 0;
}
void inserirTuplas(char transicoes[TAM][8],int *qtdTra,char estIni[2],char estFin[TAM][2],int *qtdFin){
    int i;
    printf("Quantidade de transicoes: \n");
    scanf("%d",qtdTra);
    printf("Formato: 1,a,2,b\n");
    for(i=0;i<*qtdTra;i++){
        printf("Transicao %d: ",i+1);
        scanf("%s",transicoes[i]);
    }
    printf("Estado inicial:\n");
    scanf("%s",estIni);
    printf("Quatidade de estados finais: \n");
    scanf("%d",qtdFin);
    for(i=1;i<=*qtdFin;i++){
        printf("Estado final %d: ",i);
        scanf("%s",estFin[i]);
    }
}

