#include "connect.h"

#include <stdio.h>
#include <string.h>
#include <mysql.h>
#include <b64/b64.h>

void finishWithError(MYSQL *con);

MYSQL *con;

// connect to MySQL database, returns 0 if success
int connectDB(){

    FILE *fin = fopen("secret/dbconfig.txt", "r");
    int maxLength = 200;
    char host[maxLength];
    char username[maxLength];
    char password[maxLength];

    if (fin == NULL){
        printf("Can't open dbconfig.txt");
        return 1;
    }

    if(fgets(host, maxLength, fin) == NULL){
        printf("Can't read host from dbconfig.txt");
        fclose(fin);
        return 1;
    }

    if(fgets(username, maxLength, fin) == NULL){
        printf("Can't read username from dbconfig.txt");
        fclose(fin);
        return 1;
    }

    if(fgets(password, maxLength, fin) == NULL){
        printf("Can't read password from dbconfig.txt");
        fclose(fin);
        return 1;
    }

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
        finishWithError(con);
        return 1;
    }
    int result = useDatabase("godefender");
    if(result){
        return 1;
    }
    return 0;
}

// closes the global database connection
void closeDB(){
    mysql_close(con);
}

// creates a new database returns 0 on sucess
int createDatabase(char *db){
    char query[strlen(db)+20];
    strcpy(query, "CREATE DATABASE ");
    strcat(query, db);
    if (mysql_query(con, query))
    {
        finishWithError(con);
        return 1;
    }
    return 0;
}

// returns 0 if sucessfully uses a database
int useDatabase(char *db){
    char query[strlen(db)+5];
    strcpy(query, "USE ");
    strcat(query, db);
    if (mysql_query(con, query))
    {
        finishWithError(con);
        return 1;
    }
    return 0;
}

// returns 1 if MD5 string exist in database
int isMD5InDB(char *md5){

    char query[80];
    strcpy(query, "SELECT 1 FROM signatures WHERE md5='");
    strcat(query, md5);
    strcat(query, "' LIMIT 1");

    if (mysql_query(con, query))
    {
        finishWithError(con);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
    {
        finishWithError(con);
    }
    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result))){
        mysql_free_result(result);
        return 1;
    }
    mysql_free_result(result);
    return 0;
}

// prints error message
void finishWithError(MYSQL *con){
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
}

void printMySQLInfo(){
    printf("MySQL client version: %s\n", mysql_get_client_info());
}
