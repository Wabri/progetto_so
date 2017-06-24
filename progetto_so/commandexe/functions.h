/*
*
* PURPOSE : Create the data folder to store outputs
*
* RETURN : void
*
*/
int initDataFolder() {
	char cmd[30];
	FILE *fp;
	sprintf(cmd, "%s%i", "mkdir -p ../commandexe/data/", getpid());
	fp = popen(cmd, "r");
	if (fp == NULL) {
		printf("[Error] - Error initialing process folder\n");
		exit(1);
	}
	return 0;
}

/*
*
* PURPOSE : Function that execute the c command and log the output in ../commandexe/data/[pid]/out.[index]
*
* PARAMS : char* -> command string
* PARAMS : int -> index of out.[index] log
* RETURN : int -> 0
*
*/
int execCommandAndLog(char* c, int index) {
	FILE *fp;
	char path[1035];
	char filename[7];

	sprintf(filename, "data/%i/%s.%i", getpid(), "out", index);
	FILE *f = fopen(filename, "w");
	if (f == NULL) {
		printf("[Error] - Error opening file!\n");
		exit(1);
	}

	// command open to read
	sprintf(c, "%s %s", c, "2>&1");
	fp = popen(c, "r");

	if (fp == NULL) {
		fprintf(f, "[Error] - Error executing the command\n");
	}

	// read the output a line at a time - output it.
	while (fgets(path, sizeof(path) - 1, fp) != NULL) {
		fprintf(f, "%s", path);
	}

	// closing files
	pclose(fp);
	fclose(f);

	return 0;
}