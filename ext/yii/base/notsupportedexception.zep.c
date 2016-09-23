
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
 * NotSupportedException represents an exception caused by accessing features that are not supported.
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
ZEPHIR_INIT_CLASS(yii_base_NotSupportedException) {

	ZEPHIR_REGISTER_CLASS_EX(yii\\base, NotSupportedException, yii, base_notsupportedexception, yii_base_exception_ce, yii_base_notsupportedexception_method_entry, 0);

	return SUCCESS;

}

/**
 * @return string the user-friendly name of this exception
 */
PHP_METHOD(yii_base_NotSupportedException, getName) {

	

	RETURN_STRING("Not Supported", 1);

}

