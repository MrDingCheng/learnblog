FLAG=-std=c++11 -L /usr/lib64/mysql -lmysqlclient -ljsoncpp -lpthread
blog_server:blog_server.cc db.hpp
	g++ blog_server.cc -o blog_server $(FLAG)
.PHONY:clean
clean:
	rm blog_server
