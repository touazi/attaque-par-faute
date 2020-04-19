#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_permutation.h"
#include "../head/DES_algo.h"
#include "../head/DES_tables.h"

/*cette fonction permet de chercher et j'ajouter les 8 bits manquant 
*           lors de la permutation PC2inv
* pour chaque bit manquant on fait une attaque brute une recherche exaustive sur 2^8 possibilité
* et pour cela on compare le message chiffrer juste avec avec chaqu'un des 2^8 possibiliter de k
*/
long bit_manquant_PC2inv(long MessageClair, long MessageChiffreJuste, long K) 
{
	long Ktest = K;
	printf("chiffre %lx\n",MessageChiffreJuste );
	long pos[] = {14, 15, 19, 20, 51, 54, 58, 60};
	for (long mask = 0x00L; mask < 256; ++mask){
		 if (MessageChiffreJuste == DES(MessageClair, Ktest) )
		     break;
		 long res = 0x0L;
	   	 for(int i = 0; i < 8; i++){
		 	 res = res | ( ((mask >> i) & 1) << (64 - pos[i]) );
		  }
		  Ktest = K | res;
		  mask = mask + 1;
	}
return Ktest;}
/*ce fonction chercher et ajoute les bits de pariter manquant a K
* pour chaque blocs passer en parametre de taille 8 bits
* on XOR tt les bit en eux si 
* 			==> le resultat de ce XOR egale à zero donc le nombre de bit a 1 est pair 
				donc on ajoute 1 à la fin pour que ce nombre sois impair
			==> sinon si il est egal à 1 donc le nombre est impair
				donc on ajoute une zero a fin
*le but c'est que le nombre de bits a 1 il sois impair 
*/
long bits_Parite_manquant(long K,long blocs[8]){
	long tmp, parite;
	afficher(K,64);
	for(int i = 0; i < 8; i++) {
		parite = 0;
		tmp=0x00;
		
		for(int j = 0; j < 8; j++) {
			if(j != 7) {
				 long bit=blocs[i] >> (8 - (j + 1) ) & 0x1;
				 tmp=tmp ^bit;
			}else {
				 parite = !tmp;
				 K  = K | parite << ((7 - i) * 8);
			}
		}
	}
	afficher(K ,64);
return K ;}
/*
*        Cette fonction permet de trouver la cle k 
* à partir de K16,message chifrrer et message MessageClair passé en parametre
* D'abord on récupere les 48 bits de la cle k en faisant pc1inv(pc2inv(k16))
* puis on chercher les bits manquant lors de la permutation PC2inv
* A la fin on coupe la cle qu'on a jusqu'a present en bloc de 8 bit 
* pour sache bloc en cherche le bits de parité qui on manquer lors de la permutation  PC1inv
*/
long rechercheK(long MessageClair, long MessageChiffreJuste, long K16) 
{	long blocs[8]={0};
	long k_finale = permutation( PC1inv,permutation(PC2inv, K16, 48, 56), 56, 64);
	
	 k_finale = bit_manquant_PC2inv(MessageClair, MessageChiffreJuste, k_finale);
	
	for(int i = 0; i < 8; i++) {
		 blocs[i]= k_finale >> (64 - (i + 1) * 8) & 0xFFFFFFFF;
	}

	 k_finale = bits_Parite_manquant(k_finale,blocs);
	
	return k_finale;
}
