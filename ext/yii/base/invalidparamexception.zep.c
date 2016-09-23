
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
 * InvalidParamException represents an exception caused by invalid parameters passed to a method.
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
ZEPHIR_INIT_CLASS(yii_base_InvalidParamException) {

	ZEPHIR_REGISTER_CLASS_EX(yii\\base, InvalidParamException, yii, base_invalidparamexception, spl_ce_BadMethodCallException, yii_base_invalidparamexception_method_entry, 0);

	return SUCCESS;

}

/**
 * @return string the user-friendly name of this exception
 */
PHP_METHOD(yii_base_InvalidParamException, getName) {

	

	RETURN_STRING("Invalid Parameter", 1);

}

