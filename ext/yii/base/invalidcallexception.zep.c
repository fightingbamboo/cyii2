
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
 * InvalidCallException represents an exception caused by calling a method in a wrong way.
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
ZEPHIR_INIT_CLASS(yii_base_InvalidCallException) {

	ZEPHIR_REGISTER_CLASS_EX(yii\\base, InvalidCallException, yii, base_invalidcallexception, spl_ce_BadMethodCallException, yii_base_invalidcallexception_method_entry, 0);

	return SUCCESS;

}

/**
 * @return string the user-friendly name of this exception
 */
PHP_METHOD(yii_base_InvalidCallException, getName) {

	

	RETURN_STRING("Invalid Call", 1);

}

