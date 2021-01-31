#include <stdio.h>
#include <stdlib.h> 
#include <string.h>


#define NR_MAX_PECAS  13
#define NR_PESSOA  55
#define NR_CARROS  11




typedef struct peca {

	int quantidade;
	char nome [100];
	float preco;
	int id;
	int lucro;
}produto;

typedef struct pessoa {

	char nome [100];
	char apelido [100];
	int idade;
	int contribuinte;
}cliente;

typedef struct viatura {
	
	char marca[50];
	char modelo[50];
	int ano;

}carros;

typedef struct espera{

    int contribuinte;
    int avaria;
    char modelo_carro[50];
    char marca_carro[50];
    int reparado;
}lista_espera;

typedef struct historico{

	char avaria;
	char marca_carro[50];
	char modelo_carro[50];
	char nome_cliente[50];
	char apelido_cliente[50];
	int contribuinte_cliente;
	int idade_cliente;

}historico;


void adiciona_historico(int contribuinte, historico historicos[], cliente b[], int *numtransacoes, carros c[], char avaria, int clienteatual, int poscarro){

            historicos[*numtransacoes].contribuinte_cliente = contribuinte;
			strcpy((historicos[*numtransacoes].nome_cliente),b[clienteatual].nome);
			strcpy((historicos[*numtransacoes].apelido_cliente),b[clienteatual].apelido);
			historicos[*numtransacoes].idade_cliente=b[clienteatual].idade;
			strcpy((historicos[*numtransacoes].modelo_carro),c[poscarro].modelo);
			strcpy((historicos[*numtransacoes].marca_carro),c[poscarro].marca);
			historicos[*numtransacoes].avaria = avaria;
			(*numtransacoes)++;

			// adiciona_historico(contribuinte, historicos, clientes x, numtransacoes, carros x, avaria, clienteatual, poscarro);
			// adiciona_historico(contribuinte, historicos, n, numtransacoes, m, avaria, pos, carro);

}

int	procura_por_id(int idPeca, int nrProd, produto pecas[]){
		int i;

	    for (i = 0; i < nrProd; i++) {
		if (pecas[i].id == idPeca)
		    return i;
	    }
	    return -1;
}


int ler_pecas(char *nomeFicheiro, produto pecas[]){

	int j = 0, pos,quants=0,contaDescartados=0;
	int i,id, resul;
	float preco,lucro;
	char linha[100];
	char nomepeca[100];
	char v_peca[][25]={{"pastilhas"},{"discos"},{"rolamento"},{"disco"},{"prensa"},{"triangulos"},{"topos"},{"amortecedor"},{"radiador"},{"bomba"},{"liquido"},{"elevador"},{"botoes"}};

	FILE *ficheiro = fopen(nomeFicheiro,"r");
	
	produto p;
    if (ficheiro == NULL) {
	printf("O arquivo nao pode ser aberto");
	exit(0);
    }

    while (fgets(linha, 100, ficheiro) != NULL) {

		if(sscanf(linha, "%s %f %d %d", p.nome, &p.preco, &p.id, &p.lucro)==4) {

			for(i=0;i<NR_MAX_PECAS;i++)
				{
					if((strcasecmp(p.nome,v_peca[i])==0) && (p.preco>0) && (p.id>0 && p.id <= NR_MAX_PECAS) && (p.lucro>0) && (p.id=i+1))
					{

						pos = procura_por_id(p.id, j, pecas); 
						
						if (pos != -1) {
								pecas[pos].quantidade++;
								quants++;
							    } 
							    else {
								p.quantidade = 1;
								pecas[j] = p;
								j++;
								quants++;
								if (j > NR_MAX_PECAS)
								    break;
				    			}
					}
				}		

		}
	    contaDescartados++;
	    resul = contaDescartados - quants;
	}

    fclose(ficheiro);
    printf("%d produto(s) lido(s). As linhas lidas corretamente sao %d\n", j,quants);
    printf("%d produto(s) descartado(s) \n", resul);
    return j;
}



void ver_catalogo_pecas(char *opcao ,int nrPecas, produto *pecas) {
    int i, preco, precario;
    float lucro, lucrar, conta;
    char utilizador[9] = "catalogo";

    for (i = 0; i < nrPecas; i++) {

	precario = pecas[i].preco;
	lucrar = pecas[i].lucro;
	lucrar = lucrar/100;
	conta = precario+(precario*lucrar);

    if(strcmp(opcao, utilizador) == 0) {
		if(pecas[i].quantidade>0)

			 printf("%s %0.2fEU\n", pecas[i].nome, conta);
	    }
	else printf("%d %s %0.2fEU %0.2fEU %d\n",pecas[i].quantidade, pecas[i].nome, pecas[i].preco, conta, pecas[i].lucro);
	}
}

void mostra_peca(int pos, produto *p){

	printf("%s %0.2fEU %d\n", p[pos].nome, p[pos].preco, p[pos].lucro);
		
}


void grava_pecas(char *nomeFicheiro, int nrPecas, produto pecas[]) {
    int i = 0, j;
    FILE *ficheiro = fopen(nomeFicheiro, "w");

    if (ficheiro == NULL) {
	printf("O arquivo nao pode ser aberto");
	exit(0);
    }
    for (i = 0; i < nrPecas; i++) {
		for (j = 1; j <= pecas[i].quantidade; j++)
		    fprintf(ficheiro, "%s %0.2f %d %d\n", pecas[i].nome, pecas[i].preco, pecas[i].id, pecas[i].lucro);
	}
    fclose(ficheiro);
}


int ler_cliente(char *nomeFicheiro, cliente pessoa[]){

	int i = 0, j=0,quants=0, resultado=0;
	char linha[500];
	FILE *ficheiro = fopen(nomeFicheiro,"r");
	
	cliente c;
    if (ficheiro == NULL) {
	printf("O arquivo nao pode ser aberto");
	exit(0);
    }

		    
	while (fgets(linha, 500, ficheiro) != NULL) {

        if (sscanf(linha, "%s %s %d %d", c.nome, c.apelido, &c.idade, &c.contribuinte) == 4)
          {
          	resultado = NR_PESSOA;
		  	pessoa[i] = c;

      		printf("%s %s %d %d\n", &pessoa[i].nome, &pessoa[i].apelido, pessoa[i].idade, pessoa[i].contribuinte);
      	} quants++;
      	  i++;
	}
	fclose(ficheiro);
	return quants;
}


void grava_clientes(char *nomeFicheiro, int nrClientes, cliente pessoa[]) {
    int i = 0, j, resul=1;

   	resul = ++nrClientes;

    FILE *ficheiro = fopen(nomeFicheiro, "w");

    if (ficheiro == NULL) {
	printf("O arquivo nao pode ser aberto");
	exit(0);
    }
    for (i = 0; i < resul; i++){
	fprintf(ficheiro, "%s %s %d %d\n", pessoa[i].nome, pessoa[i].apelido, pessoa[i].idade, pessoa[i].contribuinte);
    }

    fclose(ficheiro);
}


int ler_carros(char *nomeFicheiro, carros viatura[]){

	int i = 0, quants=0;
	char linha[100];
	FILE *ficheiro = fopen(nomeFicheiro,"r");
	
	carros x;

    if (ficheiro == NULL) {
	printf("O arquivo nao pode ser aberto");
	exit(0);
    }

   
    while (fgets(linha, 100, ficheiro) != NULL) {	

 
	if(sscanf(linha, "%s %s %d", x.marca, x.modelo, &x.ano)==3) {
		  	viatura[i] = x;
	} quants++;
      	  i++;
}

 fclose(ficheiro);


}

int verifica_carro(carros viatura[]){
	char marca[50];
	char modelo[50];
	int ano, i;

	printf("Qual e a marca do seu carro :\n");
		scanf("%s", marca);
	printf("Qual e a modelo do seu carro :\n");
		scanf("%s", modelo);
	printf("Qual e o ano do seu carro :\n");
		scanf("%d", &ano);

		for(i=0;i<13;i++){
	
			if((strcmp (marca, viatura[i].marca) == 0) && (strcmp(modelo,viatura[i].modelo)== 0) && (ano == viatura[i].ano)){

				return i;
				//vai para a função reparar
			}
		} return -1;
}

int verifica_cliente (int nrClientes, int contribuinte, cliente pessoa[]){
	int j;	

		for(j=0; j<nrClientes; j++){
			if(contribuinte == pessoa[j].contribuinte){
				printf("%s %s seja bemvindo/a a nossa oficina\n", pessoa[j].nome, pessoa[j].apelido);
				return j;
			}
		} return -1;
}

int cria_cliente(int contribuinte, int nrClientes, cliente pessoa[]){
	int i = 0;
	int mal=0;
	char nome [100];
	char apelido [100];
	int j, idade;

	i = nrClientes;
	do {
	printf("indique o seu nome:\n");
	scanf("%s", &nome);

	printf("indique o seu apelido:\n");
	scanf("%s", &apelido);

	printf("indique a sua idade:\n");
	scanf("%d", &idade);

	if(idade<200 && idade>0){

	strncpy (pessoa[i].nome, nome,sizeof(pessoa[i].nome));
	strncpy (pessoa[i].apelido, apelido,sizeof(pessoa[i].apelido));
	pessoa[i].idade = idade;
	pessoa[i].contribuinte = contribuinte;

		printf("%s %s %d %d\n", pessoa[i].nome, pessoa[i].apelido, pessoa[i].idade, pessoa[i].contribuinte);

	mal = 1;
	return i;
	}
	else
		printf("voce e um dinossauro ou voce e parvo\n");
		mal = -1;
	}
	while (mal = -1);
}


int verifica_avaria(int id, int nrPecas, produto pecas[]){
	int pos1;

	pos1 = procura_por_id(id, nrPecas, pecas);
	if(pecas[pos1].quantidade>0){
		return pos1;
	}

	return -1;
}

void repara_carro (int nrPecas, int nrClientes, carros viatura[], cliente pessoa[], produto pecas[]){
	cliente n;
	carros m;
	int contribuinte, carro, pos, id1, id2, id3, pos1, pos2, pos3;
	char ficheiro[15] = "reposicoes.txt";
	char avaria;

	carro = verifica_carro(viatura);
	if(carro!=-1){
		m = viatura[carro];

		printf("Indique o seu contribuinte :\n");
		scanf(" %d", &contribuinte);

		pos = verifica_cliente(nrClientes, contribuinte, pessoa);
		if(pos!=-1)
			n = pessoa[pos];
		else 
			pos = cria_cliente(contribuinte, nrClientes, pessoa);
			n = pessoa[pos];
	}
		else {
			printf("Esse tipo de carro nao e reparavel na nossa oficina \n");
		}

	printf(" 1- Travoes\n 2- Embraiagem\n 3- Suspensao\n 4- Refrigeracao\n 5- Vidro\n");
	printf("Selecione o tipo de avaria:\n");
	scanf(" %c", &avaria);

	switch (avaria) {
		    case '1': 
			id1 = 1;
			id2 = 2;
			pos1 = verifica_avaria(id1, nrPecas, pecas);
			pos2 = verifica_avaria(id2, nrPecas, pecas);
			if(pos1!=-1 && pos2!=-1){
				printf("o seu carro ira ser reparado\n");
				pecas[pos1].quantidade--;
			 	pecas[pos2].quantidade--;
			} 
			else {
				printf("Nao existem pecas suficientes para reparar o seu carro\n");
				printf("O seu carro ira ser colocado em lista de espera ate chegarem as pecas necessarias\n");
				printf("Obrigado\n");
			}
			break;

		    case '2': 
			id1 = 3;
			id2 = 4;
			id3 = 5;
			pos1 = verifica_avaria(id1, nrPecas, pecas);
			pos2 = verifica_avaria(id2, nrPecas, pecas);
			pos3 = verifica_avaria(id3, nrPecas, pecas);
			if(pos1!=-1 && pos2!=-1 && pos3!=-1){
				printf("o seu carro ira ser reparado\n");
				pecas[pos1].quantidade--;
			 	pecas[pos2].quantidade--;
			 	pecas[pos3].quantidade--;
			} 
			else {
				printf("Nao existem pecas suficientes para reparar o seu carro\n");
				printf("O seu carro ira ser colocado em lista de espera ate chegarem as pecas necessarias\n");
				printf("Obrigado\n");
			}
			break;

		    case '3': 
			id1 = 6;
			id2 = 7;
			id3 = 8;
			pos1 = verifica_avaria(id1, nrPecas, pecas);
			pos2 = verifica_avaria(id2, nrPecas, pecas);
			pos3 = verifica_avaria(id3, nrPecas, pecas);
			if(pos1!=-1 && pos2!=-1 && pos3!=-1){
				printf("o seu carro ira ser reparado\n");
				pecas[pos1].quantidade--;
			 	pecas[pos2].quantidade--;
			 	pecas[pos3].quantidade--;
			} 
			else {
				printf("Nao existem pecas suficientes para reparar o seu carro\n");
				printf("O seu carro ira ser colocado em lista de espera ate chegarem as pecas necessarias\n");
				printf("Obrigado\n");
			}
			break;

		    case '4': 
			id1 = 9;
			id2 = 10;
			id3 = 11;
			pos1 = verifica_avaria(id1, nrPecas, pecas);
			pos2 = verifica_avaria(id2, nrPecas, pecas);
			pos3 = verifica_avaria(id3, nrPecas, pecas);
			if(pos1!=-1 && pos2!=-1 && pos3!=-1){
				printf("o seu carro ira ser reparado\n");
				pecas[pos1].quantidade--;
			 	pecas[pos2].quantidade--;
			 	pecas[pos3].quantidade--;
			} 
			else {
				printf("Nao existem pecas suficientes para reparar o seu carro\n");
				printf("O seu carro ira ser colocado em lista de espera ate chegarem as pecas necessarias\n");
				printf("Obrigado\n");
			}
			break;

			case '5': 
			id1 = 12;
			id2 = 13;
			pos1 = verifica_avaria(id1, nrPecas, pecas);
			pos2 = verifica_avaria(id2, nrPecas, pecas);
			if(pos1!=-1 && pos2!=-1){
				printf("o seu carro ira ser reparado\n");
				pecas[pos1].quantidade--;
			 	pecas[pos2].quantidade--;
			} 
			else {
				printf("Nao existem pecas suficientes para reparar o seu carro\n");
				printf("O seu carro ira ser colocado em lista de espera ate chegarem as pecas necessarias\n");
				printf("Obrigado\n");
			}
			break;
			default:
			printf("Avarias de 1 a 5\n");

	}
}

void alterar_lucro(int nrPecas, produto pecas[]) {
    int idProduto, pos;
    int lucro;

    printf("Indique o id da peca cujo lucro deseja alterar\n: ");
    scanf("%d",&idProduto);
    pos = procura_por_id(idProduto,nrPecas,pecas);
    if(pos != -1) {
	printf("A alterar a peca:\n");
	mostra_peca(pos, pecas);

	printf("Indique o novo lucro da peca (%d): ",pecas[pos].lucro);
	scanf("%d",&lucro);
	pecas[pos].lucro = lucro;
	
	printf("Peca alterada com sucesso\n");
    } 
    else
	printf("Nao existem pecas em stock com esse id\n");
}

/*
lê quantos produtos estao no ficheiro reposiçoes e guarda no vector pecasRep, mete no vector temporario p, procura por id cada peça lida do ficheiro reposiçoes
e adiciona a quantidade que encontra no ficheiro desse id á quantidade que existe no vector peças original
*/
int reposicao_stock(int nrPecas, produto pecas[]) {
    int nrpecasRep = 0, i, pos;
    produto pecasRep[NR_MAX_PECAS];
    produto p;

    nrpecasRep = ler_pecas("reposicoes.txt", pecasRep);

    for (i = 0; i < nrpecasRep; i++) {
		p = pecasRep[i];
		pos = procura_por_id(p.id, nrPecas, pecas);
		if (pos != -1) {
		    // produto ja existe. alterar quantidade
		    pecas[pos].quantidade = pecas[pos].quantidade + p.quantidade;
			
		} 
    }

}

 main () {

 	int nrPecas=0, nrClientes=0, nrCarros=0;

	produto pecas [NR_MAX_PECAS];
	cliente pessoa [NR_PESSOA];
	carros viatura [NR_CARROS];

	nrPecas = ler_pecas("pecas.txt", pecas);
	nrClientes = ler_cliente("clientes.txt", pessoa);
	nrCarros = ler_carros("carros.txt", viatura);

	char opcao, opcao2, opcao3, opcaopass[9], passcerta[9] = "password";
	char stock[9] = "verstock";
	char utilizador[9] = "catalogo";

	for (;;) {
		printf("\n***** Sulauto - Cliente *****\n  1 - Ver Catalogo pecas\n  2 - Reparar\n  3 - Historico do cliente\n  A - Administrador\n**************************\nOpcao: ");
		scanf(" %c", &opcao);

		switch (opcao) {
		    case '1': 
		    ver_catalogo_pecas("catalogo", nrPecas, pecas);
		    break;

		    case '2': 
		    repara_carro(nrPecas, nrClientes, viatura, pessoa, pecas);
		    break;

		    case '3': 
		    printf("Nao temos");
		    break;

		    case 'S':
			case 's':
			grava_pecas("pecas.txt", nrPecas, pecas);
			grava_clientes("clientes.txt", nrClientes, pessoa);
			exit(1);
			break;

		    case 'A':
		    case 'a':
			printf("Insira password\n: ");
			scanf("%s", opcaopass);
			if (strcmp(opcaopass, passcerta) == 0) {
			    do {
				printf("****** Sulauto - Admin ******\n  1 - Ver Stock Pecas\n  2 - Alterar Peca\n  3 - Repor Stock\n  4 - Estatisticas\n  S - Sair\n**************************\n");
				scanf(" %c", &opcao2);

					switch (opcao2) {
					    case '1': 
					    ver_catalogo_pecas("verstock", nrPecas, pecas);
					    break;

					    case '2': 
					    alterar_lucro(nrPecas, pecas);
					    break;

					    case '3': 
					    reposicao_stock(nrPecas, pecas);
					    break;

					    case 'S':
						case 's':
						break;
					    default:printf("Inseriu um caracter invalido\n");
						}
				}
				while ((opcao2 != 'S')&&(opcao2 != 's'));
			}	
			else {
			    printf("Password errada\n");
			}
			break;
		    default:
			printf("Inseriu um caracter invalido\n");

		}
	}
}

//gcc -o trabalhofinal trabalhofinal.c
//trabalhofinal