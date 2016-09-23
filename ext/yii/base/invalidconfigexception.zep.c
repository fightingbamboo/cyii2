
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
 * InvalidConfigException represents an exception caused by incorrect object configuration.
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
ZEPHIR_INIT_CLASS(yii_base_InvalidConfigException) {

	ZEPHIR_REGISTER_CLASS_EX(yii\\base, InvalidConfigException, yii, base_invalidconfigexception, yii_base_exception_ce, yii_base_invalidconfigexception_method_entry, 0);

	return SUCCESS;

}

/**
 * @return string the user-friendly name of this exception
 */
PHP_METHOD(yii_base_InvalidConfigException, getName) {

	

	RETURN_STRING("Invalid Configuration", 1);

}

