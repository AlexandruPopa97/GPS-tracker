//POPA ALEXANDRU GABRIEL 314AB
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

struct punct
{
	int x;								//Pentru fiecare locatie am un set de coordonate pe care le-am salvat
	int y;								//sub forma acestei structuri
};
typedef struct punct pct;
int main(int argc,char **argv)
{
	int x1,x2,x3,y1,y2,y3,r1,r2,r3;
	int nr,i,j,k,locatie1,locatie2;
	int **m,X,Y,i1,i2,D,*cost,*parinte,cost_temp;
	pct *a;
	char nume_locatie[16],nume_satelit[16],*c,**v;
	FILE *Coordonate,*Avarii,*Coordonate_Finale,*Rezultat;


	Coordonate = fopen(argv[1],"rt");
	if(Coordonate == NULL)
	{
		printf("Fisierul coordonate.in nu a putut fi deschis!");
		exit(1);
	}
	Coordonate_Finale = fopen(argv[4],"wt");
	if(Coordonate_Finale == NULL)
	{
		printf("Fisierul coord_finale.out nu a putut fi deschis!");
		exit(1);
	}


	fscanf(Coordonate,"%d",&nr);
	a = (pct*)malloc(nr*sizeof(pct));				//a este un vector de structuri al carei componente sunt coordonatele
	v = (char**)malloc(nr*sizeof(char*));			//fiecare locatii
	for(i=0;i<nr;i++)								//v este o matrice pentru stringuri sa pot tine cont care
		v[i] = (char*)malloc(16*sizeof(char));		//este locatia spre a caruit drum este cerut
	for(i=0;i<nr;i++)	
	{
		fscanf(Coordonate,"%s",nume_locatie);
		strcpy(v[i],nume_locatie);
		fscanf(Coordonate,"%s",nume_satelit);
		fscanf(Coordonate,"%d%d%d",&x1,&y1,&r1);
		fscanf(Coordonate,"%s",nume_satelit);
		fscanf(Coordonate,"%d%d%d",&x2,&y2,&r2);
		fscanf(Coordonate,"%s",nume_satelit);
		fscanf(Coordonate,"%d%d%d",&x3,&y3,&r3);
		i1 = r2*r2-r1*r1+x1*x1-x2*x2+y1*y1-y2*y2;
		i2 = r3*r3-r1*r1+x1*x1-x3*x3+y1*y1-y3*y3;
		D = 4*(x1-x2)*(y1-y3)-4*(y1-y2)*(x1-x3);
		X = (2*i1*(y1-y3) - 2*i2*(y1-y2))/D;
		Y = (2*i2*(x1-x2) -2*i1*(x1-x3))/D;
		a[i].x = X;
		a[i].y = Y;
		fprintf(Coordonate_Finale,"%d %d\n",X,Y);			//imediat dupa ce am calculat coordonatele cerute le-am si
	}														//scris in fisierul coord_finale.out


	m = (int**)malloc(nr*sizeof(int*));
	for(i=0;i<nr;i++)
		m[i] = (int*)malloc(nr*sizeof(int));			//matricea m este matricea de adicenta care contine costurile
	for(i=0;i<nr;i++)									//adica distanta dintre puncte
		for(j=0;j<nr;j++)
		{
			m[i][j] = sqrt( (a[i].x - a[j].x)*(a[i].x - a[j].x) + (a[i].y - a[j].y)*(a[i].y - a[j].y) );
		}


	Avarii = fopen(argv[2],"rt");
	if(Avarii == NULL)
	{
		printf("Fisierul avarii.in nu a putut fi deschis!");
		exit(1);
	}
	while(fscanf(Avarii,"%s",nume_locatie) != EOF)			//avariile le reprezint cu valorea 9999 in matricea de adiacenta
	{
		for(i=0;i<nr;i++)
		{
			if(strcmp(v[i],nume_locatie) == 0)
				locatie1 = i;
		}
		fscanf(Avarii,"%s",nume_locatie);
		for(i=0;i<nr;i++)
		{
			if(strcmp(v[i],nume_locatie) == 0)
				locatie2 = i;
		}
		m[locatie1][locatie2] = 9999;
		m[locatie2][locatie1] = 9999;
	}
	fclose(Avarii);


	cost = (int*)malloc(nr*sizeof(int));
	parinte = (int*)malloc(nr*sizeof(int));			//aloc memorie pentru 2 vectori pe care ii voi folosii in algoritmul
	cost[0] = 0;									//bellman-ford pentru a calcula drumul de cost minim
	for(i=1;i<nr;i++)
	{
		cost[i] = 9999;
		parinte[i] = 0;
	}



	for(j=0;j<nr;j++)
		for(k=0;k<nr;k++)
			{
					cost_temp = cost[j] + m[j][k];			//acesta este algoritmul bellman-ford
				if(cost_temp < cost[k])
				{
					cost[k] = cost_temp;
					parinte[k] = j;
				}
			}



	Rezultat = fopen(argv[5],"wt");
	if(Rezultat == NULL)
	{
		printf("fisierul rezultat nu a putut fii creeat!");
		exit(1);
	}
	for(i=0;i<nr;i++)
		if(strcmp(argv[3],v[i]) == 0)				//in final scriu in fisierul rezultat.out valoarea drumului cerut
			fprintf(Rezultat,"%d",cost[i]);



	free(cost);
	free(a);
	for(i=0;i<nr;i++)
		free(v[i]);
	free(v);						//eliberez memorie si inchid fisierele folosite
	for(i=0;i<nr;i++)
		free(m[i]);
	free(m);
	free(parinte);
	fclose(Rezultat);
	fclose(Coordonate_Finale);
	fclose(Coordonate);
	return 0;
}
