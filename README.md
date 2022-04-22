MATRICOLA:875377
DOCUMENTAZIONE PROGETTO

Assunzione: verificare che nel sistema sia installato gcc.

Per iniziare, compila i file e ottieni l'eseguibile vm digitando il comando
make

Eseguendo invece 
make clean 
si ha la possibilità di eliminare i file oggetto precedentemente creati con il comando make

-vm.c: è il file sorgente contenete il main del nostro programma. Dentro al main vengono richiamati esegui e stampa, ovvero i due comandi che possono essere eseguiti sui file .cvm. Stampa ed esegui sono contenuti in stampa.c ed esegui.c (gli altri due file sorgenti).
vm.c da errore nel caso i numeri dei parametri da riga di comando non siano 3 e non siano quelli adibiti al funzionamento del programma. Deve quindi per forza esserci il seguente formato ogni volta che lanciamo un comando da terminale: 
./vm stampa file.cvm
./vm esegui file.cvm


-leggi.c: è il file sorgente dalla quale viene tradotto il codice assembly scritto riga per riga all'interno del file in un "formato" a noi manipolabile. Nella funzione read viene innanzitutto letta la dimensione dell'array che dovremo andare a creare leggendo la prima riga del file significativa (no lettere né ;), fino a quando non avrà un valore valido. Dopodiché si andrà ad allocare dinamicamente il nostro array e ad assegnarli tutte le istruzioni macchina contenute nel file. 
Si effettuano i seguenti controlli:
-se effettivamente esiste il file;
-se la malloc per l'allocazione dinamica è andata a buon fine;
-se il file contiene più righe di quante specificate ad inizio file;
-se all'interno del file sono presenti dei caratteri non accettati;
-se i parametri delle istruzioni di salto sforano le dimensioni del nostro array;
-se nel file è contenuta un'istruzione non valida.


-stampa.c: dopo aver preso tutte le istruzioni contenute all'interno del file da read stampa non farà altro che stampare tutte le istruzioni secondo il formato prestabilito:
	[posizione all'interno dell'array] ISTRUZIONE parametri dell'istruzione/funzione 
Alla fine di read però è necessario liberare la memoria allocata dinamicamente prima da read() e quindi si andrà a fare una free(programma) alla fine, quando programma non servirà più.


-esegui.c: infine nel sorgente esegui.c sono contenute tutte le istruzioni del linguaggio possibili e ne sono implementate le loro funzionalità. Inoltre è anche il posto in cui sono dichiarati stack, registri, ip ed sp, ovvero le variabili fondamentali per fare funzionare il programma, ciò su cui lavorano le funzioni. 
Tutte le istruzioni sono implementate inizialmente sotto forma di funzioni.
Nella funzione esegui è implementato il funzionamento del programma che leggiamo dal file: 
-viene letto il file e messo all'interno di programma (array dinamico);
-vengono inizializzati stack (array) e r(array) ed ip e sp;
-tramite uno switch all'interno di un while vengono lette tutte le istruzioni che sono associate al loro codice macchina e quando verranno incontrate verranno richiamate ed eseguite, portando così, se il codice è scritto correttamente all'interno del file, al risultato corretto che ci si aspettava dal programma. Alla fine di esegui come per read è necessario deallocare l'array che si era andato ad allocare dinamicamente per non incontrare problemi di memory leaks.

Entrambe esegui che read sono state pensate per un eventuale aggiornamento facilitato: nel caso si volessero aggiungere istruzioni si può facilmente aggiungere il codice macchina all'interno dello switch di read ed esegui e aggiungere la corrispettiva implementazione dell'istruzione in esegui.
