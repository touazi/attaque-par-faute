#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_tables.h"


//Permute les bits de l'entree aPermuter, selon la table table[], le nombre d'éléments de table[] doit etre égal à tailleSortie
long permutation(int table[] ,long aPermuter, int tailleEntree, int tailleSortie) {
		
	long res = 0x0L;
	long pos = 0x1L;
	long tmp;
	
	//On va selectionner le bit à la position table[i] de aPermuter et le rajouter à res à la position taille-i
	for (int i = 0; i < tailleSortie; i++) 
	{
		//On se positionne dans tmp en mettant le bit 1 dans la position table[i]
		tmp = pos << (tailleEntree - table[i]);
		
		//On récupère le bit de aPermuter à cette position
		tmp = aPermuter & tmp;
		
		//On met ce bit (s'il vaut 1) à la position actuelle (la plus forte)
		if (tmp != 0){
			//On place ce bit à 1 dans la bonne position
			tmp = 0x1L;
			tmp = tmp << (tailleSortie - i - 1);
		} 
		
		//On melange ce nouveau bit avec res
		res = res | tmp;
	}
	return res;
}
/*
long pow(int a,int b){
	if(b == 0){
		return 1;
	} else {
		return a*pow(a,b-1);
	}
}
void HixaToBinaire(long k, int n,int * t) {
	
	for(int i = n - 1; i >= 0; i--) {
	
		t[n-i-1]=(k >> i) & 1;
	}

}
long BinaireToHixa(int *tab,int nbrBit){	
	long nombre=0;
	int i=0,j=nbrBit-1;
	while(j>=0){
		if(tab[j] != 0)
			nombre =nombre + pow(2,i);
		i++;
		j--;}
	return nombre;}
long permutation( int * tablePermutation, long aPermuter ,int tailleEntree, int tailleSortie) {
	int tabEntreBinaire[ tailleEntree ],  tabPemuterBinaire[ tailleSortie ],  pos;
	HixaToBinaire(aPermuter,tailleEntree,tabEntreBinaire);
	long res = 0x0L;

	for (int i = 0; i < tailleSortie; i++) 
	{	pos=tablePermutation[i]-1;
		tabPemuterBinaire[i]=tabEntreBinaire[pos];
	}
	res=BinaireToHixa(tabPemuterBinaire,tailleSortie);
	return res;
}

*/
MESSAGE init_message(long chiffreJuste){
	MESSAGE m;
	m.msg= permutation(PI, chiffreJuste, 64, 64); 
	m.L16 = (m.msg >> 32) & 0xFFFFFFFFL; 
	m.R16 = m.msg & 0xFFFFFFFFL;
return m;}

MESSAGE init_Message(long chiffreJuste){
	MESSAGE m;
	m.msg= permutation(PI, chiffreJuste, 64, 64); 
	m.L16 = (m.msg >> 32) & 0xFFFFFFFFL; 
	m.R16 = m.msg & 0xFFFFFFFFL;
return m;}
void afficher_binaire(long k, int n) {
	
	for(int i = n - 1; i >= 0; i--) {
	if ((i+1)%8 == 0){ printf(" ");} 
		printf("%d", (k >> i) & 1); 
	}
	printf("\n");
}
void decouper_en8_blocs_6bit(long decouper,long blocs[8]){

     	for(int i = 0; i < 8; i++) {
		 				blocs[i]= decouper >> (48 - (i + 1) * 6) & 0x3F;
				} 
				
}
void decouper_en8_blocs_4bit(long decouper,long blocs[8]){
     
     	for(int i = 0; i < 8; i++) {
		 				blocs[i]= decouper >> (32 - (i + 1) * 4) & 0x0000000F;
				} 

}
void decouper_en8_blocs_8bit(long decouper,long blocs[8]){
	 	
	for(int i = 0; i < 8; i++) {
		 blocs[i]= decouper >> (64 - (i + 1) * 8) & 0xFFFFFFFF;
	}
}