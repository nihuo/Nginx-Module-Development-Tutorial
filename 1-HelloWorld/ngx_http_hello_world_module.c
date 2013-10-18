/*
 *	Author: Cui Yingjie (cuiyingjie@nihuo.com)
 *  GitHub: https://github.com/nihuo/Nginx-Module-Development-Tutorial
 * 	Nginx Module Development Tutorial 1 - Hello World
 * 
 */

#include <nginx.h>
#include <ngx_core.h>
#include <ngx_config.h>
#include <ngx_http.h>

#define HW_CONTENT_TYPE "text/plain"


static char *ngx_http_hello_world_conf_handler( ngx_conf_t *cf, 
            ngx_command_t *cmd, void *conf );


//declare directive hello_world
static ngx_command_t  ngx_http_hello_world_commands[] = {
    { ngx_string("hello_world"),
      NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS ,
      ngx_http_hello_world_conf_handler,
      0,
      0,
      NULL },
      
    ngx_null_command
};

//declare callback function of nginx events
static ngx_http_module_t ngx_http_hello_world_module_ctx = {
    NULL,                          /* preconfiguration */
    NULL,                          /* postconfiguration */
 
    NULL,                          /* create main configuration */
    NULL,                          /* init main configuration */
 
    NULL,                          /* create server configuration */
    NULL,                          /* merge server configuration */
 
    NULL,                          /* create location configuration */
    NULL                           /* merge location configuration */
};


//decalre ngx_http_hello_world_module which is in config file
ngx_module_t  ngx_http_hello_world_module = {
    NGX_MODULE_V1,
    &ngx_http_hello_world_module_ctx,       /* module context */
    ngx_http_hello_world_commands,          /* module directives */
    NGX_HTTP_MODULE,                        /* module type */
    NULL,        							/* init master */
    NULL,       							/* init module */
    NULL,                                   /* init process */
    NULL,                                   /* init thread */
    NULL,                                   /* exit thread */
    NULL,                                   /* exit process */
    NULL,                                   /* exit master */
    NGX_MODULE_V1_PADDING
};

//request handler
ngx_int_t ngx_http_hello_world_handler(ngx_http_request_t *r)
{
    ngx_buf_t   *b;
    ngx_chain_t out;
    ngx_int_t   rc;

    static u_char szHelloMsg[] = "Hello World!" ;

    //set http header information
    r->headers_out.content_type.len 	= ngx_strlen( HW_CONTENT_TYPE ) ;
    r->headers_out.content_type.data 	= (u_char *)HW_CONTENT_TYPE ;
 	

    r->headers_out.status 			= NGX_HTTP_OK;
    r->headers_out.content_length_n = sizeof( szHelloMsg ) - 1 ;

    //Add hello world message into a buf chain, and submit the chain to nginx.
    //Memory must be allocated from nginx pool. malloc and free are forbidden.
    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
    if(b == NULL)
    {
        ngx_log_error( NGX_LOG_ERR, r->connection->log, 0, "Failed to allocate response buffer." );
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    out.buf 	= b;
    out.next 	= NULL;
        
    b->pos 	= szHelloMsg ;
    b->last = szHelloMsg + sizeof( szHelloMsg ) - 1 ;

    b->memory 	= 1;
    b->last_buf = 1;

    rc = ngx_http_send_header(r);
    if(rc != NGX_OK)
    {
        return rc;
    }

    return ngx_http_output_filter(r, &out);
}

//directive handler
static char *ngx_http_hello_world_conf_handler( ngx_conf_t *cf, 
    ngx_command_t *cmd, void *conf )
{
    ngx_http_core_loc_conf_t    *clcf;

    clcf = ngx_http_conf_get_module_loc_conf( cf, ngx_http_core_module ) ;

    //specify request handler
    clcf->handler = ngx_http_hello_world_handler ;  

    return NGX_CONF_OK ;    
}

