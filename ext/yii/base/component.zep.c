
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
#include "kernel/concat.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/hash.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/string.h"
#include "kernel/array.h"


/**
 * @link http://www.yiiframework.com/
 * @copyright Copyright (c) 2008 Yii Software LLC
 * @license http://www.yiiframework.com/license/
 */
/**
 * Component is the base class that implements the *property*, *event* and *behavior* features.
 *
 * Component provides the *event* and *behavior* features, in addition to the *property* feature which is implemented in
 * its parent class [[Object]].
 *
 * Event is a way to "inject" custom code into existing code at certain places. For example, a comment object can trigger
 * an "add" event when the user adds a comment. We can write custom code and attach it to this event so that when the event
 * is triggered (i.e. comment will be added), our custom code will be executed.
 *
 * An event is identified by a name that should be unique within the class it is defined at. Event names are *case-sensitive*.
 *
 * One or multiple PHP callbacks, called *event handlers*, can be attached to an event. You can call [[trigger()]] to
 * raise an event. When an event is raised, the event handlers will be invoked automatically in the order they were
 * attached.
 *
 * To attach an event handler to an event, call [[on()]]:
 *
 * ~~~
 * $post->on('update', function ($event) {
 *     // send email notification
 * });
 * ~~~
 *
 * In the above, an anonymous function is attached to the "update" event of the post. You may attach
 * the following types of event handlers:
 *
 * - anonymous function: `function ($event) { ... }`
 * - object method: `[$object, 'handleAdd']`
 * - static class method: `['Page', 'handleAdd']`
 * - global function: `'handleAdd'`
 *
 * The signature of an event handler should be like the following:
 *
 * ~~~
 * function foo($event)
 * ~~~
 *
 * where `$event` is an [[Event]] object which includes parameters associated with the event.
 *
 * You can also attach a handler to an event when configuring a component with a configuration array.
 * The syntax is like the following:
 *
 * ~~~
 * [
 *     'on add' => function ($event) { ... }
 * ]
 * ~~~
 *
 * where `on add` stands for attaching an event to the `add` event.
 *
 * Sometimes, you may want to associate extra data with an event handler when you attach it to an event
 * and then access it when the handler is invoked. You may do so by
 *
 * ~~~
 * $post->on('update', function ($event) {
 *     // the data can be accessed via $event->data
 * }, $data);
 * ~~~
 *
 * A behavior is an instance of [[Behavior]] or its child class. A component can be attached with one or multiple
 * behaviors. When a behavior is attached to a component, its public properties and methods can be accessed via the
 * component directly, as if the component owns those properties and methods.
 *
 * To attach a behavior to a component, declare it in [[behaviors()]], or explicitly call [[attachBehavior]]. Behaviors
 * declared in [[behaviors()]] are automatically attached to the corresponding component.
 *
 * One can also attach a behavior to a component when configuring it with a configuration array. The syntax is like the
 * following:
 *
 * ~~~
 * [
 *     'as tree' => [
 *         'class' => 'Tree',
 *     ],
 * ]
 * ~~~
 *
 * where `as tree` stands for attaching a behavior named `tree`, and the array will be passed to [[\Yii::createObject()]]
 * to create the behavior object.
 *
 * @property Behavior[] $behaviors List of behaviors attached to this component. This property is read-only.
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
ZEPHIR_INIT_CLASS(yii_base_Component) {

	ZEPHIR_REGISTER_CLASS_EX(yii\\base, Component, yii, base_component, yii_base_object_ce, yii_base_component_method_entry, 0);

	/**
	 * @var array the attached event handlers (event name => handlers)
	 */
	zend_declare_property_null(yii_base_component_ce, SL("_events"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var Behavior[] the attached behaviors (behavior name => behavior)
	 */
	zend_declare_property_null(yii_base_component_ce, SL("_behaviors"), ZEND_ACC_PROTECTED TSRMLS_CC);

	yii_base_component_ce->create_object = zephir_init_properties_yii_base_Component;
	return SUCCESS;

}

/**
 * Returns the value of a component property.
 * This method will check in the following order and act accordingly:
 *
 *  - a property defined by a getter: return the getter result
 *  - a property of a behavior: return the behavior property value
 *
 * Do not call this method directly as it is a PHP magic method that
 * will be implicitly called when executing `$value = $component->property;`.
 * @param string $name the property name
 * @return mixed the property value or the value of a behavior's property
 * @throws UnknownPropertyException if the property is not defined
 * @throws InvalidCallException if the property is write-only.
 * @see __set()
 */
PHP_METHOD(yii_base_Component, __get) {

	HashTable *_3$$4;
	HashPosition _2$$4;
	zephir_fcall_cache_entry *_6 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *getter = NULL, *setter = NULL, *behavior$$4 = NULL, *_1$$4, **_4$$4, *_5$$5 = NULL, *_7$$6 = NULL, *_8$$7, *_9$$7, *_10$$7, *_11$$8, *_12$$8, *_13$$8;
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
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
		zephir_check_call_status();
		_1$$4 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
		zephir_is_iterable(_1$$4, &_3$$4, &_2$$4, 0, 0, "yii/base/Component.zep", 139);
		for (
		  ; zephir_hash_get_current_data_ex(_3$$4, (void**) &_4$$4, &_2$$4) == SUCCESS
		  ; zephir_hash_move_forward_ex(_3$$4, &_2$$4)
		) {
			ZEPHIR_GET_HVALUE(behavior$$4, _4$$4);
			ZEPHIR_CALL_METHOD(&_5$$5, behavior$$4, "cangetproperty", &_6, 0, name);
			zephir_check_call_status();
			if (zephir_is_true(_5$$5)) {
				ZEPHIR_OBS_NVAR(_7$$6);
				zephir_read_property_zval(&_7$$6, behavior$$4, name, PH_NOISY_CC);
				RETURN_CCTOR(_7$$6);
			}
		}
	}
	if ((zephir_method_exists(this_ptr, setter TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_INIT_VAR(_8$$7);
		object_init_ex(_8$$7, yii_base_invalidcallexception_ce);
		ZEPHIR_INIT_VAR(_9$$7);
		zephir_get_class(_9$$7, this_ptr, 0 TSRMLS_CC);
		ZEPHIR_INIT_VAR(_10$$7);
		ZEPHIR_CONCAT_SVSV(_10$$7, "Getting write-only property: ", _9$$7, "::", name);
		ZEPHIR_CALL_METHOD(NULL, _8$$7, "__construct", NULL, 2, _10$$7);
		zephir_check_call_status();
		zephir_throw_exception_debug(_8$$7, "yii/base/Component.zep", 141 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} else {
		ZEPHIR_INIT_VAR(_11$$8);
		object_init_ex(_11$$8, yii_base_unknownpropertyexception_ce);
		ZEPHIR_INIT_VAR(_12$$8);
		zephir_get_class(_12$$8, this_ptr, 0 TSRMLS_CC);
		ZEPHIR_INIT_VAR(_13$$8);
		ZEPHIR_CONCAT_SVSV(_13$$8, "Getting unknown property: ", _12$$8, "::", name);
		ZEPHIR_CALL_METHOD(NULL, _11$$8, "__construct", NULL, 3, _13$$8);
		zephir_check_call_status();
		zephir_throw_exception_debug(_11$$8, "yii/base/Component.zep", 143 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}

}

/**
 * Sets the value of a component property.
 * This method will check in the following order and act accordingly:
 *
 *  - a property defined by a setter: set the property value
 *  - an event in the format of "on xyz": attach the handler to the event "xyz"
 *  - a behavior in the format of "as xyz": attach the behavior named as "xyz"
 *  - a property of a behavior: set the behavior property value
 *
 * Do not call this method directly as it is a PHP magic method that
 * will be implicitly called when executing `$component->property = $value;`.
 * @param string $name the property name or the event name
 * @param mixed $value the property value
 * @throws UnknownPropertyException if the property is not defined
 * @throws InvalidCallException if the property is read-only.
 * @see __get()
 */
PHP_METHOD(yii_base_Component, __set) {

	HashTable *_20$$10;
	HashPosition _19$$10;
	zend_bool _4$$4, _10$$6, _14$$7;
	zephir_fcall_cache_entry *_3 = NULL, *_15 = NULL, *_17 = NULL, *_23 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *value, *getter = NULL, *setter = NULL, *cmp_result = NULL, _1$$4, _2$$4, _5$$5, *_6$$5, *_7$$5, _8$$6, _9$$6, _11$$7, *_12$$7, *_13$$7, *_16$$9 = NULL, *behavior$$10 = NULL, *_18$$10, **_21$$10, *_22$$11 = NULL, *_24$$13, *_25$$13, *_26$$13, *_27$$14, *_28$$14, *_29$$14;
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
		RETURN_MM_NULL();
	} else {
		ZEPHIR_SINIT_VAR(_1$$4);
		ZVAL_STRING(&_1$$4, "on ", 0);
		ZEPHIR_SINIT_VAR(_2$$4);
		ZVAL_LONG(&_2$$4, 3);
		ZEPHIR_CALL_FUNCTION(&cmp_result, "strncmp", &_3, 5, name, &_1$$4, &_2$$4);
		zephir_check_call_status();
		_4$$4 = Z_TYPE_P(cmp_result) != IS_BOOL;
		if (_4$$4) {
			_4$$4 = ZEPHIR_IS_LONG(cmp_result, 0);
		}
		if (_4$$4) {
			ZEPHIR_SINIT_VAR(_5$$5);
			ZVAL_LONG(&_5$$5, 3);
			ZEPHIR_INIT_VAR(_6$$5);
			zephir_substr(_6$$5, name, 3 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
			zephir_get_strval(name, _6$$5);
			ZEPHIR_INIT_VAR(_7$$5);
			zephir_fast_trim(_7$$5, name, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
			zephir_get_strval(name, _7$$5);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "on", NULL, 0, name, value);
			zephir_check_call_status();
			RETURN_MM_NULL();
		} else {
			ZEPHIR_SINIT_VAR(_8$$6);
			ZVAL_STRING(&_8$$6, "as ", 0);
			ZEPHIR_SINIT_VAR(_9$$6);
			ZVAL_LONG(&_9$$6, 3);
			ZEPHIR_CALL_FUNCTION(&cmp_result, "strncmp", &_3, 5, name, &_8$$6, &_9$$6);
			zephir_check_call_status();
			_10$$6 = Z_TYPE_P(cmp_result) != IS_BOOL;
			if (_10$$6) {
				_10$$6 = ZEPHIR_IS_LONG(cmp_result, 0);
			}
			if (_10$$6) {
				ZEPHIR_SINIT_VAR(_11$$7);
				ZVAL_LONG(&_11$$7, 3);
				ZEPHIR_INIT_VAR(_12$$7);
				zephir_substr(_12$$7, name, 3 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
				zephir_get_strval(name, _12$$7);
				ZEPHIR_INIT_VAR(_13$$7);
				zephir_fast_trim(_13$$7, name, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
				zephir_get_strval(name, _13$$7);
				_14$$7 = Z_TYPE_P(value) == IS_OBJECT;
				if (_14$$7) {
					_14$$7 = (zephir_is_instance_of(value, SL("yii\\base\\Behavior") TSRMLS_CC));
				}
				if (_14$$7) {
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "attachbehavior", &_15, 0, name, value);
					zephir_check_call_status();
				} else {
					ZEPHIR_CALL_CE_STATIC(&_16$$9, yii_baseyii_ce, "createobject", &_17, 6, value);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "attachbehavior", &_15, 0, name, _16$$9);
					zephir_check_call_status();
				}
				RETURN_MM_NULL();
			} else {
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
				zephir_check_call_status();
				_18$$10 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
				zephir_is_iterable(_18$$10, &_20$$10, &_19$$10, 0, 0, "yii/base/Component.zep", 210);
				for (
				  ; zephir_hash_get_current_data_ex(_20$$10, (void**) &_21$$10, &_19$$10) == SUCCESS
				  ; zephir_hash_move_forward_ex(_20$$10, &_19$$10)
				) {
					ZEPHIR_GET_HVALUE(behavior$$10, _21$$10);
					ZEPHIR_CALL_METHOD(&_22$$11, behavior$$10, "cansetproperty", &_23, 0, name);
					zephir_check_call_status();
					if (zephir_is_true(_22$$11)) {
						zephir_update_property_zval_zval(behavior$$10, name, value TSRMLS_CC);
						RETURN_MM_NULL();
					}
				}
			}
		}
	}
	if ((zephir_method_exists(this_ptr, getter TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_INIT_VAR(_24$$13);
		object_init_ex(_24$$13, yii_base_invalidcallexception_ce);
		ZEPHIR_INIT_VAR(_25$$13);
		zephir_get_class(_25$$13, this_ptr, 0 TSRMLS_CC);
		ZEPHIR_INIT_VAR(_26$$13);
		ZEPHIR_CONCAT_SVSV(_26$$13, "Setting read-only property: ", _25$$13, "::", name);
		ZEPHIR_CALL_METHOD(NULL, _24$$13, "__construct", NULL, 2, _26$$13);
		zephir_check_call_status();
		zephir_throw_exception_debug(_24$$13, "yii/base/Component.zep", 214 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} else {
		ZEPHIR_INIT_VAR(_27$$14);
		object_init_ex(_27$$14, yii_base_unknownpropertyexception_ce);
		ZEPHIR_INIT_VAR(_28$$14);
		zephir_get_class(_28$$14, this_ptr, 0 TSRMLS_CC);
		ZEPHIR_INIT_VAR(_29$$14);
		ZEPHIR_CONCAT_SVSV(_29$$14, "Setting unknown property: ", _28$$14, "::", name);
		ZEPHIR_CALL_METHOD(NULL, _27$$14, "__construct", NULL, 3, _29$$14);
		zephir_check_call_status();
		zephir_throw_exception_debug(_27$$14, "yii/base/Component.zep", 216 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}

}

/**
 * Checks if a property value is null.
 * This method will check in the following order and act accordingly:
 *
 *  - a property defined by a setter: return whether the property value is null
 *  - a property of a behavior: return whether the property value is null
 *
 * Do not call this method directly as it is a PHP magic method that
 * will be implicitly called when executing `isset($component->property)`.
 * @param string $name the property name or the event name
 * @return boolean whether the named property is null
 */
PHP_METHOD(yii_base_Component, __isset) {

	HashTable *_4$$4;
	HashPosition _3$$4;
	zephir_fcall_cache_entry *_7 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *getter = NULL, *_1$$3 = NULL, *behavior$$4 = NULL, *_2$$4, **_5$$4, *_6$$5 = NULL, *_8$$6 = NULL;
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
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
		zephir_check_call_status();
		_2$$4 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
		zephir_is_iterable(_2$$4, &_4$$4, &_3$$4, 0, 0, "yii/base/Component.zep", 248);
		for (
		  ; zephir_hash_get_current_data_ex(_4$$4, (void**) &_5$$4, &_3$$4) == SUCCESS
		  ; zephir_hash_move_forward_ex(_4$$4, &_3$$4)
		) {
			ZEPHIR_GET_HVALUE(behavior$$4, _5$$4);
			ZEPHIR_CALL_METHOD(&_6$$5, behavior$$4, "cangetproperty", &_7, 0, name);
			zephir_check_call_status();
			if (zephir_is_true(_6$$5)) {
				ZEPHIR_OBS_NVAR(_8$$6);
				zephir_read_property_zval(&_8$$6, behavior$$4, name, PH_NOISY_CC);
				RETURN_MM_BOOL(Z_TYPE_P(_8$$6) != IS_NULL);
			}
		}
	}
	RETURN_MM_BOOL(0);

}

/**
 * Sets a component property to be null.
 * This method will check in the following order and act accordingly:
 *
 *  - a property defined by a setter: set the property value to be null
 *  - a property of a behavior: set the property value to be null
 *
 * Do not call this method directly as it is a PHP magic method that
 * will be implicitly called when executing `unset($component->property)`.
 * @param string $name the property name
 * @throws InvalidCallException if the property is read only.
 */
PHP_METHOD(yii_base_Component, __unset) {

	HashTable *_4$$4;
	HashPosition _3$$4;
	zephir_fcall_cache_entry *_7 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *setter = NULL, *_8, *_9, *_10, *_1$$3, *behavior$$4 = NULL, *_2$$4, **_5$$4, *_6$$5 = NULL;
	zval *name = NULL, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_CONCAT_SV(_0, "set", name);
	ZEPHIR_CPY_WRT(setter, _0);
	if ((zephir_method_exists(this_ptr, setter TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_INIT_VAR(_1$$3);
		ZVAL_NULL(_1$$3);
		ZEPHIR_CALL_METHOD_ZVAL(NULL, this_ptr, setter, NULL, 0, _1$$3);
		zephir_check_call_status();
		RETURN_MM_NULL();
	} else {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
		zephir_check_call_status();
		_2$$4 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
		zephir_is_iterable(_2$$4, &_4$$4, &_3$$4, 0, 0, "yii/base/Component.zep", 284);
		for (
		  ; zephir_hash_get_current_data_ex(_4$$4, (void**) &_5$$4, &_3$$4) == SUCCESS
		  ; zephir_hash_move_forward_ex(_4$$4, &_3$$4)
		) {
			ZEPHIR_GET_HVALUE(behavior$$4, _5$$4);
			ZEPHIR_CALL_METHOD(&_6$$5, behavior$$4, "cansetproperty", &_7, 0, name);
			zephir_check_call_status();
			if (zephir_is_true(_6$$5)) {
				zephir_update_property_zval_zval(behavior$$4, name, ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
				RETURN_MM_NULL();
			}
		}
	}
	ZEPHIR_INIT_VAR(_8);
	object_init_ex(_8, yii_base_invalidcallexception_ce);
	ZEPHIR_INIT_VAR(_9);
	zephir_get_class(_9, this_ptr, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_10);
	ZEPHIR_CONCAT_SVSV(_10, "Unsetting an unknown or read-only property: ", _9, "::", name);
	ZEPHIR_CALL_METHOD(NULL, _8, "__construct", NULL, 2, _10);
	zephir_check_call_status();
	zephir_throw_exception_debug(_8, "yii/base/Component.zep", 285 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Calls the named method which is not a class method.
 *
 * This method will check if any attached behavior has
 * the named method and will execute it if available.
 *
 * Do not call this method directly as it is a PHP magic method that
 * will be implicitly called when an unknown method is being invoked.
 * @param string $name the method name
 * @param array $params method parameters
 * @return mixed the method return value
 * @throws UnknownMethodException when calling unknown method
 */
PHP_METHOD(yii_base_Component, __call) {

	zval *_5$$4 = NULL;
	HashTable *_2;
	HashPosition _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *params, *object = NULL, *_0, **_3, *_6, *_7, *_8, *_4$$3 = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &params);

	zephir_get_strval(name, name_param);


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
	zephir_check_call_status();
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
	zephir_is_iterable(_0, &_2, &_1, 0, 0, "yii/base/Component.zep", 311);
	for (
	  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HVALUE(object, _3);
		ZEPHIR_CALL_METHOD(&_4$$3, object, "hasmethod", NULL, 0, name);
		zephir_check_call_status();
		if (zephir_is_true(_4$$3)) {
			ZEPHIR_INIT_NVAR(_5$$4);
			zephir_create_array(_5$$4, 2, 0 TSRMLS_CC);
			zephir_array_fast_append(_5$$4, object);
			zephir_array_fast_append(_5$$4, name);
			ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, _5$$4, params);
			zephir_check_call_status();
			RETURN_MM();
		}
	}
	ZEPHIR_INIT_VAR(_6);
	object_init_ex(_6, yii_base_unknownmethodexception_ce);
	ZEPHIR_INIT_VAR(_7);
	zephir_get_class(_7, this_ptr, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_8);
	ZEPHIR_CONCAT_SVSVS(_8, "Calling unknown method: ", _7, "::", name, "()");
	ZEPHIR_CALL_METHOD(NULL, _6, "__construct", NULL, 2, _8);
	zephir_check_call_status();
	zephir_throw_exception_debug(_6, "yii/base/Component.zep", 311 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * This method is called after the object is created by cloning an existing one.
 * It removes all behaviors because they are attached to the old object.
 */
PHP_METHOD(yii_base_Component, __clone) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("_events"), _0 TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("_behaviors"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns a value indicating whether a property is defined for this component.
 * A property is defined if:
 *
 * - the class has a getter or setter method associated with the specified name
 *   (in this case, property name is case-insensitive);
 * - the class has a member variable with the specified name (when `$checkVars` is true);
 * - an attached behavior has a property of the given name (when `$checkBehaviors` is true).
 *
 * @param string $name the property name
 * @param boolean $checkVars whether to treat member variables as properties
 * @param boolean $checkBehaviors whether to treat behaviors' properties as properties of this component
 * @return boolean whether the property is defined
 * @see canGetProperty()
 * @see canSetProperty()
 */
PHP_METHOD(yii_base_Component, hasProperty) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool checkVars, checkBehaviors, _3;
	zval *name_param = NULL, *checkVars_param = NULL, *checkBehaviors_param = NULL, *_0 = NULL, *_1, *_2, *_4 = NULL, *_5, *_6;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &name_param, &checkVars_param, &checkBehaviors_param);

	zephir_get_strval(name, name_param);
	if (!checkVars_param) {
		checkVars = 1;
	} else {
		checkVars = zephir_get_boolval(checkVars_param);
	}
	if (!checkBehaviors_param) {
		checkBehaviors = 1;
	} else {
		checkBehaviors = zephir_get_boolval(checkBehaviors_param);
	}


	ZEPHIR_INIT_VAR(_1);
	if (checkVars) {
		ZVAL_BOOL(_1, 1);
	} else {
		ZVAL_BOOL(_1, 0);
	}
	ZEPHIR_INIT_VAR(_2);
	if (checkBehaviors) {
		ZVAL_BOOL(_2, 1);
	} else {
		ZVAL_BOOL(_2, 0);
	}
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "cangetproperty", NULL, 0, name, _1, _2);
	zephir_check_call_status();
	_3 = zephir_is_true(_0);
	if (!(_3)) {
		ZEPHIR_INIT_VAR(_5);
		ZVAL_BOOL(_5, 0);
		ZEPHIR_INIT_VAR(_6);
		if (checkBehaviors) {
			ZVAL_BOOL(_6, 1);
		} else {
			ZVAL_BOOL(_6, 0);
		}
		ZEPHIR_CALL_METHOD(&_4, this_ptr, "cansetproperty", NULL, 0, name, _5, _6);
		zephir_check_call_status();
		_3 = zephir_is_true(_4);
	}
	RETURN_MM_BOOL(_3);

}

/**
 * Returns a value indicating whether a property can be read.
 * A property can be read if:
 *
 * - the class has a getter method associated with the specified name
 *   (in this case, property name is case-insensitive);
 * - the class has a member variable with the specified name (when `$checkVars` is true);
 * - an attached behavior has a readable property of the given name (when `$checkBehaviors` is true).
 *
 * @param string $name the property name
 * @param boolean $checkVars whether to treat member variables as properties
 * @param boolean $checkBehaviors whether to treat behaviors' properties as properties of this component
 * @return boolean whether the property can be read
 * @see canSetProperty()
 */
PHP_METHOD(yii_base_Component, canGetProperty) {

	HashTable *_6$$4;
	HashPosition _5$$4;
	zephir_fcall_cache_entry *_10 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool checkVars, checkBehaviors, _1, _2;
	zval *name_param = NULL, *checkVars_param = NULL, *checkBehaviors_param = NULL, *getter = NULL, *_3 = NULL, *behavior$$4 = NULL, *_4$$4, **_7$$4, *_8$$5 = NULL, *_9$$5 = NULL;
	zval *name = NULL, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &name_param, &checkVars_param, &checkBehaviors_param);

	zephir_get_strval(name, name_param);
	if (!checkVars_param) {
		checkVars = 1;
	} else {
		checkVars = zephir_get_boolval(checkVars_param);
	}
	if (!checkBehaviors_param) {
		checkBehaviors = 1;
	} else {
		checkBehaviors = zephir_get_boolval(checkBehaviors_param);
	}


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_CONCAT_SV(_0, "get", name);
	ZEPHIR_CPY_WRT(getter, _0);
	_1 = (zephir_method_exists(this_ptr, getter TSRMLS_CC)  == SUCCESS);
	if (!(_1)) {
		_2 = checkVars;
		if (_2) {
			ZEPHIR_CALL_FUNCTION(&_3, "property_exists", NULL, 4, this_ptr, name);
			zephir_check_call_status();
			_2 = zephir_is_true(_3);
		}
		_1 = _2;
	}
	if (_1) {
		RETURN_MM_BOOL(1);
	}
	if (checkBehaviors) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
		zephir_check_call_status();
		_4$$4 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
		zephir_is_iterable(_4$$4, &_6$$4, &_5$$4, 0, 0, "yii/base/Component.zep", 377);
		for (
		  ; zephir_hash_get_current_data_ex(_6$$4, (void**) &_7$$4, &_5$$4) == SUCCESS
		  ; zephir_hash_move_forward_ex(_6$$4, &_5$$4)
		) {
			ZEPHIR_GET_HVALUE(behavior$$4, _7$$4);
			ZEPHIR_INIT_NVAR(_9$$5);
			if (checkVars) {
				ZVAL_BOOL(_9$$5, 1);
			} else {
				ZVAL_BOOL(_9$$5, 0);
			}
			ZEPHIR_CALL_METHOD(&_8$$5, behavior$$4, "cangetproperty", &_10, 0, name, _9$$5);
			zephir_check_call_status();
			if (zephir_is_true(_8$$5)) {
				RETURN_MM_BOOL(1);
			}
		}
	}
	RETURN_MM_BOOL(0);

}

/**
 * Returns a value indicating whether a property can be set.
 * A property can be written if:
 *
 * - the class has a setter method associated with the specified name
 *   (in this case, property name is case-insensitive);
 * - the class has a member variable with the specified name (when `$checkVars` is true);
 * - an attached behavior has a writable property of the given name (when `$checkBehaviors` is true).
 *
 * @param string $name the property name
 * @param boolean $checkVars whether to treat member variables as properties
 * @param boolean $checkBehaviors whether to treat behaviors' properties as properties of this component
 * @return boolean whether the property can be written
 * @see canGetProperty()
 */
PHP_METHOD(yii_base_Component, canSetProperty) {

	HashTable *_6$$4;
	HashPosition _5$$4;
	zephir_fcall_cache_entry *_10 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool checkVars, checkBehaviors, _1, _2;
	zval *name_param = NULL, *checkVars_param = NULL, *checkBehaviors_param = NULL, *setter = NULL, *_3 = NULL, *behavior$$4 = NULL, *_4$$4, **_7$$4, *_8$$5 = NULL, *_9$$5 = NULL;
	zval *name = NULL, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &name_param, &checkVars_param, &checkBehaviors_param);

	zephir_get_strval(name, name_param);
	if (!checkVars_param) {
		checkVars = 1;
	} else {
		checkVars = zephir_get_boolval(checkVars_param);
	}
	if (!checkBehaviors_param) {
		checkBehaviors = 1;
	} else {
		checkBehaviors = zephir_get_boolval(checkBehaviors_param);
	}


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_CONCAT_SV(_0, "set", name);
	ZEPHIR_CPY_WRT(setter, _0);
	_1 = (zephir_method_exists(this_ptr, setter TSRMLS_CC)  == SUCCESS);
	if (!(_1)) {
		_2 = checkVars;
		if (_2) {
			ZEPHIR_CALL_FUNCTION(&_3, "property_exists", NULL, 4, this_ptr, name);
			zephir_check_call_status();
			_2 = zephir_is_true(_3);
		}
		_1 = _2;
	}
	if (_1) {
		RETURN_MM_BOOL(1);
	}
	if (checkBehaviors) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
		zephir_check_call_status();
		_4$$4 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
		zephir_is_iterable(_4$$4, &_6$$4, &_5$$4, 0, 0, "yii/base/Component.zep", 414);
		for (
		  ; zephir_hash_get_current_data_ex(_6$$4, (void**) &_7$$4, &_5$$4) == SUCCESS
		  ; zephir_hash_move_forward_ex(_6$$4, &_5$$4)
		) {
			ZEPHIR_GET_HVALUE(behavior$$4, _7$$4);
			ZEPHIR_INIT_NVAR(_9$$5);
			if (checkVars) {
				ZVAL_BOOL(_9$$5, 1);
			} else {
				ZVAL_BOOL(_9$$5, 0);
			}
			ZEPHIR_CALL_METHOD(&_8$$5, behavior$$4, "cansetproperty", &_10, 0, name, _9$$5);
			zephir_check_call_status();
			if (zephir_is_true(_8$$5)) {
				RETURN_MM_BOOL(1);
			}
		}
	}
	RETURN_MM_BOOL(0);

}

/**
 * Returns a value indicating whether a method is defined.
 * A method is defined if:
 *
 * - the class has a method with the specified name
 * - an attached behavior has a method with the given name (when `$checkBehaviors` is true).
 *
 * @param string $name the property name
 * @param boolean $checkBehaviors whether to treat behaviors' methods as methods of this component
 * @return boolean whether the property is defined
 */
PHP_METHOD(yii_base_Component, hasMethod) {

	HashTable *_2$$4;
	HashPosition _1$$4;
	zephir_fcall_cache_entry *_5 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool checkBehaviors;
	zval *name_param = NULL, *checkBehaviors_param = NULL, *behavior$$4 = NULL, *_0$$4, **_3$$4, *_4$$5 = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name_param, &checkBehaviors_param);

	zephir_get_strval(name, name_param);
	if (!checkBehaviors_param) {
		checkBehaviors = 1;
	} else {
		checkBehaviors = zephir_get_boolval(checkBehaviors_param);
	}


	if ((zephir_method_exists(this_ptr, name TSRMLS_CC)  == SUCCESS)) {
		RETURN_MM_BOOL(1);
	}
	if (checkBehaviors) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
		zephir_check_call_status();
		_0$$4 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
		zephir_is_iterable(_0$$4, &_2$$4, &_1$$4, 0, 0, "yii/base/Component.zep", 444);
		for (
		  ; zephir_hash_get_current_data_ex(_2$$4, (void**) &_3$$4, &_1$$4) == SUCCESS
		  ; zephir_hash_move_forward_ex(_2$$4, &_1$$4)
		) {
			ZEPHIR_GET_HVALUE(behavior$$4, _3$$4);
			ZEPHIR_CALL_METHOD(&_4$$5, behavior$$4, "hasmethod", &_5, 0, name);
			zephir_check_call_status();
			if (zephir_is_true(_4$$5)) {
				RETURN_MM_BOOL(1);
			}
		}
	}
	RETURN_MM_BOOL(0);

}

/**
 * Returns a list of behaviors that this component should behave as.
 *
 * Child classes may override this method to specify the behaviors they want to behave as.
 *
 * The return value of this method should be an array of behavior objects or configurations
 * indexed by behavior names. A behavior configuration can be either a string specifying
 * the behavior class or an array of the following structure:
 *
 * ~~~
 * 'behaviorName' => [
 *     'class' => 'BehaviorClass',
 *     'property1' => 'value1',
 *     'property2' => 'value2',
 * ]
 * ~~~
 *
 * Note that a behavior class must extend from [[Behavior]]. Behavior names can be strings
 * or integers. If the former, they uniquely identify the behaviors. If the latter, the corresponding
 * behaviors are anonymous and their properties and methods will NOT be made available via the component
 * (however, the behaviors can still respond to the component's events).
 *
 * Behaviors declared in this method will be attached to the component automatically (on demand).
 *
 * @return array the behavior configurations.
 */
PHP_METHOD(yii_base_Component, behaviors) {

	

	array_init(return_value);
	return;

}

/**
 * Returns a value indicating whether there is any handler attached to the named event.
 * @param string $name the event name
 * @return boolean whether there is any handler attached to the event.
 */
PHP_METHOD(yii_base_Component, hasEventHandlers) {

	zend_bool _1;
	zephir_fcall_cache_entry *_4 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *_0, *_2, *_3;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
	zephir_check_call_status();
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
	_1 = zephir_array_isset(_0, name);
	if (_1) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
		zephir_array_fetch(&_3, _2, name, PH_NOISY | PH_READONLY, "yii/base/Component.zep", 488 TSRMLS_CC);
		_1 = !(ZEPHIR_IS_EMPTY(_3));
	}
	if (_1) {
		RETURN_MM_BOOL(1);
	} else {
		ZEPHIR_RETURN_CALL_CE_STATIC(yii_base_event_ce, "hashandlers", &_4, 7, this_ptr, name);
		zephir_check_call_status();
		RETURN_MM();
	}

}

/**
 * Attaches an event handler to an event.
 *
 * The event handler must be a valid PHP callback. The followings are
 * some examples:
 *
 * ~~~
 * function ($event) { ... }         // anonymous function
 * [$object, 'handleClick']          // $object->handleClick()
 * ['Page', 'handleClick']           // Page::handleClick()
 * 'handleClick'                     // global function handleClick()
 * ~~~
 *
 * The event handler must be defined with the following signature,
 *
 * ~~~
 * function ($event)
 * ~~~
 *
 * where `$event` is an [[Event]] object which includes parameters associated with the event.
 *
 * @param string $name the event name
 * @param callable $handler the event handler
 * @param mixed $data the data to be passed to the event handler when the event is triggered.
 * When the event handler is invoked, this data can be accessed via [[Event::data]].
 * @param boolean $append whether to append new event handler to the end of the existing
 * handler list. If false, the new handler will be inserted at the beginning of the existing
 * handler list.
 * @see off()
 */
PHP_METHOD(yii_base_Component, on) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool append, _0, _1;
	zval *name_param = NULL, *handler, *data = NULL, *append_param = NULL, *events = NULL, *event = NULL, *elements = NULL, *_2;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 2, &name_param, &handler, &data, &append_param);

	zephir_get_strval(name, name_param);
	if (!data) {
		data = ZEPHIR_GLOBAL(global_null);
	}
	if (!append_param) {
		append = 1;
	} else {
		append = zephir_get_boolval(append_param);
	}


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(events);
	zephir_read_property_this(&events, this_ptr, SL("_events"), PH_NOISY_CC);
	if (Z_TYPE_P(events) != IS_ARRAY) {
		ZEPHIR_INIT_NVAR(events);
		array_init(events);
	}
	ZEPHIR_INIT_VAR(elements);
	array_init(elements);
	zephir_array_append(&elements, handler, PH_SEPARATE, "yii/base/Component.zep", 538);
	zephir_array_append(&elements, data, PH_SEPARATE, "yii/base/Component.zep", 539);
	_0 = append == 1;
	if (!(_0)) {
		_0 = !(zephir_array_isset(events, name));
	}
	_1 = _0;
	if (!(_1)) {
		zephir_array_fetch(&_2, events, name, PH_NOISY | PH_READONLY, "yii/base/Component.zep", 541 TSRMLS_CC);
		_1 = ZEPHIR_IS_EMPTY(_2);
	}
	if (_1) {
		if (zephir_array_isset(events, name)) {
			ZEPHIR_OBS_VAR(event);
			zephir_array_fetch(&event, events, name, PH_NOISY, "yii/base/Component.zep", 543 TSRMLS_CC);
		} else {
			ZEPHIR_INIT_NVAR(event);
			array_init(event);
		}
		if (Z_TYPE_P(event) != IS_ARRAY) {
			ZEPHIR_INIT_NVAR(event);
			array_init(event);
		}
		zephir_array_append(&event, elements, PH_SEPARATE, "yii/base/Component.zep", 551);
		zephir_array_update_zval(&events, name, &event, PH_COPY | PH_SEPARATE);
	} else {
		if (zephir_array_isset(events, name)) {
			ZEPHIR_OBS_NVAR(event);
			zephir_array_fetch(&event, events, name, PH_NOISY, "yii/base/Component.zep", 555 TSRMLS_CC);
		} else {
			ZEPHIR_INIT_NVAR(event);
			array_init(event);
		}
		if (Z_TYPE_P(event) != IS_ARRAY) {
			ZEPHIR_INIT_NVAR(event);
			array_init(event);
		}
		ZEPHIR_MAKE_REF(event);
		ZEPHIR_CALL_FUNCTION(NULL, "array_unshift", NULL, 8, event, elements);
		ZEPHIR_UNREF(event);
		zephir_check_call_status();
		zephir_array_update_zval(&events, name, &event, PH_COPY | PH_SEPARATE);
	}
	zephir_update_property_this(this_ptr, SL("_events"), events TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Detaches an existing event handler from this component.
 * This method is the opposite of [[on()]].
 * @param string $name event name
 * @param callable $handler the event handler to be removed.
 * If it is null, all handlers attached to the named event will be removed.
 * @return boolean if a handler is found and detached
 * @see on()
 */
PHP_METHOD(yii_base_Component, off) {

	HashTable *_7$$6;
	HashPosition _6$$6;
	zend_bool removed = 0, _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *handler = NULL, *events = NULL, *temp_event = NULL, *removed_temp_event = NULL, *_0, *_2, *_3, *i$$6 = NULL, *event$$6 = NULL, *_4$$6, *_5$$6, **_8$$6, *_9$$7, *_10$$9 = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name_param, &handler);

	zephir_get_strval(name, name_param);
	if (!handler) {
		handler = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
	zephir_check_call_status();
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
	_1 = !(zephir_array_isset(_0, name));
	if (!(_1)) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
		zephir_array_fetch(&_3, _2, name, PH_NOISY | PH_READONLY, "yii/base/Component.zep", 586 TSRMLS_CC);
		_1 = ZEPHIR_IS_EMPTY(_3);
	}
	if (_1) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_OBS_VAR(events);
	zephir_read_property_this(&events, this_ptr, SL("_events"), PH_NOISY_CC);
	if (Z_TYPE_P(handler) == IS_NULL) {
		if (zephir_array_isset(events, name)) {
			zephir_array_unset(&events, name, PH_SEPARATE);
		}
		zephir_update_property_this(this_ptr, SL("_events"), events TSRMLS_CC);
		RETURN_MM_BOOL(1);
	} else {
		removed = 0;
		_4$$6 = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
		zephir_array_fetch(&_5$$6, _4$$6, name, PH_NOISY | PH_READONLY, "yii/base/Component.zep", 601 TSRMLS_CC);
		zephir_is_iterable(_5$$6, &_7$$6, &_6$$6, 0, 0, "yii/base/Component.zep", 611);
		for (
		  ; zephir_hash_get_current_data_ex(_7$$6, (void**) &_8$$6, &_6$$6) == SUCCESS
		  ; zephir_hash_move_forward_ex(_7$$6, &_6$$6)
		) {
			ZEPHIR_GET_HMKEY(i$$6, _7$$6, _6$$6);
			ZEPHIR_GET_HVALUE(event$$6, _8$$6);
			zephir_array_fetch_long(&_9$$7, event$$6, 0, PH_NOISY | PH_READONLY, "yii/base/Component.zep", 602 TSRMLS_CC);
			if (ZEPHIR_IS_EQUAL(_9$$7, handler)) {
				ZEPHIR_OBS_NVAR(temp_event);
				zephir_array_fetch(&temp_event, events, name, PH_NOISY, "yii/base/Component.zep", 603 TSRMLS_CC);
				zephir_array_unset(&temp_event, i$$6, PH_SEPARATE);
				zephir_array_update_zval(&events, name, &temp_event, PH_COPY | PH_SEPARATE);
				removed = 1;
			}
		}
		if (removed) {
			ZEPHIR_OBS_VAR(removed_temp_event);
			zephir_array_fetch(&removed_temp_event, events, name, PH_NOISY, "yii/base/Component.zep", 612 TSRMLS_CC);
			ZEPHIR_CALL_FUNCTION(&_10$$9, "array_values", NULL, 9, removed_temp_event);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(removed_temp_event, _10$$9);
			zephir_array_update_zval(&events, name, &removed_temp_event, PH_COPY | PH_SEPARATE);
			zephir_update_property_this(this_ptr, SL("_events"), events TSRMLS_CC);
		}
		RETURN_MM_BOOL(removed);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Triggers an event.
 * This method represents the happening of an event. It invokes
 * all attached handlers for the event including class-level handlers.
 * @param string $name the event name
 * @param Event $event the event parameter. If not set, a default [[Event]] object will be created.
 */
PHP_METHOD(yii_base_Component, trigger) {

	HashTable *_8$$3;
	HashPosition _7$$3;
	zend_bool _1, _10$$6;
	zephir_fcall_cache_entry *_13 = NULL, *_15 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name, *event = NULL, *_0, *_2, *_3, *_4$$3, *handler$$3 = NULL, *_5$$3, *_6$$3, **_9$$3, *_11$$7, *_12$$7, *_14$$7 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name, &event);

	if (!event) {
		ZEPHIR_CPY_WRT(event, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(event);
	}


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
	zephir_check_call_status();
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
	_1 = zephir_array_isset(_0, name);
	if (_1) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
		zephir_array_fetch(&_3, _2, name, PH_NOISY | PH_READONLY, "yii/base/Component.zep", 633 TSRMLS_CC);
		_1 = !(ZEPHIR_IS_EMPTY(_3));
	}
	if (_1) {
		if (Z_TYPE_P(event) == IS_NULL) {
			ZEPHIR_INIT_NVAR(event);
			object_init_ex(event, yii_base_event_ce);
			ZEPHIR_CALL_METHOD(NULL, event, "__construct", NULL, 10);
			zephir_check_call_status();
		}
		ZEPHIR_OBS_VAR(_4$$3);
		zephir_read_property(&_4$$3, event, SL("sender"), PH_NOISY_CC);
		if (Z_TYPE_P(_4$$3) == IS_NULL) {
			zephir_update_property_zval(event, SL("sender"), this_ptr TSRMLS_CC);
		}
		if (0) {
			zephir_update_property_zval(event, SL("handled"), ZEPHIR_GLOBAL(global_true) TSRMLS_CC);
		} else {
			zephir_update_property_zval(event, SL("handled"), ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
		}
		zephir_update_property_zval(event, SL("name"), name TSRMLS_CC);
		_5$$3 = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
		zephir_array_fetch(&_6$$3, _5$$3, name, PH_NOISY | PH_READONLY, "yii/base/Component.zep", 646 TSRMLS_CC);
		zephir_is_iterable(_6$$3, &_8$$3, &_7$$3, 0, 0, "yii/base/Component.zep", 656);
		for (
		  ; zephir_hash_get_current_data_ex(_8$$3, (void**) &_9$$3, &_7$$3) == SUCCESS
		  ; zephir_hash_move_forward_ex(_8$$3, &_7$$3)
		) {
			ZEPHIR_GET_HVALUE(handler$$3, _9$$3);
			_10$$6 = Z_TYPE_P(handler$$3) == IS_ARRAY;
			if (_10$$6) {
				_10$$6 = zephir_fast_count_int(handler$$3 TSRMLS_CC) >= 2;
			}
			if (_10$$6) {
				zephir_array_fetch_long(&_11$$7, handler$$3, 1, PH_NOISY | PH_READONLY, "yii/base/Component.zep", 648 TSRMLS_CC);
				zephir_update_property_zval(event, SL("data"), _11$$7 TSRMLS_CC);
				zephir_array_fetch_long(&_12$$7, handler$$3, 0, PH_NOISY | PH_READONLY, "yii/base/Component.zep", 649 TSRMLS_CC);
				ZEPHIR_CALL_FUNCTION(NULL, "call_user_func", &_13, 11, _12$$7, event);
				zephir_check_call_status();
				ZEPHIR_OBS_NVAR(_14$$7);
				zephir_read_property(&_14$$7, event, SL("handled"), PH_NOISY_CC);
				if (zephir_is_true(_14$$7)) {
					RETURN_MM_NULL();
				}
			}
		}
	}
	ZEPHIR_CALL_CE_STATIC(NULL, yii_base_event_ce, "trigger", &_15, 12, this_ptr, name, event);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns the named behavior object.
 * @param string $name the behavior name
 * @return Behavior the behavior object, or null if the behavior does not exist
 */
PHP_METHOD(yii_base_Component, getBehavior) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *_0, *_1, *_2;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_0);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
	if (zephir_array_isset(_1, name)) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
		zephir_array_fetch(&_0, _2, name, PH_NOISY, "yii/base/Component.zep", 670 TSRMLS_CC);
	} else {
		ZVAL_NULL(_0);
	}
	RETURN_CCTOR(_0);

}

/**
 * Returns all behaviors attached to this component.
 * @return Behavior[] list of behaviors attached to this component
 */
PHP_METHOD(yii_base_Component, getBehaviors) {

	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
	zephir_check_call_status();
	RETURN_MM_MEMBER(this_ptr, "_behaviors");

}

/**
 * Attaches a behavior to this component.
 * This method will create the behavior object based on the given
 * configuration. After that, the behavior object will be attached to
 * this component by calling the [[Behavior::attach()]] method.
 * @param string $name the name of the behavior.
 * @param string|array|Behavior $behavior the behavior configuration. This can be one of the following:
 *
 *  - a [[Behavior]] object
 *  - a string specifying the behavior class
 *  - an object configuration array that will be passed to [[Yii::createObject()]] to create the behavior object.
 *
 * @return Behavior the behavior object
 * @see detachBehavior()
 */
PHP_METHOD(yii_base_Component, attachBehavior) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *behavior;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &behavior);

	zephir_get_strval(name, name_param);


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "attachbehaviorinternal", NULL, 0, name, behavior);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Attaches a list of behaviors to the component.
 * Each behavior is indexed by its name and should be a [[Behavior]] object,
 * a string specifying the behavior class, or an configuration array for creating the behavior.
 * @param array $behaviors list of behaviors to be attached to the component
 * @see attachBehavior()
 */
PHP_METHOD(yii_base_Component, attachBehaviors) {

	HashTable *_1;
	HashPosition _0;
	zephir_fcall_cache_entry *_3 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *behaviors, *name = NULL, *behavior = NULL, **_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &behaviors);



	ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(behaviors, &_1, &_0, 0, 0, "yii/base/Component.zep", 721);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HMKEY(name, _1, _0);
		ZEPHIR_GET_HVALUE(behavior, _2);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "attachbehaviorinternal", &_3, 0, name, behavior);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Detaches a behavior from the component.
 * The behavior's [[Behavior::detach()]] method will be invoked.
 * @param string $name the behavior's name.
 * @return Behavior the detached behavior. Null if the behavior does not exist.
 */
PHP_METHOD(yii_base_Component, detachBehavior) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *behavior = NULL, *behaviors = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(behaviors);
	zephir_read_property_this(&behaviors, this_ptr, SL("_behaviors"), PH_NOISY_CC);
	ZEPHIR_OBS_VAR(behavior);
	if (zephir_array_isset_fetch(&behavior, behaviors, name, 0 TSRMLS_CC)) {
		zephir_array_unset(&behaviors, name, PH_SEPARATE);
		zephir_update_property_this(this_ptr, SL("_behaviors"), behaviors TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, behavior, "detach", NULL, 0);
		zephir_check_call_status();
		RETURN_CCTOR(behavior);
	} else {
		RETURN_MM_NULL();
	}

}

/**
 * Detaches all behaviors from the component.
 */
PHP_METHOD(yii_base_Component, detachBehaviors) {

	HashTable *_1;
	HashPosition _0;
	zval *name = NULL, *behavior = NULL, *behaviors = NULL, **_2;
	zephir_fcall_cache_entry *_3 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(behaviors);
	zephir_read_property_this(&behaviors, this_ptr, SL("_behaviors"), PH_NOISY_CC);
	zephir_is_iterable(behaviors, &_1, &_0, 0, 0, "yii/base/Component.zep", 756);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HMKEY(name, _1, _0);
		ZEPHIR_GET_HVALUE(behavior, _2);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "detachbehavior", &_3, 0, name);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Makes sure that the behaviors declared in [[behaviors()]] are attached to this component.
 */
PHP_METHOD(yii_base_Component, ensureBehaviors) {

	HashTable *_3$$3;
	HashPosition _2$$3;
	zval *_0, *_1$$3, *name$$3 = NULL, *behavior$$3 = NULL, *behaviors$$3 = NULL, **_4$$3;
	zephir_fcall_cache_entry *_5 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("_behaviors"), PH_NOISY_CC);
	if (Z_TYPE_P(_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(_1$$3);
		array_init(_1$$3);
		zephir_update_property_this(this_ptr, SL("_behaviors"), _1$$3 TSRMLS_CC);
		ZEPHIR_OBS_VAR(behaviors$$3);
		zephir_read_property_this(&behaviors$$3, this_ptr, SL("_behaviors"), PH_NOISY_CC);
		zephir_is_iterable(behaviors$$3, &_3$$3, &_2$$3, 0, 0, "yii/base/Component.zep", 771);
		for (
		  ; zephir_hash_get_current_data_ex(_3$$3, (void**) &_4$$3, &_2$$3) == SUCCESS
		  ; zephir_hash_move_forward_ex(_3$$3, &_2$$3)
		) {
			ZEPHIR_GET_HMKEY(name$$3, _3$$3, _2$$3);
			ZEPHIR_GET_HVALUE(behavior$$3, _4$$3);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "attachbehaviorinternal", &_5, 0, name$$3, behavior$$3);
			zephir_check_call_status();
		}
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Attaches a behavior to this component.
 * @param string $name the name of the behavior.
 * @param string|array|Behavior $behavior the behavior to be attached
 * @return Behavior the attached behavior.
 */
PHP_METHOD(yii_base_Component, attachBehaviorInternal) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_1 = NULL;
	zval *name, *behavior = NULL, *_0$$3 = NULL, *_2$$5, *_3$$6, *_4$$6;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name, &behavior);

	ZEPHIR_SEPARATE_PARAM(behavior);


	if (!(zephir_is_instance_of(behavior, SL("yii\\base\\Behavior") TSRMLS_CC))) {
		ZEPHIR_CALL_CE_STATIC(&_0$$3, yii_baseyii_ce, "createobject", &_1, 6, behavior);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(behavior, _0$$3);
	}
	if (Z_TYPE_P(name) == IS_LONG) {
		ZEPHIR_CALL_METHOD(NULL, behavior, "attach", NULL, 0, this_ptr);
		zephir_check_call_status();
		zephir_update_property_array_append(this_ptr, SL("_behaviors"), behavior TSRMLS_CC);
	} else {
		_2$$5 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
		if (zephir_array_isset(_2$$5, name)) {
			_3$$6 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
			zephir_array_fetch(&_4$$6, _3$$6, name, PH_NOISY | PH_READONLY, "yii/base/Component.zep", 790 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(NULL, _4$$6, "detach", NULL, 0);
			zephir_check_call_status();
		}
		ZEPHIR_CALL_METHOD(NULL, behavior, "attach", NULL, 0, this_ptr);
		zephir_check_call_status();
		zephir_update_property_array(this_ptr, SL("_behaviors"), name, behavior TSRMLS_CC);
	}
	RETVAL_ZVAL(behavior, 1, 0);
	RETURN_MM();

}

zend_object_value zephir_init_properties_yii_base_Component(zend_class_entry *class_type TSRMLS_DC) {

		zval *_0, *_1$$3;

		ZEPHIR_MM_GROW();
	
	{
		zval *this_ptr = NULL;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
		if (Z_TYPE_P(_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(_1$$3);
			array_init(_1$$3);
			zephir_update_property_this(this_ptr, SL("_events"), _1$$3 TSRMLS_CC);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJVAL_P(this_ptr);
	}

}

