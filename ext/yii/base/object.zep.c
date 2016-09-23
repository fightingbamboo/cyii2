
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
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/concat.h"
#include "kernel/exception.h"


/**
 * @link http://www.yiiframework.com/
 * @copyright Copyright (c) 2008 Yii Software LLC
 * @license http://www.yiiframework.com/license/
 */
/**
 * Object is the base class that implements the *property* feature.
 *
 * A property is defined by a getter method (e.g. `getLabel`), and/or a setter method (e.g. `setLabel`). For example,
 * the following getter and setter methods define a property named `label`:
 *
 * ~~~
 * private _label;
 *
 * public function getLabel()
 * {
 *     return this->_label;
 * }
 *
 * public function setLabel(value)
 * {
 *     this->_label = value;
 * }
 * ~~~
 *
 * Property names are *case-insensitive*.
 *
 * A property can be accessed like a member variable of an object. Reading or writing a property will cause the invocation
 * of the corresponding getter or setter method. For example,
 *
 * ~~~
 * // equivalent to label = object->getLabel();
 * label = object->label;
 * // equivalent to object->setLabel('abc');
 * object->label = 'abc';
 * ~~~
 *
 * If a property has only a getter method and has no setter method, it is considered as *read-only*. In this case, trying
 * to modify the property value will cause an exception.
 *
 * One can call [[hasProperty()]], [[canGetProperty()]] and/or [[canSetProperty()]] to check the existence of a property.
 *
 * Besides the property feature, Object also introduces an important object initialization life cycle. In particular,
 * creating an new instance of Object or its derived class will involve the following life cycles sequentially:
 *
 * 1. the class constructor is invoked;
 * 2. object properties are initialized according to the given configuration;
 * 3. the `init()` method is invoked.
 *
 * In the above, both Step 2 and 3 occur at the end of the class constructor. It is recommended that
 * you perform object initialization in the `init()` method because at that stage, the object configuration
 * is already applied.
 *
 * In order to ensure the above life cycles, if a child class of Object needs to override the constructor,
 * it should be done like the following:
 *
 * ~~~
 * public function __construct(param1, param2, ..., config = [])
 * {
 *     ...
 *     parent::__construct(config);
 * }
 * ~~~
 *
 * That is, a `config` parameter (defaults to `[]`) should be declared as the last parameter
 * of the constructor, and the parent implementation should be called at the end of the constructor.
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
ZEPHIR_INIT_CLASS(yii_base_Object) {

	ZEPHIR_REGISTER_CLASS(yii\\base, Object, yii, base_object, yii_base_object_method_entry, 0);

	zend_class_implements(yii_base_object_ce TSRMLS_CC, 1, yii_base_configurable_ce);
	return SUCCESS;

}

/**
 * @return string the fully qualified name of this class.
 */
PHP_METHOD(yii_base_Object, className) {

	

	zephir_get_called_class(return_value TSRMLS_CC);
	return;

}

/**
 * Constructor.
 * The default implementation does two things:
 *
 * - Initializes the object with the given configuration `config`.
 * - Call [[init()]].
 *
 * If this method is overridden in a child class, it is recommended that
 *
 * - the last parameter of the constructor is a configuration array, like `config` here.
 * - call the parent implementation at the end of the constructor.
 *
 * @param array config name-value pairs that will be used to initialize the object properties
 */
PHP_METHOD(yii_base_Object, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *config_param = NULL;
	zval *config = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &config_param);

	if (!config_param) {
		ZEPHIR_INIT_VAR(config);
		array_init(config);
	} else {
		zephir_get_arrval(config, config_param);
	}


	if (!(ZEPHIR_IS_EMPTY(config))) {
		ZEPHIR_CALL_CE_STATIC(NULL, yii_baseyii_ce, "configure", &_0, 1, this_ptr, config);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "init", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Initializes the object.
 * This method is invoked at the end of the constructor after the object is initialized with the
 * given configuration.
 */
PHP_METHOD(yii_base_Object, init) {

	


}

/**
 * Returns the value of an object property.
 *
 * Do not call this method directly as it is a PHP magic method that
 * will be implicitly called when executing `value = object->property;`.
 * @param string name the property name
 * @return mixed the property value
 * @throws UnknownPropertyException if the property is not defined
 * @throws InvalidCallException if the property is write-only
 * @see __set()
 */
PHP_METHOD(yii_base_Object, __get) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *getter = NULL, *setter = NULL, *_1$$5, *_2$$5, *_3$$5, *_4$$6, *_5$$6, *_6$$6;
	zval *name = NULL, *_0 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_CONCAT_SV(_0, "get", name);
	ZEPHIR_CPY_WRT(getter, _0);
	ZEPHIR_INIT_LNVAR(_0);
	ZEPHIR_CONCAT_SV(_0, "set", name);
	ZEPHIR_CPY_WRT(setter, _0);
	if ((zephir_method_exists(this_ptr, getter TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_RETURN_CALL_METHOD_ZVAL(this_ptr, getter, NULL, 0);
		zephir_check_call_status();
		RETURN_MM();
	} else {
		if ((zephir_method_exists(this_ptr, setter TSRMLS_CC)  == SUCCESS)) {
			ZEPHIR_INIT_VAR(_1$$5);
			object_init_ex(_1$$5, yii_base_invalidcallexception_ce);
			ZEPHIR_INIT_VAR(_2$$5);
			zephir_get_class(_2$$5, this_ptr, 0 TSRMLS_CC);
			ZEPHIR_INIT_VAR(_3$$5);
			ZEPHIR_CONCAT_SVSV(_3$$5, "Getting write-only property: ", _2$$5, "::", name);
			ZEPHIR_CALL_METHOD(NULL, _1$$5, "__construct", NULL, 2, _3$$5);
			zephir_check_call_status();
			zephir_throw_exception_debug(_1$$5, "yii/base/Object.zep", 139 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		} else {
			ZEPHIR_INIT_VAR(_4$$6);
			object_init_ex(_4$$6, yii_base_unknownpropertyexception_ce);
			ZEPHIR_INIT_VAR(_5$$6);
			zephir_get_class(_5$$6, this_ptr, 0 TSRMLS_CC);
			ZEPHIR_INIT_VAR(_6$$6);
			ZEPHIR_CONCAT_SVSV(_6$$6, "Getting unknown property: ", _5$$6, "::", name);
			ZEPHIR_CALL_METHOD(NULL, _4$$6, "__construct", NULL, 3, _6$$6);
			zephir_check_call_status();
			zephir_throw_exception_debug(_4$$6, "yii/base/Object.zep", 141 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}

}

/**
 * Sets value of an object property.
 *
 * Do not call this method directly as it is a PHP magic method that
 * will be implicitly called when executing `object->property = value;`.
 * @param string name the property name or the event name
 * @param mixed value the property value
 * @throws UnknownPropertyException if the property is not defined
 * @throws InvalidCallException if the property is read-only
 * @see __get()
 */
PHP_METHOD(yii_base_Object, __set) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *value, *getter = NULL, *setter = NULL, *_1$$5, *_2$$5, *_3$$5, *_4$$6, *_5$$6, *_6$$6;
	zval *name = NULL, *_0 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &value);

	zephir_get_strval(name, name_param);


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_CONCAT_SV(_0, "get", name);
	ZEPHIR_CPY_WRT(getter, _0);
	ZEPHIR_INIT_LNVAR(_0);
	ZEPHIR_CONCAT_SV(_0, "set", name);
	ZEPHIR_CPY_WRT(setter, _0);
	if ((zephir_method_exists(this_ptr, setter TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_CALL_METHOD_ZVAL(NULL, this_ptr, setter, NULL, 0, value);
		zephir_check_call_status();
	} else {
		if ((zephir_method_exists(this_ptr, getter TSRMLS_CC)  == SUCCESS)) {
			ZEPHIR_INIT_VAR(_1$$5);
			object_init_ex(_1$$5, yii_base_invalidcallexception_ce);
			ZEPHIR_INIT_VAR(_2$$5);
			zephir_get_class(_2$$5, this_ptr, 0 TSRMLS_CC);
			ZEPHIR_INIT_VAR(_3$$5);
			ZEPHIR_CONCAT_SVSV(_3$$5, "Setting read-only property: ", _2$$5, "::", name);
			ZEPHIR_CALL_METHOD(NULL, _1$$5, "__construct", NULL, 2, _3$$5);
			zephir_check_call_status();
			zephir_throw_exception_debug(_1$$5, "yii/base/Object.zep", 166 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		} else {
			ZEPHIR_INIT_VAR(_4$$6);
			object_init_ex(_4$$6, yii_base_unknownpropertyexception_ce);
			ZEPHIR_INIT_VAR(_5$$6);
			zephir_get_class(_5$$6, this_ptr, 0 TSRMLS_CC);
			ZEPHIR_INIT_VAR(_6$$6);
			ZEPHIR_CONCAT_SVSV(_6$$6, "Setting unknown property: ", _5$$6, "::", name);
			ZEPHIR_CALL_METHOD(NULL, _4$$6, "__construct", NULL, 3, _6$$6);
			zephir_check_call_status();
			zephir_throw_exception_debug(_4$$6, "yii/base/Object.zep", 168 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Checks if the named property is set (not null).
 *
 * Do not call this method directly as it is a PHP magic method that
 * will be implicitly called when executing `isset(object->property)`.
 *
 * Note that if the property is not defined, false will be returned.
 * @param string name the property name or the event name
 * @return boolean whether the named property is set (not null).
 */
PHP_METHOD(yii_base_Object, __isset) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *getter = NULL, *_1$$3 = NULL;
	zval *name = NULL, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_CONCAT_SV(_0, "get", name);
	ZEPHIR_CPY_WRT(getter, _0);
	if ((zephir_method_exists(this_ptr, getter TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_CALL_METHOD_ZVAL(&_1$$3, this_ptr, getter, NULL, 0);
		zephir_check_call_status();
		RETURN_MM_BOOL(Z_TYPE_P(_1$$3) != IS_NULL);
	} else {
		RETURN_MM_BOOL(0);
	}

}

/**
 * Sets an object property to null.
 *
 * Do not call this method directly as it is a PHP magic method that
 * will be implicitly called when executing `unset(object->property)`.
 *
 * Note that if the property is not defined, this method will do nothing.
 * If the property is read-only, it will throw an exception.
 * @param string name the property name
 * @throws InvalidCallException if the property is read only.
 */
PHP_METHOD(yii_base_Object, __unset) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *getter = NULL, *setter = NULL, *_1$$3, *_2$$5, *_3$$5, *_4$$5;
	zval *name = NULL, *_0 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_CONCAT_SV(_0, "get", name);
	ZEPHIR_CPY_WRT(getter, _0);
	ZEPHIR_INIT_LNVAR(_0);
	ZEPHIR_CONCAT_SV(_0, "set", name);
	ZEPHIR_CPY_WRT(setter, _0);
	if ((zephir_method_exists(this_ptr, setter TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_INIT_VAR(_1$$3);
		ZVAL_NULL(_1$$3);
		ZEPHIR_CALL_METHOD_ZVAL(NULL, this_ptr, setter, NULL, 0, _1$$3);
		zephir_check_call_status();
	} else {
		if ((zephir_method_exists(this_ptr, getter TSRMLS_CC)  == SUCCESS)) {
			ZEPHIR_INIT_VAR(_2$$5);
			object_init_ex(_2$$5, yii_base_invalidcallexception_ce);
			ZEPHIR_INIT_VAR(_3$$5);
			zephir_get_class(_3$$5, this_ptr, 0 TSRMLS_CC);
			ZEPHIR_INIT_VAR(_4$$5);
			ZEPHIR_CONCAT_SVSV(_4$$5, "Unsetting read-only property: ", _3$$5, "::", name);
			ZEPHIR_CALL_METHOD(NULL, _2$$5, "__construct", NULL, 2, _4$$5);
			zephir_check_call_status();
			zephir_throw_exception_debug(_2$$5, "yii/base/Object.zep", 215 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Calls the named method which is not a class method.
 *
 * Do not call this method directly as it is a PHP magic method that
 * will be implicitly called when an unknown method is being invoked.
 * @param string name the method name
 * @param array params method parameters
 * @throws UnknownMethodException when calling unknown method
 * @return mixed the method return value
 */
PHP_METHOD(yii_base_Object, __call) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name, *params, *_0, *_1, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name, &params);



	ZEPHIR_INIT_VAR(_0);
	object_init_ex(_0, yii_base_unknownmethodexception_ce);
	ZEPHIR_INIT_VAR(_1);
	zephir_get_class(_1, this_ptr, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_SVS(_2, "Calling unknown method: ", _1, "::name()");
	ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, 2, _2);
	zephir_check_call_status();
	zephir_throw_exception_debug(_0, "yii/base/Object.zep", 232 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Returns a value indicating whether a property is defined.
 * A property is defined if:
 *
 * - the class has a getter or setter method associated with the specified name
 *   (in this case, property name is case-insensitive);
 * - the class has a member variable with the specified name (when `checkVars` is true);
 *
 * @param string name the property name
 * @param boolean checkVars whether to treat member variables as properties
 * @return boolean whether the property is defined
 * @see canGetProperty()
 * @see canSetProperty()
 */
PHP_METHOD(yii_base_Object, hasProperty) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool checkVars, _2;
	zval *name_param = NULL, *checkVars_param = NULL, *_0 = NULL, *_1, *_3 = NULL, *_4;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name_param, &checkVars_param);

	zephir_get_strval(name, name_param);
	if (!checkVars_param) {
		checkVars = 1;
	} else {
		checkVars = zephir_get_boolval(checkVars_param);
	}


	ZEPHIR_INIT_VAR(_1);
	if (checkVars) {
		ZVAL_BOOL(_1, 1);
	} else {
		ZVAL_BOOL(_1, 0);
	}
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "cangetproperty", NULL, 0, name, _1);
	zephir_check_call_status();
	_2 = zephir_is_true(_0);
	if (!(_2)) {
		ZEPHIR_INIT_VAR(_4);
		ZVAL_BOOL(_4, 0);
		ZEPHIR_CALL_METHOD(&_3, this_ptr, "cansetproperty", NULL, 0, name, _4);
		zephir_check_call_status();
		_2 = zephir_is_true(_3);
	}
	RETURN_MM_BOOL(_2);

}

/**
 * Returns a value indicating whether a property can be read.
 * A property is readable if:
 *
 * - the class has a getter method associated with the specified name
 *   (in this case, property name is case-insensitive);
 * - the class has a member variable with the specified name (when `checkVars` is true);
 *
 * @param string name the property name
 * @param boolean checkVars whether to treat member variables as properties
 * @return boolean whether the property can be read
 * @see canSetProperty()
 */
PHP_METHOD(yii_base_Object, canGetProperty) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool checkVars, _1, _2;
	zval *name_param = NULL, *checkVars_param = NULL, *_3 = NULL;
	zval *name = NULL, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name_param, &checkVars_param);

	zephir_get_strval(name, name_param);
	if (!checkVars_param) {
		checkVars = 1;
	} else {
		checkVars = zephir_get_boolval(checkVars_param);
	}


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_CONCAT_SV(_0, "get", name);
	_1 = (zephir_method_exists(this_ptr, _0 TSRMLS_CC)  == SUCCESS);
	if (!(_1)) {
		_2 = checkVars;
		if (_2) {
			ZEPHIR_CALL_FUNCTION(&_3, "property_exists", NULL, 4, this_ptr, name);
			zephir_check_call_status();
			_2 = zephir_is_true(_3);
		}
		_1 = _2;
	}
	RETURN_MM_BOOL(_1);

}

/**
 * Returns a value indicating whether a property can be set.
 * A property is writable if:
 *
 * - the class has a setter method associated with the specified name
 *   (in this case, property name is case-insensitive);
 * - the class has a member variable with the specified name (when `checkVars` is true);
 *
 * @param string name the property name
 * @param boolean checkVars whether to treat member variables as properties
 * @return boolean whether the property can be written
 * @see canGetProperty()
 */
PHP_METHOD(yii_base_Object, canSetProperty) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool checkVars, _1, _2;
	zval *name_param = NULL, *checkVars_param = NULL, *_3 = NULL;
	zval *name = NULL, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name_param, &checkVars_param);

	zephir_get_strval(name, name_param);
	if (!checkVars_param) {
		checkVars = 1;
	} else {
		checkVars = zephir_get_boolval(checkVars_param);
	}


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_CONCAT_SV(_0, "set", name);
	_1 = (zephir_method_exists(this_ptr, _0 TSRMLS_CC)  == SUCCESS);
	if (!(_1)) {
		_2 = checkVars;
		if (_2) {
			ZEPHIR_CALL_FUNCTION(&_3, "property_exists", NULL, 4, this_ptr, name);
			zephir_check_call_status();
			_2 = zephir_is_true(_3);
		}
		_1 = _2;
	}
	RETURN_MM_BOOL(_1);

}

/**
 * Returns a value indicating whether a method is defined.
 *
 * The default implementation is a call to php function `method_exists()`.
 * You may override this method when you implemented the php magic method `__call()`.
 * @param string name the property name
 * @return boolean whether the property is defined
 */
PHP_METHOD(yii_base_Object, hasMethod) {

	zval *name_param = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	RETURN_MM_BOOL((zephir_method_exists(this_ptr, name TSRMLS_CC)  == SUCCESS));

}

