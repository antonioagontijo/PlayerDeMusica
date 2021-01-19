#include <stdlib.h>
#include <stdio.h>
#include <string.h>//necess�rio para o strcpy
#include <locale.h>//biblioteca que permite o uso de acentua��o
#include <time.h>//biblioteca de tempo, usada para gerar n�meros aleat�rios
#define TAMANHO 100 //definir tamanho dos vetores
#define LIMITE 1000 //definir tamanho dos c�digos que ser�o gerados para as m�sicas
struct dadoDaMusica {//cria��o de struct
	char nomeMusica[TAMANHO];
	char nomeAlbum[TAMANHO];
	char nomeArtista[TAMANHO];
	char genero[TAMANHO];
	int ano, code;
	float duracao;
	dadoDaMusica* prox;
} *Head;
//escopo das variaveis
void inserirMusica(char nome[TAMANHO], char album[TAMANHO], char artista[TAMANHO], char genero[TAMANHO], int ano, float duracao, int code);
int menu();
void Listar();
int removerMusica(int nome);
int geraCodigo(int guardaCodigo[], int limite, int cont);
bool existe(int valores[], int tam, int valor);
dadoDaMusica* busca(int ID);
int main() {
	setlocale(LC_ALL, "portuguese");//c�digo para habilitar a acentua��o.
	float aux_duracao;//vari�veis com 'aux' s�o usadas para receber os dados informados pelo usu�rio, para posteriormente serem armazenadas na lista
	int op, aux_ano, c, excluir, aux_code, cont = 0, guardaCodigo[1000], conf;
	//'op' usado pelo menu, 'c' usado para limpeza do buffer do teclado,
	//'excluir' usado para armazenar o valor que o usu�rio informar, e que ser� usa pela fun��o de remover.
	//a vari�vel 'cont' e o vetor 'guardaCodigo' s�o usadas pela fun��o de criar n�meros aleat�rios.
	//E a vari�vel 'conf' � usado pelo while de confirma��o de exclus�o da musica
	char aux_nomeMusica[TAMANHO], aux_nomeAlbum[TAMANHO], aux_nomeArtista[TAMANHO], aux_genero[TAMANHO];
	dadoDaMusica* ElementoBusca;
	ElementoBusca = (dadoDaMusica*)malloc(sizeof(dadoDaMusica));
	while (1) {
		op = menu();
		switch (op)
		{
		case 1://INSER��O DE DADOS
			printf("Digite o nome da m�sica:\n");
			gets_s(aux_nomeMusica);
			system("Cls");
			printf("Digite o nome do �lbum:\n");
			gets_s(aux_nomeAlbum);
			system("Cls");
			printf("Digite o nome do artista:\n");
			gets_s(aux_nomeArtista);
			system("Cls");
			printf("Informe o g�nero:\n");
			gets_s(aux_genero);
			system("Cls");
			printf("Digite o ano:\n");
			scanf_s("%d", &aux_ano);
			system("Cls");
			printf("Digite a dura��o da m�sica:\n");
			scanf_s("%f", &aux_duracao);
			while ((c = getchar()) != '\n' && c != EOF) {} //limpeza do buffer do teclado.
			aux_code = geraCodigo(guardaCodigo, LIMITE, cont);//chamada da fun��o que gera c�digos de identifica��o para cada m�sica
			inserirMusica(aux_nomeMusica, aux_nomeAlbum, aux_nomeArtista, aux_genero, aux_ano, aux_duracao, aux_code);// Chamada da fun��o que salva os dados na lista
			break;
		case 2://LISTAR TODAS AS MUSICAS
			Listar();
			break;
		case 3://BUSCAR MUSICA
			printf("Digite o ID da m�sica: ");
			scanf_s("%d", &aux_code);
			while ((c = getchar()) != '\n' && c != EOF) {}
			ElementoBusca = busca(aux_code);//chamada da fun��o de busca, ela retorna o valor que foi buscado, e os dados s�o exibidos na tela para o usu�rio nas linha abaixo
			if (ElementoBusca != 0)
			{
				system("Cls");
				printf("--------M�SICA--------\n");
				printf("%s\n", ElementoBusca->nomeMusica);
				printf("�lbum: %s\n", ElementoBusca->nomeAlbum);
				printf("Artista: %s\n", ElementoBusca->nomeArtista);
				printf("G�nero: %s\n", ElementoBusca->genero);
				printf("Ano: %d\n", ElementoBusca->ano);
				printf("Dura��o: %0.2fmin\n", ElementoBusca->duracao);
				printf("ID: %d\n", ElementoBusca->code);
				printf("----------------------\n");
			}
			else
			{
				system("Cls");//caso a musica n�o seja encontrada
				printf("---------OPS!---------\n");
				printf("M�sica n�o encontrada.\n");
				printf("----------------------\n");
			}
			system("pause");
			break;
		case 4://REMOVE MUSICA
			int res;
			/*No parte de remo��o, primeiramente reutilizei a fun��o de busca para exibir na tela o nome da m�sica, e uma pergunta de confirma��o se o
			usu�rio realmente deseja remover a m�sica. Se sim, chama a fun��o de remo��o, se n�o, retorna para tela inicial.*/
			printf("--------REMOVER-------\n");
			printf("Digite o ID da m�sica:");
			scanf_s("%d", &excluir);
			while ((c = getchar()) != '\n' && c != EOF) {}
			ElementoBusca = busca(excluir);
			if (ElementoBusca != 0)
			{
				conf = 0;
				while (conf < 1 || conf > 2)//While para garantir que o usu�rio digite umas das op��es pedidas
				{
					system("Cls");
					printf("--------M�SICA--------\n");
					printf("\"%s\"\n", ElementoBusca->nomeMusica);
					printf("Deseja mesmo excluir?\n");
					printf("[1]SIM\n");
					printf("[2]N�O\n");
					printf("----------------------\n");
					scanf_s("%d", &conf);
					while ((c = getchar()) != '\n' && c != EOF) {}
				}
				if (conf == 1)
				{
					res = removerMusica(excluir);
					//mensagem de confirma��o de remo��o
					system("Cls");
					printf("----SUCESSO!----\n");
					printf("M�sica removida.\n");
					printf("----------------\n");
				}
				else
					break;
			}
			else
			{//caso a m�sica n�o seja encontrada
				system("Cls");
				printf("---------OPS!---------\n");
				printf("M�sica n�o encontrada.\n");
				printf("----------------------\n");
			}
			system("pause");
			break;
		case 5://SAIR
			return 0;//encerra o programa
		default:
			//mensagem que pede para o usu�rio digitar apenas uma das op��es informadas
			system("Cls");
			printf("---------------INV�LIDO--------------\nFavor digitar um dos valor informados\n-------------------------------------\n");
			system("pause");
		}
	}
	system("pause");
	return 0;
}//FIM DA MAIN
int menu() //FUN��O MENU
{
	int op, c;
	system("Cls");
	printf("---------------MENU---------------\n");
	printf("[1]Adicionar uma m�sica � playlist\n");
	printf("[2]Exibir playlist\n");
	printf("[3]Buscar m�sica\n");
	printf("[4]Remover m�sica\n");
	printf("[5]Sair\n");
	printf("Digite sua escolha: ");
	printf("\n----------------------------------\n");
	scanf_s("%d", &op);
	while ((c = getchar()) != '\n' && c != EOF) {}
	system("Cls");
	return op;
}
//FUN��O DE INSER��O
void inserirMusica(char nome[TAMANHO], char album[TAMANHO], char artista[TAMANHO], char genero[TAMANHO], int ano, float duracao, int code)
//Recebe como par�metro todos os dados das m�sicas informados pelo usu�rio, e salvos temporariamente nas vari�veis com 'aux'
{
	dadoDaMusica* NovoElemento;
	NovoElemento = (struct dadoDaMusica*)malloc(sizeof(struct dadoDaMusica));
	dadoDaMusica* ElementoVarredura;
	ElementoVarredura = (struct dadoDaMusica*)malloc(sizeof(struct dadoDaMusica));
	//aqui os dados que foram passados pelo usu�rio, s�o armazenados na struct
	NovoElemento->ano = ano;
	NovoElemento->duracao = duracao;
	NovoElemento->code = code;
	strcpy_s(NovoElemento->nomeMusica, nome);
	strcpy_s(NovoElemento->nomeAlbum, album);
	strcpy_s(NovoElemento->nomeArtista, artista);
	strcpy_s(NovoElemento->genero, genero);
	if (Head == NULL)
	{
		Head = NovoElemento;
		Head->prox = NULL;
	}
	else
	{
		ElementoVarredura = Head;
		while (ElementoVarredura->prox != NULL)
			ElementoVarredura = ElementoVarredura->prox;
		ElementoVarredura->prox = NovoElemento;
		NovoElemento->prox = NULL;
	}
}
/*As fun��es de remo��es e de busca utilizam um c�digo de identifica��o para fazer as buscas. Esse c�digo � �nico e � gerado e
atrelado em cada m�sica automaticamente, toda vez que o usu�rio insere uma m�sica nova*/
//FUN��O DE REMO��O
int removerMusica(int ID)
//Recebe como par�metro o valor salvo na vari�vel excluir,
{
	dadoDaMusica* ElementoVarredura;
	ElementoVarredura = (struct dadoDaMusica*)malloc(sizeof(struct dadoDaMusica));
	dadoDaMusica* Anterior;
	Anterior = (struct dadoDaMusica*)malloc(sizeof(struct dadoDaMusica));
	ElementoVarredura = Head;
	while (ElementoVarredura != NULL) {
		if (ElementoVarredura->code == ID) {
			if (ElementoVarredura == Head) {
				Head = ElementoVarredura->prox;
				free(ElementoVarredura);
				return 1;
			}
			else {
				Anterior->prox = ElementoVarredura->prox;
				free(ElementoVarredura);
				return 1;
			}
		}
		else {
			Anterior = ElementoVarredura;
			ElementoVarredura = ElementoVarredura->prox;
		}
	}
	return 0;
}
void Listar()//FUN��O DE LISTAGEM
{
	dadoDaMusica* ElementoVarredura;
	ElementoVarredura = (struct dadoDaMusica*)malloc(sizeof(struct dadoDaMusica));
	ElementoVarredura = Head;
	if (ElementoVarredura == NULL) {
		//caso o usu�rio tente listar as m�sicas, mas a lista estiver vazia, essa mensagem ser� exibida.
		system("Cls");
		printf("--------------LISTA VAZIA!--------------\n");
		printf("Ainda n�o foi adicionado nenhuma m�sica.\n");
		printf("----------------------------------------\n");
		system("pause");
		return;
	}
	printf("---------------Playlist---------------\n");
	printf("(Para ver as informa��es completas de \n");
	printf("cada m�sica, utilize a op��o de BUSCA)\n");
	printf("--------------------------------------\n");
	while (ElementoVarredura != NULL) {
		printf("\"%s\" - %s\n", ElementoVarredura->nomeMusica, ElementoVarredura->nomeArtista);
		printf("ID: %d\n\n", ElementoVarredura->code);
		ElementoVarredura = ElementoVarredura->prox;
	}
	printf("--------------------------------------\n");
	system("pause");
	return;
}
//FUN��O QUE GERA O C�DIGOS ALETAT�RIOS
int geraCodigo(int numeros[], int limite, int cont)
//Recebe como par�metro o vetor 'gardaCodigo', para guarda os c�digo que foram gerados pela fun��o, recebe tamb�m um valor limite dos n�meros que podem ser gerados,
//e um contador para acessar os espa�os do vetor
{
	srand(time(NULL));
	int v;//armazena temporariamente o n�mero gerado
	v = rand() % limite;// gerador valores aleat�ria com base no rel�gio do sistema
	while (existe(numeros, cont, v)) {
		v = rand() % limite;
	}
	numeros[cont] = v;
	return numeros[cont];
	cont++;
}
//FUN��O DE CHECAGEM
bool existe(int valores[], int tam, int valor)
//Recebe como par�metro, o vetor 'guardaCodigo', o valor salvo na vari�vel contador, e o valor salvo na vari�vel 'v' que cont�m o n�mero gerado em 'geraCodigo()'
//Essa fun��o checa se o c�digo que foi gerado aleatoriamente j� existe ou n�o,
//e assim garantir que cada m�sica tem um n�mero de identifica��o �nico.
{
	for (int i = 0; i < tam; i++)
	{
		if (valores[i] == valor)
			return true;
	}return false;
}
//FUN��O DE BUSCA
dadoDaMusica* busca(int ID)
//Recebe como par�metro o valor salvo na vari�vel aux_code, que s�o os c�digos de identifica��o de cada musica
{
	dadoDaMusica* ElementoVarredura;
	ElementoVarredura = (struct dadoDaMusica*)malloc(sizeof(struct dadoDaMusica));
	ElementoVarredura = Head;
	while (ElementoVarredura != NULL) {
		if (ElementoVarredura->code == ID)
			return ElementoVarredura;
		else
			ElementoVarredura = ElementoVarredura->prox;
	}
	return 0;
}