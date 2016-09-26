
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * @link http://www.yiiframework.com/
 * @copyright Copyright (c) 2008 Yii Software LLC
 * @license http://www.yiiframework.com/license/
 */
/**
 * ViewContextInterface is the interface that should implemented by classes who want to support relative view names.
 *
 * The method [[getViewPath()]] should be implemented to return the view path that may be prefixed to a relative view name.
 *
 * @author Paul Klimov <klimov.paul@gmail.com>
 * @since 2.0
 */
ZEPHIR_INIT_CLASS(yii_base_ViewContextInterface) {

	ZEPHIR_REGISTER_INTERFACE(yii\\base, ViewContextInterface, yii, base_viewcontextinterface, yii_base_viewcontextinterface_method_entry);

	return SUCCESS;

}

/**
 * @return string the view path that may be prefixed to a relative view name.
 */
ZEPHIR_DOC_METHOD(yii_base_ViewContextInterface, getViewPath);

