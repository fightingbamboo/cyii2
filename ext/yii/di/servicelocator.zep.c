
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
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/object.h"
#include "Zend/zend_closures.h"
#include "kernel/exception.h"
#include "kernel/concat.h"
#include "kernel/hash.h"


/**
 * @link http://www.yiiframework.com/
 * @copyright Copyright (c) 2008 Yii Software LLC
 * @license http://www.yiiframework.com/license/
 */
/**
 * ServiceLocator implements a [service locator](http://en.wikipedia.org/wiki/Service_locator_pattern).
 *
 * To use ServiceLocator, you first need to register component IDs with the corresponding component
 * definitions with the locator by calling [[set()]] or [[setComponents()]].
 * You can then call [[get()]] to retrieve a component with the specified ID. The locator will automatically
 * instantiate and configure the component according to the definition.
 *
 * For example,
 *
 * ```php
 * $locator = new \yii\di\ServiceLocator;
 * $locator->setComponents([
 *     'db' => [
 *         'class' => 'yii\db\Connection',
 *         'dsn' => 'sqlite:path/to/file.db',
 *     ],
 *     'cache' => [
 *         'class' => 'yii\caching\DbCache',
 *         'db' => 'db',
 *     ],
 * ]);
 *
 * $db = $locator->get('db');  // or $locator->db
 * $cache = $locator->get('cache');  // or $locator->cache
 * ```
 *
 * Because [[\yii\base\Module]] extends from ServiceLocator, modules and the application are all service locators.
 *
 * @property array $components The list of the component definitions or the loaded component instances (ID =>
 * definition or instance). This property is read-only.
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
ZEPHIR_INIT_CLASS(yii_di_ServiceLocator) {

	ZEPHIR_REGISTER_CLASS_EX(yii\\di, ServiceLocator, yii, di_servicelocator, yii_base_component_ce, yii_di_servicelocator_method_entry, 0);

	/**
	 * @var array shared component instances indexed by their IDs
	 */
	zend_declare_property_null(yii_di_servicelocator_ce, SL("_components"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var array component definitions indexed by their IDs
	 */
	zend_declare_property_null(yii_di_servicelocator_ce, SL("_definitions"), ZEND_ACC_PROTECTED TSRMLS_CC);

	yii_di_servicelocator_ce->create_object = zephir_init_properties_yii_di_ServiceLocator;
	return SUCCESS;

}

/**
 * Getter magic method.
 * This method is overridden to support accessing components like reading properties.
 * @param string $name component or property name
 * @return mixed the named property value
 */
PHP_METHOD(yii_di_ServiceLocator, __get) {

	zephir_fcall_cache_entry *_1 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *_0 = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "has", NULL, 0, name);
	zephir_check_call_status();
	if (zephir_is_true(_0)) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "get", NULL, 0, name);
		zephir_check_call_status();
		RETURN_MM();
	} else {
		ZEPHIR_RETURN_CALL_PARENT(yii_di_servicelocator_ce, this_ptr, "__get", &_1, 33, name);
		zephir_check_call_status();
		RETURN_MM();
	}

}

/**
 * Checks if a property value is null.
 * This method overrides the parent implementation by checking if the named component is loaded.
 * @param string $name the property name or the event name
 * @return boolean whether the property value is null
 */
PHP_METHOD(yii_di_ServiceLocator, __isset) {

	zephir_fcall_cache_entry *_2 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *_0 = NULL, *_1;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_INIT_VAR(_1);
	ZVAL_BOOL(_1, 1);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "has", NULL, 0, name, _1);
	zephir_check_call_status();
	if (zephir_is_true(_0)) {
		RETURN_MM_BOOL(1);
	} else {
		ZEPHIR_RETURN_CALL_PARENT(yii_di_servicelocator_ce, this_ptr, "__isset", &_2, 34, name);
		zephir_check_call_status();
		RETURN_MM();
	}

}

/**
 * Returns a value indicating whether the locator has the specified component definition or has instantiated the component.
 * This method may return different results depending on the value of `$checkInstance`.
 *
 * - If `$checkInstance` is false (default), the method will return a value indicating whether the locator has the specified
 *   component definition.
 * - If `$checkInstance` is true, the method will return a value indicating whether the locator has
 *   instantiated the specified component.
 *
 * @param string $id component ID (e.g. `db`).
 * @param boolean $checkInstance whether the method should check if the component is shared and instantiated.
 * @return boolean whether the locator has the specified component definition or has instantiated the component.
 * @see set()
 */
PHP_METHOD(yii_di_ServiceLocator, has) {

	zend_bool checkInstance;
	zval *id_param = NULL, *checkInstance_param = NULL, *_0$$3, *_1$$4;
	zval *id = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &id_param, &checkInstance_param);

	zephir_get_strval(id, id_param);
	if (!checkInstance_param) {
		checkInstance = 0;
	} else {
		checkInstance = zephir_get_boolval(checkInstance_param);
	}


	if (checkInstance) {
		_0$$3 = zephir_fetch_nproperty_this(this_ptr, SL("_components"), PH_NOISY_CC);
		RETURN_MM_BOOL(zephir_array_isset(_0$$3, id));
	} else {
		_1$$4 = zephir_fetch_nproperty_this(this_ptr, SL("_definitions"), PH_NOISY_CC);
		RETURN_MM_BOOL(zephir_array_isset(_1$$4, id));
	}

}

/**
 * Returns the component instance with the specified ID.
 *
 * @param string $id component ID (e.g. `db`).
 * @param boolean $throwException whether to throw an exception if `$id` is not registered with the locator before.
 * @return object|null the component of the specified ID. If `$throwException` is false and `$id`
 * is not registered before, null will be returned.
 * @throws InvalidConfigException if `$id` refers to a nonexistent component ID
 * @see has()
 * @see set()
 */
PHP_METHOD(yii_di_ServiceLocator, get) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_3 = NULL;
	zend_bool throwException, _2$$4;
	zval *id_param = NULL, *throwException_param = NULL, *component = NULL, *_0, *definition = NULL, *copy_definition = NULL, *copy_object = NULL, *object = NULL, *_1, *_4$$7;
	zval *id = NULL, *_5$$7;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &id_param, &throwException_param);

	zephir_get_strval(id, id_param);
	if (!throwException_param) {
		throwException = 1;
	} else {
		throwException = zephir_get_boolval(throwException_param);
	}


	ZEPHIR_OBS_VAR(component);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_components"), PH_NOISY_CC);
	if (zephir_array_isset_fetch(&component, _0, id, 0 TSRMLS_CC)) {
		RETURN_CCTOR(component);
	}
	ZEPHIR_OBS_VAR(definition);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_definitions"), PH_NOISY_CC);
	if (zephir_array_isset_fetch(&definition, _1, id, 0 TSRMLS_CC)) {
		ZEPHIR_CPY_WRT(copy_definition, definition);
		_2$$4 = Z_TYPE_P(definition) == IS_OBJECT;
		if (_2$$4) {
			_2$$4 = !((zephir_instance_of_ev(definition, zend_ce_closure TSRMLS_CC)));
		}
		if (_2$$4) {
			zephir_update_property_array(this_ptr, SL("_components"), id, copy_definition TSRMLS_CC);
			RETURN_CCTOR(definition);
		} else {
			ZEPHIR_CALL_CE_STATIC(&object, yii_baseyii_ce, "createobject", &_3, 6, copy_definition);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(copy_object, object);
			zephir_update_property_array(this_ptr, SL("_components"), id, copy_object TSRMLS_CC);
			RETURN_CCTOR(object);
		}
	} else if (throwException) {
		ZEPHIR_INIT_VAR(_4$$7);
		object_init_ex(_4$$7, yii_base_invalidconfigexception_ce);
		ZEPHIR_INIT_VAR(_5$$7);
		ZEPHIR_CONCAT_SV(_5$$7, "Unknown component ID: ", id);
		ZEPHIR_CALL_METHOD(NULL, _4$$7, "__construct", NULL, 3, _5$$7);
		zephir_check_call_status();
		zephir_throw_exception_debug(_4$$7, "yii/di/ServiceLocator.zep", 147 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} else {
		RETURN_MM_NULL();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Registers a component definition with this locator.
 *
 * For example,
 *
 * ```php
 * // a class name
 * $locator->set('cache', 'yii\caching\FileCache');
 *
 * // a configuration array
 * $locator->set('db', [
 *     'class' => 'yii\db\Connection',
 *     'dsn' => 'mysql:host=127.0.0.1;dbname=demo',
 *     'username' => 'root',
 *     'password' => '',
 *     'charset' => 'utf8',
 * ]);
 *
 * // an anonymous function
 * $locator->set('cache', function ($params) {
 *     return new \yii\caching\FileCache;
 * });
 *
 * // an instance
 * $locator->set('cache', new \yii\caching\FileCache);
 * ```
 *
 * If a component definition with the same ID already exists, it will be overwritten.
 *
 * @param string $id component ID (e.g. `db`).
 * @param mixed $definition the component definition to be registered with this locator.
 * It can be one of the followings:
 *
 * - a class name
 * - a configuration array: the array contains name-value pairs that will be used to
 *   initialize the property values of the newly created object when [[get()]] is called.
 *   The `class` element is required and stands for the the class of the object to be created.
 * - a PHP callable: either an anonymous function or an array representing a class method (e.g. `['Foo', 'bar']`).
 *   The callable will be called by [[get()]] to return an object associated with the specified component ID.
 * - an object: When [[get()]] is called, this object will be returned.
 *
 * @throws InvalidConfigException if the definition is an invalid configuration array
 */
PHP_METHOD(yii_di_ServiceLocator, set) {

	zend_bool _3;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *id_param = NULL, *definition, *_0$$3, *_1$$3, *_2, *_4, *_5 = NULL, *_6$$8, *_8$$9, *_9$$9, *_10$$9;
	zval *id = NULL, *text$$8, *_7$$8;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &id_param, &definition);

	zephir_get_strval(id, id_param);


	if (Z_TYPE_P(definition) == IS_NULL) {
		_0$$3 = zephir_fetch_nproperty_this(this_ptr, SL("_components"), PH_NOISY_CC);
		zephir_array_unset(&_0$$3, id, PH_SEPARATE);
		_1$$3 = zephir_fetch_nproperty_this(this_ptr, SL("_definitions"), PH_NOISY_CC);
		zephir_array_unset(&_1$$3, id, PH_SEPARATE);
		RETURN_MM_NULL();
	}
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("_components"), PH_NOISY_CC);
	zephir_array_unset(&_2, id, PH_SEPARATE);
	_3 = Z_TYPE_P(definition) == IS_OBJECT;
	if (!(_3)) {
		ZEPHIR_INIT_VAR(_4);
		ZVAL_BOOL(_4, 1);
		ZEPHIR_CALL_FUNCTION(&_5, "is_callable", NULL, 19, definition, _4);
		zephir_check_call_status();
		_3 = zephir_is_true(_5);
	}
	if (_3) {
		zephir_update_property_array(this_ptr, SL("_definitions"), id, definition TSRMLS_CC);
	} else {
		if (Z_TYPE_P(definition) == IS_ARRAY) {
			if (zephir_array_isset_string(definition, SS("class"))) {
				zephir_update_property_array(this_ptr, SL("_definitions"), id, definition TSRMLS_CC);
			} else {
				ZEPHIR_INIT_VAR(text$$8);
				ZVAL_STRING(text$$8, "class", 1);
				ZEPHIR_INIT_VAR(_6$$8);
				object_init_ex(_6$$8, yii_base_invalidconfigexception_ce);
				ZEPHIR_INIT_VAR(_7$$8);
				ZEPHIR_CONCAT_SVSVS(_7$$8, "The configuration for the \"", id, "\" component must contain a \"", text$$8, "\" element.");
				ZEPHIR_CALL_METHOD(NULL, _6$$8, "__construct", NULL, 3, _7$$8);
				zephir_check_call_status();
				zephir_throw_exception_debug(_6$$8, "yii/di/ServiceLocator.zep", 216 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_INIT_VAR(_8$$9);
			object_init_ex(_8$$9, yii_base_invalidconfigexception_ce);
			ZEPHIR_INIT_VAR(_9$$9);
			zephir_gettype(_9$$9, definition TSRMLS_CC);
			ZEPHIR_INIT_VAR(_10$$9);
			ZEPHIR_CONCAT_SVSV(_10$$9, "Unexpected configuration type for the \"", id, "\" component: ", _9$$9);
			ZEPHIR_CALL_METHOD(NULL, _8$$9, "__construct", NULL, 3, _10$$9);
			zephir_check_call_status();
			zephir_throw_exception_debug(_8$$9, "yii/di/ServiceLocator.zep", 219 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Removes the component from the locator.
 * @param string $id the component ID
 */
PHP_METHOD(yii_di_ServiceLocator, clear) {

	zval *id_param = NULL, *_0, *_1;
	zval *id = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &id_param);

	zephir_get_strval(id, id_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_definitions"), PH_NOISY_CC);
	zephir_array_unset(&_0, id, PH_SEPARATE);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_components"), PH_NOISY_CC);
	zephir_array_unset(&_1, id, PH_SEPARATE);
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns the list of the component definitions or the loaded component instances.
 * @param boolean $returnDefinitions whether to return component definitions instead of the loaded component instances.
 * @return array the list of the component definitions or the loaded component instances (ID => definition or instance).
 */
PHP_METHOD(yii_di_ServiceLocator, getComponents) {

	zval *returnDefinitions_param = NULL, *_0;
	zend_bool returnDefinitions;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &returnDefinitions_param);

	if (!returnDefinitions_param) {
		returnDefinitions = 1;
	} else {
		returnDefinitions = zephir_get_boolval(returnDefinitions_param);
	}


	ZEPHIR_INIT_VAR(_0);
	if (returnDefinitions) {
		zephir_read_property_this(&_0, this_ptr, SL("_definitions"), PH_NOISY_CC);
	} else {
		zephir_read_property_this(&_0, this_ptr, SL("_components"), PH_NOISY_CC);
	}
	RETURN_CCTOR(_0);

}

/**
 * Registers a set of component definitions in this locator.
 *
 * This is the bulk version of [[set()]]. The parameter should be an array
 * whose keys are component IDs and values the corresponding component definitions.
 *
 * For more details on how to specify component IDs and definitions, please refer to [[set()]].
 *
 * If a component definition with the same ID already exists, it will be overwritten.
 *
 * The following is an example for registering two component definitions:
 *
 * ```php
 * [
 *     'db' => [
 *         'class' => 'yii\db\Connection',
 *         'dsn' => 'sqlite:path/to/file.db',
 *     ],
 *     'cache' => [
 *         'class' => 'yii\caching\DbCache',
 *         'db' => 'db',
 *     ],
 * ]
 * ```
 *
 * @param array $components component definitions or instances
 */
PHP_METHOD(yii_di_ServiceLocator, setComponents) {

	HashTable *_1;
	HashPosition _0;
	zephir_fcall_cache_entry *_3 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *components, *id = NULL, *component = NULL, **_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &components);



	zephir_is_iterable(components, &_1, &_0, 0, 0, "yii/di/ServiceLocator.zep", 277);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HMKEY(id, _1, _0);
		ZEPHIR_GET_HVALUE(component, _2);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "set", &_3, 0, id, component);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

zend_object_value zephir_init_properties_yii_di_ServiceLocator(zend_class_entry *class_type TSRMLS_DC) {

		zval *_0, *_2, *_4, *_1$$3, *_3$$4, *_5$$5;

		ZEPHIR_MM_GROW();
	
	{
		zval *this_ptr = NULL;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("_definitions"), PH_NOISY_CC);
		if (Z_TYPE_P(_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(_1$$3);
			array_init(_1$$3);
			zephir_update_property_this(this_ptr, SL("_definitions"), _1$$3 TSRMLS_CC);
		}
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
		if (Z_TYPE_P(_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(_3$$4);
			array_init(_3$$4);
			zephir_update_property_this(this_ptr, SL("_events"), _3$$4 TSRMLS_CC);
		}
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("_components"), PH_NOISY_CC);
		if (Z_TYPE_P(_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(_5$$5);
			array_init(_5$$5);
			zephir_update_property_this(this_ptr, SL("_components"), _5$$5 TSRMLS_CC);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJVAL_P(this_ptr);
	}

}

