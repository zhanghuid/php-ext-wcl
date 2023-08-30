/* wcl extension for PHP */

#ifndef PHP_WCL_H
#define PHP_WCL_H

extern zend_module_entry wcl_module_entry;
#define phpext_wcl_ptr &wcl_module_entry

#define PHP_WCL_VERSION "0.1.0"

#if defined(ZTS) && defined(COMPILE_DL_WCL)
    ZEND_TSRMLS_CACHE_EXTERN()
#endif

ZEND_BEGIN_MODULE_GLOBALS(wcl)
    zend_long filter_blank;
ZEND_END_MODULE_GLOBALS(wcl)

ZEND_EXTERN_MODULE_GLOBALS(wcl)

#define WCL_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(wcl, v)

#endif /* PHP_WCL_H */
