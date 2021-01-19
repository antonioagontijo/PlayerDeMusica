#include <stdlib.h>
#include <stdio.h>
#include <string.h>//necessário para o strcpy
#include <locale.h>//biblioteca que permite o uso de acentuação
#include <time.h>//biblioteca de tempo, usada para gerar números aleatórios
#define TAMANHO 100 //definir tamanho dos vetores
#define LIMITE 1000 //definir tamanho dos códigos que serão gerados para as músicas
struct dadoDaMusica {//criação de struct
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
	setlocale(LC_ALL, "portuguese");//código para habilitar a acentuação.
	float aux_duracao;//variáveis com 'aux' são usadas para receber os dados informados pelo usuário, para posteriormente serem armazenadas na lista
	int op, aux_ano, c, excluir, aux_code, cont = 0, guardaCodigo[1000], conf;
	//'op' usado pelo menu, 'c' usado para limpeza do buffer do teclado,
	//'excluir' usado para armazenar o valor que o usuário informar, e que será usa pela função de remover.
	//a variável 'cont' e o vetor 'guardaCodigo' são usadas pela função de criar números aleatórios.
	//E a variável 'conf' é usado pelo while de confirmação de exclusão da musica
	char aux_nomeMusica[TAMANHO], aux_nomeAlbum[TAMANHO], aux_nomeArtista[TAMANHO], aux_genero[TAMANHO];
	dadoDaMusica* ElementoBusca;
	ElementoBusca = (dadoDaMusica*)malloc(sizeof(dadoDaMusica));
	while (1) {
		op = menu();
		switch (op)
		{
		case 1://INSERÇÃO DE DADOS
			printf("Digite o nome da música:\n");
			gets_s(aux_nomeMusica);
			system("Cls");
			printf("Digite o nome do álbum:\n");
			gets_s(aux_nomeAlbum);
			system("Cls");
			printf("Digite o nome do artista:\n");
			gets_s(aux_nomeArtista);
			system("Cls");
			printf("Informe o gênero:\n");
			gets_s(aux_genero);
			system("Cls");
			printf("Digite o ano:\n");
			scanf_s("%d", &aux_ano);
			system("Cls");
			printf("Digite a duração da música:\n");
			scanf_s("%f", &aux_duracao);
			while ((c = getchar()) != '\n' && c != EOF) {} //limpeza do buffer do teclado.
			aux_code = geraCodigo(guardaCodigo, LIMITE, cont);//chamada da função que gera códigos de identificação para cada música
			inserirMusica(aux_nomeMusica, aux_nomeAlbum, aux_nomeArtista, aux_genero, aux_ano, aux_duracao, aux_code);// Chamada da função que salva os dados na lista
			break;
		case 2://LISTAR TODAS AS MUSICAS
			Listar();
			break;
		case 3://BUSCAR MUSICA
			printf("Digite o ID da música: ");
			scanf_s("%d", &aux_code);
			while ((c = getchar()) != '\n' && c != EOF) {}
			ElementoBusca = busca(aux_code);//chamada da função de busca, ela retorna o valor que foi buscado, e os dados são exibidos na tela para o usuário nas linha abaixo
			if (ElementoBusca != 0)
			{
				system("Cls");
				printf("--------MÚSICA--------\n");
				printf("%s\n", ElementoBusca->nomeMusica);
				printf("Álbum: %s\n", ElementoBusca->nomeAlbum);
				printf("Artista: %s\n", ElementoBusca->nomeArtista);
				printf("Gênero: %s\n", ElementoBusca->genero);
				printf("Ano: %d\n", ElementoBusca->ano);
				printf("Duração: %0.2fmin\n", ElementoBusca->duracao);
				printf("ID: %d\n", ElementoBusca->code);
				printf("----------------------\n");
			}
			else
			{
				system("Cls");//caso a musica não seja encontrada
				printf("---------OPS!---------\n");
				printf("Música não encontrada.\n");
				printf("----------------------\n");
			}
			system("pause");
			break;
		case 4://REMOVE MUSICA
			int res;
			/*No parte de remoção, primeiramente reutilizei a função de busca para exibir na tela o nome da música, e uma pergunta de confirmação se o
			usuário realmente deseja remover a música. Se sim, chama a função de remoção, se não, retorna para tela inicial.*/
			printf("--------REMOVER-------\n");
			printf("Digite o ID da música:");
			scanf_s("%d", &excluir);
			while ((c = getchar()) != '\n' && c != EOF) {}
			ElementoBusca = busca(excluir);
			if (ElementoBusca != 0)
			{
				conf = 0;
				while (conf < 1 || conf > 2)//While para garantir que o usuário digite umas das opções pedidas
				{
					system("Cls");
					printf("--------MÚSICA--------\n");
					printf("\"%s\"\n", ElementoBusca->nomeMusica);
					printf("Deseja mesmo excluir?\n");
					printf("[1]SIM\n");
					printf("[2]NÂO\n");
					printf("----------------------\n");
					scanf_s("%d", &conf);
					while ((c = getchar()) != '\n' && c != EOF) {}
				}
				if (conf == 1)
				{
					res = removerMusica(excluir);
					//mensagem de confirmação de remoção
					system("Cls");
					printf("----SUCESSO!----\n");
					printf("Música removida.\n");
					printf("----------------\n");
				}
				else
					break;
			}
			else
			{//caso a música não seja encontrada
				system("Cls");
				printf("---------OPS!---------\n");
				printf("Música não encontrada.\n");
				printf("----------------------\n");
			}
			system("pause");
			break;
		case 5://SAIR
			return 0;//encerra o programa
		default:
			//mensagem que pede para o usuário digitar apenas uma das opções informadas
			system("Cls");
			printf("---------------INVÁLIDO--------------\nFavor digitar um dos valor informados\n-------------------------------------\n");
			system("pause");
		}
	}
	system("pause");
	return 0;
}//FIM DA MAIN
int menu() //FUNÇÃO MENU
{
	int op, c;
	system("Cls");
	printf("---------------MENU---------------\n");
	printf("[1]Adicionar uma música à playlist\n");
	printf("[2]Exibir playlist\n");
	printf("[3]Buscar música\n");
	printf("[4]Remover música\n");
	printf("[5]Sair\n");
	printf("Digite sua escolha: ");
	printf("\n----------------------------------\n");
	scanf_s("%d", &op);
	while ((c = getchar()) != '\n' && c != EOF) {}
	system("Cls");
	return op;
}
//FUNÇÃO DE INSERÇÃO
void inserirMusica(char nome[TAMANHO], char album[TAMANHO], char artista[TAMANHO], char genero[TAMANHO], int ano, float duracao, int code)
//Recebe como parâmetro todos os dados das músicas informados pelo usuário, e salvos temporariamente nas variáveis com 'aux'
{
	dadoDaMusica* NovoElemento;
	NovoElemento = (struct dadoDaMusica*)malloc(sizeof(struct dadoDaMusica));
	dadoDaMusica* ElementoVarredura;
	ElementoVarredura = (struct dadoDaMusica*)malloc(sizeof(struct dadoDaMusica));
	//aqui os dados que foram passados pelo usuário, são armazenados na struct
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
/*As funções de remoções e de busca utilizam um código de identificação para fazer as buscas. Esse código é único e é gerado e
atrelado em cada música automaticamente, toda vez que o usuário insere uma música nova*/
//FUNÇÃO DE REMOÇÃO
int removerMusica(int ID)
//Recebe como parâmetro o valor salvo na variável excluir,
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
void Listar()//FUNÇÃO DE LISTAGEM
{
	dadoDaMusica* ElementoVarredura;
	ElementoVarredura = (struct dadoDaMusica*)malloc(sizeof(struct dadoDaMusica));
	ElementoVarredura = Head;
	if (ElementoVarredura == NULL) {
		//caso o usuário tente listar as músicas, mas a lista estiver vazia, essa mensagem será exibida.
		system("Cls");
		printf("--------------LISTA VAZIA!--------------\n");
		printf("Ainda não foi adicionado nenhuma música.\n");
		printf("----------------------------------------\n");
		system("pause");
		return;
	}
	printf("---------------Playlist---------------\n");
	printf("(Para ver as informações completas de \n");
	printf("cada música, utilize a opção de BUSCA)\n");
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
//FUNÇÃO QUE GERA O CÓDIGOS ALETATÓRIOS
int geraCodigo(int numeros[], int limite, int cont)
//Recebe como parâmetro o vetor 'gardaCodigo', para guarda os código que foram gerados pela função, recebe também um valor limite dos números que podem ser gerados,
//e um contador para acessar os espaços do vetor
{
	srand(time(NULL));
	int v;//armazena temporariamente o número gerado
	v = rand() % limite;// gerador valores aleatória com base no relógio do sistema
	while (existe(numeros, cont, v)) {
		v = rand() % limite;
	}
	numeros[cont] = v;
	return numeros[cont];
	cont++;
}
//FUNÇÃO DE CHECAGEM
bool existe(int valores[], int tam, int valor)
//Recebe como parâmetro, o vetor 'guardaCodigo', o valor salvo na variável contador, e o valor salvo na variável 'v' que contém o número gerado em 'geraCodigo()'
//Essa função checa se o código que foi gerado aleatoriamente já existe ou não,
//e assim garantir que cada música tem um número de identificação único.
{
	for (int i = 0; i < tam; i++)
	{
		if (valores[i] == valor)
			return true;
	}return false;
}
//FUNÇÃO DE BUSCA
dadoDaMusica* busca(int ID)
//Recebe como parâmetro o valor salvo na variável aux_code, que são os códigos de identificação de cada musica
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