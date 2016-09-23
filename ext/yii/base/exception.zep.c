
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"


/**
 * @link http://www.yiiframework.com/
 * @copyright Copyright (c) 2008 Yii Software LLC
 * @license http://www.yiiframework.com/license/
 */
/**
 * Exception represents a generic exception for all purposes.
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
ZEPHIR_INIT_CLASS(yii_base_Exception) {

	ZEPHIR_REGISTER_CLASS_EX(yii\\base, Exception, yii, base_exception, zend_exception_get_default(TSRMLS_C), yii_base_exception_method_entry, 0);

	return SUCCESS;

}

/**
 * @return string the user-friendly name of this exception
 */
PHP_METHOD(yii_base_Exception, getName) {

	

	RETURN_STRING("Exception", 1);

}

