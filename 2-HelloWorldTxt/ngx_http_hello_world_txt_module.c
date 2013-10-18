/*
 *	Author: Cui Yingjie (cuiyingjie@nihuo.com)
 *  GitHub: https://github.com/nihuo/Nginx-Module-Development-Tutorial
 * 	Nginx Module Development Tutorial 2 - Hello World Txt
 * 
 */

#include <nginx.h>
#include <ngx_core.h>
#include <ngx_config.h>
#include <ngx_http.h>

#define HW_CONTENT_TYPE "text/plain"


static char *ngx_http_hello_world_txt_conf_handler( ngx_conf_t *cf, 
            ngx_command_t *cmd, void *conf );
static void *ngx_http_hello_world_txt_create_loc_conf(ngx_conf_t *cf);
static char *ngx_http_hello_world_txt_merge_loc_conf(ngx_conf_t *cf,
        void *parent, void *child);

typedef struct {
    ngx_str_t  m_sHelloMsg ;    
} ngx_http_hello_world_txt_loc_conf;


//declare directive hello_world
static ngx_command_t  ngx_http_hello_world_txt_commands[] = {
    { ngx_string("hello_world_txt"),
      NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1 ,      //NGX_CONF_TAKE1 instead of NGX_CONF_NOARGS
      ngx_http_hello_world_txt_conf_handler,
      NGX_HTTP_LOC_CONF_OFFSET,                 //NGX_HTTP_LOC_CONF_OFFSET instead of 0
      0,
      NULL },
      
    ngx_null_command
};

//declare callback function of nginx events
static ngx_http_module_t ngx_http_hello_world_txt_module_ctx = {
    NULL,                          /* preconfiguration */
    NULL,                          /* postconfiguration */
 
    NULL,                          /* create main configuration */
    NULL,                          /* init main configuration */
 
    NULL,                          /* create server configuration */
    NULL,                          /* merge server configuration */
 
    ngx_http_hello_world_txt_create_loc_conf,    /* create location configration */
    ngx_http_hello_world_txt_merge_loc_conf      /* merge location configration */
};


//decalre ngx_http_hello_world_txt_module which is in config file
ngx_module_t  ngx_http_hello_world_txt_module = {
    NGX_MODULE_V1,
    &ngx_http_hello_world_txt_module_ctx,       /* module context */
    ngx_http_hello_world_txt_commands,          /* module directives */
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
ngx_int_t ngx_http_hello_world_txt_handler(ngx_http_request_t *r)
{
    ngx_buf_t   *b;
    ngx_chain_t out;
    ngx_int_t   rc;
    ngx_http_hello_world_txt_loc_conf    *pConf ;
    static u_char szHelloMsg[] = "Hello World!" ;
    u_char *psBuf ;

    pConf = ngx_http_get_module_loc_conf( r, ngx_http_hello_world_txt_module ) ;

    //set http header information
    r->headers_out.content_type.len 	= ngx_strlen( HW_CONTENT_TYPE ) ;
    r->headers_out.content_type.data 	= (u_char *)HW_CONTENT_TYPE ;
 	

    r->headers_out.status 			= NGX_HTTP_OK;
    r->headers_out.content_length_n = pConf->m_sHelloMsg.len + sizeof( szHelloMsg ) - 1 ;

    //Add hello world message into a buf chain, and submit the chain to nginx.
    //Memory must be allocated from nginx pool. malloc and free are forbidden.
    b = ngx_pcalloc( r->pool, sizeof( ngx_buf_t ) );
    if(b == NULL)
        return NGX_HTTP_INTERNAL_SERVER_ERROR;

    out.buf 	= b;
    out.next 	= NULL;

    //join two string, hello world + message from configuration
    psBuf = ngx_pcalloc( r->pool, pConf->m_sHelloMsg.len + sizeof( szHelloMsg ) + 1 );
    if(psBuf == NULL)
        return NGX_HTTP_INTERNAL_SERVER_ERROR;

    memcpy( psBuf, szHelloMsg, sizeof( szHelloMsg ) - 1 ) ;
    memcpy( psBuf + sizeof( szHelloMsg ) - 1 , pConf->m_sHelloMsg.data, pConf->m_sHelloMsg.len ) ;

    b->pos 	= psBuf ;
    b->last = psBuf + pConf->m_sHelloMsg.len + sizeof( szHelloMsg ) - 1 ;

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
static char *ngx_http_hello_world_txt_conf_handler( ngx_conf_t *cf, 
    ngx_command_t *cmd, void *conf )
{
    ngx_http_core_loc_conf_t    *clcf;

    clcf = ngx_http_conf_get_module_loc_conf( cf, ngx_http_core_module ) ;

    //specify request handler
    clcf->handler = ngx_http_hello_world_txt_handler ;  

    //copy parameter message to configuration data
    ngx_http_hello_world_txt_loc_conf   *pHWConf = conf ;
    ngx_str_t                           *value ;

    value = cf->args->elts; 

    pHWConf->m_sHelloMsg.data = ngx_palloc( cf->pool, value[ 1 ].len );
    if( pHWConf->m_sHelloMsg.data == NULL )
    {
        ngx_log_error( NGX_LOG_ERR, cf->log, 0, "Failed to allocate buffer." );
        return NGX_CONF_ERROR;
    }

    pHWConf->m_sHelloMsg.len = value[ 1 ].len ;
    memcpy( pHWConf->m_sHelloMsg.data, value[ 1 ].data , value[ 1 ].len ) ;

    return NGX_CONF_OK ;    
}

//initialize configuration data
static void *
ngx_http_hello_world_txt_create_loc_conf(ngx_conf_t *cf)
{
    ngx_http_hello_world_txt_loc_conf  *pConf;
    pConf = ngx_pcalloc(cf->pool, sizeof(ngx_http_hello_world_txt_loc_conf));
    if (pConf == NULL) 
    {
        ngx_log_error( NGX_LOG_ERR, cf->log, 0, "Failed in allocating ngx_http_hello_world_txt_loc_conf" );
        return NULL;
    }

    return pConf ; 
}

//merge configuration data. In fact, this function is useless in example. 
//It's just be used to show how configuration data should be merged.
static char *
ngx_http_hello_world_txt_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_hello_world_txt_loc_conf *prev = parent;
    ngx_http_hello_world_txt_loc_conf *conf = child;

    ngx_conf_merge_str_value( conf->m_sHelloMsg, prev->m_sHelloMsg, "" ) ;

    return NGX_CONF_OK ;
}



