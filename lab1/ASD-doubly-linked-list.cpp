// FILE DA MODIFICARE
#include <iostream>
#include <fstream>
#include "ASD-doubly-linked-list.h"

using namespace list;
using namespace std;

/*Descrizione da come e' fatta  la struttura node. */
/*I dettagli interni non saranno visibili dal main*/
struct list::node {  
  Elem info;
  node *prev;
  node *next;
};

/**************************************************/
/*      funzioni da implementare                    */
/**************************************************/
  
/* crea la lista vuota */
void list::createEmpty(List& li){
  li = new node;
  li->next = li;
  li->prev = li;
}

/* "smantella" la lista (tranne la sentinella) */
void list::clear(List& li){
  li->next = NULL;
  li->prev = NULL;
}

/* restituisce true se la lista e' vuota */
bool list::isEmpty(const List& li){
  return li->next == li;
}

/* restituisce la dimensione della lista */
unsigned int list::size(const List& li){
  unsigned int tmp = 0;
  List cur = li->next;
  while (cur != li) {   
    tmp++;
    cur= cur->next;
  }
  return tmp;
}

/* restituisce l'elemento in posizione pos */
/* se pos non e corretta, solleva una eccezione di tipo string*/
Elem list::get(unsigned int pos, const List& li){
  if (pos <0 || pos >= size(li)) 
  throw string("posizione non corretta");
  List cur = li->next;
  for(int i=0; i<pos; i++){
    cur= cur->next;
  }
  return cur->info;
}


/* modifica l'elemento in posizione pos */
/* se pos non e' corretta, solleva una eccezione di tipo string*/
void list::set(unsigned int pos, Elem el, const List& li){
  if (pos <0 || pos >= size(li))
  throw string("posizione non corretta");
  List cur = li->next;
  for(int i=0; i<pos; i++){
    cur= cur->next;
  } 
  cur->info = el;
}

/* inserisce l'elemento in posizione pos*/
/*shiftando a destra gli altri elementi */
/*se pos non e' corretta, solleva una eccezione di tipo string*/
void list::add(unsigned int pos, Elem el, const List& li){
  if (pos < 0 || pos > size(li))
  throw string("posizione non corretta");
  List cur = li;
  for(int i=0; i < pos; i++){
    cur= cur->next;
  }
  List nuovalista= new node;
  nuovalista->info=el;
  nuovalista->prev=cur;
  nuovalista->next=cur->next;
  cur->next->prev=nuovalista;
  cur->next=nuovalista;
  }

/* inserisce l'elemento alla fine della lista */
void list::addRear(Elem el, const List& li){
  List cur = li->prev;
  List nuovalista= new node;
  nuovalista->info=el;
  nuovalista->prev=cur;
  nuovalista->next=li;
  cur->next=nuovalista;
  li->prev=nuovalista;
}

/* inserisce l'elemento all'inizio della lista */
void list::addFront(Elem el, const List& li) {
  List cur = li->next;
  List nuovalista= new node;
  nuovalista->info=el;
  nuovalista->next=cur;
  nuovalista->prev=li;
  cur->prev=nuovalista;
  li->next=nuovalista;
}

/* cancella l'elemento in posizione pos dalla lista */
/* se pos non e' corretta, solleva una eccezione di tipo string*/
void list::removePos(unsigned int pos,const List& li){
	if (pos < 0 || pos > size(li))
  throw string("posizione non corretta");
  List cur = li->next;
  for(int i=0; i<pos; i++){
    cur= cur->next;
  }
  cur->prev->next = cur->next;
  cur->next->prev = cur->prev;
}

/* cancella tutte le occorrenze dell'elemento elem*/
/*se presenti, dalla lista */
void list::removeEl(Elem el,const List& li){
  List cur = li->next;
  for(int i =0 ; i < size(li); i++){
    if(cur->info==el){
      cur->prev->next = cur->next;
      cur->next->prev = cur->prev;
    }
  }
  cur=cur->next;
}

/**************************************************/
/*      funzioni implementate                    */
/**************************************************/
  
/* riempie una lista da file */
void list::readFromFile(string name_file, const List& li){
  ifstream infile;
  string read_data;
  infile.open(name_file);
  while (getline (infile,read_data)){
    if(read_data.length()>0){
      addRear(stoi(read_data),li);
    }
  }
}

/* riempie una lista da standard input */
void list::readFromStdin(const List& li){
  cout << "Inserire una sequenza di numeri separati da spazi seguiti da END per terminare\n";
  string read_data;
  cin>>read_data;
  while(read_data!="END"){
    addRear(stoi(read_data),li);
    cin>>read_data;
  }
}

/* stampa la lista */
void list::print(const List& li){
  if(li==li->next){
    cout<<"vuota";
  }
  List cur = li->next;  // q "salta la sentinella" e va alla testa della lista
  while (cur != li) {   
    cout << cur->info;
    cur= cur->next;
    if(cur!=li) cout<<" <-> ";
  }
  cout<<endl;
}

/* produce una string contenendo la lista*/
std::string list::tostring(const List& li){
  string out="";
  if(li==li->next){
    out+="vuota";
  }
  List cur = li->next;  // q "salta la sentinella" e va alla testa della lista
  while (cur != li) {   
    out+=to_string(cur->info);
    cur= cur->next;
    if(cur!=li) out+=" <-> ";
  }
  return out;
}
