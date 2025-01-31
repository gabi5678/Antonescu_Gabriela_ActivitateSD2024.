//#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Camion Camion;
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;


struct Camion {
	int serie;
	char* marca;
	float greutate;
};

struct NodPrincipal {
	Camion info;
	NodSecundar* vecini;
	NodPrincipal* next;
};


struct NodSecundar {
	NodPrincipal* nod;
	NodSecundar* next;
};

//inserare in lista principala la inceput

NodPrincipal* inserarePrincipala(NodPrincipal* graf, Camion c) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = c;
	nou->next = graf;
	nou->vecini = NULL;
	return nou;
}


// functie de cautare nod principal dupa serie camion

NodPrincipal* cautareDupaSerie(NodPrincipal* graf, int serie) {
	while (graf && graf->info.serie != serie) {
		graf = graf->next;
	}
	return graf;
}



//inserare in lista secundara la sfarsit

void inserareSecundara(NodSecundar** cap, NodPrincipal* nod) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->nod = nod;
	nou->next = NULL;
	if (*cap) {
		NodSecundar* p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else {
		cap = nou;
	}
}


//fucntie de inserare muchie in lista

void inserareMuchie(NodPrincipal* graf, int serieStart, int serieStop) {
	NodPrincipal* nodStart = cautareDupaSerie(graf, serieStart);
	NodPrincipal* nodStop = cautareDupaSerie(graf, serieStop);
	inserareSecundara(&(nodStart)->vecini, nodStop);
	inserareSecundara(&(nodStop)->vecini, nodStart);
}


Camion creareCamion(int serie, const char* marca, float greutate) {
	Camion c;
	c.serie = serie;
	c.greutate = c.greutate;
	c.marca = (char*)malloc((sizeof(char) * (strlen(marca)) + 1));
	strcpy_s(c.marca, strlen(marca) + 1,marca);
	return c;
}

//parcurgere in latime 0 1 3 2 4
//parcurgere in adancime 0 1 2 4 3




void main() {
	NodPrincipal* graf=NULL;
	//inserare 5 noduri cu id-urile 0,1,2,3,4
	graf = inserarePrincipala(graf, creareCamion(4, "Scania", 20));
	graf = inserarePrincipala(graf, creareCamion(3, "Volvo", 30));
	graf = inserarePrincipala(graf, creareCamion(2, "Reno", 25));
	graf = inserarePrincipala(graf, creareCamion(1, "MAN", 15));
	graf = inserarePrincipala(graf, creareCamion(0, "Mercedes", 40));

	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 0, 3);
	inserareMuchie(graf, 2, 4);
	inserareMuchie(graf, 3, 4);
	inserareMuchie(graf, 1, 3);




}