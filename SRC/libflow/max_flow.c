#include "max_flow.h"


int maj_flot(int F, int** flot, struct Graph g, struct amel chaine_amel){
	int queue = chaine_amel.queue;
	int delta = chaine_amel.ec[queue];
	int newF = F + delta;
	int nc;
	int np;
	do {
		nc = chaine_amel.chn[queue];
		np = chaine_amel.orig[queue];
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
	while (np!=chaine_amel.source);
	return newF;
}

int flot_max(struct Graph g, int source, int puit, struct amel (*f)(struct Graph,int**,int,int,int** (*f)(struct Graph,int**,int,int)), int** (*f2)(struct Graph,int**,int,int)){
	int N = g.nbMaxNodes+1;
	int i,j;	
	int *flot[N]; 
    for (i=0; i<N; i++) 
         flot[i] = (int *)malloc(N * sizeof(int)); 
	int F = 0;
	for (i = 0;i<N;i++){
		for (j = 0;j<N;j++){
			flot[i][j] = 0;
		}
	}
	F = 0;
	struct amel chaine_amel;

	while (true){
		if (chaine_amel.chn != NULL){
			free(chaine_amel.chn);
			free(chaine_amel.orig);
			free(chaine_amel.ec);
		}
		chaine_amel = f(g,flot,source,puit,f2);
		if (chaine_amel.succes){
			F = maj_flot(F, flot, g, chaine_amel);
		} else {
			break;
		}
	}

	for (i = 0;i<N;i++){
		free(flot[i]);	
	}

	free(chaine_amel.chn);
	free(chaine_amel.orig);
	free(chaine_amel.ec);

	return F;
}

struct amel bfsMethod(struct Graph g, int** flot,  int source, int puit, int** (*f)(struct Graph,int**,int,int)){
	int N = g.nbMaxNodes+1;
	int *chn = malloc(N * sizeof(int));
	int *orig = malloc(N * sizeof(int));
	int *ec = malloc(N * sizeof(int));
	int *marque = malloc(N * sizeof(int));

	int i;
	for (i = 0 ; i< N;i++){
		chn[i] = 0;
		orig[i] = 0;
		ec[i] = 0;
		marque[i] = 0;
	}

	int succes = 0;
	int head = 1;
	int queue = 1;
	chn[1] = source;
	orig[1] = NAN;
	ec[1] = INFINITY;
	marque[source] = 1;

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

	free(marque);

	struct amel chaine_amel;
	chaine_amel.succes = succes;
	chaine_amel.chn = chn;
	chaine_amel.orig = orig;
	chaine_amel.ec = ec;
	chaine_amel.source = source;
	chaine_amel.queue = queue;
	return chaine_amel;

}

struct amel shortestMethod(struct Graph g, int** flot, int source, int puit, int** (*f)(struct Graph,int**,int,int)){
	int N = g.nbMaxNodes+1;
	int *chn = malloc(N*sizeof(int));
	int *orig = malloc(N*sizeof(int));
	int *ec = malloc(N*sizeof(int));
	int *marque = malloc(N*sizeof(int));

	int i;
	for (i = 0 ; i< N;i++){
		chn[i] = 0;
		orig[i] = 0;
		ec[i] = 0;
		marque[i] = 0;
	}
	ec[0] = INFINITY;

	int ** chm = f(g, flot, source, puit);

	i = 0;
	while (chm[i][0] != -1){
		i++;
	}

	i--;
	int im = i+1;

	while (i>=0){
		chn[im-i]=chm[i][0];
		orig[im-i]=chm[i+1][0];	
		ec[im-i]=MIN(ec[im-i-1],chm[i][1]);
		i--;
	}

	struct amel chaine_amel;
	chaine_amel.succes = (chm[0][0] != -1);
	chaine_amel.chn = chn;
	chaine_amel.orig = orig;
	chaine_amel.ec = ec;
	chaine_amel.source = source;
	chaine_amel.queue = im;

	for (i = 0;i<N;i++){
		free(chm[i]);
	}

	free(chm);
	free(marque);

	return chaine_amel;
}

int** djikstra(struct Graph g, int** flot, int source, int puit){

	int N = g.nbMaxNodes+1;

	int *marque = malloc(N*sizeof(int));
	int *dist = malloc(N*sizeof(int));
	int *p = malloc(N*sizeof(int));
	int *d = malloc(N*sizeof(int));

	for (int i = 0;i<N;i++){
		marque[i] = 0;
		dist[i] = INFINITY;
		p[i] = NAN;
		d[i] = 0;
	}

	dist[source] = 0;
	p[source] = -1;
	d[source] =  INFINITY;

	int finished = 0;

	while (!finished){

		int a = -1;
		int m = INFINITY;
		for (int i = 1; i<N; i++){
			if (!marque[i] && dist[i] < m){
				a = i;
				m = dist[i];
			}		
		}

		if (a == -1){
			free(marque);
			free(dist);
			free(p);
			free(d);

			int **chm = malloc(N*sizeof(int*));
			chm[0] = malloc(2*sizeof(int));
			chm[0][0] = -1;
			return chm;
		}

		marque[a]=1;
		struct cchainedList* l = g.list[a]->next;
		while (l->value != -1){
			if (!marque[l->value]){
				if (l->secondValue-flot[a][l->value] >0 && dist[a]+(l->secondValue-flot[a][l->value]) < dist[l->value]){
					dist[l->value] = dist[a]+(l->secondValue-flot[a][l->value]);
					d[l->value] = (l->secondValue-flot[a][l->value]);
					p[l->value] = a;
				}
			}
			l = l->next;
		}

		finished = 1;
		for (int i = 1;i<N;i++){
			finished = finished && marque[i];
		}
	}

	int **chm = malloc(N*sizeof(int*));

	int current = puit;
	int i = 0;

	while (p[current] != -1){
		chm[i] = malloc(2*sizeof(int));
		chm[i][0] = current;
		chm[i][1] = d[current];
		current = p[current];
		i++;
	}

	chm[i] = malloc(2*sizeof(int));
	chm[i][0] = current;
	chm[i][1] = d[current];

	i++;

	chm[i] = malloc(2*sizeof(int));
	chm[i][0] = -1;

	free(dist);
	free(p);
	free(d);
	free(marque);

	return chm;

}

int** floyd_warshall(struct Graph g, int** flot, int source, int puit){
	int N = g.nbMaxNodes+1;
	int W[N][N];
	int C[N][N];
	int D[N][N];

	for (int i = 1; i<N; i++){
		struct cchainedList* l = g.list[i]->next;
		for (int j = 1; j<N; j++){
			W[i][j] = -1;
			C[i][j] = -1;
			D[i][j] = 0;
		}
		while (l->value != -1){
			if (l->secondValue - flot[i][l->value] > 0){
				W[i][l->value] = l->secondValue - flot[i][l->value];
				C[i][l->value] = l->value; 
				D[i][l->value] = l->secondValue - flot[i][l->value];
			}	
			l = l->next;
		}
	}


	for (int k = 1; k<N;k++){
		for (int j = 1;j<N;j++){
			for (int i = 1;i<N;i++){
				if (W[i][k]>=0 && W[k][j]>=0){
					if (W[i][k]+W[k][j] < W[i][j] || W[i][j] <0){
						W[i][j] = W[i][k] + W[k][j];
						C[i][j] = k;
					}
				}
				
			}
		}
	}

	int **chm = malloc(N*sizeof(int*));
	int current = puit;
	int i =0;

	if (W[source][puit] == -1){
		chm[0] = (int*) malloc(2*sizeof(int));
		chm[0][0] = -1;
		return chm;
	}

	while (current != C[source][current]){
		chm[i] = (int *) malloc(2*sizeof(int));
		chm[i][0] = current;
		chm[i][1] = D[C[source][current]][current];
		if (i>0)
			current = C[source][current];
		else
			current = C[source][current];

		if ((i>0 && C[current][chm[i-1][0]] != chm[i][0])){
			chm[i][0] = C[current][chm[i-1][0]];
			chm[i-1][1] = D[chm[i][0]][chm[i-1][0]];
			chm[i][1] = D[C[source][chm[i][0]]][chm[i][0]];
			i++;
		}

		if (i==0 && C[current][puit] != puit){
			current = C[current][puit];
			chm[i][1] = D[current][puit];
		}
		i++;
	}


	prev:
	chm[i] = (int*) malloc(2*sizeof(int));
	chm[i][0] = current;
	chm[i][1] = D[source][current];
	if (i>0 && C[current][chm[i-1][0]] != chm[i][0] && C[current][chm[i-1][0]] != chm[i-1][0]){
		chm[i][0] = C[current][chm[i-1][0]];
		chm[i-1][1] = D[chm[i][0]][chm[i-1][0]];
		chm[i][1] = D[C[source][chm[i][0]]][chm[i][0]];
		i++;
		goto prev;
	}
	chm[++i] = (int*) malloc(2*sizeof(int));
	chm[i][0] = source;
	chm[i][1] = INFINITY;

	chm[++i] =(int*) malloc(2*sizeof(int));
	chm[i][0] = -1;
	chm[i][1] = -1;

	return chm;

}