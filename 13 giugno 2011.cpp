#include <iostream>
using namespace std;
struct da_fare {
char compito[80]; // descrizione del compito da svolgere
struct {short int a,m,g;} scade; // data di scadenza
da_fare* succ; // puntatore al successivo
};
typedef da_fare* lista;

/*questa funzione restituisce "true" se la stringa passata come secondo
argomento è contenuta nella stringa passata al primo argomento,
o al massimo le è identica */

bool SottoStringa(char* stringa, char* sottostringa) /* alla funzione vanno passate le due stringhe come puntatori, ma dato che nella traccia non ti obbliga 
ad usarli per forza, io uso gli array,che sono puntatori mascherati che puntano al primo elemento,essendo più comodi da usare  */
{
	int i=0;
	int d=0;
	bool c=false;
	while (stringa[i]!= '\0')
	{
	if (sottostringa[d]==stringa[i]) // non uso lo steso indice perchè finche sottostringa non è uguale a stringa faccio scorrere solo stringa
	{
		d++;i++;c=true; // invece quando sono uguali scorrono entrembi 
	}
	else i++; // se sono diversi scorre solo i(ovvero solo stringa)
	}
	if (c) return true ; // c è un valore booleano
	else return false;
}
/*questa funzione restituisce "true" se la struttura passata come secondo
argomento ha una data posteriore o identica a quella della struttura
passata come primo argomento */
bool antecedente(da_fare a, da_fare b)
{
	bool d=false,e=false,f=false;
if (b.scade.g>=a.scade.g) d=true; // verifica se il secondo giorno è maggiore ugale al primo giorno  
else d=false;
if (b.scade.m>=a.scade.m) e=true; // verifica se il secondo mese è maggiore ugale al primo mese 
 else e=false;
 if (b.scade.a>=a.scade.a) f=true; // verifica se il secondo anno è maggiore ugale al primo anno 
 else f=false;
 if (d && e && f) return true ; // essendo d,e,f booleane se mi danno tutte true la funzione restituisce true
 else return false;	 //altrimenti false
}
/* questa procedura stampa i valori dei campi della struttura passatale come
argomento
 */
void visualizza_compito(da_fare a)
{
	cout << a.compito << endl << a.scade.g << " " << a.scade.m << " " << a.scade.a << endl;
}
/* questa procedura chiede all'utente di inserire i valori del nuovo compito
che si sta per introdurre nella lista e riempie quindi di contenuto i campi
della struttura passatale per riferimento leggendoli dalla tastiera
NB: la descrizione del compito può contenere spazi bianchi, quindi è bene
usare la funzione cin.getline() */
void immetti_compito(da_fare& a)
{
	cout << "Inserisci il compito da svolgere\n";
	cin.getline(a.compito,80);
	cout << "Inserisci giorno mese ed anno di scadenza\n";
	cin >> a.scade.g >> a.scade.m >> a.scade.a;
}
/* questa procedura realizza l'inserimento ordinato del nuovo compito passato
al secondo argomento, secondo il valore del campo scade
NB: per l'inserimento si utilizzi la funzione
bool antecedente(da_fare a, da_fare b)
 */
void nuovo_compito(lista& inizio, da_fare e)
{
	lista p=0,q,d;
	for (q=inizio; q!=0 && antecedente(*q,e);q=q->succ) p=q; // q viene passato dereferenziato, in questo modo restituirà il valore
	d = new da_fare;
	*d=e;
	d->succ=q;
	if (q==inizio) inizio=d;
	else p->succ=d; 
}
/* questa funzione elimina il primo elemento della lista dopo averne ricopiato
i valori nella struttura passatale per riferimento al secondo argomento
NB: la funzione restituisce false sse la lista è vuota  */
bool elimina_primo(lista& inizio, da_fare& e)
{
		lista q=inizio;
		if (q==0) return false;
		e=*q;
		 inizio=q->succ;
		 delete q;
		 return true;
}
/* questa funzione elimina dalla lista l'elemento il cui campo compito
contiene la stringa del campo compito della struttura passata al secondo
argomento; prima di eliminare l'elemento copia i suoi valori nella
struttura passata per riferimento al secondo membro
NB: la funzione restituisce false sse l'elemento non esiste */
bool elimina_compito(lista& inizio, da_fare& e)
{
	lista p,q;
	for (q=inizio; q!=0 && !SottoStringa(q->compito,e.compito);q=q->succ) p=q;
	if (q==0) return false;
	if (q==inizio) inizio=q->succ;
	else p->succ=q->succ;
	e=*q;
	delete q;
	return true;
}
/*questa procedura stampa i valori di tutti gli elementi della lista
iniziando dal primo, uno per ogni riga */
void visualizza_tutti(lista p)
{
	while (p!=0) // qui ho usato la procedura standard per stampare una lista, invece il prof utilizza la funzione visualizza compito per stamparla
	{
	cout << p->compito << " entro il " << p->scade.g << " " << p->scade.m << " " << p->scade.a << endl;
	p=p->succ;
}
}
int main ()
{
char r;
lista compiti = 0; // inizializzo la lista
da_fare el; // variabile della struct
	cout << "Salve! Ecco quello che puoi fare:\na: aggiungi un nuovo compito da svolgere\n" 
<< "u: elimina il compito piu' urgente\ne: elimina un particolare elemento\nv: visualizza tutti i compiti da svolgere " << endl;
	do{
	cin >> r;
    cin.get(); //in questo modo ho il cin pulito, altrimenti nel getline avrebbe preso l'ultimo carattere del cin di sopra
 switch (r)
 {
 	case 'a' : { 
		immetti_compito(el);
		nuovo_compito(compiti,el);
	 } break;
	 case 'u' : {
	 elimina_primo(compiti,el);
	 cout << "Eliminato: " << el.compito << endl;
	 }break;
	 case 'e' :
	 	{
	 		cout << "Immetti un testo contenuto nel compito da eliminare: " ;
	 		cin >> el.compito;
		 	elimina_compito(compiti,el);
		 	cout << "Eliminato: " << el.compito << endl;
		 
	 	//else cout << "il compito non e' presente nella lista" << endl;
		 } break;
		 case 'v' : {
		 	visualizza_tutti(compiti);
		 }break;
 }
 } while (r== 'a' || r== 'u' || r== 'e' || r== 'v' );
 return 0;
}

