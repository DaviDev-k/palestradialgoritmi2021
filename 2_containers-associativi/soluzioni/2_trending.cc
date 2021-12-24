// https://training.olinfo.it/#/task/ois_trending/statement

#include <bits/stdc++.h>

using namespace std;

void scan(int &n);

void scan(string &s);

void println(string s);


int main(int argc, char **argv) {
	if (argc > 1) { (void) !freopen(argv[1], "r", stdin); }
	
	int N, T;
	scan(N);
	scan(T);
	
	int i = 0;  // iteratore che scorre gli intervalli [0, T) e [T, N]
	string t;   // nome del topic
	
	deque <string> q;                             // coda dei trending topics degli ultimi T secondi
	unordered_map<string, int> counter;           // contatore delle occorrenze di ogni topic presente nella coda
	map<int, set<string>, greater<int>> buckets;  // associa il set di topic con lo stesso conteggio al conteggio stesso
	/*
	 * buckets[count] = {t | counter[t] == count}  (tutti i topics con conteggio pari a count)
	 * buckets mantiene gli interi in ordine decrescente e le stringhe in ordine crescente
	 */
	
	/* Inserisci i primi T topics */
	for (; i < T; i++) {
		scan(t);
		counter[t]++;    // incrementa il conteggio per il topic `t`, inseriscilo se non presente
		q.push_back(t);  // aggiungi `t` nella coda temporale
	}
	for (auto &t: q) { buckets[counter[t]].insert(t); }  // aggiungi `t` al bucket con chiave il conteggio di `t`
	
	for (; i <= N; i++) {  // rimanenti N - T topics
		
		/* map e set ordinati: dei topic con la maggiore occorrenza, stampane il minore */
		println(*(buckets.begin()->second.begin()));  // prima stringa del primo set
		
		/* Rimuovi topic vecchio */
		t = q.front();                                                   // topic più vecchio
		buckets[counter[t]].erase(t);                                    // rimuovi `t` dal bucket del suo conteggio
		if (buckets[counter[t]].empty()) { buckets.erase(counter[t]); }  // ripulisci il bucket se vuoto
		counter[t]--;                                                    // decrementa il conteggio di `t`
		if (counter[t] > 0) { buckets[counter[t]].insert(t); }           // inserisci `t` nel bucket del suo conteggio
		else { counter.erase(t); }                                       // rimuovi `t` da counter se non più nella coda
		
		/* Aggiungi topic nuovo */
		scan(t);
		if (counter[t] > 0) {  // se `t` era già presente nella coda, rimuovi `t` dal bucket del suo conteggio
			buckets[counter[t]].erase(t);
			if (buckets[counter[t]].empty()) { buckets.erase(counter[t]); }
		}
		counter[t]++;                   // incrementa il conteggio di `t`
		buckets[counter[t]].insert(t);  // inserisci `t` nel bucket del suo nuovo conteggio
		q.push_back(t);                 // inserisci `t` in coda a `q`
		q.pop_front();                  // rimuovi il topic più vecchio dalla coda
	}
}


/*
 * NOTE:
 *
 * - In questo problema, a differenza di 1_trap.cc, viene utilizzata una mappa per contare le occorrenze, poiché un
 *   multiset non permetterebbe la rimozione di una singola chiave, ma le eliminerebbe tutte
 *
 * - `begin()` è un iterator, ovvero un puntatore ad un dato dello stesso tipo dei valori contenuti nella collection a
 *   cui si riferisce; essendo un puntatore, per accedere al valore puntato bisogna dereferenziarlo con l'operatore `*`;
 *   similmente l'operatore `->` serve per accedere al campo di un puntotore, che altrimenti andrebbe dereferenziato:
 *   (pointer->field == *(pointer).field) (riga 43)
 *
 * - `q` è memorizzato come deque invece che come queue per permetterne l'iterazione
 *
 * - Utilizzare una variabile iteratore dichiarata esternamente ai cicli (`i`) è molto utile se serve suddividere
 *   l'iterazione lungo uno stessa sequenza in più intervalli consecutivi ([0, T) e [T, N])
 *
 */


void scan(int &n) {
	n = 0;
	bool neg = false;
	char c = getchar();
	while (!(c == '-' || (c >= '0' && c <= '9'))) { c = getchar(); }
	if (c == '-') {
		neg = true;
		c = getchar();
	}
	for (; !feof(stdin) && c >= '0' && c <= '9'; c = getchar()) {
		n = n * 10 + c - '0';
	}
	if (neg) { n *= -1; }
}

void scan(string &s) {
	s = "";
	char c = getchar();
	while (c == ' ' || c == '\n' || c == '\t') { c = getchar(); }
	for (; !feof(stdin) && c != ' ' && c != '\n' && c != '\t'; c = getchar()) {
		s += c;
	}
}

void println(string s) {
	for (int i = 0; s[i] != 0; i++) { putchar(s[i]); }
	putchar('\n');
}
