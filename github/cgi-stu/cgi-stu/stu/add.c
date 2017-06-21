#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

char * headname = "head.html";
char * footname = "footer.html";


int cgiMain()
{
  FILE * fd;

    	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char ino[32] = "\0";
	char name[16] = "\0";
	char sept[32] = "\0";

  char ch;

  if(!(fd = fopen(headname, "r"))){
		fprintf(cgiOut, "Cannot open file, %s\n", headname);
		return -1;
	}
	ch = fgetc(fd);

	while(ch != EOF){
		fprintf(cgiOut, "%c", ch);
		ch = fgetc(fd);
	}
fclose(fd);

	int status = 0;


	status = cgiFormString("ino", ino, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get ino error!\n");
		return 1;
	}

	status = cgiFormString("name", name, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get name  error!\n");
		return 1;
	}

	status = cgiFormString("sept",  sept, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sept error!\n");
		return 1;
	}

	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

	//int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}



	/*strcpy(sql, "create table information(iid int not null primary key, iname varchar(20) not null,sid int not null)");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}*/



	sprintf(sql,"insert into information values(%d,'%s','%s',1)",
	atoi(ino),name,sept);
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
			fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "add student ok!\n");
	mysql_close(db);
	return 0;
}
