
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
 * ModelEvent represents the parameter needed by [[Model]] events.
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
ZEPHIR_INIT_CLASS(yii_base_ModelEvent) {

	ZEPHIR_REGISTER_CLASS_EX(yii\\base, ModelEvent, yii, base_modelevent, yii_base_event_ce, NULL, 0);

	/**
	 * @var boolean whether the model is in valid status. Defaults to true.
	 * A model is in valid status if it passes validations or certain checks.
	 */
	zend_declare_property_bool(yii_base_modelevent_ce, SL("isValid"), 1, ZEND_ACC_PUBLIC TSRMLS_CC);

	return SUCCESS;

}

