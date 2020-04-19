#ifndef H_DES_permutation
#define H_DES_permutation
#include "../head/DES_tables.h"
// Fonction de permutation de bits

MESSAGE init_message(long );
message init_Message(long );
long binaire(long);

long permutation(int[], long, int, int);

void afficher_binaire(long , int );
void decouper_en8_blocs_4bit(long ,long );
void decouper_en8_blocs_6bit(long ,long );
void decouper_en8_blocs_8bit(long ,long );

#endif
