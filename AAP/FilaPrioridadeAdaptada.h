struct no {
    int info;
    int prior;
    int tipo;
    no *link;
};

no *inicializaFP(no *L)
{
    L = NULL;
    return L;
}

no *insereFP(no *L, int valor, int prior)
{
    no *N, *P, *ANT;

    N = new no;
    N->info = valor;
    N->prior = prior;

    if (L == NULL) {
        L = N;
        N->link = NULL;
    }
    else {
        P = L;

        while ((P != NULL) && (prior >= P->prior)) {
            ANT = P;
            P = P->link;
        }
        if (P == L) {
            N->link = L;
            L = N;
        }
        else {
            ANT->link = N;
            N->link = P;
        }
    }
    return L;
}

no *removeFP(no *L, int *n, int * prior) {
	no *AUX;

	if (L != NULL) {
		*n = L->info;
		*prior = L->prior; 
		AUX = L;
		L = L->link;
		delete AUX;
	}
	return L;
}

void exibe(no *L)
{
    no *P = L;
    cout << " ";
    while (P != NULL) {
		cout << "Voo " << P->info << " (" << P->prior << ") |";
        P = P->link;
    }
}
