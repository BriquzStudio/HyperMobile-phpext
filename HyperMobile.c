/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2010 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header 297205 2010-03-30 21:09:07Z johannes $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_HyperMobile.h"

/* If you declare any globals in php_HyperMobile.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(HyperMobile)
*/

/* True global resources - no need for thread safety here */
static int le_HyperMobile;

/* {{{ HyperMobile_functions[]
 *
 * Every user visible function must have an entry in HyperMobile_functions[].
 */
zend_function_entry HyperMobile_functions[] = {
	PHP_ME(HyperMobile,__construct,NULL,ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(HyperMobile,__destruct,NULL,ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
	PHP_ME(HyperMobile,loadjsfromstring,NULL,ZEND_ACC_PUBLIC)
	PHP_ME(HyperMobile,loadjsfromfile,NULL,ZEND_ACC_PUBLIC)
	PHP_ME(HyperMobile,convert,NULL,ZEND_ACC_PUBLIC)
	PHP_ME(HyperMobile,getError,NULL,ZEND_ACC_PUBLIC)
	PHP_ME(HyperMobile,getErrorMsg,NULL,ZEND_ACC_PUBLIC)
	PHP_ME(HyperMobile,getObjc,NULL,ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}	/* Must be the last line in HyperMobile_functions[] */
};
/* }}} */

/* {{{ HyperMobile_module_entry
 */
zend_module_entry HyperMobile_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"HyperMobile",
	HyperMobile_functions,
	PHP_MINIT(HyperMobile),
	PHP_MSHUTDOWN(HyperMobile),
	PHP_RINIT(HyperMobile),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(HyperMobile),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(HyperMobile),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_HYPERMOBILE
ZEND_GET_MODULE(HyperMobile)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("HyperMobile.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_HyperMobile_globals, HyperMobile_globals)
    STD_PHP_INI_ENTRY("HyperMobile.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_HyperMobile_globals, HyperMobile_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_HyperMobile_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_HyperMobile_init_globals(zend_HyperMobile_globals *HyperMobile_globals)
{
	HyperMobile_globals->global_value = 0;
	HyperMobile_globals->global_string = NULL;
}
*/
/* }}} */

zend_class_entry *HyperMobile_ce;
/* 类方法的参数 */
/*ZEND_BEGIN_ARG_INFO(setName_args, 0)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()
*/
/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(HyperMobile)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/

	zend_class_entry hyperMobile;
	INIT_CLASS_ENTRY(hyperMobile,"HyperMobile",HyperMobile_functions);
	HyperMobile_ce = zend_register_internal_class(&hyperMobile TSRMLS_CC);
	zend_declare_property_null(HyperMobile_ce,ZEND_STRL("js_content"),ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_null(HyperMobile_ce,ZEND_STRL("err_msg"),ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_null(HyperMobile_ce,ZEND_STRL("objc_content"),ZEND_ACC_PRIVATE TSRMLS_CC);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(HyperMobile)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(HyperMobile)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(HyperMobile)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(HyperMobile)
{
	php_info_print_table_start();
	php_info_print_table_header(2,"HyperMobile support option","value");
	php_info_print_table_row(2, "HyperMobile", "enabled");
	php_info_print_table_row(2, "Working model options", "compiler,converter");
	php_info_print_table_row(2, "Current Working model", "converter");
	php_info_print_table_row(2, "Working engine", "Hyper-lang");
	php_info_print_table_row(2, "Working engine type", "javascript to objective-c");
	php_info_print_table_row(2, "HyperMobile version", "0.1alpha");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_HyperMobile_compiled(string arg)
   Return a string to confirm that the module is compiled in */
/*PHP_FUNCTION(confirm_HyperMobile_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "HyperMobile", arg);
	RETURN_STRINGL(strg, len, 0);
}*/
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/
/* =============================================================================
***  从这开始HyperMobile的逻辑成员代码 
***=============================================================================
*/
/** {{{ 构造函数 */
PHP_METHOD(HyperMobile, __construct) {
	RETURN_TRUE;
}
/* }}} */


/** {{{ 析构函数 */
PHP_METHOD(HyperMobile, __destruct) {
	RETURN_TRUE;
}
/* }}} */


/** {{{ 从字符串载入js代码 */
PHP_METHOD(HyperMobile, loadjsfromstring) {
	char *arg=NULL;
	int arg_len;
	zval *value,*self;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg,&arg_len) == FAILURE){
		WRONG_PARAM_COUNT;
	}
	self=getThis();
	MAKE_STD_ZVAL(value);
	ZVAL_STRING(value,arg,0);
	SEPARATE_ZVAL_TO_MAKE_IS_REF(&value);
	zend_update_property(Z_OBJCE_P(self), self, ZEND_STRL("js_content"), value TSRMLS_CC);
	RETURN_TRUE;
}
/* }}} */


/** {{{ 从文件载入js代码 */
PHP_METHOD(HyperMobile, loadjsfromfile) {
	RETURN_TRUE;
}
/* }}} */


/** {{{ 转换代码 */
PHP_METHOD(HyperMobile, convert) {
	RETURN_TRUE;
}
/* }}} */


/** {{{ 获取是否出错，返回布尔值 */
PHP_METHOD(HyperMobile, getError) {
	RETURN_FALSE;
}
/* }}} */


/** {{{ 获取错误消息 */
PHP_METHOD(HyperMobile, getErrorMsg) {
	zval *self,*ErrorMsg;
	self = getThis();
	ErrorMsg=zend_read_property(Z_OBJCE_P(self),self,ZEND_STRL("err_msg"),0 TSRMLS_CC);
	RETURN_STRING(Z_STRVAL_P(ErrorMsg),0);
}
/* }}} */


/** {{{ 获取oc代码 */
PHP_METHOD(HyperMobile, getObjc) {
	zval *self,*Objc;
	self = getThis();
	Objc=zend_read_property(Z_OBJCE_P(self),self,ZEND_STRL("objc_content"),0 TSRMLS_CC);
	RETURN_STRING(Z_STRVAL_P(Objc),0);
}
/* }}} */



/* =============================================================================
***  HyperMobile的逻辑成员代码 结束
***=============================================================================
*/
/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
