# Progetto di Sistemi Operativi

Esercizio 1: 
============
Scheduler di processi
---------------------

In un sistema operativo, la gestione dei task (o processi) è una questione di primaria
importanza che viene spesso riferita col nome di scheduling. Per i nostri scopi, un task è
definito dalle seguenti informazioni: un identificatore numerico (ID), un nome (NOME
TASK, stringa che può contenere al massimo 8 caratteri), una priorità (PRIORITA’,
numero compreso fra 0 e 9) e il numero di cicli di esecuzione che richiede per essere
completato (ESECUZIONI RIMANENTI). Si supponga che un task possa richiedere al più
99 cicli di esecuzione per essere completato.

Lo scheduler è una funzionalità (del sistema operativo) che gestisce una coda in cui i task
vengono mantenuti ordinati in base alla politica di scheduling adottata. In questo esercizio
supporremo l’esistenza di due possibili politiche di scheduling:

    * Scheduling su **PRIORITA'** (scheduling di default) :
    si ordinano i task in modo decrescente rispetto al valore di PRIORITA’ ad essi associato (quindi da 9 a 0). Il
    task da eseguire per primo sarà quello a cui è stato associato il numero di
    PRIORITA’ più basso.
    I task con uguale valore di PRIORITA’ dovranno essere ordinati in modo
    decrescente rispetto al loro identificatore numerico ID.

    * Scheduling su **ESECUZIONI RIMANENTI**: 
    si ordinano i task in modo crescente rispetto al numero di ESECUZIONI RIMANENTI necessarie per il loro
    completamento. Il task da eseguire per primo sarà quello che necessita del maggior
    numero di ESECUZIONI RIMANENTI per essere completato.
    
Scrivere e provare un programma in C che simuli la funzionalità di scheduling dei task di
un sistema operativo. In particolare il programma, attraverso un menu di opzioni, dovrà
consentire di:

    1. inserire un nuovo task, richiedendo la sua priorità, il nome ed il numero di
    esecuzioni necessarie per il suo completamento (l'identificatore ID è univoco e
    viene assegnato automaticamente dal programma). Il task inserito dovrà poi essere
    posizionato nella coda a seconda della politica di scheduling utilizzata;
    
    2. eseguire il task che si trova in testa alla coda;
    3. eseguire il task il cui identificatore ID è specificato dall'utente;
    4. eliminare il task il cui identificatore ID è specificato dall'utente;
    5. modificare la **PRIORITA’** del task il cui identificatore ID è specificato dall'utente;
    6. cambiare la politica di scheduling utilizzata, passando dalla a) alla b) e viceversa;
    7. uscire dal programma.
    
L’esecuzione di un task con ESECUZIONI RIMANENTI = 1 comporta l’eliminazione del
task stesso dalla coda, altrimenti il numero di ESECUZIONI RIMANENTI viene
decrementato di 1 e l’ordinamento della coda aggiornato a seconda della politica di
scheduling utilizzata.

**Al termine di ogni operazione richiesta dall’utente, si deve stampare la coda risultante deitask sotto forma di elenco ordinato.**

NOTA BENE:

    1. Il campo NOME TASK può contenere al massimo 8 caratteri.
    2. Il campo PRIORITA’ è numero compreso fra 0 e 9.
    3. Il campo ESECUZIONI RIMANENTI è un numero compreso fra 1 e 99.
    4. Non essendo noto a priori il numero massimo di processi che il sistema operativo
    può eseguire contemporaneamente, si richiede di utilizzare l'allocazione
    dinamica dei dati all’interno dello heap (quindi utilizzando le istruzioni malloc,
    calloc, ...)
    
    
# Esercizio 2 
## esecutore di comandi (versione sequenziale e parallela)

Scrivere un programma che continuamente legge dallo standard input righe di testo
terminate da caratteri di fine riga (\n). Il programma termina quando inserisco una riga di
testo vuota. Ciascuna riga rappresenta un comando esterno da eseguire, quindi contiene il
nome del comando e gli eventuali argomenti:

*comando argomento1 argomento2 ...*

Il programma deve eseguire **sequenzialmente** i comandi (lanciati con gli eventuali
argomenti indicati) in modo da salvare lo standard output di ciascun comando su di un file
chiamato "out.k", ove k è il numero progressivo del comando eseguito.

Ad esempio, se il programma inizialmente legge dallo standard input le seguenti tre righe:

    * ls -la
    * date
    * cat /etc/passwd
    
allora il file "out.1" conterrà l’elenco dei file della directory, il file "out.2" conterrà la data e
l’ora al momento dell’esecuzione, ed il file "out.3" sarà una copia del file “/etc/passwd”.

Risolvere inoltre lo stesso esercizio supponendo però di voler eseguire i comandi non
sequenzialmente ma in parallelo, ovvero generando n processi (dove n è il numero
complessivo di righe di comando inserite) ognuno dei quali dedicato alla esecuzione di
una riga di comando.

Si gestiscano anche le situazioni di errore che si possono verificare più frequentemente.

# Esercizio 3
## scambio di messaggi

Si realizzi una infrastruttura software per lo scambio di messaggi tra processi client (d'ora
in avanti semplicemente “client”) gestita da un processo server (d’ora in avanti
semplicemente “server”). La comunicazione tra client avviene nel seguente modo: un
client può inviare un messaggio testuale a un altro client o ad un gruppo di client
affidandolo al server, che si occupa di recapitarlo.
Tutte le comunicazioni fra tutti i processi in gioco andranno realizzate utilizzando segnali e
pipe con nome.
Il server svolge le seguenti funzioni:

    * mantiene la lista dei client connessi. 
    * riceve messaggi testuali da inoltrare ai client.
    
Il client esegue le seguenti attività:

    * si connette al server, si disconnette dal server.
    * invia e riceve messaggi testuali.
    
Il funzionamento del software dovrà essere il seguente: viene mandato in esecuzione il
server, che rimane in attesa di informazioni da parte dei client (connessioni,
disconnessioni, messaggi testuali da inoltrare). Vengono poi avviati alcuni processi client
(ogni client sarà avviato in terminali distinti). Quindi i client propongono un menu con le
scelte possibili, che sono:

    1. Connessione, con la quale il client si registra presso il server.
    2. Richiesta elenco ID dei client registrati, con la quale si richiede al server l'elenco dei client attualmente registrati.
    3. Invio di un messaggio testuale a un altro client o a un insieme di client (specificandone l'ID).
    4. Disconnessione, con la quale il client richiede la cancellazione della registrazione presso il server.
    5. Uscita dal programma.
    
Il server riconosce il tipo di richiesta del client ed esegue ciò che essa prevede. In
particolare, in corrispondenza di una richiesta di connessione il server assocerà al client
un ID univoco di registrazione, che dovrà poi essere rimosso nel caso in cui lo stesso
client richieda esplicitamente la disconnessione dal server (tramite la scelta 4) o nel caso
in cui il client venga terminato (utilizzando la scelta 5 oppure premendo Ctrl-C da
terminale).

Le infrastrutture da utilizzare per lo scambio di informazioni fra i processi sono le seguenti:

    * un (unico) pipe con nome, creato dal server quando viene mandato in esecuzione,
    che viene utilizzato (in maniera condivisa) dai client in scrittura (per comunicare le
    proprie richieste al server) e dal server in lettura; il server è l’unico processo a cui è
    permessa la lettura dal pipe, i client potranno solo scrivere su tale pipe.
    
    * un pipe con nome (uno per ogni client), creato appositamente dal server quando
    necessario, e utilizzato dal server in scrittura e dal client in lettura per inviarel'elenco 
    degli ID dei client attualmente registrati e per inviare messaggi testuali (il
    server usa il pipe associato al destinatario per recapitarlo).
    
    * una serie di segnali, inviati dal server ai vari client, per notificare eventi quali la
    ricezione di un messaggio per un client (notifica al client destinatario) o l'errore per
    aver richiesto l'inoltro di un messaggio verso un client inesistente (notifica al client
    mittente).
    
Si gestiscano anche le situazioni di errore che si possono verificare più frequentemente.