	g++ -c server.cpp && g++ server.o -o server -l ssl -l crypto -L/usr/include/mysql/mysql -l mysqlclient && ./server