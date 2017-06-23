 
char* concat(const char *s1, const char *s2)
{
    int i_s1 = 0;
    int i_s2 = 0;

    if(&(s1)[0] != NULL)
        i_s1 = strlen(s1);

    if(&(s2)[0] != NULL)
        i_s2 = strlen(s2);

    // printf("s2: %s\n", &(s2)[0]);
    // printf("s1: %s\n", &(s1)[0]);
    // printf("size s2: %zu\n", sizeof(&(s2)));
    // printf("size s1: %zu\n", sizeof(&(s1)));
    
    char *result = malloc(i_s1+i_s2+1);//+1 for the zero-terminator

    //in real code you would check for errors in malloc here
    if(&(s1)[0] != NULL)
        strcpy(result, s1);
    
    if(&(s2)[0] != NULL)
        strcat(result, s2);

    return result;
}

int readLine (int fd, char *str) {
    /* Read a single ’\0’-terminated line into str from fd */
    /* Return 0 when the end-of-input is reached and 1 otherwise */
    int n;
    do { /* Read characters until ’\0’ or end-of-input */
        n = read (fd, str, 1); /* Read one character */
    } while (n > 0 && *str++ != '\0');
    return (n > 0); /* Return false if end-of-input */
}