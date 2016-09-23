
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
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/exception.h"
#include "kernel/concat.h"


/**
 * @link http://www.yiiframework.com/
 * @copyright Copyright (c) 2008 Yii Software LLC
 * @license http://www.yiiframework.com/license/
 */
/**
 * Instance represents a reference to a named object in a dependency injection (DI) container or a service locator.
 *
 * You may use [[get()]] to obtain the actual object referenced by [[id]].
 *
 * Instance is mainly used in two places:
 *
 * - When configuring a dependency injection container, you use Instance to reference a class name, interface name
 *   or alias name. The reference can later be resolved into the actual object by the container.
 * - In classes which use service locator to obtain dependent objects.
 *
 * The following example shows how to configure a DI container with Instance:
 *
 * ```php
 * $container = new \yii\di\Container;
 * $container->set('cache', 'yii\caching\DbCache', Instance::of('db'));
 * $container->set('db', [
 *     'class' => 'yii\db\Connection',
 *     'dsn' => 'sqlite:path/to/file.db',
 * ]);
 * ```
 *
 * And the following example shows how a class retrieves a component from a service locator:
 *
 * ```php
 * class DbCache extends Cache
 * {
 *     public $db = 'db';
 *
 *     public function init()
 *     {
 *         parent::init();
 *         $this->db = Instance::ensure($this->db, 'yii\db\Connection');
 *     }
 * }
 * ```
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
ZEPHIR_INIT_CLASS(yii_di_Instance) {

	ZEPHIR_REGISTER_CLASS(yii\\di, Instance, yii, di_instance, yii_di_instance_method_entry, 0);

	/**
	 * @var string the component ID, class name, interface name or alias name
	 */
	zend_declare_property_null(yii_di_instance_ce, SL("id"), ZEND_ACC_PUBLIC TSRMLS_CC);

	return SUCCESS;

}

/**
 * Constructor.
 * @param string $id the component ID
 */
PHP_METHOD(yii_di_Instance, __construct) {

	zval *id_param = NULL;
	zval *id = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &id_param);

	zephir_get_strval(id, id_param);


	zephir_update_property_this(this_ptr, SL("id"), id TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Creates a new Instance object.
 * @param string $id the component ID
 * @return Instance the new Instance object.
 */
PHP_METHOD(yii_di_Instance, of) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *id_param = NULL;
	zval *id = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &id_param);

	zephir_get_strval(id, id_param);


	object_init_ex(return_value, yii_di_instance_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 31, id);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Resolves the specified reference into the actual object and makes sure it is of the specified type.
 *
 * The reference may be specified as a string or an Instance object. If the former,
 * it will be treated as a component ID, a class/interface name or an alias, depending on the container type.
 *
 * If you do not specify a container, the method will first try `Yii::$app` followed by `Yii::$container`.
 *
 * For example,
 *
 * ```php
 * use yii\db\Connection;
 *
 * // returns Yii::$app->db
 * $db = Instance::ensure('db', Connection::className());
 * // or
 * $instance = Instance::of('db');
 * $db = Instance::ensure($instance, Connection::className());
 * ```
 *
 * @param object|string|static $reference an object or a reference to the desired object.
 * You may specify a reference in terms of a component ID or an Instance object.
 * @param string $type the class/interface name to be checked. If null, type check will not be performed.
 * @param ServiceLocator|Container $container the container. This will be passed to [[get()]].
 * @return object the object referenced by the Instance, or `$reference` itself if it is an object.
 * @throws InvalidConfigException if the reference is invalid
 */
PHP_METHOD(yii_di_Instance, ensure) {

	zend_bool _2, _3$$8;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *reference = NULL, *type = NULL, *container = NULL, *class = NULL, *valueType = NULL, *_7, *_8, *_0$$4, *_1$$3, *component$$8 = NULL, *class_name$$10 = NULL, *message$$10 = NULL, *id$$10 = NULL, *_4$$10, *_5$$10, *_6$$10;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &reference, &type, &container);

	ZEPHIR_SEPARATE_PARAM(reference);
	if (!type) {
		type = ZEPHIR_GLOBAL(global_null);
	}
	if (!container) {
		ZEPHIR_CPY_WRT(container, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(container);
	}


	if (Z_TYPE_P(reference) == IS_ARRAY) {
		if (zephir_array_isset_string(reference, SS("class"))) {
			ZEPHIR_OBS_VAR(class);
			zephir_array_fetch_string(&class, reference, SL("class"), PH_NOISY, "yii/di/Instance.zep", 109 TSRMLS_CC);
		} else {
			ZEPHIR_CPY_WRT(class, type);
		}
		if (!(zephir_instance_of_ev(container, yii_di_container_ce TSRMLS_CC))) {
			ZEPHIR_OBS_VAR(_0$$4);
			zephir_read_static_property_ce(&_0$$4, yii_baseyii_ce, SL("container") TSRMLS_CC);
			ZEPHIR_CPY_WRT(container, _0$$4);
		}
		zephir_array_unset_string(&reference, SS("class"), PH_SEPARATE);
		ZEPHIR_INIT_VAR(_1$$3);
		array_init(_1$$3);
		ZEPHIR_RETURN_CALL_METHOD(container, "get", NULL, 0, class, _1$$3, reference);
		zephir_check_call_status();
		RETURN_MM();
	} else if (ZEPHIR_IS_EMPTY(reference)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(yii_base_invalidconfigexception_ce, "The required component is not specified.", "yii/di/Instance.zep", 116);
		return;
	}
	_2 = Z_TYPE_P(type) == IS_NULL;
	if (!(_2)) {
		_2 = zephir_is_instance_of(reference, Z_STRVAL_P(type), Z_STRLEN_P(type) TSRMLS_CC);
	}
	if (Z_TYPE_P(reference) == IS_STRING) {
		ZEPHIR_INIT_NVAR(reference);
		object_init_ex(reference, yii_di_instance_ce);
		ZEPHIR_CALL_METHOD(NULL, reference, "__construct", NULL, 31, reference);
		zephir_check_call_status();
	} else if (_2) {
		RETVAL_ZVAL(reference, 1, 0);
		RETURN_MM();
	}
	if (zephir_instance_of_ev(reference, yii_di_instance_ce TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(&component$$8, reference, "get", NULL, 32, container);
		zephir_check_call_status();
		_3$$8 = Z_TYPE_P(type) == IS_NULL;
		if (!(_3$$8)) {
			_3$$8 = zephir_is_instance_of(component$$8, Z_STRVAL_P(type), Z_STRLEN_P(type) TSRMLS_CC);
		}
		if (_3$$8) {
			RETURN_CCTOR(component$$8);
		} else {
			ZEPHIR_INIT_VAR(class_name$$10);
			zephir_get_class(class_name$$10, component$$8, 0 TSRMLS_CC);
			_4$$10 = zephir_fetch_nproperty_this(reference, SL("id"), PH_NOISY_CC);
			ZEPHIR_CPY_WRT(id$$10, _4$$10);
			ZEPHIR_INIT_VAR(message$$10);
			ZEPHIR_CONCAT_SVS(message$$10, "\"", id$$10, "\" refers to a ");
			ZEPHIR_INIT_VAR(_5$$10);
			ZEPHIR_CONCAT_VSVS(_5$$10, class_name$$10, " component. ", type, " is expected.");
			zephir_concat_self(&message$$10, _5$$10 TSRMLS_CC);
			ZEPHIR_INIT_VAR(_6$$10);
			object_init_ex(_6$$10, yii_base_invalidconfigexception_ce);
			ZEPHIR_CALL_METHOD(NULL, _6$$10, "__construct", NULL, 3, message$$10);
			zephir_check_call_status();
			zephir_throw_exception_debug(_6$$10, "yii/di/Instance.zep", 137 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	if (Z_TYPE_P(reference) == IS_OBJECT) {
		ZEPHIR_INIT_VAR(valueType);
		zephir_get_class(valueType, reference, 0 TSRMLS_CC);
	} else {
		ZEPHIR_INIT_NVAR(valueType);
		zephir_gettype(valueType, reference TSRMLS_CC);
	}
	ZEPHIR_INIT_VAR(_7);
	object_init_ex(_7, yii_base_invalidconfigexception_ce);
	ZEPHIR_INIT_VAR(_8);
	ZEPHIR_CONCAT_SVVS(_8, "Invalid data type: ", valueType, type, " is expected.");
	ZEPHIR_CALL_METHOD(NULL, _7, "__construct", NULL, 3, _8);
	zephir_check_call_status();
	zephir_throw_exception_debug(_7, "yii/di/Instance.zep", 143 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Returns the actual object referenced by this Instance object.
 * @param ServiceLocator|Container $container the container used to locate the referenced object.
 * If null, the method will first try `Yii::$app` then `Yii::$container`.
 * @return object the actual object referenced by this Instance object.
 */
PHP_METHOD(yii_di_Instance, get) {

	zend_bool _2;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *container = NULL, *_0$$3, *_1, *_3, *_4 = NULL, *_5, *_6$$4, *_7$$4, *_8$$5, *_9$$5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &container);

	if (!container) {
		container = ZEPHIR_GLOBAL(global_null);
	}


	if (Z_TYPE_P(container) == IS_OBJECT) {
		_0$$3 = zephir_fetch_nproperty_this(this_ptr, SL("id"), PH_NOISY_CC);
		ZEPHIR_RETURN_CALL_METHOD(container, "get", NULL, 0, _0$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_OBS_VAR(_1);
	zephir_read_static_property_ce(&_1, yii_baseyii_ce, SL("app") TSRMLS_CC);
	_2 = Z_TYPE_P(_1) == IS_OBJECT;
	if (_2) {
		_3 = zephir_fetch_static_property_ce(yii_baseyii_ce, SL("app") TSRMLS_CC);
		_5 = zephir_fetch_nproperty_this(this_ptr, SL("id"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&_4, _3, "has", NULL, 0, _5);
		zephir_check_call_status();
		_2 = zephir_is_true(_4);
	}
	if (_2) {
		_6$$4 = zephir_fetch_static_property_ce(yii_baseyii_ce, SL("app") TSRMLS_CC);
		_7$$4 = zephir_fetch_nproperty_this(this_ptr, SL("id"), PH_NOISY_CC);
		ZEPHIR_RETURN_CALL_METHOD(_6$$4, "get", NULL, 0, _7$$4);
		zephir_check_call_status();
		RETURN_MM();
	} else {
		_8$$5 = zephir_fetch_static_property_ce(yii_baseyii_ce, SL("container") TSRMLS_CC);
		_9$$5 = zephir_fetch_nproperty_this(this_ptr, SL("id"), PH_NOISY_CC);
		ZEPHIR_RETURN_CALL_METHOD(_8$$5, "get", NULL, 0, _9$$5);
		zephir_check_call_status();
		RETURN_MM();
	}

}

