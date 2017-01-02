#ifndef CONNECT_H_INCLUDED
#define CONNECT_H_INCLUDED

int connectDB();
void closeDB();
void createDatabase(char *db);
void printMySQLInfo();

#endif // CONNECT_H_INCLUDED
