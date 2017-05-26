Per usare il programma :

    gcc executor.c
    ./a.out *comando -arg1 -arg2 ...
    

esempio:

    ./a.out ps -aux
    

# TO-DO

    1) Fare in modo che il programma scriva su out.k con k intero corrispondente al numero di esecuzione
    2) Esecuzione in **parallelo**?

# DONE
	
	1) Fatto
	2) La mia risoluzione al problema del parallelismo è stata loggare l'ouput dei vari processi in sotto cartelle ognuna di
	nome personalizzato in base al PID del processo. Così non avremo problemi di lock su files.