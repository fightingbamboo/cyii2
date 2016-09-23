
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
#include "ext/spl/spl_exceptions.h"


/**
 * @link http://www.yiiframework.com/
 * @copyright Copyright (c) 2008 Yii Software LLC
 * @license http://www.yiiframework.com/license/
 */
/**
 * UnknownMethodException represents an exception caused by accessing an unknown object method.
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
ZEPHIR_INIT_CLASS(yii_base_UnknownMethodException) {

	ZEPHIR_REGISTER_CLASS_EX(yii\\base, UnknownMethodException, yii, base_unknownmethodexception, spl_ce_BadMethodCallException, yii_base_unknownmethodexception_method_entry, 0);

	return SUCCESS;

}

/**
 * @return string the user-friendly name of this exception
 */
PHP_METHOD(yii_base_UnknownMethodException, getName) {

	

	RETURN_STRING("Unknown Method", 1);

}

