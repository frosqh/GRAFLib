#include <math.h>
#include "graph.h"
#include "list.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y));

struct amel {
	int succes;
	int *chn;
	int *orig;
	int *ec;
	int source;
	int queue;
};

struct val_flot {
	int **flot;
	int val;
};

struct val_flot maj_flot(int F, int** flot, struct Graph g, struct amel chaine_amel){
	int queue = chaine_amel.queue;
	int delta = chaine_amel.ec[queue];
	int newF = F + delta;
	while (true){
		int nc = chaine_amel.chn[queue];
		int np = chaine_amel.orig[queue];
		if (np>0){
			flot[np][nc] = flot[np][nc]+delta;
		} else {
			np = -np;
			flot[nc][np] = flot[nc][np]+delta;
		}
		if (np == chaine_amel.source){
			break;
		}
		queue--;
		while (chaine_amel.chn[queue] != np){
			queue--;
		}
	}
	struct val_flot val;
	val.val = newF;
	val.flot = flot;
	return val;
}

int flot_max(struct Graph g, int source, int puit, struct amel (*f)(struct Graph,int**,int,int)){
	int N = g.nbMaxNodes+1;
	int i,j;	
	int *flot[N]; 
    for (i=0; i<N; i++) 
         flot[i] = (int *)malloc(N * sizeof(int)); 
	int F = 0;

	//Init flot
	for (i = 0;i<N;i++){
		for (j = 0;j<N;j++){
			flot[i][j] = 0;
		}
	}
	F = 0;

	//Passed ! 

	int chn[N];
	int orig[N];
	int ec[N];
	for (i = 0;i<N;i++){
		chn[i] = 0;
		orig[i] = 0;
		ec[i] = 0;
	}

	//Passed ! 

	int succes;

	while (true){
		struct amel chaine_amel = f(g,flot,source,puit);
		if (chaine_amel.succes){
			struct val_flot val = maj_flot(F, flot, g, chaine_amel);
			for (i = 0;i<N;i++){
				for (j = 0;j<N;j++){
					flot[i][j] = val.flot[i][j];
				}
			}
			F = val.val;
		} else {
			break;
		}
	}

	return F;
}

struct amel firstAmel(struct Graph g, int** flot,  int source, int puit){
	int N = g.nbMaxNodes+1;
	int *chn = malloc(N * sizeof(int));
	int *orig = malloc(N * sizeof(int));
	int *ec = malloc(N * sizeof(int));
	int *marque = malloc(N * sizeof(int));

	//Passed ! 

	int i;
	for (i = 0 ; i< N;i++){
		chn[i] = 0;
		orig[i] = 0;
		ec[i] = 0;
		marque[i] = 0;
	}

	//Passed ! 

	int succes = 0;
	int head = 1;
	int queue = 1;
	chn[1] = source;
	orig[1] = NAN;
	ec[1] = INFINITY;
	marque[source] = 1;

	//Passed

	while (!succes && queue-head>=0){
		int nc = chn[head];
		struct cchainedList** ls = g.list;
		struct cchainedList* l = ls[nc];
		l = l->next;
		while (l->value != -1){
			int nn = l->value;
			if (!marque[nn] && flot[nc][nn] < l->secondValue){
				marque[nn] = 1;
				chn[queue+1] = nn;
				queue++;
				orig[queue] = nc;
				ec[queue] = MIN(ec[head],l->secondValue-flot[nc][nn]);
								if (nn==puit){
					succes = 1;
					break;
				}
			}
			l = l->next;
		}
		head++;
	}

	struct amel chaine_amel;
	chaine_amel.succes = succes;
	chaine_amel.chn = chn;
	chaine_amel.orig = orig;
	chaine_amel.ec = ec;
	chaine_amel.source = source;
	chaine_amel.queue = queue;
	return chaine_amel;

}

int main(char args[]){
	struct Graph g = createGraph(6,true);
	addNode(g,1);
	addNode(g,2);
	addNode(g,3);
	addNode(g,4);
	addNode(g,5);
	addNode(g,6);
	addEdge(g,1,2,16);
	addEdge(g,1,3,13);
	addEdge(g,2,3,10);
	addEdge(g,3,2,4);
	addEdge(g,2,4,12);
	addEdge(g,4,3,9);
	addEdge(g,3,5,14);
	addEdge(g,5,4,7);
	addEdge(g,4,6,20);
	addEdge(g,5,6,4);
	printf("%d\n",flot_max(g,1,6,firstAmel));
}