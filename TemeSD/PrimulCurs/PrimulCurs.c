#include<stdio.h>
#include<malloc.h>

struct Client {
	int id;
	int varsta;
	char* numele;
	float buget;
	char initialaTata;
};
struct Client initializare(int id, int varsta, const char* numele, float buget, char initialaTata) {
	struct Client c;
	c.id = id;
	c.varsta = varsta;
	c.numele = (char*)malloc(strlen(numele) + 1 * sizeof(char));
	strcpy_s(c.numele, strlen(numele) + 1, numele);
	c.buget = buget;
	c.initialaTata = initialaTata;
	return c;
}

void afisare(struct Client c) {
	printf("ID: %d. varsta: %d", c.id, c.varsta);
	printf("Numele: %s \n", c.numele);
	printf("Buget: %.2f \n", c.buget);
	printf("IntitialaTata %c \n", c.initialaTata);



}

float calculVarstaMedie(struct Client* clienti, int nrElemente) {
	float suma = 0;
	for (int i = 0; i < nrElemente; i++) {
		suma += clienti[i].varsta;
	}
	return suma / nrElemente;
}

void afisareVector(struct Client* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisare(vector[i]);
		printf("\n");
	}
}

struct Client* copiazaPrimeleNElemente(struct Client* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate

	struct Client* v = NULL;
	v = (struct Client*)(malloc)(sizeof(struct Client) * nrElementeCopiate);
	for (int i = 0; i < nrElementeCopiate; i++) {
		v[i] = vector[i];
		v[i].numele = (char*)malloc(strlen(vector[i].numele) + 1);
		strcpy_s(v[i].numele, strlen(vector[i].numele) + 1, vector[i].numele);
	}


	return v;
}

void dezalocare(struct Client** vector, int* nrElemente) {
	for (int i = 0; i < *nrElemente; i++) {
		free((*vector)[i].numele);
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

void copiazaClientiCuBugetMare(struct Client* vector, char nrElemente, float bugetMinim, struct Client** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
	*dimensiune = 0;

	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].buget >= bugetMinim) {
			(*dimensiune)++;
		}
	}
	*vectorNou = (struct Client*)malloc(sizeof(struct Client) * *dimensiune);
	int k = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].buget >= bugetMinim) {
			(*vectorNou[k]) = vector[i];
			(*vectorNou)[k].numele = (char*)malloc(sizeof(vector[i].numele) + 1);
			strcpy_s((*vectorNou)[k].numele), sizeof(vector[i].numele) + 1, vector[i];
			k++;

		}
	}
}

struct Client getPrimulClientDupaNume(struct Client* vector, int nrElemente, const char* numeCautat) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Client c;
	for (int i = 0; i < nrElemente; i++) {
		if (strcmp(vector[i].numele, numeCautat) == 0) {
			c = vector[i];
			c.numele = (char*)malloc(strlen(vector[i].numele) + 1);
			strcpy_s(c.numele, strlen(vector[i].numele) + 1, vector[i].numele);
			return c;
		}
	}


}



int main() {
	struct Client  client = initializare(2, 23, "Popesco", 2000, 'B');
	afisare(client);

	struct Client multiclienti[30];
	int nrClienti = 3;
	struct Client* clienti;
	clienti = (struct Client*)(malloc)(nrClienti * sizeof(struct Client));

	clienti[0] = initializare(1, 22, "ionesc", 100, 'u');
	clienti[1] = initializare(2, 22, "vasilescu", 200, 'v');
	clienti[2] = initializare(3, 95, "Batranescu", 200, 'k');
	printf("\n");
	afisareVector(clienti, nrClienti);
	printf("\n");
	printf("Vector: ");
	printf("%.2f\n", calculVarstaMedie(clienti, 3));
	printf("\n");
	int nrClientiFideli = 2;
	struct Client* vectorScurt = NULL;// = (struct Client*)(malloc)(nrClientiFideli * sizeof(struct Client));
	vectorScurt = copiazaPrimeleNElemente(clienti, nrClienti, vectorScurt, nrClientiFideli);
	printf("Afisare nr clienti fideli ");
	struct Client c = getPrimulClientDupaNume(clienti, nrClienti, "vasilescu");
	afisare(c);
	free(c.numele);

	//afisareVector(vectorScurt, nrClientiFideli);
	dezalocare(&clienti, &nrClienti);
	printf("vectorul dupa stergere: ");
	afisareVector(clienti, nrClienti);


	return 0;
}