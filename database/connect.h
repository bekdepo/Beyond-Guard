#ifndef CONNECT_H_INCLUDED
#define CONNECT_H_INCLUDED

int connectDB();
void closeDB();
void createDatabase(char *db);
int isMD5InDB(char *md5);
void printMySQLInfo();
void useDatabase(char *db);

#endif // CONNECT_H_INCLUDED
