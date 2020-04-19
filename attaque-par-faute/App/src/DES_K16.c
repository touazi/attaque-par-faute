#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_permutation.h"
#include "../head/DES_tables.h"
void afficher_ki_parMessage (){}

/*cette fonction permet d'annalyser les messages chiffrées avec erreur 
* pour chaque sbox elle peut etre attaquer par 6 message differents
* d'abord une calcule l'erreur qui est E(R16 oxr R16faut)
* puis on découpe cette erreur en block de 6 bit
* pour  sbox[j] je regarde bloc[j] qui lui correspend si c eagle à 0 
		==> donc ce message n'attque pas la cette sbox
		==> sinon le message attaque la sbox et on stock la position du message dans PosMessageParSbox[j]
*/
void annalyse_messages_faux(long MessageChiffreJuste,long MessagesChiffresFaux [],int PosMessageParSbox[8][6]){
	long E_ERREUR, blocs[8];
	MESSAGE IPMessageChiffreJuste = init_message(MessageChiffreJuste);
printf("IPMessageChiffreJuste.R16");printf("               ");afficher(IPMessageChiffreJuste.R16,32);
	printf("\n\n\n\n\n\n");
	printf("               ");printf("**********************************************************************************\n");
	printf("               ");printf("*******************************position de fautes*********************************\n");
	printf("               ");printf("**********************************************************************************\n");
	for(int i = 0; i < 32; i++) {
	MESSAGE IPMessagesChiffresFaux = init_message(MessagesChiffresFaux[i]);
	E_ERREUR = permutation(E, (IPMessageChiffreJuste.R16 ^ IPMessagesChiffresFaux.R16) & 0xFFFFFFFFL, 32, 48); 
printf("tttttttttt");printf("               ");afficher(MessagesChiffresFaux[i],32);
	printf("                              ");afficher(E_ERREUR,48);
	for(int i = 0; i < 8; i++) {
		 blocs[i]= E_ERREUR >> (48 - (i + 1) * 6) & 0x3F;
	}

			for(int j = 0;j < 8; j ++){
					if(  blocs[j] != 0){
						int pos=0;
						while(PosMessageParSbox[j][pos]!=0){
							pos++;
						}
						PosMessageParSbox[j][pos]=i;
					}
				}
			}
			printf("\n\n\n\n\n\n");
			printf("*********************************************************************************\n");
			printf("*************pour chaque Sbox on affiche la liste qui l'a attqué****************\n");
			printf("*********************************************************************************\n");
			
				for(int j = 0;j < 8; j ++){
				printf("\n sbox %d liste messages :",j+1 );
					for(int i = 0;i < 6; i ++){
						if(i!=5)
						printf(" %d,",PosMessageParSbox[j][i] );
						 else printf(" %d",PosMessageParSbox[j][i] );
						}	
			}	
			printf("\n\n\n\n*********************************************************************************\n");
			printf("*************************fin affiche la Sbox position****************************\n");
		printf("*********************************************************************************\n\n\n\n\n");
			
		}




void solutions_ki_ParMessage(long verif,long E_R15,long E_R15f,int sol[8][6][15],int nbSol[8][6] ,int numSbox,int numMsg){
	for (int k16i = 0 ; k16i < 64 ; k16i++) {

				int ligneSboxjuste = ((((E_R15^ k16i) >> 5) & 0x00000001) << 1) | ((E_R15^ k16i) &  0x00000001);
				int coloneSboxjuste = ((E_R15^ k16i) >> 1) & 0x0000000F;
				int ligneSboxfaux = ((((E_R15f^ k16i) >> 5) & 0x00000001) << 1) | ((E_R15f^ k16i) &  0x00000001);
				int coloneSboxfaux = ((E_R15f^ k16i) >> 1) & 0x0000000F;
				
				if ( (Sbox[numSbox][ligneSboxjuste][coloneSboxjuste] ^ 
						 Sbox[numSbox][ligneSboxfaux][coloneSboxfaux] )==	((int) verif) ) 
				{	
					sol[numSbox][numMsg][nbSol[numSbox][numMsg]] = k16i;
					++nbSol[numSbox][numMsg];
				}
				
			}

}


long concat(long k16i, long bitsAjouer){
long tmp;
tmp=k16i<<6;
tmp=tmp | bitsAjouer;
return tmp;
}

//Cette fonction permet de trouver la solution unique pour une Sbox donné
//
long solution_Ki_final(int tabSol[8][6][15],int nbSol[8][6],int numSbox){
	int numSolf0 = 0;
		long sol = (long) tabSol[numSbox][0][numSolf0];
		for (int m = 1; m < 6; m++){
			int numSolf=0;
			for (numSolf = 0; numSolf < nbSol[numSbox][m]; numSolf++)
				if (sol == tabSol[numSbox][m][numSolf])
					break;
			
			if (numSolf == nbSol[numSbox][m]){
				m = 1;
				++numSolf0;
				sol = (long) tabSol[numSbox][0][numSolf0];
			}
		}
	return sol;	
}
/*
* 
*
*
*/
long rechercheK16(long chiffreJuste, long chiffreFaux[]) {	
	long K16 = 0x000000000000L;
	long Pinv_L16XorL16F, E_R15, E_R15f;
	MESSAGE dechiffFaux,dechiffJuste;

	long blocs_Pinv_L16XorL16F[8],blocs_E_R15f[8],blocs_E_R15[8];
	int PosMessageParSbox[8][6] = {{0}};
	
	annalyse_messages_faux(chiffreJuste, chiffreFaux,PosMessageParSbox);
	dechiffJuste=init_message( chiffreJuste);
	E_R15 = permutation( E, dechiffJuste.R16, 32, 48); 
	
	for (int numSbox = 0; numSbox < 8 ; numSbox++) {
	printf("\nSbox %d\n", numSbox + 1);	
		int sol[8][6][15] = {{{0}}};
		int nbSol[8][6] = {{0}};
			for (int numMsg = 0; numMsg < 6 ; numMsg++) {
				dechiffFaux = init_message(chiffreFaux[PosMessageParSbox[numSbox][numMsg]]);
	      Pinv_L16XorL16F = permutation(Pinv, dechiffJuste.L16 ^ dechiffFaux.L16, 32, 32);
	      E_R15f = permutation( E, dechiffFaux.R16, 32, 48);
	 			decouper_en8_blocs_4bit ( Pinv_L16XorL16F , blocs_Pinv_L16XorL16F);
	 			decouper_en8_blocs_6bit (E_R15f, blocs_E_R15f);
	 			decouper_en8_blocs_6bit (E_R15 , blocs_E_R15);
			 	solutions_ki_ParMessage( blocs_Pinv_L16XorL16F[numSbox],blocs_E_R15[numSbox],blocs_E_R15f[numSbox],sol,nbSol,numSbox,numMsg);
			
			}
printf("\nSbox %d\n", numSbox + 1);
		for (int f = 0; f < 6; f++) 
		{
			printf("Faute %d : %d solutions\t", f+1, nbSol[numSbox][f]);
			for (int i = 0; i < nbSol[numSbox][f]; i++) 
				printf("%x ", sol[numSbox][f][i]);
			printf("\n"); 
		}
		

		long solSbon=solution_Ki_final(sol,nbSol,numSbox);
		K16= concat(K16, solSbon);
	}
	
	return K16;
}
