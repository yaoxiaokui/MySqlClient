MySql Client in Linux:

Version1: mysqlClientLinux.cpp is the source file

compiling:
    #g++ -o mysqlClientLinux mysqlClientLinux.cpp -lmysqlclient

running:
    #./mysqlClientLinux

    Then input the mysql server host's name or ip, port number, user's name, user's password, and database name.

Version2: mysqlClientLinux2.cpp is the source file,packing the C API of MySql to the MySql class. So, wo can use the MySql class to create a object to operate the database.


