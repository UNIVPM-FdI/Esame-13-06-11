#include <iostream>
using namespace std;
struct da_fare {
    char compito[80];
    struct{//sottostruttura che comprende giorni,mesi,anni.
        short int g;
        short int m;
        short int a;
    }scade;
    da_fare* succ;
};
typedef da_fare* lista;

bool SottoStringa(char*, char*);
bool antecedente(da_fare, da_fare);
void visualizza_compito(da_fare a);
void immetti_compito(da_fare&);
void nuovo_compito(lista&,da_fare);
bool elimina_primo(lista&,da_fare&);
bool elimina_compito(lista&,da_fare&);
void visualizza_tutti(lista p0);

int main(){
    lista compiti=0;
    da_fare elem;
    char r;
    do{
        cout<<"MENU"<<endl;
        cout<<"a: aggiungi un nuovo compito da svolgere"<<endl;
        cout<<"u: elimina il compito più urgente"<<endl;
        cout<<"e: elimina un particolare elemento"<<endl;
        cout<<"v: visualizza tutti i compiti da svolgere"<<endl;
        cout<<"scelga"<<endl;
        cin>>r;
        cin.get();//riaggera il flusso di ingresso
        switch(r){
        case 'a':{
            immetti_compito(elem);
            nuovo_compito(compiti,elem);
        break;
        }
        case 'u':{
            elimina_primo(compiti,elem);
            visualizza_compito(elem);
            break;
        }
        case 'e':{
            cout<<"Immetti un testo contenuto nel compito da eliminare:"<<endl;
            cin.getline(elem.compito,80);
            elimina_compito(compiti,elem);
            break;
        }
        case 'v':{
            visualizza_tutti(compiti);
            break;
        }
        }
    }while(r=='a'||r=='u'||r=='e'||r=='v');
    return 0;
}

bool SottoStringa(char stringa[], char sottostringa[]){
short int i=0,j=0;
bool flag=false;
while(sottostringa[j]!='\0'){
    if(stringa[i]==sottostringa[j]){
        flag=true;
        i++;
        j++;
    }
    else
        i++;
}
if (flag) return true;
else return false;
}

bool antecedente(da_fare a,da_fare b){
bool flag=false;
if(b.scade.a<=a.scade.a)flag=true;{
    if(b.scade.m<=a.scade.m) flag=true;{
        if(b.scade.g<=a.scade.g)flag=true;{
        }
    }
}
if(flag)return true;
else return false;
}

void visualizza_compito(da_fare a){
cout<<a.compito<<" "<<"entro il"<<endl;;
cout<<a.scade.g<<" "<<a.scade.m<<" "<<a.scade.a<<endl;
}

void immetti_compito(da_fare& a){
cout<<"inserisci il nome del compito"<<endl;
cin.getline(a.compito,80);
cout<<"inserisci l anno"<<endl;
cin>>a.scade.a;
cout<<"inserisci il mese"<<endl;
cin>>a.scade.m;
cout<<"inserisci il giorno"<<endl;
cin>>a.scade.g;
}

void nuovo_compito(lista& inizio, da_fare e){
lista p = 0, q, r;
for (q=inizio; q!=0 && antecedente(*q,e); q = q->succ)//ordina per data tramite antecedente
p = q;
r = new da_fare;
*r=e;//==r->compito=e.compito;r->scade.a=e.scade.a;r->scade.m=e.scade.m;r->scade.g=e.scade.g;//Copia tutti i valori di
r->succ = q;
if (q == inizio) inizio= r;
else p->succ = r;
}

bool elimina_primo(lista& inizio, da_fare& e){
lista p = inizio;
if (p == 0) return false;
e = *p;
inizio = p->succ;
delete p;
return true;
}

bool elimina_compito(lista& inizio, da_fare& a){
lista p, q;
for (q = inizio; q!=0 && !SottoStringa(q->compito,a.compito); q=q->succ)//trova i file in base alla parola chiave
p = q;
if (q == 0) return false;
if (q == inizio) inizio = q->succ;
else p->succ = q->succ;
a = *q;
delete q;
cout<<"ho eliminato"<<endl;
visualizza_compito(a);
return true;
}

void visualizza_tutti(lista p0){//stampa tutti i valori della lista
while(p0!=0){
    visualizza_compito(*p0);
    p0=p0->succ;
}
}

//coded by DarkCerfa
