/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
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

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_array_square_sum.h"

/* If you declare any globals in php_array_square_sum.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(array_square_sum)
*/

/* True global resources - no need for thread safety here */
static int le_array_square_sum;

/* {{{ array_square_sum_functions[]
 *
 * Every user visible function must have an entry in array_square_sum_functions[].
 */
const zend_function_entry array_square_sum_functions[] = {
	PHP_FE(confirm_array_square_sum_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(array_square_sum,	NULL)
	PHP_FE_END	/* Must be the last line in array_square_sum_functions[] */
};
/* }}} */

/* {{{ array_square_sum_module_entry
 */
zend_module_entry array_square_sum_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"array_square_sum",
	array_square_sum_functions,
	PHP_MINIT(array_square_sum),
	PHP_MSHUTDOWN(array_square_sum),
	PHP_RINIT(array_square_sum),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(array_square_sum),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(array_square_sum),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_ARRAY_SQUARE_SUM_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_ARRAY_SQUARE_SUM
ZEND_GET_MODULE(array_square_sum)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("array_square_sum.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_array_square_sum_globals, array_square_sum_globals)
    STD_PHP_INI_ENTRY("array_square_sum.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_array_square_sum_globals, array_square_sum_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_array_square_sum_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_array_square_sum_init_globals(zend_array_square_sum_globals *array_square_sum_globals)
{
	array_square_sum_globals->global_value = 0;
	array_square_sum_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(array_square_sum)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(array_square_sum)
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
PHP_RINIT_FUNCTION(array_square_sum)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(array_square_sum)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(array_square_sum)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "array_square_sum support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_array_square_sum_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_array_square_sum_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "array_square_sum", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/

/* {{{ proto string array_square_sum(string str)
    */
PHP_FUNCTION(array_square_sum)
{
    zval* array_data;
    HashTable *ht_data;
    int ret;
    char* key;
    uint index;
    zval **pdata;
    double sum = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &array_data) == FAILURE) {
        return;
    }   

    ht_data = Z_ARRVAL_P(array_data);
    zend_hash_internal_pointer_reset(ht_data);
    while ( HASH_KEY_NON_EXISTANT != (ret = zend_hash_get_current_key(ht_data, &key, &index, 0)) ) { 
        ret = zend_hash_get_current_data(ht_data, &pdata);
    
        if( Z_TYPE_P(*pdata) == IS_LONG){
            sum +=  Z_LVAL_P(*pdata) *  Z_LVAL_P(*pdata);
        }else {
            RETURN_FALSE;
        }   
        zend_hash_move_forward(ht_data);
    }   
    zend_hash_internal_pointer_end(Z_ARRVAL_P(array_data));
    RETVAL_DOUBLE(sum);
}
/* }}} */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
