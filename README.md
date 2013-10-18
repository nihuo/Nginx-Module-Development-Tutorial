Nginx-Module-Development-Tutorial
=================================

/*
 *	Author: Cui Yingjie (cuiyingjie@nihuo.com)
 *  GitHub: https://github.com/nihuo/Nginx-Module-Development-Tutorial
 * 	Nginx Module Development Tutorial
 * 
 */


1) Introduction
=====================================================================
The tutorial is for newbies of nginx module development. It's free for all. 

You are assumed to have below knowledge:

	A> C programmming
	B> HTTP (http header, cookie, url....)
	C> Summary of how nginx work


Anyone can add any tutorials which are helpful for nginx module development 
into this tutorial. Any help or any contribution will be highly appreciated.



2) How to take this tutorial
=====================================================================
A> Below documents are strongly recommended to be read at first:

	1. http://www.evanmiller.org/nginx-modules-guide.html
	2. http://antoine.bonavita.free.fr/nginx_mod_dev_en.html

B> Take tutorials in sub folder as order. 

C> Take each tutorial from reading readme.txt at first

D> Read code
	You should pay attention to comments in codes.
	
F> Build it and test it

G> Try to modify it


3) Development Environment
=====================================================================
The tutorial is developed in OSX 10.8.5. I think it will be ok is most system. 
OSX and Linux is recommended. 

A> Requirements

	a. PCRE library ( it's required for compiling nginx)
		It can be installed in OSX via below commands:
			brew install PCRE

		You also can download from http://www.pcre.org/ and 
		compile & install it from source. 

	b. modern C compiler ( clang or gcc will be ok )

