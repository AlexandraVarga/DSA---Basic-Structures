#include <stdio.h>
#include <math.h>
#include <limits.h>

//structura de data pt graf, matrice de adiacenta
double dist[100][100]; //distante dintre noduri
//nodurile grafului sunt puncte
typedef struct {
	double x, y;
} point;
point pts[100];
//nr de puncte/noduri
int n;
double optimal_sol;

#define DOUBLE_MAX 1.79769e+308

int search(int x[], int k)
{
    for (int i = 0; i < n; i++)
        if (x[i] == k)
            return 1;
    return 0;
}

void tsp_greedy(int x[]){
	//x[0], x[1], ..., x[n-1] contine o permutare a multimii 1:n
	for (int i = 0; i < n; i++)
		x[i] = 0;
    x[0] = 1;
    int length = 1;
    int k;
    while (length < n)
    {
        double minim = DOUBLE_MAX;
        for (int i = 1; i <= n; i++)
            if (dist[x[length-1]][i] <  minim && i != x[length-1] && search(x, i) == 0)
            {
                k = i;
                minim = dist[x[length-1]][i];
            }
        x[length] = k;
        length++;
    }
}

void afisare(int x[]){
	double tour_length = 0;

	for (int i = 0; i < n-1; i++){
		printf("%d - ", x[i]);
		tour_length += dist[x[i]][x[i + 1]];
	}
	tour_length += dist[x[n - 1]][x[0]];
	printf("%d - %d\n", x[n-1], x[0]);
	printf("tour length     = %f\n", tour_length);
	printf("optimal length  = %f\n", optimal_sol);
}

double euclidean_dist(int i, int j){
	return sqrt((pts[i].x - pts[j].x)*(pts[i].x - pts[j].x) + (pts[i].y - pts[j].y)*(pts[i].y - pts[j].y));
}

int main(){

	FILE* f = fopen("date_tsp.txt", "r");
	int dummy;
	fscanf(f,"%d", &n);
	for (int i = 1; i <= n; i++){
		fscanf(f,"%d%lf%lf", &dummy, &pts[i].x, &pts[i].y);
	}
	fscanf(f, "%lf", &optimal_sol);
	fclose(f);
	for (int i = 1; i <= n; i++){
		for (int j = i + 1; j <= n; j++){
			dist[i][j] = euclidean_dist(i, j);
			dist[j][i] = dist[i][j];
		}
	}

	int x[100];
	tsp_greedy(x);
	afisare(x);
	return 0;
}
