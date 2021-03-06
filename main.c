//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Seção de variáveiss
#define MAX_TAMANHO_DA_PALAVRA 100
#define NUMERO_ITENS 5
#define OPCOES_DIA 3
#define OPCOES_MENU 4
#define MAX_TAMANHO_NOME 150
#define VALOR_PROVA 10

int sair = 0;
int final = 0;

void criarlinha(int n);
void inserindoInfoDoProtagonista(char tipo, int info);
void itemprova();

//Lista dinâmica
struct listadinamica
{
	char palavra [MAX_TAMANHO_DA_PALAVRA];
	struct listadinamica *p;
	
};

typedef struct listadinamica Item;
typedef struct listadinamica* listadef;

listadef *crialistadinamica (){
	listadef *plista;
	plista = (listadef*) malloc (sizeof(listadef));
	
	if (plista != NULL)
	{
		*plista = NULL;
	}
	
	return plista;
}

void escrevelistadinamicaf(listadef *ponteiro, char n[MAX_TAMANHO_DA_PALAVRA]) {
	Item *no;
	no = (Item*) malloc (sizeof(Item));
	strcpy(no->palavra, n);
	no->p = (*ponteiro);
	*ponteiro = no;

}

int qtd_itens(listadef *p){
	int cont = 0;
	Item *no = *p;

	while (no != NULL)
	{
		cont++;
		no=no->p;
	}
	
	return cont;
}

void ler_lista(listadef *p){
	Item *no = *p;

	for (int i = 0; i< qtd_itens(p); i++){
		criarlinha(40);
		printf("(%d) %s\n", i, no->palavra);
		no=no->p;
	}
	criarlinha(40);
}

int remover_elemento(listadef *p, char n [MAX_TAMANHO_DA_PALAVRA]){
	
	if ((p == NULL) || ((*p)  == NULL)) {
		return 0;
	} else {
		Item *no_atual, *no_ant;
		no_atual = *p;

		while(no_atual != NULL && no_atual->palavra != n){
			if (strcmp(no_atual->palavra, n) == 0) {
				break;
			}
			no_ant = no_atual;
			no_atual = no_atual->p;
		}

		if (no_atual == 0) {
			return 2; //Se retornar 2 não achou o elemento
		} else {
			if (no_atual == *p) {
				*p = no_atual->p;
			} else {
				no_ant->p = no_atual->p;
			}

		}
		free(no_atual);
		return 1;
	}


}


struct protag
{
    char nome[MAX_TAMANHO_DA_PALAVRA];
    int energia;
    int estudo;
    int social;
    int dinheiro;
    int saude;
    int dia_atual;
    int nota;
    listadef *listaitem;
};

struct protag protagonista;

//Seção menus
void criarlinha(int n) {
    for (int i = 0; i < n; i++) {
        printf("-");
    }
    printf("\n");
}

void imprimeListaDePalavras(char arr[][MAX_TAMANHO_DA_PALAVRA], int tam){
    
    criarlinha(34);

    for(int i =0; i < tam; i++  ){
        printf("|(%d) %s \n",i, arr[i]);
        criarlinha(34);
    }

}


//Criar personagem
void Protagonista(){
    fflush(stdin);

    printf("Qual o nome do aluno?\n");
        fgets(protagonista.nome, MAX_TAMANHO_DA_PALAVRA, stdin);
    
    protagonista.energia = 10;
    protagonista.dinheiro = 10;
    protagonista.estudo = 0;
    protagonista.saude = 10;
    protagonista.social = 0;
    protagonista.nota = 0;
    protagonista.listaitem = crialistadinamica();
}

//Lê os créditos
void LerCreditos(){
  
    char aux_str[MAX_TAMANHO_DA_PALAVRA];

    FILE *fpInfo;

    fpInfo = fopen("Creditos.txt" , "r");
   
    criarlinha(34);

    if(fpInfo == NULL){
        printf("Erro na abertura do arquivo -> não foi possível mostrar os créditos\n");
        return;
    } 

    while(!feof(fpInfo)){
       fgets(aux_str,MAX_TAMANHO_DA_PALAVRA, fpInfo);
        printf("%s\n",aux_str);
   }

    fclose(fpInfo);
}

//Introdução
void LerInicio(){

    printf("Texto do inicio\n");

}

//Compra de itens nos dias comuns
void ItemDias(){
    int aux;
    fflush(stdin);

    printf("Compre itens para usar na hora da prova! Voce tem %d de dinheiro sobrando\n", protagonista.dinheiro);

    char itens[NUMERO_ITENS][MAX_TAMANHO_DA_PALAVRA] = {"Cafe (+2 de energia) - 2 reais", "Barrinha de cereal (+5 de energia) - 5 reais", "Livro didatico (+3 de estudo) - 10 reais", "Folha de resposta (+10 de ... estudo?) - 20 reais", "To so dando uma olhadinha (voltar ao menu)"};
    imprimeListaDePalavras(itens, NUMERO_ITENS);

    scanf("%d", &aux);

    switch (aux)
    {
    case 0:
        //café
        if (protagonista.dinheiro >= 2) {
            printf("Voce comprou um cafe!\n");
            protagonista.dinheiro -= 2;
            escrevelistadinamicaf(protagonista.listaitem, "Cafe (+2 de energia)");
        } else {
            printf("Sem dinheiro o suficiente! (Saldo restante: %d reais)\n", protagonista.dinheiro);
        }
        break;
    case 1:
        //Barrinha
        if (protagonista.dinheiro >= 5) {
            printf("Voce comprou uma barrinha de cereal!\n");
            protagonista.dinheiro -= 5;    
            escrevelistadinamicaf(protagonista.listaitem, "Barrinha de cereal (+5 de energia)");
        } else {
            printf("Sem dinheiro o suficiente! (Saldo restante: %d reais)\n", protagonista.dinheiro);
        }
        break;
    case 2:
        //livro
        if (protagonista.dinheiro >= 10) {
            printf("Voce comprou um livro didatico!\n");
            protagonista.dinheiro -= 10;
            escrevelistadinamicaf(protagonista.listaitem, "Livro didatico (+3 de estudo)");
        } else {
            printf("Sem dinheiro o suficiente! (Saldo restante: %d reais)\n", protagonista.dinheiro);
        }
        break;
    case 3:
        //Respostas
        if (protagonista.dinheiro >= 20) {
            printf("Voca comprou uma folha de respostas!\n");
            protagonista.dinheiro -=20;
            escrevelistadinamicaf(protagonista.listaitem, "Folha de resposta (+10 de ... estudo?)");
        } else {
            printf("Sem dinheiro o suficiente! (Saldo restante: %d reais)\n", protagonista.dinheiro);
        }
        break;
    case 4:
        break;
    default:
        printf("Houve um erro, por favor digite novamente\n");
        ItemDias();
        break;
    }
	
	protagonista.energia--;

}

//Sistema de Salvar (0 )
void Carregar(){
   
    char aux_str[MAX_TAMANHO_DA_PALAVRA];

    FILE *fpInfo;
    int num = 0;
   
    fpInfo = fopen("Save.txt" , "r");
   
    char att[6] = {'e', '&','s','z','d','a'};
    char attInfo[6][MAX_TAMANHO_DA_PALAVRA] = {"Energia", "Estudo", "Social", "Saude", "Dinheiro","Dia Atual"};

    printf("Carregando as informacoes...... \n");
    criarlinha(34);

    if(fpInfo == NULL){
        printf("Erro na abertura do arquivo -> não foi possível recuperar as informações salvas\n");
        return;
    } 


    printf("Informaçoes salvas :");



    while(!feof(fpInfo)){
        if(num == 0){
            fgets(aux_str,MAX_TAMANHO_DA_PALAVRA, fpInfo);
            strcpy(protagonista.nome , aux_str);
            printf("Bem vindo de volta %s\n", protagonista.nome);

        } else if (num > 0 && num < 7){
            int info = atoi(fgets(aux_str,MAX_TAMANHO_DA_PALAVRA, fpInfo));
            printf("%s : %d\n",attInfo[num - 1], info);
            inserindoInfoDoProtagonista(att[num - 1], info);
        } else {
            break;
        }
        num ++;
   }

    fclose(fpInfo);


}

int obtendoInfoDoProtagonista(char tipo){
    switch(tipo){
        case 'e' :
            return protagonista.energia;
        case '&' : 
            return protagonista.estudo;
        case 's' :
            return protagonista.social;
        case 'z' :
            return protagonista.saude;
        case 'd' :
            return protagonista.dinheiro;
        default :
            return protagonista.dia_atual;
    }
}

void inserindoInfoDoProtagonista(char tipo, int info){
    switch(tipo) {
        case 'e' :
            protagonista.energia = info;
        case '&' :
            protagonista.estudo = info;
        case 's' :
            protagonista.social = info;
        case 'z' :
            protagonista.saude = info;
        case 'd' :
            protagonista.dinheiro = info;
        default :
            protagonista.dia_atual = info;
    }

}


void Salvar(){
    char aux_str[MAX_TAMANHO_DA_PALAVRA];
    FILE *fpInfo;

    char c;
    
    fpInfo = fopen("Save.txt" , "w");


    char att[6] = {'e', '&','s','z','d','a'};

    if( fpInfo == NULL){
        printf("Erro na abertura do arquivo - Não foi possível salvar as informações\n");
        return;
    } 

    fprintf(fpInfo, protagonista.nome);

    for(int i =0; i < 6; i++){
        fprintf(fpInfo, strcat(itoa(obtendoInfoDoProtagonista(att[i]), aux_str, 10), "\n"));
    }
    fclose(fpInfo);
}

//Ações nos dias comuns
void atividade(){
    char ativ;
    printf("Praticou alguma atividade fisica? (s ou n) \n");
    scanf(" %c", &ativ);
      if(ativ == 's'){
        protagonista.saude += 2;
        protagonista.energia -=1;
        printf("Voce ganhou 2 pontos! \n");
        } else if (ativ == 'n'){
            printf("Sem alteracao na pontuacao. \n");
            } else{
               printf("Resposta invalida! Por favor, responda com 's' em caso afirmativo ou com 'n' em caso negativo.\n");
               criarlinha(34);
               atividade();
               }
 printf("\n");
}

void agua(){
    char agu;
    printf("Bebeu 2L ou mais de agua? (s ou n)\n");
    scanf(" %c", &agu);
    if(agu == 's'){
        protagonista.saude += 3;
        protagonista.energia -=1;
        printf("Voce ganhou 3 pontos! \n");
        } else if (agu == 'n'){
              printf("Sem alteracao na pontuacao. \n");
              } else{
                 printf("Resposta invalida! Por favor, responda com 's' em caso afirmativo ou com 'n' em caso negativo.\n");
                 printf("As perguntas serao recomecadas: \n");
                 criarlinha(34);
                 agua();
                 }
 printf("\n");
}

void sono(){
    char son;
    printf("Teve de 7 a 9 horas de sono? (s ou n) \n");
    scanf(" %c", &son);
    if(son == 's'){
        protagonista.saude += 4;
        protagonista.energia -=1;
        printf("Voce ganhou 4 pontos! \n");
        } else if (son == 'n'){
            printf("Sem alteracao na pontuacao. \n");
            }else {
              printf("Resposta invalida! Por favor, responda com 's' em caso afirmativo ou com 'n' em caso negativo.\n");
              printf("As perguntas serao recomecadas: \n");
              criarlinha(34);
              sono();
              }
 printf("\n");
}

void compra(){
    char comp;
    printf("Esta trabalhando regularmente? \n");
    scanf(" %c", &comp);
    if(comp == 's'){
        protagonista.dinheiro += 5;
        protagonista.energia -=1;
        printf("Voce ganhou 5 pontos! \n");
        } else if (comp == 'n'){
            printf("Sem alteracao na pontuacao. \n");
        }else{
            printf("Resposta invalida! Por favor, responda com 's' em caso afirmativo ou com 'n' em caso negativo.\n");
            printf("As perguntas serao recomecadas: \n");
            criarlinha(34);
            compra();
            }
 printf("\n");
}

void gasto(){
    char imp;
    printf("Esta ganhando uma renda extra? \n");
    scanf(" %c", &imp);
    if(imp == 's'){
        protagonista.dinheiro += 4;
        protagonista.energia -=1;
        printf("Voce ganhou 4 pontos! \n");
        } else if (imp == 'n'){
            printf("Sem alteracao na pontuacao. \n");
            }else{
            printf("Resposta invalida! Por favor, responda com 's' em caso afirmativo ou com 'n' em caso negativo.\n");
            printf("As perguntas serao recomecadas: \n");
            criarlinha(34);
            gasto();
            }
 printf("\n");
}

void mensagem(){
    char msg;
     printf("Teve uma troca de mensagens legal com alguem? \n");
    scanf(" %c", &msg);
    if(msg == 's'){
        protagonista.social += 3;
        protagonista.energia -=1;
        printf("Voce ganhou 3 pontos! \n");
        } else if (msg == 'n'){
            printf("Sem alteracao na pontuacao. \n");
            } else {
            printf("Resposta invalida! Por favor, responda com 's' em caso afirmativo ou com 'n' em caso negativo.\n");
            printf("As perguntas serao recomecadas: \n");
            criarlinha(34);
            mensagem();
            }
 printf("\n");
}

void redes(){
    char rede;
    printf("Interagiu nas redes sociais \n");
    scanf(" %c", &rede);
    if(rede == 's'){
        protagonista.social += 2;
        protagonista.energia -=1;
        printf("Voce ganhou 2 pontos! \n");
        } else if (rede == 'n'){
            printf("Sem alteracao na pontuacao. \n");
            } else {
            printf("Resposta invalida! Por favor, responda com 's' em caso afirmativo ou com 'n' em caso negativo.\n");
            printf("As perguntas serao recomecadas: \n");
            criarlinha(34);
            redes();
            }
 printf("\n");
}

void hoje(){
    char est1;
    printf("Voce estudou hoje? \n");
    scanf(" %c", &est1);
    if(est1 == 's'){
        protagonista.estudo += 4;
        protagonista.energia -=1;
        printf("Voce ganhou 4 pontos! \n");
        } else if (est1 == 'n'){
            printf("Sem alteracao na pontuacao. \n");
            } else {
            printf("Resposta invalida! Por favor, responda com 's' em caso afirmativo ou com 'n' em caso negativo.\n");
            printf("As perguntas serao recomecadas: \n");
            criarlinha(34);
            hoje();
            }
 printf("\n");
}

void curso(){
    char est2;
    printf("Estudou algum(a) curso/materia extracurricular? \n");
    scanf(" %c", &est2);
    if(est2 == 's'){
        protagonista.estudo += 2;
        protagonista.energia -=1;
        printf("Voce ganhou 2 pontos! \n");
        } else if (est2 == 'n'){
            printf("Sem alteracao na pontuacao. \n");
            } else {
            printf("Resposta invalida! Por favor, responda com 's' em caso afirmativo ou com 'n' em caso negativo.\n");
            printf("As perguntas serao recomecadas: \n");
            criarlinha(34);
            curso();
            }
 printf("\n");
}

void meta(){
    char est3;
    printf("Cumpriu sua meta de estudos do dia? \n");
    scanf(" %c", &est3);
    if(est3 == 's'){
        protagonista.estudo += 3;
        protagonista.energia -=1;
        printf("Voce ganhou 3 pontos! \n");
        } else if (est3 == 'n'){
            printf("Sem alteracao na pontuacao. \n");
        } else {
            printf("Resposta invalida! Por favor, responda com 's' em caso afirmativo ou com 'n' em caso negativo.\n");
            printf("As perguntas serao recomecadas: \n");
            criarlinha(34);
            meta();
            }
 printf("\n");
}

void AcoesDias(){

    char s, n;


    printf("Responda com 's' caso voce tenha feito aquela acao ou 'n' caso voce nao tenha a feito: \n");
    printf("\n");

    if(protagonista.energia>0){
    printf("Acoes relacionadas a saude: \n");
    printf("\n");

    atividade(s,n);}
    if(protagonista.energia>0){
    agua(s,n);}
    if(protagonista.energia>0){
    sono(s,n);}

    if(protagonista.energia>0){
    printf("Acoes relacionadas ao dinheiro: \n");
    printf("\n");

    compra(s,n);}
    if(protagonista.energia>0){
    gasto(s,n);}

    if(protagonista.energia>0){
    printf("Acoes relacionadas a vida social: \n");
    printf("\n");

    mensagem(s,n);}
    if(protagonista.energia>0){
    redes(s,n);}

    if(protagonista.energia>0){
    printf("Acoes relacionadas ao estudo: \n");
    printf("\n");

    hoje(s,n);}
    if(protagonista.energia>0){
    curso(s,n);}
    if(protagonista.energia>0){
    meta(s,n);} else{
    printf("Voce nao tem energia suficiente para realizar mais acoes\n");
    }

}


//Sistema de provas
void Prova(int dia){
    int vida_prova, aux, continua = 0, maxprova, r;
    char prova[3][MAX_TAMANHO_DA_PALAVRA] = {"Tentar responder as questoes (-1 energia)", "Usar um item", "Desisto!"};

    if(dia <= 4) {
            printf("Hora da prova 1!\n");
            maxprova = VALOR_PROVA;
    } else {
            printf("Hora da prova final!\n");
            maxprova = VALOR_PROVA*2;
    }
    
    vida_prova = maxprova;

    while (continua == 0){

        if (protagonista.energia <= 0)
        {
            break;
        }
        

        printf("Ainda faltam %d de %d questoes\nVoce tem %d de energia sobrando\n", vida_prova, maxprova, protagonista.energia);

        imprimeListaDePalavras(prova, 3);
        scanf("%d", &aux);

        switch (aux)
        {
        case 0:
            r = (rand() % 4) + 0.5*protagonista.estudo;
            vida_prova = vida_prova - r;
            printf("Voce conseguiu fazer %d questoes\n", r);
            break;
        
        case 1:
            itemprova();
            break;
        case 2:
            printf("Voce desistiu de fazer a prova. Acontece\n");
            protagonista.energia = -1;
            continua = 1;
        default:

            break;
        }

        if (vida_prova <= 0) {
            continua = 1;
        } else {
            protagonista.energia--;
        }
    }

    if (protagonista.energia >= 0) {
        printf("Voce terminou a prova!\n");
        protagonista.nota++;
    } else {
        printf("Voce nao conseguiu terminar a prova\n");
    }
}

void itemprova(){
    int aux;

    if (qtd_itens(protagonista.listaitem) <= 0) {
        printf("Voce nao tem nenhum item!\n");
    } else {
        ler_lista(protagonista.listaitem);

        printf("Que item voce quer utilizar?\n");
        fflush(stdin);
        scanf("%d", &aux);

        Item *no;
	    no = *protagonista.listaitem;

        for (int i = 0; i < aux; i++) {
            if (no == NULL) {
                break;
            } else {
                no = no->p;
            }
	    }

        //if (no->palavra == "Cafe (+2 de energia)") {
        
        if (strcmp(no->palavra, "Cafe (+2 de energia)") == 0) {
            protagonista.energia += 3;
            remover_elemento(protagonista.listaitem, "Cafe (+2 de energia)");
        } else if (strcmp(no->palavra, "Barrinha de cereal (+5 de energia)") == 0) {
            protagonista.energia += 6;
            remover_elemento(protagonista.listaitem, "Barrinha de cereal (+5 de energia)");
        } else if (strcmp(no->palavra, "Livro didatico (+3 de estudo)") == 0) {
            protagonista.estudo += 3;
            remover_elemento(protagonista.listaitem, "Livro didatico (+3 de estudo)");
        } else if (strcmp(no->palavra, "Folha de resposta (+10 de ... estudo?)") == 0) {
            protagonista.estudo += 10;
            remover_elemento(protagonista.listaitem, "Folha de resposta (+10 de ... estudo?)");
        } else {
            printf("0");
        }

        printf("Voce usou o item! \n");
    }
}

int *selectionSort (int *vet, int N){
    int i=0, j=0, menor=0, troca=0;

    for(i=0;i<N-1;i++){
        menor=i;
        for(j=i+1;j<N;j++){
            if(vet[j] < vet[menor]){
                menor=j;
            }
        }
        if(i!=menor){
            troca=vet[i];
            vet[i]=vet[menor];
            vet[menor]=troca;

        }
    }
    return vet;

}

void Final(){
    criarlinha(34);
    printf("Voce chegou ao FINAL do nosso jogo! \n");
    printf("\n");
    int vetor[4]={protagonista.saude, protagonista.dinheiro,protagonista.estudo, protagonista.social};

    vetor[4]=selectionSort(vetor,4);

    printf("Suas pontuacoes (da menor para maior) foram: ");
    for(int i=0;i<4;i++){
        printf("%i ",vetor[i]);
    }
    printf("\n");
    printf("Sendo %d pontos em relacao a sua SAUDE, %d pontos em relacao ao seu DINHEIRO, %d pontos em relacao ao seu ESTUDO e %d pontos em relacao a sua vida SOCIAL.  \n", protagonista.saude, protagonista.dinheiro, protagonista.estudo, protagonista.social);
    printf("\n");
    printf("Agora, as consequencias da sua pontuacao: \n");
    printf("\n");

    printf("SAUDE: \n");
    if(protagonista.saude >= 28){
        printf("Olha só! Você foi um dos unicos que nao ficou doente nesse inverno e foi atleta destaque da CAAP!\n");
    } else if (protagonista.saude < 28 && protagonista.saude >= 14){
        printf("Voce teve uma gripe leve, porem teve que faltar dos treinos da atletica da semana.\n");
    } else if (protagonista.saude < 14&& protagonista.saude>=0){
        printf("Ops... voce pegou sarampo no campus de SBC \n");
    }
printf("\n");
    printf("DINHEIRO: \n");
    if(protagonista.dinheiro >= 37){
        printf("Boa! Voce conseguiu pagar o aluguel da rep, suas contas e ainda sobrou dinheiro! \n");
    } else if (protagonista.dinheiro < 37 && protagonista.dinheiro >= 18){
        printf("Voce conseguiu pagar as contas, mas nao sobrou nada.\n");
    } else if (protagonista.dinheiro < 18 && protagonista.dinheiro>=0){
        printf("Voce ficou devendo o aluguel da rep. \n");
        }else if (protagonista.dinheiro < 0){
        printf("Voce teve que pedir dinheiro empretado aos seus amigos para passar o mes");
        }

printf("\n");
    printf("ESTUDO: \n");
    if(protagonista.estudo >= 44){
        printf("Parebens! Voce fechou todas as materias com A!\n");
    } else if (protagonista.estudo < 44 && protagonista.estudo >= 22){
        printf("Voce passou em todas as materias, porem apenas com notas C e D \n");
    } else if (protagonista.estudo < 22 && protagonista.estudo>=0){
        printf("Voce reprovou uma materia e passou com D nas outras \n");
        }else if (protagonista.estudo < 0){
        printf("Voce tirou F em todas as materias");
        }
printf("\n");
    printf("SOCIAL: \n");
    if(protagonista.social >= 13){
        printf("Ual, voce foi o centro das atencoes no Agacaiu! \n");
    } else if (protagonista.social < 13 && protagonista.social >= 0){
        printf("Conseguiu se enturmar e fazer amizade na sala de aula nova.\n");
    }else if (protagonista.social < 0){
        printf("Vixe, seus amigos marcaram um role no Sinucao e nao te chamaram. \n");
        }

printf("\n");
    //final prova:
    //Se nota = 0 -> reprosvou as duas / nota = 1 -> passou em uma / se nota = 2 -> Passou nas duas
    printf("E por fim, o resultado das PROVAS: \n");
    if(protagonista.nota == 0){
        printf("Voce reprovou nas duas provas. \n");
    } else if(protagonista.nota == 1){
        printf("Você passou em apenas uma prova. \n");
    } else if(protagonista.nota == 2){
        printf("Parabens! Voce passou nas duas provas! \n");
    }
printf("\n");
}

//Exibe a tela de início
int tela(){
    fflush(stdin);
    int esc = 0;

    char menu[OPCOES_MENU][MAX_TAMANHO_DA_PALAVRA] = {"Novo jogo", "Carregar jogo", "Creditos", "Sair"};
    imprimeListaDePalavras(menu, OPCOES_MENU);

    scanf(" %d", &esc);

    if (esc == 0) {
        Protagonista();
    } else if (esc == 1) {
        Carregar();
    } else if (esc == 2) {
        LerCreditos();
        tela();
    } else if (esc == 3){
        sair = 1;
    } else {
        printf("Houve um erro, por favor digite novamente\n");
        tela();
    }

    return esc;
}

void dias(){
    int esc;
    fflush(stdin);

    char diaacoes[OPCOES_DIA][MAX_TAMANHO_DA_PALAVRA] = {"Fazer alguma coisa!", "Ir no mercadinho", "Ir dormir (encerrar o dia)"};
    
    printf("Mais um dia comeca! O que %s vai fazer hoje?\n", protagonista.nome);
    while (1 == 1) {    

        printf("%s tem %d/10 de energia restando\n", protagonista.nome, protagonista.energia);
        imprimeListaDePalavras(diaacoes, OPCOES_DIA);
        scanf(" %d", &esc);

        if (esc == 0) {
            AcoesDias();
        } else if (esc == 1) {
            ItemDias();
        } else if (esc == 2) {
            break;
        } else {
            printf("Houve algum erro, por favor digite novamente");
        }
    }

}


int determinarDia(int carregado){
    if(carregado == 1) {
        return protagonista.dia_atual;
    } 
    else{
        return 1;
    }

}

void passagemDasSemanas(int dia, char s){
    for (dia <= 7; dia++;){
            if (sair==1) {
                break;
            }
            printf("Voce esta no dia %d/7\n", dia);
            if (dia == 3 || dia == 7) {
                Prova(dia);
            } else {
                dias();                
            }

            protagonista.energia = 10;
            protagonista.saude -= 2;

            fflush(stdin);
            printf("Pronto para o proximo dia? (s ou n)\n");
            scanf(" %c", &s);
            if (s == 'n') {
                sair = 1;
            }

            fflush(stdin);
            printf("Deseja salvar o jogo? (s ou n)\n");
            scanf(" %c", &s);


            if (s == 's') {
                protagonista.dia_atual = dia;
                Salvar();
            }

            if (dia >= 7){
                final = 1;
                break;
            }
    }
}

// getters e setters do "Java"
// void inserindoInfoDoProtagonista(char info[]){


// }


void main(){
    char s;
    LerInicio();

    while(sair == 0 || final == 0) {
        int carregado = tela();
        int dia = determinarDia(carregado);
        passagemDasSemanas(dia, s);
    }

    if (final == 1) {
        Final();
        printf("Obrigado por jogar!");
        LerCreditos();
    }

    printf("BYE BYE");

}


