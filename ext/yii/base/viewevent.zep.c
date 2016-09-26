
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
 * ViewEvent represents events triggered by the [[View]] component.
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
ZEPHIR_INIT_CLASS(yii_base_ViewEvent) {

	ZEPHIR_REGISTER_CLASS_EX(yii\\base, ViewEvent, yii, base_viewevent, yii_base_event_ce, NULL, 0);

	/**
	 * @var string the view file being rendered.
	 */
	zend_declare_property_null(yii_base_viewevent_ce, SL("viewFile"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * @var array the parameter array passed to the [[View::render()]] method.
	 */
	zend_declare_property_null(yii_base_viewevent_ce, SL("params"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * @var string the rendering result of [[View::renderFile()]].
	 * Event handlers may modify this property and the modified output will be
	 * returned by [[View::renderFile()]]. This property is only used
	 * by [[View::EVENT_AFTER_RENDER]] event.
	 */
	zend_declare_property_null(yii_base_viewevent_ce, SL("output"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * @var boolean whether to continue rendering the view file. Event handlers of
	 * [[View::EVENT_BEFORE_RENDER]] may set this property to decide whether
	 * to continue rendering the current view file.
	 */
	zend_declare_property_bool(yii_base_viewevent_ce, SL("isValid"), 1, ZEND_ACC_PUBLIC TSRMLS_CC);

	return SUCCESS;

}

