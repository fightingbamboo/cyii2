
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
 * ViewNotFoundException represents an exception caused by view file not found.
 *
 * @author Alexander Makarov
 * @since 2.0.10
 */
ZEPHIR_INIT_CLASS(yii_base_ViewNotFoundException) {

	ZEPHIR_REGISTER_CLASS_EX(yii\\base, ViewNotFoundException, yii, base_viewnotfoundexception, yii_base_invalidparamexception_ce, yii_base_viewnotfoundexception_method_entry, 0);

	return SUCCESS;

}

/**
 * @return string the user-friendly name of this exception
 */
PHP_METHOD(yii_base_ViewNotFoundException, getName) {

	

	RETURN_STRING("View not Found", 1);

}

