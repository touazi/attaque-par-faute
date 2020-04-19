#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_permutation.h"
#include "../head/DES_tables.h"

/*cette fonction fais une rotation a Gauche pour 28 bits
	/*On met dans tmp le bit le poid fort 
	/*On décale les bits d'un cran à gauche
	/*On retire le bit de poids fort de half_key
	/*on met le bit du poid fort  a la place du bit de poid faible*/
long rotate_half_key(long half_key){
	 long top_bit;
	 top_bit = (half_key & 0x8000000) >> 27;
return	 (half_key <<1 | top_bit)& 0x0FFFFFFF;	}

/* cette fonction fais la rotation de la clé donnée 
	* on découpe d'abord la clé en gauche et droite 
	* puis on leur fais la rotation pour chaque coté
	*/
long rotate_key(long key){
	 long Left = (key  >> 28) & 0xFFFFFFFL;
	 long Rigth = key & 0xFFFFFFFL;;
	 return (rotate_half_key(Left)<< 28 | rotate_half_key(Rigth)) & 0xFFFFFFFFFFFFFFL;
}
/* cette fonction génere les 16 cles 
* D'abord 
*
*
*
*
*/
void DES_key_schedule(long Ki[], long K){
	 int v[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
	 long permuted_key = permutation(PC1, K,  64, 56);
	
	 for(int i = 0; i < 16; i++) {
		 if (v[i] != 1)
		 	permuted_key = rotate_key(rotate_key(permuted_key));
		 else
			permuted_key = rotate_key(permuted_key);
			 
		 Ki[i] = permutation(PC2, permuted_key, 56, 48);
	}
}
/* Cette fonction calule  F(Ri XOR Ki)   
*    F(Ri XOR Ki)= P(S(E(Ri) XOR Ki))
*	 on commance par calculer E(Ri)
*    ensuite E(Ri) xor Ki
*    apres on separe ce résultat en 8 bloc de 6 bit pour les mettre dans la boite S
*	 	pour chaque 6 bit on concate le premier et le dernier bit pour trouver la ligne Sbox
*	 	et les autre bit 2 3 4 5 serons utilisier pour calculer la colone de la Sbox
*	 apres on conctene le resultat de la sbox des 6 bit avec le resultat des bit d'avant
*	 enfin on fais la permutation .
*/
long F(long Ri, long Ki) { 
	
	int ligneSbox,colonneSbox;
	long Expention,RiOXRKi,bloc6bit,resi,res = 0x0L,permute; 
	
	Expention= permutation(E, Ri, 32, 48) ;
	RiOXRKi=Expention^ Ki;
	
	for (int i = 0 ; i < 8 ; i++){
		 bloc6bit = (RiOXRKi >> (48 - (6 * ( i + 1 ))) & 0x3FL);
		 ligneSbox = ((((bloc6bit) >> 5) & 0x00000001) << 1) | ((bloc6bit) & 0x00000001);
		 colonneSbox = (bloc6bit  >> 1) & 0x0000000F;
		 resi=(Sbox[i][ligneSbox][colonneSbox] << (32 - (4 * (i + 1))));
		 res = res | resi;
	}
	permute=permutation(P, res, 32, 32);
	return permute;
}
/*
* cette fonction implémente l'agorithme du DES
* D'abord on génere les 16 clé a partire de la clé K
* Ensuite on fais une permutation initial IP pour le message donnée
* Apres on fais les 16 tours de festeil:
	R[i+1]=L[i] XOR F(R[i] XOR K[i])
	L[i+1]=R[i]
* Puis  on conctte le resultat gauche et droite de feistel 
* A la fin on fais la permutation inverce PIinv
*/
long DES(long MessageClair, long K) 
{
	long LiPlus1, RiPlus1, Ki[16] = {0};
	DES_key_schedule(Ki, K);
	
	message IpMessageClair =init_Message(MessageClair); 
	
	for (int i = 0; i < 16; i++) {
		RiPlus1 =IpMessageClair.L ^F(IpMessageClair.R, Ki[i]);
		LiPlus1 = IpMessageClair.R;
		
		IpMessageClair.R = RiPlus1;	
		IpMessageClair.L = LiPlus1;
	 }
	
	long concat=IpMessageClair.R << 32 | IpMessageClair.L;
	
	return permutation( PIinv, concat , 64, 64);

}
