/*
*
* PURPOSE : Concat two strings
*
* PARAMS : char* s1 -> first string
* PARAMS : char* s2 -> second string
* RETURN : char* -> string concatenated
*
*/
char* concat(const char *s1, const char *s2){
    int i_s1 = 0;
    int i_s2 = 0;

    if(&(s1)[0] != NULL)
        i_s1 = strlen(s1);

    if(&(s2)[0] != NULL)
        i_s2 = strlen(s2);

    char *result = malloc(i_s1+i_s2+1);//+1 for the zero-terminator

    //in real code you would check for errors in malloc here
    if(&(s1)[0] != NULL)
        strcpy(result, s1);
    
    if(&(s2)[0] != NULL)
        strcat(result, s2);

    return result;
}

/*
*
* PURPOSE : read a line from a file and write it in str
*
* PARAMS : int fd -> file descriptor
* PARAMS : char* str -> where the line read will go
* RETURN : int -> 1 if ok, 0 end-of-input
*
*/
int readLine(int fd, char *str) {
    /* Read a single ’\0’-terminated line into str from fd */
    /* Return 0 when the end-of-input is reached and 1 otherwise */
    int n;
    do { /* Read characters until ’\0’ or end-of-input */
        n = read (fd, str, 1); /* Read one character */
    } while (n > 0 && *str++ != '\0');
    return (n > 0); /* Return false if end-of-input */
}