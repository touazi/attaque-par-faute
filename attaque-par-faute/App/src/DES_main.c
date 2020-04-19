#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_algo.h"
#include "../head/DES_K16.h"
#include "../head/DES_K.h"


int main()
{
	//Clair et chiffrés : bloc de 64 bits en hexadecimal
		long MessageClair = 0x57294338ADA26BB3;
	long MessageChiffreJuste =0x830D16A5B08A9DA8;

	long MessagesChiffresFaux[] = {
			0x811C16A5B08B9DAC,0x830F16A1B08B9DA8,0x830D14E5B08B9DA8,0x831D12A3A08B9DA8,
			0x825D12A1A28A9DA8,0x824D16A5B0889DA8,0x834D12A5B08A9FA8,0x824D16A4A09E9DAA,
			0x8B4D16A4A09A9DA8,0x830516A4F09A9DA8,0x830D1EA4F08E9DA8,0xC30D16ACF0DE9DA8,
			0xC30D16A4B89A9DA9,0xC30D06A5B0C29DA9,0xC30D16A5B0CA95A8,0xC30D06A5B08A8CA1,
			0xE30D06A5B4CA9CA8,0x832D16A5B48A8DA8,0x830D36A5B08A8CA8,0x870D5685B08A9CE8,
			0x870D17A5908A8CE8,0x870D56A5B0AA9DA8,0x930D17A5B08ABDA8,0x970D56B5B18ADD88,
			0x170D16B5B18AD9A8,0x838D16B5B08A99A8,0x830D96A5B18AD9A8,0x83081625B18ADDA8,
			0x830816A5318AD9B8,0x830916A5B00A9DB8,0x830816A5B08A1DBC,0x830916E5B08B9D3C,
			};
/*
	long MessageClair = 0xB307FD04379D8075;
	long MessageChiffreJuste =0x937B2FD61208B0DD;
	long MessagesChiffresFaux[] = {0x916E2F961208B0CD
,0x93692F961209B0DD
,0x937B2DD21209B0DD
,0x932B2BD40209B0DD
,0x922B2FD20008B0DD
,0x923B2BD6120AB0DD
,0x933B2BD60208B2DD
,0x923B2BD7420CB0DF
,0x9A3B2BD75218B0DD
,0x93732FD65218B0DD
,0x937B27D75208B0DD
,0xD37B3FDF525CB0DD
,0x937B2FD75A58B0DC
,0x937B3FD61200B0DC
,0xD37B3FD61208B8DD
,0xD37B3FD61608B094
,0xF37B2FD61648B09D
,0x935B2FD61608B19D
,0x937B0FD61608A09D
,0x877B6EF61608A19D
,0x977B2ED63608A09D
,0x977B6FD61228B0DD
,0x877B2ED6120890DD
,0x837B2ED61308F0FD
,0x177B2EC61308B4DD
,0x93FB2FC61308B0DD
,0x937BAFC61208B4DD
,0x937A2F461308F0CD
,0x937F2FD69308B4C9
,0x937E2FD61288B0CD
,0x937E2FD6120830D9
,0x937E2FD21209B049			};*/
	long dechiffJuste;
	long   k16_finale =0x000000000000L;
//	long  kkl = chercher_k16(MessageChiffreJuste,MessagesChiffresFaux,& k16_finale);
	//printf("kkl  = %lx\n", kkl); 
	//printf("dans la maiiiiiiiiiiiiiiiiiiiiii %lx  \n", kkl& 0x00000000000000FF );
//	printf("\nK16 = %lx\n",  k16_finale);
	//Exemple d'exécution d'un chiffrement DES
	//printf("\n######################################################################\n\n");
	
//	printf("Exemple exécution DES\n\n");
//	printf("Clair = %lx | Clé = %lx | Chiffré : %lx\n", clair, chiffreJuste, DES(clair, chiffreJuste));
	
//	printf("\n######################################################################\n\n");
	
//	printf("Recherche K16\n");
	
//	Recherche de la clé K16 avec les chiffrés faux donnés
	long K16 = rechercheK16(MessageChiffreJuste, MessagesChiffresFaux);
	
	printf("\nK16 = %lx\n", K16);
	
	printf("\n######################################################################\n\n");
	
	printf("Recherche K\n");
	
	//Recherche de la clé K de 64 bit
	long K = rechercheK(MessageClair, MessageChiffreJuste, K16);
	
	printf("\nK 64 bits = %lx\n", K);
	
	printf("\n######################################################################\n\n");
	
	printf("Vérification de la clé trouvée\n\n");
	printf("Chiffré donné = %lx\n",MessageChiffreJuste);
	printf("\nChiffré trouvé = %lx\n",DES(MessageClair,K));
	
	printf("\n######################################################################\n\n");
	
	return EXIT_SUCCESS;
}
