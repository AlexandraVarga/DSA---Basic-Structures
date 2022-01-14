#include <stdio.h>
typedef struct{
	int s, f; //timpii de start si final
	char nume[100]; //denumire
}activitate;
activitate activitati[100];
int n;
void sort()
{
    activitate aux;
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (activitati[i].f > activitati[j].f)
            {
                aux = activitati[i];
                activitati[i] = activitati[j];
                activitati[j] = aux;
            }
}

void select_activitati(int x[], int* nr_activitati){
	//se selecteaza activitatile conform strategiei greedy
	//x[i] contine numere 0:n-1
	//x[i] = k, inseamna ca am selectat activitatea k
	//nr_activitati se modifica
	sort();
	x[0] = 0;
	*nr_activitati = 1;
	for (int m = 1; m < n; m++)
        if (activitati[m].s >= activitati[x[*nr_activitati-1]].f)
        {
            x[*nr_activitati] = m;
            (*nr_activitati)++;
        }
}

void afisare(int x[], int nr){
	printf("Am selectat %d activitati\n", nr);
	for (int i = 0; i < nr; i++){
		printf("(%2d) %2d : %2d %s", x[i], activitati[x[i]].s, activitati[x[i]].f, activitati[x[i]].nume);
	}
}

int main(){
	FILE* f = fopen("date_activitati.txt", "r");
	fscanf(f,"%d", &n);
	for (int i = 0; i < n; i++){
		fscanf(f,"%d%d", &activitati[i].s, &activitati[i].f);
		fgets(activitati[i].nume, 100, f);
	}
	fclose(f);

	int x[100];
	for (int i = 0; i < n; i++)
        x[i] = 0;
	int nr_activitati = 0;
	select_activitati(x, &nr_activitati);
	afisare(x, nr_activitati);
	return 0;
}
