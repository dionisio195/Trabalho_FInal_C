/*-----------------------------------------
Onde não há conselhos fracassam os projetos,
mas com os muitos conselheiros há bom êxito.

Provérbios 15:22
Soli Deo Gloria
-------------------------------------------
Código por Pedro Dionísio de Souza
Matrícula: 211030255, Turma: CC 2021.1
-----------------------------------------*/
//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NOME 256
#define MAX_ARQ 1024
#define MAX_VOOS 2048
#define MAX_RES 2048

//protótipos de funções
	void menu();
	void clear();
	bool valida_data(int data[3]);
	bool valida_hora(int hora[2]);
	bool valida_cpf(int cpf[11]);
	bool valida_sexo(char c);

//structs
typedef struct { //dados do voo
	int  maxPassageiros, horario[2], data[3];
	char numVoo[8], statusVoo[10], status[9];
} flight;
typedef struct { //dados da reserva
	int dataNascimento[3], CPF[11];
	flight voo;
	char nomePassageiro[MAX_NOME], sexo, numReserva[9], statusReserva[10];
} booking;

//main
int main(void) { 
	//Declarações
	unsigned short opcao, i;
	char sexoPalavra[15],gbnum[10],jebnum[8],resComp[10],numComp[8],cabecalho[MAX_NOME],nomeComp[2*MAX_NOME];
	flight voo, vooTemp;
	booking reserva, reservaTemp;
	FILE *galatic, *galatic_b, *galatic_temp;
	
	//Instruções
	printf("----------- BEM-VINDO(A) ------------\n-------------------------------------\n---- INTERFACE DA GALACTIC BIRDS ----\n-------------------------------------\nDigite qualquer caracter para continuar\n");
	scanf("%*c");//pausa no sistema

	do {
		do{
			clear();
			menu();
			scanf("%hu", &opcao); //escolha da opção do usuário (1 a 9)
		} while(opcao>9 || opcao<1);

		switch (opcao) {
			case 1: //cadastrar voo
				clear();
				galatic = fopen("galatic_voos_arq.csv","a+t");

				if (galatic==NULL){
					printf("Não foi possível abrir o arquivo :(\n\nReinicie o programa para tentar novamente\n");
					exit(0);	
				}

				printf("--------- Cadastro de Voo ---------\n\nDigite o numero do voo a ser cadastrado:\nJEB-");
				scanf("%s", voo.numVoo); //receber o numero do voo
				printf("\n");

				do{
					fscanf(galatic, "%[^,],%i,%i/%i/%i,%i:%i,%[^,],\n", vooTemp.numVoo, &vooTemp.maxPassageiros, &vooTemp.data[0],&vooTemp.data[1],&vooTemp.data[2], &vooTemp.horario[0],&vooTemp.horario[1], vooTemp.status ); //leitura do numero do voo do arquivo

					if(strcmp(vooTemp.numVoo,voo.numVoo)==0){
						printf("--------- Voo já cadastrado ---------\n\n");
						printf("-------------------------------------\nDigite qualquer caracter para continuar:");
						scanf("%*c");
						break;
					}
				}while(!feof(galatic));

				//colocar no arquivo
				if (strlen(voo.numVoo)!=4){//validando o numero do voo
					do{
						clear();
						printf("Número de voo inválido.\nPor favor, digite-o novamente.\nJEB-");
						scanf("%s\n", voo.numVoo);
						printf("\n");
					}while(strlen(voo.numVoo) != 4);
				}
				fprintf(galatic, "JEB-%s,", voo.numVoo);//colocar no arquivo

				printf("Digite o número máximo de passageiros:\n");
				scanf("%d", &voo.maxPassageiros);	printf("\n"); //receber o numero máximo de passageiros
				
				fprintf(galatic, "%d,", voo.maxPassageiros);//colocar no arquivo

				printf("Digite a data do voo no formato dd/mm/aaaa:\n[Dê um enter antes de cada barra /]\n");
				scanf("%d", &voo.data[0]); printf("/");
				scanf("%d", &voo.data[1]); printf("/");
				scanf("%d", &voo.data[2]); printf("\n");//receber a data

				if (voo.data[2]>=2030) { //validando a data do voo
					if(valida_data(voo.data)==false){
						do{
							clear();
							printf("Data inválida!\nPor favor, digite-a novamente (dd/mm/aaaa):\n[Dê um enter antes de cada barra /]\n");
							scanf("%d", &voo.data[0]); printf("/");
							scanf("%d", &voo.data[1]); printf("/");
							scanf("%d", &voo.data[2]);
							printf("\n");
						}while(valida_data(voo.data)==false);
					} 
				} else {
					do{
							clear();
							printf("Data inválida!\nPor favor, digite-a novamente (dd/mm/aaaa):\n[Dê um enter antes de cada barra /]\n");
							scanf("%d", &voo.data[0]); printf("/");
							scanf("%d", &voo.data[1]); printf("/");
							scanf("%d", &voo.data[2]);
							printf("\n");
						}while(valida_data(voo.data)==false);
				}
				fprintf(galatic, "%d/%d/%d,", voo.data[0], voo.data[1], voo.data[2]);//colocar no arquivo

				printf("Digite o horário do voo:\n[Dê um enter antes dos dois pontos :]\n");
				scanf("%d", &voo.horario[0]); printf(":");
				scanf("%d", &voo.horario[1]); printf("\n"); //receber o horario do voo

				if(valida_hora(voo.horario)==false){ //validando o horario do voo
					do{
						clear();
						printf("Horário inválido!\nPor favor, digite-o novamente (hh:mm):\n");
						scanf("%d[^:]", &voo.horario[0]);
						scanf("%d", &voo.horario[1]); printf("\n");
					}while(valida_hora(voo.horario)==false);
				}
				fprintf(galatic, "%d:%d,", voo.horario[0], voo.horario[1]);//colocar no arquivo

				strcpy(voo.statusVoo, "ativo");
				fprintf(galatic, "%s,\n", voo.statusVoo);//status do voo é dito ativo até que ele seja cancelado ou excluido cancelado ou excluido

				printf("----- Voo cadastrado com sucesso -----\n\n");
				fclose(galatic);

				setbuf(stdin, NULL);
				printf("Digite qualquer caracter para continuar\n");
				scanf("%*c");

				break;
			case 2: //cadastrar reserva
				clear();
				galatic_b = fopen("galatic_reservas_arq.csv", "a+t");//abrir o arquivo

				if (galatic_b==NULL){
					printf("--- E R R O ---\nNão foi possível abrir o arquivo :(\nReinicie o programa para tentar novamente\n");
					exit(0);	
				}

				printf("------- Cadastro de Reserva -------\n\n");
				printf("Digite o numero da reserva a ser cadastrada:\nGB-");
				scanf("%s", reserva.numReserva); printf("\n");

				if(strlen(reserva.numReserva)!=6){//validação do numero da reserva
					do{
						clear();
						printf("Número de Reserva inválido.\nPor favor, digite-o novamente:\nGB-");
						scanf("%s", reserva.numReserva); printf("\n");
					}while(strlen(reserva.numReserva)!=6);
				} 
				fprintf(galatic_b, "GB-%s,", reserva.numReserva);// colcoar no arquivo

				printf("Digite o número do seu voo:\nJEB-");
				scanf("%s", reserva.voo.numVoo); printf("\n");

				do{ //verificação: caso o voo não exista, não fazer a reserva
					fscanf(galatic_b, "%[^,],%[^,],%[^,],%i.%i.%i-%i,%[^,],%i/%i/%i,%[^,],\n", gbnum,jebnum, reservaTemp.nomePassageiro, &reservaTemp.CPF[0],&reservaTemp.CPF[1],&reservaTemp.CPF[2],&reservaTemp.CPF[3], sexoPalavra,&reservaTemp.dataNascimento[0],&reservaTemp.dataNascimento[1],&reservaTemp.dataNascimento[2], reservaTemp.statusReserva); //leitura da struct inteira no arquivo

					if(strcmp(jebnum,reserva.voo.numVoo)==0){
						printf("---------- Voo inexistente ----------\n");
						printf("Cadastre tal voo antes de fazer reservas nele\n\n");
						printf("-------------------------------------\nDigite qualquer caracter para continuar:");
						scanf("%*c");
						break;
					}
				}while(!feof(galatic_b));

				if (strlen(reserva.voo.numVoo)!=4){ //validação do numero do voo
					do{
						clear();
						printf("Número de voo inválido.\nPor favor, digite-o novamente.\nJEB-");
						scanf("%s", reserva.voo.numVoo);
						printf("\n");
					}while(strlen(reserva.voo.numVoo) != 4);
				}

				//verificação da existência do voo
				galatic=fopen("galatic_voos_arq.csv", "rt");
				if (galatic==NULL){
					printf("Houve problemas ao abrir o arquivo :(\n\nReinicie o programa para tentar novamente\n");
					exit(0);
				}

				fgets(cabecalho,MAX_NOME,galatic);//pular o cabeçalho na leitura

				do {
					fscanf(galatic, "%[^,],%i,%i/%i/%i,%i:%i,%[^,],\n", vooTemp.numVoo, &vooTemp.maxPassageiros, &vooTemp.data[0],&vooTemp.data[1],&vooTemp.data[2], &vooTemp.horario[0],&vooTemp.horario[1], vooTemp.status ); //leitura do numero do voo do arquivo e passagem para o inicio do próximo struct pela leitura completa desse
					
					if (strcmp(vooTemp.numVoo, reserva.voo.numVoo)==0){ //verificar se o voo já está cadastrado
						break;
					} else if (strcmp(vooTemp.numVoo, reserva.voo.numVoo)==1) {
						printf("Voo não cadastrado.\nGentileza cadastrá-lo antes.");
						exit(0);
					}
				} while (!feof(galatic));
				fclose(galatic);

				fprintf(galatic_b, "JEB-%s,", reserva.voo.numVoo);//colocar no arquivo

				printf("Digite o nome completo do(a) passageiro(a):\n");
				fflush(stdin);
				fgets(reserva.nomePassageiro, MAX_NOME, stdin); //receber o nome do passageiro
				scanf("%[^\n]", reserva.nomePassageiro); printf("\n");
				fprintf(galatic_b, "%s,", reserva.nomePassageiro);//colocar no arquivo

				do{ //verifivação: caso tal pessoa ja tiver reserva ativa feita em seu nome, não repeti-la
					fscanf(galatic_b, "%[^,],%[^,],%[^,],%i.%i.%i-%i,%[^,],%i/%i/%i,%[^,],\n", gbnum,jebnum, reservaTemp.nomePassageiro, &reservaTemp.CPF[0],&reservaTemp.CPF[1],&reservaTemp.CPF[2],&reservaTemp.CPF[3], sexoPalavra,&reservaTemp.dataNascimento[0],&reservaTemp.dataNascimento[1],&reservaTemp.dataNascimento[2], reservaTemp.statusReserva); //leitura da struct inteira no arquivo

					if (strcmp(reservaTemp.nomePassageiro,reserva.nomePassageiro)==0 && strcmp(gbnum,reserva.numReserva)==0) { //verificação efetiva
						printf("--- Esse(a) passageiro(a) já efetuou esta reserva ---\n\n");
						printf("-----------------------------------------------------\nDigite qualquer caracter para continuar");
						scanf("%*c");
					}
				}while(!feof(galatic_b));

				printf("Digite o CPF do(a) passageiro(a) no formato XXX.XXX.XXX-XX:\n[Dê um enter antes de cada ponto ou hífem, e dê um espaço entre os números]\n");

				scanf("%d%d%d", &reserva.CPF[0], &reserva.CPF[1], &reserva.CPF[2]); printf(".");
				scanf("%d%d%d", &reserva.CPF[3], &reserva.CPF[4], &reserva.CPF[5]); printf(".");
				scanf("%d%d%d", &reserva.CPF[6], &reserva.CPF[7], &reserva.CPF[8]); printf("-");
				scanf("%d%d", &reserva.CPF[9], &reserva.CPF[10]); printf("\n"); //receber o cpf do passageiro

				if (valida_cpf(reserva.CPF)==false){ //validar o cpf
					do{
						clear();
						printf("CPF inválido! por favor, digite-o novamente [XXX.XXX.XXX-XX]:\n[Dê um enter antes de cada ponto e hífem, e dê um espaço entre os números]\n");
						scanf("%d%d%d", &reserva.CPF[0], &reserva.CPF[1], &reserva.CPF[2]); printf(".");
						scanf("%d%d%d", &reserva.CPF[3], &reserva.CPF[4], &reserva.CPF[5]); printf(".");
						scanf("%d%d%d", &reserva.CPF[6], &reserva.CPF[7], &reserva.CPF[8]); printf("-");
						scanf("%d%d", &reserva.CPF[9], &reserva.CPF[10]);
					}while(valida_cpf(reserva.CPF)==false);
				}	
				fprintf(galatic_b, "%d%d%d.%d%d%d.%d%d%d-%d%d,", reserva.CPF[0],reserva.CPF[1],reserva.CPF[2], reserva.CPF[3], reserva.CPF[4], reserva.CPF[5], reserva.CPF[6], reserva.CPF[7], reserva.CPF[8], reserva.CPF[9], reserva.CPF[10]);//colocar no arquivo 

				printf("Digite o sexo do(a) passageiro(a):\n- M para Masculino\n- F para Feminino\n- N para Não declarar\n");
				fflush(stdin);
				fgetc(stdin); //receber o sexo do passageiro
				scanf("%c", &reserva.sexo); printf("\n");

				if (valida_sexo(reserva.sexo)==false){//validar sexo entre as opções M, F e N
					do{
						clear();
						printf("Sexo inválido!\nPor favor, digite-o novamente:\n[M para Masculino ou F para Feminino]\n");
						scanf("%c", &reserva.sexo); printf("\n");
					}while(valida_sexo(reserva.sexo)==false);
				}

				if (reserva.sexo=='M'||reserva.sexo=='m'){//colocar no arquivo o sexo por extenso
					fprintf(galatic_b, "Masculino,");
				} else if (reserva.sexo=='F'||reserva.sexo=='n'){
					fprintf(galatic_b, "Feminino,");
				} else if (reserva.sexo=='N'||reserva.sexo=='n'){
					fprintf(galatic_b, "Nao declarado,");
				}

				printf("Digite a data de nascimento do(a) passageiro(a):\n[substitua as barras por enters]\n");
				scanf("%d", &reserva.dataNascimento[0]); printf("/");
				scanf("%d", &reserva.dataNascimento[1]); printf("/");
				scanf("%d", &reserva.dataNascimento[2]); //colocar no arquivo

				if(valida_data(reserva.dataNascimento)==false){
					do{
						clear();
						printf("Data inválida!\nPor favor, digite-a novamente (dd/mm/aaaa):\n");
						scanf("%d", &reserva.dataNascimento[0]); printf("/");
						scanf("%d", &reserva.dataNascimento[1]); printf("/");
						scanf("%d[^\n]", &reserva.dataNascimento[2]);
					}while(valida_data(voo.data)==false); //colocar no arquivo
				} printf("\n");
				fprintf(galatic_b, "%d/%d/%d,", reserva.dataNascimento[0], reserva.dataNascimento[1], reserva.dataNascimento[2]);

				strcpy(reserva.statusReserva, "ativa");
				fprintf(galatic_b, "%s,\n", reserva.statusReserva); //reserva é dita ativa até que seja cancelada

				printf("--- Reserva cadastrada com sucesso ---\n\n");
				fclose(galatic_b);//fechar o arquivo

				setbuf(stdin, NULL);
				printf("---------------------------------------\n");
				printf("Digite qualquer caracter para continuar\n");
				scanf("%*c");

				//não repetir a reserva no mesmo voo para o mesmo passageiro
				break;
			case 3: //consultar voo
				clear();

				printf("--------- Consulta ao Voo ---------\n\nDigite o numero do voo a ser consultado:\n[Formato JEB-XXXX]\n");
				scanf("%s", numComp); //leitura do numero do voo a ser consultado

				flight vooTemp;
				
				galatic=fopen("galatic_voos_arq.csv", "rt"); //abrir o arquivo
				if(galatic==NULL){
					printf("Não foi possível abrir o arquivo!\n\nReinicie o programa para tentar de novo.\n");
					exit(0);
				}
				
				char cabecalho[MAX_NOME];
				fgets(cabecalho,MAX_NOME,galatic);//pular o cabeçalho até o \n
				i=0;
				do {
					fscanf(galatic, "%[^,],%i,%i/%i/%i,%i:%i,%[^,],\n", vooTemp.numVoo, &vooTemp.maxPassageiros, &vooTemp.data[0],&vooTemp.data[1],&vooTemp.data[2], &vooTemp.horario[0],&vooTemp.horario[1], vooTemp.status ); //leitura do numero do voo do arquivo
					
					if (strcmp(vooTemp.numVoo, numComp)==0) {
						break;
					}
					i++;
				} while (!feof(galatic));
			
				printf("\n\n------- Informações do voo -------\n\n");
				printf("Número do voo: %s\n", vooTemp.numVoo);

				//fseek(galatic, sizeof(voo.maxPassageiros), SEEK_CUR);
				//fscanf(galatic, "%d[^,]", &vooTemp.maxPassageiros);
				printf("Máximo de passageiros: %d\n", vooTemp.maxPassageiros);

				//fseek(galatic, sizeof(voo.statusVoo) ,SEEK_CUR);
				//fscanf(galatic, "%s", vooTemp.status);
				printf("Status do voo: %s\n", vooTemp.status);
				
				//printf("Porcentagem de ocupação: %.2f %%", float(contador/voo.maxPassageiros)*100)
				printf("Data do voo: %d/%d/%d\n", vooTemp.data[0], vooTemp.data[1], vooTemp.data[2]);
				printf("Horário do voo: %d:%d\n", vooTemp.horario[0], vooTemp.horario[1]);
				
				setbuf(stdin, NULL);
				printf("\n-----------------------------------\n\n");
				printf("Digite qualquer caracter para continuar\n");
				scanf("%*c");

				fclose(galatic);

				break;
		
			case 4: //consultar reserva
				clear();
				setbuf(stdin,NULL);
				printf("--------- Consulta à Reserva ---------\n\nDigite o numero da reserva a ser consultada:\n");
				scanf("%s", resComp); printf("\n");

				galatic_b=fopen("galatic_reservas_arq.csv", "r"); //abrir o arquivo
				if(galatic_b==NULL){
					clear();
					printf("Não foi possível abrir o arquivo :(\n\nReinicie o programa para tentar novamente.\n");
					exit(0);
				} else {
					setbuf(galatic_b,NULL);
					fgets(cabecalho,MAX_NOME,galatic_b);//leitura do cabeçalho para posicionar o cursor nas informações
					do { //leitura da struct inteira dentro do arquivo
						fscanf(galatic_b, "%[^,],%[^,],%[^,],%i.%i.%i-%i,%[^,],%i/%i/%i,%[^,],\n", gbnum,jebnum, reservaTemp.nomePassageiro, &reservaTemp.CPF[0],&reservaTemp.CPF[1],&reservaTemp.CPF[2],&reservaTemp.CPF[3], sexoPalavra,&reservaTemp.dataNascimento[0],&reservaTemp.dataNascimento[1],&reservaTemp.dataNascimento[2], reservaTemp.statusReserva); 

						if (strcmp(resComp,gbnum)==0){ //se for o mesmo GB, printar as informações
							printf("-------------------------------------\n");
							printf("Número da reserva: %s\n", gbnum);
							printf("Status da reserva: %s\n", reservaTemp.statusReserva);
							printf("Número do voo: %s\n\n", jebnum);
							printf("----- Dados do(a) Passageiro(a) -----\n");
							printf("Nome do passageiro: %s\n", reservaTemp.nomePassageiro);
							printf("CPF do passageiro: %d.%d.%d-%d\n", reservaTemp.CPF[0], reservaTemp.CPF[1], reservaTemp.CPF[2], reservaTemp.CPF[3]);
							printf("Sexo: %s\n",sexoPalavra);
							printf("Data de nascimento: %d/%d/%d\n\n", reservaTemp.dataNascimento[0], reservaTemp.dataNascimento[1], reservaTemp.dataNascimento[2]);
							break;
						} else {
							printf("Número de reserva inexistente\n");
							break;
						}
					} while (!feof(galatic_b));
				}

				fclose(galatic_b);

				setbuf(stdin, NULL);
				printf("-------------------------------------\n");
				printf("Digite qualquer caracter para continuar\n");
				scanf("%*c");
				break;

			case 5: //consultar passageiro
				clear();
				printf("-------- Consulta ao(à) passageiro(a) ---------\n\nDigite o nome completo do(a) passageiro(a):\n");
				scanf("%s", nomeComp);//leitura do nome a ser consultado
				printf("\n------- Reservas desse(a) Passageiro(a) -------\n\n");

				galatic_b=fopen("galatic_reservas_arq.csv", "r");
				if(galatic_b==NULL){
					printf("Houve problemas ao abrir o arquivo :(\n\nReinicie o programa para tentar novamente");
					exit(0);
				} else { //caso o arquivo abra
					fgets(cabecalho,MAX_NOME,galatic_b);//pular cabeçalho
					do{
						fscanf(galatic_b, "%[^,],%[^,],%[^,],%i.%i.%i-%i,%[^,],%i/%i/%i,%[^,],\n", gbnum,jebnum, reservaTemp.nomePassageiro, &reservaTemp.CPF[0],&reservaTemp.CPF[1],&reservaTemp.CPF[2],&reservaTemp.CPF[3], sexoPalavra,&reservaTemp.dataNascimento[0],&reservaTemp.dataNascimento[1],&reservaTemp.dataNascimento[2], reservaTemp.statusReserva);//leitura da stuct com as infos

						if(strcmp(reservaTemp.nomePassageiro, nomeComp)==0){//mostrar todas reservas com tal nome
							printf("Numero da reserva: %s\nStatus da reserva: %s\nNumero do voo: %s\n----------------------------------------------\n\n", gbnum, reservaTemp.statusReserva, jebnum);
						}
					}while(!feof(galatic));
				}
				fclose(galatic_b);
				setbuf(stdin, NULL);
				printf("Digite qualquer caracter para continuar\n");
				scanf("%*c");
				
				break;

			case 6: //cancelar voo
				clear();
				printf("-------- Cancelamento de Voo --------\n\nDigite o numero do voo a ser candelado:\n[Formato JEB-XXXX]\n");
				scanf("%s", numComp);

				galatic=fopen("galatic_voos_arq.csv", "r");
				galatic_temp=fopen("galatic_temp.csv", "a+t");

				if(galatic==NULL||galatic_temp==NULL){
					printf("Não foi possível abrir o arquivo :(\n\nReinicie o programa para tentar novamente\n");
					exit(0);
				} else {
					fgets(cabecalho,MAX_NOME,galatic);//leitura do cabeçalho
					fprintf(galatic_temp,"%s", cabecalho);//transcrição do cabeçalho
					do{
						setbuf(galatic,NULL);//limpar buffer
						fscanf(galatic,"%[^,],%i,%i/%i/%i,%i:%i,%[^,],\n", jebnum, &vooTemp.maxPassageiros, &vooTemp.data[0], &vooTemp.data[1], &vooTemp.data[2], &vooTemp.horario[0], &vooTemp.horario[1], vooTemp.statusVoo);

						if (strcmp(numComp,jebnum)!=0){ //voo não será cancelado
							fprintf(galatic_temp, "%s,%d,%d/%d/%d,%d:%d,%s,\n", jebnum, vooTemp.maxPassageiros, vooTemp.data[0], vooTemp.data[1], vooTemp.data[2], vooTemp.horario[0], vooTemp.horario[1], vooTemp.statusVoo);//transcrição dos voos não cancelados
						} else {
							fprintf(galatic_temp, "%s,%d,%d/%d/%d,%d:%d,cancelado,\n", jebnum, vooTemp.maxPassageiros, vooTemp.data[0], vooTemp.data[1], vooTemp.data[2], vooTemp.horario[0], vooTemp.horario[1]);
							//reecrita do voo a ser cancelado trocando o status
						}
					}while(!feof(galatic));//repetir até terminar o arquivo
				}

				fclose(galatic);
				fclose(galatic_temp);//fechar os arquivos
				remove("galatic_voos_arq.csv");
				rename("galatic_temp.csv","galatic_voos_arq.csv");

				//para cancelar as reservas vinculadas a tal voo
				galatic_b=fopen("galatic_reservas_arq.csv","r");
				galatic_temp=fopen("galatic_temp.csv","a+t");

				if (galatic_b==NULL||galatic_temp==NULL){
					printf("Houve problemas ao abrir o arquivo :(\n\nReinicie o programa para tentar novamente");
					exit(0);
				} else {
					setbuf(galatic_b,NULL);
					fgets(cabecalho,MAX_NOME,galatic_b); //pular o cabeçalho
					fprintf(galatic_temp,"%s",cabecalho); // reescrever o cabeçalho no arq temporário
					do{
						fscanf(galatic_b,"%[^,],%[^,],%[^,],%d.%d.%d-%d,%[^,],%d/%d/%d,%[^,],\n", gbnum, jebnum, reservaTemp.nomePassageiro, &reservaTemp.CPF[0], &reservaTemp.CPF[1],&reservaTemp.CPF[2],&reservaTemp.CPF[3],sexoPalavra,&reservaTemp.dataNascimento[0],&reservaTemp.dataNascimento[1],&reservaTemp.dataNascimento[2],reservaTemp.statusReserva);

						if(strcmp(numComp,jebnum)==0){//trocar as reservas vinculadas para cancelá-las
							fprintf(galatic_temp,"%s,%s,%s,%d.%d.%d-%d,%s,%d/%d/%d,cancelada,\n", gbnum, jebnum, reservaTemp.nomePassageiro, reservaTemp.CPF[0], reservaTemp.CPF[1],reservaTemp.CPF[2],reservaTemp.CPF[3],sexoPalavra,reservaTemp.dataNascimento[0],reservaTemp.dataNascimento[1],reservaTemp.dataNascimento[2]);
						} else { //transcrever as reservas não vinculadas
							fprintf(galatic_temp,"%s,%s,%s,%d.%d.%d-%d,%s,%d/%d/%d,%s,\n", gbnum, jebnum, reservaTemp.nomePassageiro, reservaTemp.CPF[0], reservaTemp.CPF[1],reservaTemp.CPF[2],reservaTemp.CPF[3],sexoPalavra,reservaTemp.dataNascimento[0],reservaTemp.dataNascimento[1],reservaTemp.dataNascimento[2],reservaTemp.statusReserva);
						}
					}while(!feof(galatic_b));
				}

				fclose(galatic_b);
				fclose(galatic_temp);

				remove("galatic_reservas_arq.csv");//excluir o arquivo antigo
				rename("galatic_temp.csv","galatic_reservas_arq.csv");//renomear o temporário para permanente

				setbuf(stdin,NULL);
				printf("\n------- Voo %s cancelado -------\n-------------------------------------\nDigite quaquer caracter para continuar\n", jebnum);
				scanf("%*c");
				break;

			case 7: //cancelar reserva
				clear();
				printf("-------- Cancelamento de Reserva --------\n\nDigite o numero da reserva a ser candelada:\n[Formato GB-XXXXXX]\n");
				setbuf(stdin,NULL);
				scanf("%s",resComp);

				galatic_b=fopen("galatic_reservas_arq.csv","r");
				galatic_temp=fopen("galatic_temp.csv","a+t");

				if (galatic_b==NULL||galatic_temp==NULL){
					printf("Houve problemas ao abrir o arquivo :(\n\nReinicie o programa para tentar novamente");
					exit(0);
				} else {
					setbuf(galatic_b,NULL);
					fgets(cabecalho,MAX_NOME,galatic_b); //pular o cabeçalho
					fprintf(galatic_temp,"%s",cabecalho); // reescrever o cabeçalho no arq temporário
					do{
						fscanf(galatic_b,"%[^,],%[^,],%[^,],%d.%d.%d-%d,%[^,],%d/%d/%d,%[^,],\n", gbnum, jebnum, reservaTemp.nomePassageiro, &reservaTemp.CPF[0], &reservaTemp.CPF[1],&reservaTemp.CPF[2],&reservaTemp.CPF[3],sexoPalavra,&reservaTemp.dataNascimento[0],&reservaTemp.dataNascimento[1],&reservaTemp.dataNascimento[2],reservaTemp.statusReserva);

						if(strcmp(resComp,gbnum)==0){//trocar as reservas para cancelá-las
							fprintf(galatic_temp,"%s,%s,%s,%d.%d.%d-%d,%s,%d/%d/%d,cancelada,\n", gbnum, jebnum, reservaTemp.nomePassageiro, reservaTemp.CPF[0], reservaTemp.CPF[1],reservaTemp.CPF[2],reservaTemp.CPF[3],sexoPalavra,reservaTemp.dataNascimento[0],reservaTemp.dataNascimento[1],reservaTemp.dataNascimento[2]);
						} else { //transcrever as reservas que não serão canceladas
							fprintf(galatic_temp,"%s,%s,%s,%d.%d.%d-%d,%s,%d/%d/%d,%s,\n", gbnum, jebnum, reservaTemp.nomePassageiro, reservaTemp.CPF[0], reservaTemp.CPF[1],reservaTemp.CPF[2],reservaTemp.CPF[3],sexoPalavra,reservaTemp.dataNascimento[0],reservaTemp.dataNascimento[1],reservaTemp.dataNascimento[2],reservaTemp.statusReserva);
						}
					}while(!feof(galatic_b));
				}

				fclose(galatic_b);//fechar os arquivos
				fclose(galatic_temp);

				remove("galatic_reservas_arq.csv");//excluir o arquivo antigo
				rename("galatic_temp.csv","galatic_reservas_arq.csv");//renomear o temporário para o permanente

				printf("\n------- Reserva %s cancelada -------\n-------------------------------------\nDigite qualquer caracter para continuar\n", resComp);
				scanf("%*c");
				break;

			case 8: //excluir voo
				clear();
				printf("---------- Exclusão de Voo ----------\n\nDigite o numero do voo a ser excluido:\n[Formato JEB-XXXX]\n");
				scanf("%s",numComp);

				galatic=fopen("galatic_voos_arq.csv", "r");//abertura para leitura do arquivo a ser alterado
				galatic_temp=fopen("galatic_temp.csv", "a+t");//abertura pra escrta em arquivo temporário

				if (galatic==NULL || galatic_temp==NULL){
					printf("Houve problemas ao abrir o arquivo :(\n\nReinicie o programa para tentar novamente\n");
					exit(0);
				} else {
					setbuf(galatic,NULL);
					fgets(cabecalho,MAX_NOME,galatic);//pular o cabeçalho
					fprintf(galatic_temp,"%s", cabecalho);//transcrição do cabeçalho para o arquivo temporário

					do{
						setbuf(galatic,NULL);
						fscanf(galatic,"%[^,],%i,%i/%i/%i,%i:%i,%[^,],\n", jebnum, &vooTemp.maxPassageiros, &vooTemp.data[0], &vooTemp.data[1], &vooTemp.data[2], &vooTemp.horario[0], &vooTemp.horario[1], vooTemp.statusVoo);

						if (strcmp(numComp,jebnum)!=0){ //voo não será excluido
							fprintf(galatic_temp, "%s,%d,%d/%d/%d,%d:%d,%s,\n", jebnum, vooTemp.maxPassageiros, vooTemp.data[0], vooTemp.data[1], vooTemp.data[2], vooTemp.horario[0], vooTemp.horario[1], vooTemp.statusVoo);//transcrição dos voos não excluidos
						}
					}while(!feof(galatic));
				}

				fclose(galatic);
				fclose(galatic_temp);

				remove("galatic_voos_arq.csv");
				rename("galatic_temp.csv","galatic_voos_arq.csv");

				//para excluir as reservas vinculadas a tal voo
				galatic_b=fopen("galatic_reservas_arq.csv","r");
				galatic_temp=fopen("galatic_temp.csv","a+t");

				if (galatic_b==NULL||galatic_temp==NULL){
					printf("Houve problemas ao abrir o arquivo :(\n\nReinicie o programa para tentar novamente");
				} else {
					setbuf(galatic_b,NULL);
					fgets(cabecalho,MAX_NOME,galatic_b); //pular o cabeçalho
					fprintf(galatic_temp,"%s",cabecalho); // reescrever o cabeçalho no arq temporário
					do{
						fscanf(galatic_b,"%[^,],%[^,],%[^,],%d.%d.%d-%d,%[^,],%d/%d/%d,%[^,],\n", gbnum, jebnum, reservaTemp.nomePassageiro, &reservaTemp.CPF[0], &reservaTemp.CPF[1],&reservaTemp.CPF[2],&reservaTemp.CPF[3],sexoPalavra,&reservaTemp.dataNascimento[0],&reservaTemp.dataNascimento[1],&reservaTemp.dataNascimento[2],reservaTemp.statusReserva);

						if(strcmp(numComp,jebnum)!=0){//reservas não vinculadas são reescritas
							fprintf(galatic_temp,"%s,%s,%s,%d.%d.%d-%d,%s,%d/%d/%d,%s,\n", gbnum, jebnum, reservaTemp.nomePassageiro, reservaTemp.CPF[0], reservaTemp.CPF[1],reservaTemp.CPF[2],reservaTemp.CPF[3],sexoPalavra,reservaTemp.dataNascimento[0],reservaTemp.dataNascimento[1],reservaTemp.dataNascimento[2],reservaTemp.statusReserva);
						}
					}while(!feof(galatic_b));
				}

				fclose(galatic_b);
				fclose(galatic_temp);

				remove("galatic_reservas_arq.csv");
				rename("galatic_temp.csv","galatic_reservas_arq.csv");

				setbuf(stdin,NULL);
				printf("\n------- Voo %s excluido -------\n-------------------------------------\nDigite qualquer caracter para continuar\n", jebnum);
				scanf("%*c");
				break;

			case 9: //Sair do programa
				clear();
				printf("----- Obrigado por voar com a Galatic Birds -----\n----------- Desejamo-lhe ótimos voos ------------\n-------------- Programa encerrado ---------------\n");
				exit(0);
				break;
			default:
				clear();
		}
	} while(opcao!=9);
  return 0;
}

//Funções e Procedimentos adicionais
void menu(){ //Menu e suas opções
	printf("----------- M E N U -------------\n");
	printf("------ Selecione uma opção ------\n\n");
	printf("1) Cadastrar voo\n");
	printf("2) Cadastrar reserva\n");
	printf("3) Consultar voo\n");
	printf("4) Consultar reserva\n");
	printf("5) Consultar passageiro\n");
	printf("6) Cancelar voo\n");
	printf("7) Cancelar reserva\n");
	printf("8) Excluir voo\n");
	printf("9) Sair do Programa\n\n");
	printf("---------------------------------\n");
}

bool valida_data(int data[3]){ //validação da data
	bool bissexto, valido;

	if (data[2]%4==0){ //verificação do ser bissexto ou não
		if (data[2]%100==0){
			if (data[2]%400==0){
				bissexto=true;
			} else {
				bissexto=false;
			}
		} else {
			bissexto=true;
		}
	} else {
		bissexto=false;
	}

	if(data[2]<0){ //validar ano
		valido=false;		
	} else {
		if(data[1]>12||data[1]<1){//validar mes
			valido=false;
		} else {
			if (data[1]==1||data[1]==3||data[1]==5||data[1]==7||data[1]==8||data[1]==10||data[1]==12){ //meses de 31 dias 
				if(data[0]>31 || data[0]<1){
					valido=false;
				} else {
					valido=true;
				}
			} else if (data[1]==4||data[1]==6||data[1]==9||data[1]==11){//meses com 30 dias
				if(data[0]>30 || data[0]<1){
					valido=false;
				} else {
					valido=true;
				}
			} else if (data[1]==2){ //feveireiro -> analisar ano bissexto
				if (bissexto==true) {// 29/02
					if(data[0]>29 || data[0]<1){
						valido=false;
					} else {
						valido=true;
					}
				} else {
					if(data[0]>28 || data[0]<1){
						valido=false;
					} else{
						valido=true;
					}
				}
			}
		}
	} 
	return valido;
}
bool valida_hora(int hora[2]){ //validação do horario
	bool valido;
	if (hora[0]<0 || hora[0]>23){
		valido=false;
	} else if (hora[1]<0||hora[1]>=60){
		valido=false;
	} else {
		valido=true;
	}
	return valido;
}
bool valida_cpf(int cpf[11]){ //validação do cpf
	int i, verif_1=0, verif_2=0;
	bool valido;

	for(i=0; i<9; i++){
		verif_1=verif_1+cpf[i]*(8-i+2);
	}

	for(i=0; i<10; i++){
		verif_2=verif_2+cpf[i]*(9-i+2);
	}

	if((verif_1*10)%11!=cpf[9]){
		valido=false;
	} else if((verif_2*10)%11!=cpf[10]){
		valido=false;
	} else {
		valido=true;
	}
	return valido;
}
bool valida_sexo(char c){ //validação do sexo
	if (c=='F' || c=='f' || c=='M' || c=='m'||c=='N'||c=='n'){
		return true;
	} else {
		return false;
	}
}

void clear(){ // Limpar o Terminal
#if defined(linux) || defined(unix) || defined(APPLE)
  system("clear");
#endif
#if defined(_WIN32) || defined(_WIN64)
  system("cls");
#endif
}