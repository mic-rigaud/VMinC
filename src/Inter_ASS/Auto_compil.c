#include "interpret.h"


void resetBuffer(char *buffer,int cpt){
	
	int i;
	for(i=0;i<=cpt;i++){
		buffer[i]='\0';
	}


}

int seekop(char * word){

	char OPCODWDS[20][5]={"nop","add","sub","mult","div","and","or","xor","shl","shr","slt","sle","seq","load","store","jmp","braz","branz","scall","stop"};
	int i=0;
	
	for(i=0;i<=19;i++){
		if(strcmp(word,OPCODWDS[i])==0){
			return i;
		}
	}
	return -1;	
}

int seekreg(char * word){

	char REGTBL[6][3]={"NAN","r1","r2","r3","r4","r5"};
	int i=0;
	
	for(i=0;i<=6;i++){
		if(strcmp(word,REGTBL[i])==0){
			return i;
		}
	}
	return -1;	
}


void splitInstruct(Tableau * tab,char * INSTRUCTCODE){

	char sep=',';
	char *temp1=malloc(1000*sizeof(char));
	int i=0;
	
	while(*INSTRUCTCODE!='\0'){
		
		if( * INSTRUCTCODE!=sep ){
		
			temp1[i]=(char) * INSTRUCTCODE;
			i++;
			INSTRUCTCODE++;
		
		}
		else{
			if(strcmp(temp1,"")!=0){
			
					strcpy(tab->mot,temp1); 
					resetBuffer(temp1,i);
					tab->suivant = malloc(sizeof(Tableau));
					tab = tab->suivant;
					i=0;
					
			}
			
			INSTRUCTCODE++;
		
		}
		
		if(* INSTRUCTCODE=='\0'){
			strcpy(tab->mot,temp1);
		}
	}

}

void AnalyseText(const char * filepath, Tableau *tab){
	
	printf("Ouverture de : %s\n",filepath);
	FILE * file=NULL;
	
	char temp;
	char *temp1=malloc(1000*sizeof(char));
	int i=0;
	
	file =fopen(filepath,"r");
	
	if (file!=NULL) 
	{
		printf("Fichier trouve, traitement en cours\n");
		printf("\n");
		printf("Instructions lues : \n");
		printf("\n");
		
		temp=fgetc(file);
		
		while(temp!=EOF)
		{
			printf("%c",temp);
			
			if(temp!=' ' && temp!='\n' && temp!='	' && temp!='\r' && temp!='\0' ){
			
				temp1[i]= (char) temp;
				i++;
				temp=fgetc(file);
				
			}
			else{
				
				if(strcmp(temp1,"")!=0){
				
					strcpy(tab->mot,temp1); 
					resetBuffer(temp1,i);
					tab->suivant = malloc(sizeof(Tableau));
					tab = tab->suivant;
					i=0;
					
				}
				temp=fgetc(file);
			}
			
		}
		fclose(file);
	}
	else
	{
		printf("Fichier introuvable\n");
	} 
	printf("\n");
	printf("Fin instructions \n");
	printf("\n");
}

void AnalyseLexique(Tableau * tab,unsigned Commande[1000]){

	int OPCODTBL[20]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13};
	int i=0;
	int operand;
	int tempint;
	
	unsigned bopcode;
	unsigned breg1;
	unsigned boo;
	unsigned bparam;
	unsigned breg2;
	unsigned INSTRUC;
	
	printf("%s\n",tab->mot);
	printf("%d\n",OPCODTBL[19]);
	
	while(tab->suivant!=NULL){
	
		operand=seekop(tab->mot);
		
		switch (operand){
			
			/* nop */	
			case 0: ;
				bopcode=0b0000;
				break;
			/* add */
			case 1: ;
				bopcode=0b0000;
				break;
			/* sub */
			case 2: ;
				bopcode=0b0000;
				break;
			/* mult */
			case 3: ;
				bopcode=0b0000;
				break;
			/* div */
			case 4:
				bopcode=0b0000;
				break;
			/* and */
			case 5:
				bopcode=0b0000;
				break;
			/* or */
			case 6:
				bopcode=0b0000;
				break;
			/* xor */
			case 7:
				bopcode=0b0000;
				break;
			/* shl */
			case 8:
				bopcode=0b0000;
				break;
			/* shr */
			case 9:
				bopcode=0b0000;
				break;
			/* slt */
			case 10:
				bopcode=0b0000;
				break;
			/* sle */
			case 11:
				bopcode=0b0000;
				break;
			/* seq */
			case 12:
				bopcode=0b0000;
				break;
			/* load */
			case 13: ;
			
				bopcode=0b01101<<27;
				printf("%08X\n",bopcode);
				tab=tab->suivant;
				int r=0;
				Tableau *temptab = malloc(sizeof(Tableau));
				
				
				splitInstruct(temptab,tab->mot);
				printf("Premier : %s\n",temptab->mot);
				
				r=seekreg(temptab->mot);
				switch(r){
					
					case 0:
						breg1=0b00000<<22;
						break;
					
					case 1:
						breg1=0b00001<<22;
						break;
					case 2:
						breg1=0b00010<<22;
						break;
					case 3:
						breg1=0b00011<<22;
						break;
					case 4:
						breg1=0b00100<<22;
						break;
					case 5:
						breg1=0b00101<<22;
						break;
				}
				
				printf("%08X\n",breg1);
				
				temptab=temptab->suivant;
				printf("Deuxieme : %s\n",temptab->mot);
				r=seekreg(temptab->mot);
				
				if(r==-1){
					boo=0<<21;
				}
				else{
					boo=1<<21;
				}
		
				printf("boo : %08X\n",boo);
				
				if(boo==0){
					tempint=atoi(temptab->mot);
					bparam=tempint<<5;	
				}
				
				else{
				
				r=seekreg(temptab->mot);
					switch(r){
					
						case 0:
							bparam=0b00000<<5;
							break;
					
						case 1:
							bparam=0b00001<<5;
							break;
						case 2:
							bparam=0b00010<<5;
							break;
						case 3:
							bparam=0b00011<<5;
							break;
						case 4:
							bparam=0b00100<<5;
							break;
						case 5:
							bparam=0b00101<<5;
							break;
					}
				
				}
				
				printf("bparam : %08X\n",bparam);
				temptab=temptab->suivant;
				printf("Troisieme : %s\n",temptab->mot);
				r=seekreg(temptab->mot);
				switch(r){
					
					case 0:
						breg2=0b00000;
						break;
					
					case 1:
						breg2=0b00001;
						break;
					case 2:
						breg2=0b00010;
						break;
					case 3:
						breg2=0b00011;
						break;
					case 4:
						breg2=0b00100;
						break;
					case 5:
						breg2=0b00101;
						break;
				}
				
				printf("breg2 : %08X\n",breg2);
				
				INSTRUC= bopcode | breg1 | boo | bparam | breg2;   
				Commande[i]=INSTRUC;
				i++;
				break;
			/* store */
			case 14:
				bopcode=0b0000;
				break;
			/* jmp */
			case 15:
				bopcode=0b0000;
				break;
			/* braz */
			case 16:
				bopcode=0b0000;
				break;
			/* branz */
			case 17:
				bopcode=0b0000;
				break;
			/* scall */
			case 18:
				bopcode=0b0000;
				break;
			/* stop */
			case 19:
				bopcode=0b0000;
				break;
			
			default :
				 break;
		}
		tab=tab->suivant;
	}	
	
}
