#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Nb_bits 32
#define Nb_reg 5
//define OPCODWDS {"nop","add","sub","mult","div","and","or","xor","shl","shr","slt","sle","seq","load","store","jmp","braz","branz","scall","stop"}
//define OPCODTBL {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13}

//regname r1,r2,r3,r4
// %08X,letruc 



typedef struct Tableau_ Tableau;
struct Tableau_{
    char mot[50];
    Tableau * suivant;
};

/* Permet de récupérer le text et de le stocker dans un tableau, cf la structure */
int AnalyseText(const char * filepath, Tableau * LEX);
/*Permet de générer la commande sous forme de tableau Hexa */
void AnalyseLexique(Tableau * tab,unsigned Commande[10000]);
/*génère le code */
int createCode(const char * filepath,unsigned Commande[10000]);
