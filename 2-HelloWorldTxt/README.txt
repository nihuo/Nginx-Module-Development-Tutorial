/*
 *	Author: Cui Yingjie (cuiyingjie@nihuo.com)
 *	GitHub: https://github.com/nihuo/Nginx-Module-Development-Tutorial
 *	Nginx Module Development Tutorial 2 - Hello World Txt
 * 
 */

1) Introduction
=====================================================================
It's based on Hello World module, an extra message which can be customized
in nginx.conf could be displayed with hello message.

Two new functions are added to process configuration data:
	ngx_http_hello_world_txt_create_loc_conf
	ngx_http_hello_world_txt_merge_loc_conf

New struct (ngx_http_hello_world_txt_loc_conf) has been declared to store 
configuration data.

Configuration data will be gotten in ngx_http_hello_world_txt_conf_handler. 


2) Build
=====================================================================
Enter folder which nginx source is in and run below commands:

./configure --add-module=[full path of module folder]

	e.g.
	./configure --add-module=/Users/nihuo/projects/Nginx-Module-Development-Tutorial/2-HelloWorldTxt

make
make install


nginx will be installed into /usr/local/nginx


3) Run
=====================================================================
A> Edit /usr/local/nginx/conf/nginx.conf. Add hello_world_txt directive. 

	location / {
		hello_world_txt	" My Friends";
	}

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








