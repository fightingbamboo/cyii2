
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
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"


/**
 * @link http://www.yiiframework.com/
 * @copyright Copyright (c) 2008 Yii Software LLC
 * @license http://www.yiiframework.com/license/
 */
/**
 * ExitException represents a normal termination of an application.
 *
 * Do not catch ExitException. Yii will handle this exception to terminate the application gracefully.
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
ZEPHIR_INIT_CLASS(yii_base_ExitException) {

	ZEPHIR_REGISTER_CLASS_EX(yii\\base, ExitException, yii, base_exitexception, zend_exception_get_default(TSRMLS_C), yii_base_exitexception_method_entry, 0);

	/**
	 * @var integer the exit status code
	 */
	zend_declare_property_null(yii_base_exitexception_ce, SL("statusCode"), ZEND_ACC_PUBLIC TSRMLS_CC);

	return SUCCESS;

}

/**
 * Constructor.
 * @param integer $status the exit status code
 * @param string $message error message
 * @param integer $code error code
 * @param \Exception $previous The previous exception used for the exception chaining.
 */
PHP_METHOD(yii_base_ExitException, __construct) {

	zval *message = NULL;
	zval *status_param = NULL, *message_param = NULL, *code_param = NULL, *previous = NULL, *_0, *_1;
	int status, code, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 4, &status_param, &message_param, &code_param, &previous);

	if (!status_param) {
		status = 0;
	} else {
		status = zephir_get_intval(status_param);
	}
	if (!message_param) {
		ZEPHIR_INIT_VAR(message);
		ZVAL_EMPTY_STRING(message);
	} else {
		zephir_get_strval(message, message_param);
	}
	if (!code_param) {
		code = 0;
	} else {
		code = zephir_get_intval(code_param);
	}
	if (!previous) {
		previous = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, status);
	zephir_update_property_this(this_ptr, SL("statusCode"), _0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, code);
	ZEPHIR_CALL_PARENT(NULL, yii_base_exitexception_ce, this_ptr, "__construct", NULL, 0, message, _1, previous);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

