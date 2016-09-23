
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
#include "kernel/fcall.h"
#include "kernel/memory.h"


/**
 * @link http://www.yiiframework.com/
 * @copyright Copyright (c) 2008 Yii Software LLC
 * @license http://www.yiiframework.com/license/
 */
/**
 * ActionEvent represents the event parameter used for an action event.
 *
 * By setting the [[isValid]] property, one may control whether to continue running the action.
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
ZEPHIR_INIT_CLASS(yii_base_ActionEvent) {

	ZEPHIR_REGISTER_CLASS_EX(yii\\base, ActionEvent, yii, base_actionevent, yii_base_event_ce, yii_base_actionevent_method_entry, 0);

	/**
	 * @var Action the action currently being executed
	 */
	zend_declare_property_null(yii_base_actionevent_ce, SL("action"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * @var mixed the action result. Event handlers may modify this property to change the action result.
	 */
	zend_declare_property_null(yii_base_actionevent_ce, SL("result"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * @var boolean whether to continue running the action. Event handlers of
	 * [[Controller::EVENT_BEFORE_ACTION]] may set this property to decide whether
	 * to continue running the current action.
	 */
	zend_declare_property_bool(yii_base_actionevent_ce, SL("isValid"), 1, ZEND_ACC_PUBLIC TSRMLS_CC);

	return SUCCESS;

}

/**
 * Constructor.
 * @param Action $action the action associated with this action event.
 * @param array $config name-value pairs that will be used to initialize the object properties
 */
PHP_METHOD(yii_base_ActionEvent, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *action, *config = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &action, &config);

	if (!config) {
		ZEPHIR_INIT_VAR(config);
		array_init(config);
	}


	zephir_update_property_this(this_ptr, SL("action"), action TSRMLS_CC);
	ZEPHIR_CALL_PARENT(NULL, yii_base_actionevent_ce, this_ptr, "__construct", &_0, 10, config);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

