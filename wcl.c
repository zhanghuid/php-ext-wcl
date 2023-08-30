/* wcl extension for PHP */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_wcl.h"

ZEND_DECLARE_MODULE_GLOBALS(wcl)

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE()  \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

/* {{{ PHP_INI */
PHP_INI_BEGIN()
STD_PHP_INI_ENTRY("wcl.filter_blank", "0", PHP_INI_ALL, OnUpdateBool, filter_blank, zend_wcl_globals, wcl_globals)
PHP_INI_END()
/* }}} */

/* {{{ void wcl_test1()
 */
PHP_FUNCTION(wcl_test1)
{
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("The extension %s is loaded and working!\r\n", "wcl");
}
/* }}} */

/* {{{ string wcl_test2( [ string $var ] )
 */
PHP_FUNCTION(wcl_test2)
{
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
	Z_PARAM_OPTIONAL
	Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}
/* }}}*/

/* {{{ int wcl(string filepath)
 */
PHP_FUNCTION(wcl)
{
	char *filepath = NULL;
	int argc = ZEND_NUM_ARGS();
	size_t filepath_len;
	char ch, pre = '\n';
	FILE *fp;
	zend_long lcount = 0;

	if (zend_parse_parameters(argc, "s", &filepath, &filepath_len) == FAILURE)
	{
		return;
	}

	/* php_error(E_WARNING, "wcl: not yet implemented"); */

	if ((fp = fopen(filepath, "r")) == NULL)
	{
		char *buf = NULL;
		// php_error(E_WARNING, "wcl: Input file does not exist!");
		php_error(E_WARNING, "wcl: Input file: %s does not exist!", filepath);
		// fprintf(stderr, "Input file does not exist!\n");
		// exit(1);
	}
	php_error(E_WARNING, "is filter: %ld", WCL_G(filter_blank));

	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch == '\n')
		{
			if (WCL_G(filter_blank) && pre == ch)
			{
				continue;
			}
			lcount++;
		}
	}
	fclose(fp);

	RETURN_LONG(lcount);
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(wcl)
{
#if defined(ZTS) && defined(COMPILE_DL_WCL)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(wcl)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "wcl support", "enabled");
	php_info_print_table_end();
}
/* }}} */

PHP_MINIT_FUNCTION(wcl)
{
	REGISTER_INI_ENTRIES();

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(wcl)
{
	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_wcl_test1, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_wcl_test2, 0)
ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ wcl_functions[]
 */
static const zend_function_entry wcl_functions[] = {
	PHP_FE(wcl_test1, arginfo_wcl_test1)
		PHP_FE(wcl_test2, arginfo_wcl_test2)
			PHP_FE(wcl, NULL)
				PHP_FE_END};
/* }}} */

/* {{{ wcl_module_entry
 */
zend_module_entry wcl_module_entry = {
	STANDARD_MODULE_HEADER,
	"wcl",				/* Extension name */
	wcl_functions,		/* zend_function_entry */
	PHP_MINIT(wcl),		/* PHP_MINIT - Module initialization */
	PHP_MSHUTDOWN(wcl), /* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(wcl),		/* PHP_RINIT - Request initialization */
	NULL,				/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(wcl),		/* PHP_MINFO - Module info */
	PHP_WCL_VERSION,	/* Version */
	STANDARD_MODULE_PROPERTIES};
/* }}} */

#ifdef COMPILE_DL_WCL
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(wcl)
#endif
