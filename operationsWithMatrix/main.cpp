#include <stdio.h>
#include "Matriz.cpp"

int main()
{
	Matriz a(3,3);
	Matriz b(2,2);
	Matriz c(2,2);
	
	
	a.preenche();
	
	if(a.e_triang_sup())
		printf("e triangular superior\n");
	if(a.e_triang_inf())
		printf("e triangular inferior\n");
	
	if(a.e_simetrica())
		printf("E simetrica\n");
		
	if(a.e_anti_simetrica())
		printf("\nE anti simetrica");
	
	a.mostra();
}

/*
Matriz();
~Matriz();
preenche();
mostra();
adiciona();
subtrae();
multiplica();
multiplica_constante();
e_igual();
e_diferente();
set_valor();
get_linhas();
get_colunas();
transposta();
potencia();
e_triang_sup();
e_triang_inf();
e_simetrica();
e_anti_simetrica();


e_identidade();
e_ortogonal();
e_permutacao()
*/

