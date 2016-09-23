
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
#include "kernel/operators.h"
#include "kernel/concat.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"


/**
 * @link http://www.yiiframework.com/
 * @copyright Copyright (c) 2008 Yii Software LLC
 * @license http://www.yiiframework.com/license/
 */
/**
 * NotInstantiableException represents an exception caused by incorrect dependency injection container
 * configuration or usage.
 *
 * @author Sam Mousa <sam@mousa.nl>
 * @since 2.0.9
 */
ZEPHIR_INIT_CLASS(yii_di_NotInstantiableException) {

	ZEPHIR_REGISTER_CLASS_EX(yii\\di, NotInstantiableException, yii, di_notinstantiableexception, yii_base_invalidconfigexception_ce, yii_di_notinstantiableexception_method_entry, 0);

	return SUCCESS;

}

/**
 * @inheritdoc
 */
PHP_METHOD(yii_di_NotInstantiableException, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *class, *message = NULL, *code = NULL, *previous = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 3, &class, &message, &code, &previous);

	if (!message) {
		ZEPHIR_CPY_WRT(message, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(message);
	}
	if (!code) {
		ZEPHIR_INIT_VAR(code);
		ZVAL_LONG(code, 0);
	}
	if (!previous) {
		previous = ZEPHIR_GLOBAL(global_null);
	}


	if (Z_TYPE_P(message) == IS_NULL) {
		ZEPHIR_INIT_NVAR(message);
		ZEPHIR_CONCAT_SV(message, "Can not instantiate ", class);
	}
	ZEPHIR_CALL_PARENT(NULL, yii_di_notinstantiableexception_ce, this_ptr, "__construct", NULL, 0, message, code, previous);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * @return string the user-friendly name of this exception
 */
PHP_METHOD(yii_di_NotInstantiableException, getName) {

	

	RETURN_STRING("Not instantiable", 1);

}

