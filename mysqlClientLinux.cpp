/*************************************************************************
	> File Name: mysqlClient.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 22 Jun 2016 11:21:55 AM CST
 ************************************************************************/

#include <iostream>
#include <mysql/mysql.h>
#include <string>
#include <cstring>
#include <iomanip>
#include <stdio.h>
using namespace std;



int main(int argc, char * argv[])
{
    //输入主机地址
    cout << "Input Mysql host name: ";
    string hostName;
    getline(cin, hostName, '\n');

    //输入连接的端口号
    cout << "Input Mysql port(默认写0): ";
    unsigned int port;
    cin >> port;
    getchar();

    //输入数据库用户名
    cout << "Input Mysql user name: ";
    string userName;
    getline(cin, userName, '\n');
    
    //输入数据库用户密码
    cout << "Input Mysql user passward: ";
    string passward;
    getline(cin, passward, '\n');

    //输入数据库名字
    cout << "Input Mysql database name(可不输入): ";
    string databaseName;
    getline(cin, databaseName, '\n');



    //初始化MYSQL结构
    MYSQL mysql;
    MYSQL * connection = mysql_init(&mysql);
    if(connection == NULL){
        cerr << "mysql init error" << endl;
        return -1;
    }
    
    //连接数据库
    connection = mysql_real_connect(connection, hostName.c_str(), userName.c_str(), passward.c_str(), databaseName.c_str(), port, NULL, 0);
    if(connection == NULL){
        cerr << "mysql_real_connect error" << endl;
    }
    else{
        cout << "mysql connect successful." << endl;
    }

    //设置查询字符集属性为utf-8
    if(mysql_query(connection, "set names utf8")){
        cout << "set names utf8 error" << endl;
        return -1;
    }

    //进入查询循环
    while(1){
        cout << "mysql> ";
        string query;
        getline(cin, query, '\n');

        //输入quit，则退出
        if(query.compare("quit") == 0 || query.compare("QUIT") == 0){
            cout << "Bye" << endl;
            return 0;
        }


        if(query.compare(0, 6, "select")==0 || query.compare(0, 6, "SELECT")==0 ||
           query.compare(0, 4, "show") == 0 || query.compare(0, 4, "SHOW")==0 ||
           query.compare(0, 4, "desc") == 0 || query.compare(0, 4, "DESC") == 0)
        {
            //执行sql语句
            int ret = mysql_query(connection, query.c_str());
            if(ret!=0){
                cerr << "ERROR: You have an error in you SQL syntax." << endl;
                continue;
            }

            //将查询的结果读取到客户端
            MYSQL_RES * mysql_result = mysql_store_result(connection);
            if(mysql_result==NULL){
                //此时是出错
                if(mysql_error(connection)){
                    cerr << "mysql_store_result error" << endl;
                    continue;
                }
                //此时是输出为空
                cout << endl;
                continue;
            }
            //判断查询结果是否为空
            ret = mysql_num_rows(mysql_result);
            if(ret == 0){
                cout << "Empty." << endl;
                continue;
            }


            //获得查询的数据
            MYSQL_FIELD * fetch_fields = mysql_fetch_fields(mysql_result);


            //获得表的列数
            int num_fields = mysql_num_fields(mysql_result);

            //输出分割线
            for(int i = 0; i < num_fields; ++i)
                cout << "----------------";
            cout << endl;


            //输出表头
            for(int i = 0; i < num_fields; ++i){
                cout << setiosflags(ios::left) << setw(15) << fetch_fields[i].name << "|";
            }
            cout << endl;

            //输出分割线
            for(int i = 0; i < num_fields; ++i)
                cout << "----------------";
            cout << endl;

            //查询表的内容
            MYSQL_ROW query_content = NULL;
            while(query_content = mysql_fetch_row(mysql_result)){
                for(int i = 0; i < num_fields; ++i){
                    if(query_content[i] == NULL)
                        cout << setiosflags(ios::left) << setw(15) << "NULL" << "|";
                    else
                        cout << setiosflags(ios::left) << setw(15) << query_content[i] << "|";
                }
                cout << endl;
            }

            //输出分割线
            for(int i = 0; i < num_fields; ++i)
                cout << "----------------";
            cout << endl;
            
            //释放存放查询结果的内存
            mysql_free_result(mysql_result);

        }
        else{
            //执行sql语句
            int ret = mysql_query(connection, query.c_str());
            if(ret!=0){
                cerr << "ERROR: You have an error in you SQL syntax." << endl;
                continue;
            }

            if(query.compare(0, 4, "drop")==0 || query.compare(0, 4, "DROP")==0){
                cout << "Drop OK." << endl;
            }

            if(query.compare(0, 6, "create") == 0 || query.compare(0, 6, "CREATE")==0){
                cout << "Create OK." << endl;
            }
            
            if(query.compare(0, 6, "insert") == 0 || query.compare(0, 6, "INSERT") == 0){
                cout << "Insert OK." << endl;
            }

        }

    }

    return 0;
}
