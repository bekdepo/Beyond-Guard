#include "connect.h"

#include <stdio.h>
#include <string.h>

#include <mysql.h>

#include <b64/b64.h>

void finish_with_error(MYSQL *con);

MYSQL *con;

// connect to MySQL database
int connectDB(){

    FILE *fin = fopen("secret/dbconfig.txt", "r");
    char host[100];
    char username[100];
    char password[100];

    if (fin == NULL){
        printf("Can't open dbconfig.txt");
        return 0;
    }

    fscanf(fin, "%s", host);
    fscanf(fin, "%s", username);
    fscanf(fin, "%s", password);
    fclose(fin);

    char *plainHost = (char*)b64_decode(host, strlen(host));
    char *plainUsername = (char*)b64_decode(username, strlen(username));
    char *plainPassword = (char*)b64_decode(password, strlen(password));

    con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        return 1;
    }

    if (mysql_real_connect(con, plainHost, plainUsername, plainPassword,
          NULL, 0, NULL, 0) == NULL)
    {
        finish_with_error(con);
    }

    //createDatabase("testingjon123");
    closeDB();

    return 0;
}

void closeDB(){
    mysql_close(con);
}

void createDatabase(char *db){
    char query[100];
    strcpy(query, "CREATE DATABASE ");
    strcat(query, db);
    if (mysql_query(con, query))
    {
        finish_with_error(con);
    }
}

// prints error message
void finish_with_error(MYSQL *con){
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

void printMySQLInfo(){
    printf("MySQL client version: %s\n", mysql_get_client_info());
}
