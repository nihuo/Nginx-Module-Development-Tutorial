/*
 *	Author: Cui Yingjie (cuiyingjie@nihuo.com)
 *  GitHub: https://github.com/nihuo/Nginx-Module-Development-Tutorial
 * 	Nginx Module Development Tutorial 1 - Hello World
 * 
 */

1) Introduction
=====================================================================
Please read below documents at first:
	1) http://www.nginxguts.com/2011/01/plugs/


It's a most simple nginx module. There are just two files:
	config
		Tell building system how to huild this module.

	ngx_http_hello_world_module.c
		C code.



2) Build
=====================================================================
Enter folder which nginx source is in and run below commands:

./configure --add-module=[full path of module folder]

	e.g.
	./configure --add-module=/Users/nihuo/projects/Nginx-Module-Development-Tutorial/1-HelloWorld

make
make install


nginx will be installed into /usr/local/nginx


3) Run
=====================================================================
A> Edit /usr/local/nginx/conf/nginx.conf. Add hello_world directive. 

	location / {
		hello_world;
	}

	Recommend change listen port to a new one which is bigger than 1024.
	e.g.
		listen       8000;


B> Run below command:

/usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx.conf

if nginx had been launched, plz take a look at:
	http://wiki.nginx.org/CommandLine#Upgrading_To_a_New_Binary_On_The_Fly.

If it's too complicated for you, you just need stop nginx at first and relaunch it:
	/usr/local/nginx/sbin/nginx -s stop
	/usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx.conf

If you just changed configuration file, only reloading is required:
	/usr/local/nginx/sbin/nginx -s reload


C) Launch browser and visit below url:
	http://localhost:8000/








