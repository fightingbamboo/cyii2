
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
 * ```php
 * $post->on('update', function ($event) {
 *     // send email notification
 * });
 * ```
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
 * ```php
 * function foo($event)
 * ```
 *
 * where `$event` is an [[Event]] object which includes parameters associated with the event.
 *
 * You can also attach a handler to an event when configuring a component with a configuration array.
 * The syntax is like the following:
 *
 * ```php
 * [
 *     'on add' => function ($event) { ... }
 * ]
 * ```
 *
 * where `on add` stands for attaching an event to the `add` event.
 *
 * Sometimes, you may want to associate extra data with an event handler when you attach it to an event
 * and then access it when the handler is invoked. You may do so by
 *
 * ```php
 * $post->on('update', function ($event) {
 *     // the data can be accessed via $event->data
 * }, $data);
 * ```
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
 * ```php
 * [
 *     'as tree' => [
 *         'class' => 'Tree',
 *     ],
 * ]
 * ```
 *
 * where `as tree` stands for attaching a behavior named `tree`, and the array will be passed to [[\BaseYii::createObject()]]
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
	 * @var Behavior[]|null the attached behaviors (behavior name => behavior). This is `null` when not initialized.
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
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *getter = NULL, *behavior = NULL, *_1$$4, **_4$$4, *_5$$5 = NULL, *_6$$6 = NULL, *_7$$7, *_8$$7, *_9$$7, *_10$$8, *_11$$8, *_12$$8;
	zval *name = NULL, *_0 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_CONCAT_SV(_0, "get", name);
	ZEPHIR_CPY_WRT(getter, _0);
	if ((zephir_method_exists(this_ptr, getter TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_RETURN_CALL_METHOD_ZVAL(this_ptr, getter, NULL, 0);
		zephir_check_call_status();
		RETURN_MM();
	} else {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
		zephir_check_call_status();
		_1$$4 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
		zephir_is_iterable(_1$$4, &_3$$4, &_2$$4, 0, 0, "yii/base/Component.zep", 136);
		for (
		  ; zephir_hash_get_current_data_ex(_3$$4, (void**) &_4$$4, &_2$$4) == SUCCESS
		  ; zephir_hash_move_forward_ex(_3$$4, &_2$$4)
		) {
			ZEPHIR_GET_HVALUE(behavior, _4$$4);
			ZEPHIR_CALL_METHOD(&_5$$5, behavior, "cangetproperty", NULL, 0, name);
			zephir_check_call_status();
			if (zephir_is_true(_5$$5)) {
				ZEPHIR_OBS_NVAR(_6$$6);
				zephir_read_property_zval(&_6$$6, behavior, name, PH_NOISY_CC);
				RETURN_CCTOR(_6$$6);
			}
		}
	}
	ZEPHIR_INIT_LNVAR(_0);
	ZEPHIR_CONCAT_SV(_0, "set", name);
	if ((zephir_method_exists(this_ptr, _0 TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_INIT_VAR(_7$$7);
		object_init_ex(_7$$7, yii_base_invalidcallexception_ce);
		ZEPHIR_INIT_VAR(_8$$7);
		zephir_get_class(_8$$7, this_ptr, 0 TSRMLS_CC);
		ZEPHIR_INIT_VAR(_9$$7);
		ZEPHIR_CONCAT_SVSV(_9$$7, "Getting write-only property: ", _8$$7, "::", name);
		ZEPHIR_CALL_METHOD(NULL, _7$$7, "__construct", NULL, 2, _9$$7);
		zephir_check_call_status();
		zephir_throw_exception_debug(_7$$7, "yii/base/Component.zep", 138 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} else {
		ZEPHIR_INIT_VAR(_10$$8);
		object_init_ex(_10$$8, yii_base_unknownpropertyexception_ce);
		ZEPHIR_INIT_VAR(_11$$8);
		zephir_get_class(_11$$8, this_ptr, 0 TSRMLS_CC);
		ZEPHIR_INIT_VAR(_12$$8);
		ZEPHIR_CONCAT_SVSV(_12$$8, "Getting unknown property: ", _11$$8, "::", name);
		ZEPHIR_CALL_METHOD(NULL, _10$$8, "__construct", NULL, 3, _12$$8);
		zephir_check_call_status();
		zephir_throw_exception_debug(_10$$8, "yii/base/Component.zep", 140 TSRMLS_CC);
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

	HashTable *_14$$6;
	HashPosition _13$$6;
	zephir_fcall_cache_entry *_11 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *value, *setter = NULL, *behavior = NULL, _1 = zval_used_for_init, _2 = zval_used_for_init, *_3 = NULL, *_4 = NULL, *_5$$4, _6$$4, *_7$$4, _8$$5, *_9$$5, *_10$$5 = NULL, *_12$$6, **_15$$6, *_16$$7 = NULL, *_17$$9, *_18$$9, *_19$$9, *_20$$10, *_21$$10, *_22$$10;
	zval *name = NULL, *_0 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &value);

	zephir_get_strval(name, name_param);


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_CONCAT_SV(_0, "set", name);
	ZEPHIR_CPY_WRT(setter, _0);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "on ", 0);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_LONG(&_2, 3);
	ZEPHIR_CALL_FUNCTION(&_3, "strncmp", NULL, 5, name, &_1, &_2);
	zephir_check_call_status();
	ZEPHIR_SINIT_NVAR(_1);
	ZVAL_STRING(&_1, "as ", 0);
	ZEPHIR_SINIT_NVAR(_2);
	ZVAL_LONG(&_2, 3);
	ZEPHIR_CALL_FUNCTION(&_4, "strncmp", NULL, 5, name, &_1, &_2);
	zephir_check_call_status();
	if ((zephir_method_exists(this_ptr, setter TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_CALL_METHOD_ZVAL(NULL, this_ptr, setter, NULL, 0, value);
		zephir_check_call_status();
		RETURN_MM_NULL();
	} else if (ZEPHIR_IS_LONG_IDENTICAL(_3, 0)) {
		ZEPHIR_INIT_VAR(_5$$4);
		ZEPHIR_SINIT_VAR(_6$$4);
		ZVAL_LONG(&_6$$4, 3);
		ZEPHIR_INIT_VAR(_7$$4);
		zephir_substr(_7$$4, name, 3 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
		zephir_fast_trim(_5$$4, _7$$4, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "on", NULL, 0, _5$$4, value);
		zephir_check_call_status();
		RETURN_MM_NULL();
	} else if (ZEPHIR_IS_LONG_IDENTICAL(_4, 0)) {
		ZEPHIR_SINIT_VAR(_8$$5);
		ZVAL_LONG(&_8$$5, 3);
		ZEPHIR_INIT_VAR(_9$$5);
		zephir_substr(_9$$5, name, 3 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
		ZEPHIR_INIT_NVAR(name);
		zephir_fast_trim(name, _9$$5, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
		ZEPHIR_INIT_VAR(_10$$5);
		if (zephir_is_instance_of(value, SL("yii\\base\\Behavior") TSRMLS_CC)) {
			ZEPHIR_CPY_WRT(_10$$5, value);
		} else {
			ZEPHIR_CALL_CE_STATIC(&_10$$5, yii_baseyii_ce, "createobject", &_11, 6, value);
			zephir_check_call_status();
		}
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "attachbehavior", NULL, 0, name, _10$$5);
		zephir_check_call_status();
		RETURN_MM_NULL();
	} else {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
		zephir_check_call_status();
		_12$$6 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
		zephir_is_iterable(_12$$6, &_14$$6, &_13$$6, 0, 0, "yii/base/Component.zep", 188);
		for (
		  ; zephir_hash_get_current_data_ex(_14$$6, (void**) &_15$$6, &_13$$6) == SUCCESS
		  ; zephir_hash_move_forward_ex(_14$$6, &_13$$6)
		) {
			ZEPHIR_GET_HVALUE(behavior, _15$$6);
			ZEPHIR_CALL_METHOD(&_16$$7, behavior, "cansetproperty", NULL, 0, name);
			zephir_check_call_status();
			if (zephir_is_true(_16$$7)) {
				zephir_update_property_zval_zval(behavior, name, value TSRMLS_CC);
				RETURN_MM_NULL();
			}
		}
	}
	ZEPHIR_INIT_LNVAR(_0);
	ZEPHIR_CONCAT_SV(_0, "get", name);
	if ((zephir_method_exists(this_ptr, _0 TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_INIT_VAR(_17$$9);
		object_init_ex(_17$$9, yii_base_invalidcallexception_ce);
		ZEPHIR_INIT_VAR(_18$$9);
		zephir_get_class(_18$$9, this_ptr, 0 TSRMLS_CC);
		ZEPHIR_INIT_VAR(_19$$9);
		ZEPHIR_CONCAT_SVSV(_19$$9, "Setting read-only property: ", _18$$9, "::", name);
		ZEPHIR_CALL_METHOD(NULL, _17$$9, "__construct", NULL, 2, _19$$9);
		zephir_check_call_status();
		zephir_throw_exception_debug(_17$$9, "yii/base/Component.zep", 190 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} else {
		ZEPHIR_INIT_VAR(_20$$10);
		object_init_ex(_20$$10, yii_base_unknownpropertyexception_ce);
		ZEPHIR_INIT_VAR(_21$$10);
		zephir_get_class(_21$$10, this_ptr, 0 TSRMLS_CC);
		ZEPHIR_INIT_VAR(_22$$10);
		ZEPHIR_CONCAT_SVSV(_22$$10, "Setting unknown property: ", _21$$10, "::", name);
		ZEPHIR_CALL_METHOD(NULL, _20$$10, "__construct", NULL, 3, _22$$10);
		zephir_check_call_status();
		zephir_throw_exception_debug(_20$$10, "yii/base/Component.zep", 192 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}

}

/**
 * Checks if a property is set, i.e. defined and not null.
 * This method will check in the following order and act accordingly:
 *
 *  - a property defined by a setter: return whether the property is set
 *  - a property of a behavior: return whether the property is set
 *  - return `false` for non existing properties
 *
 * Do not call this method directly as it is a PHP magic method that
 * will be implicitly called when executing `isset($component->property)`.
 * @param string $name the property name or the event name
 * @return boolean whether the named property is set
 * @see http://php.net/manual/en/function.isset.php
 */
PHP_METHOD(yii_base_Component, __isset) {

	HashTable *_4$$4;
	HashPosition _3$$4;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *getter = NULL, *behavior = NULL, *_1$$3 = NULL, *_2$$4, **_5$$4, *_6$$5 = NULL, *_7$$6 = NULL;
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
		zephir_is_iterable(_2$$4, &_4$$4, &_3$$4, 0, 0, "yii/base/Component.zep", 225);
		for (
		  ; zephir_hash_get_current_data_ex(_4$$4, (void**) &_5$$4, &_3$$4) == SUCCESS
		  ; zephir_hash_move_forward_ex(_4$$4, &_3$$4)
		) {
			ZEPHIR_GET_HVALUE(behavior, _5$$4);
			ZEPHIR_CALL_METHOD(&_6$$5, behavior, "cangetproperty", NULL, 0, name);
			zephir_check_call_status();
			if (zephir_is_true(_6$$5)) {
				ZEPHIR_OBS_NVAR(_7$$6);
				zephir_read_property_zval(&_7$$6, behavior, name, PH_NOISY_CC);
				RETURN_MM_BOOL(Z_TYPE_P(_7$$6) != IS_NULL);
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
 * @see http://php.net/manual/en/function.unset.php
 */
PHP_METHOD(yii_base_Component, __unset) {

	HashTable *_4$$4;
	HashPosition _3$$4;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *setter = NULL, *behavior = NULL, *_7, *_8, *_9, *_1$$3, *_2$$4, **_5$$4, *_6$$5 = NULL;
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
		zephir_is_iterable(_2$$4, &_4$$4, &_3$$4, 0, 0, "yii/base/Component.zep", 259);
		for (
		  ; zephir_hash_get_current_data_ex(_4$$4, (void**) &_5$$4, &_3$$4) == SUCCESS
		  ; zephir_hash_move_forward_ex(_4$$4, &_3$$4)
		) {
			ZEPHIR_GET_HVALUE(behavior, _5$$4);
			ZEPHIR_CALL_METHOD(&_6$$5, behavior, "cansetproperty", NULL, 0, name);
			zephir_check_call_status();
			if (zephir_is_true(_6$$5)) {
				zephir_update_property_zval_zval(behavior, name, ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
				RETURN_MM_NULL();
			}
		}
	}
	ZEPHIR_INIT_VAR(_7);
	object_init_ex(_7, yii_base_invalidcallexception_ce);
	ZEPHIR_INIT_VAR(_8);
	zephir_get_class(_8, this_ptr, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_9);
	ZEPHIR_CONCAT_SVSV(_9, "Unsetting an unknown or read-only property: ", _8, "::", name);
	ZEPHIR_CALL_METHOD(NULL, _7, "__construct", NULL, 2, _9);
	zephir_check_call_status();
	zephir_throw_exception_debug(_7, "yii/base/Component.zep", 260 TSRMLS_CC);
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

	HashTable *_2;
	HashPosition _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *params = NULL;
	zval *name_param = NULL, *params_param = NULL, *object = NULL, *callData = NULL, *_0, **_3, *_5, *_6, *_7, *_4$$3 = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &params_param);

	zephir_get_strval(name, name_param);
	zephir_get_arrval(params, params_param);


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
	zephir_check_call_status();
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
	zephir_is_iterable(_0, &_2, &_1, 0, 0, "yii/base/Component.zep", 287);
	for (
	  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HVALUE(object, _3);
		ZEPHIR_CALL_METHOD(&_4$$3, object, "hasmethod", NULL, 0, name);
		zephir_check_call_status();
		if (zephir_is_true(_4$$3)) {
			ZEPHIR_INIT_NVAR(callData);
			zephir_create_array(callData, 2, 0 TSRMLS_CC);
			zephir_array_fast_append(callData, object);
			zephir_array_fast_append(callData, name);
			ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, callData, params);
			zephir_check_call_status();
			RETURN_MM();
		}
	}
	ZEPHIR_INIT_VAR(_5);
	object_init_ex(_5, yii_base_unknownmethodexception_ce);
	ZEPHIR_INIT_VAR(_6);
	zephir_get_class(_6, this_ptr, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_7);
	ZEPHIR_CONCAT_SVSVS(_7, "Calling unknown method: ", _6, "::", name, "()");
	ZEPHIR_CALL_METHOD(NULL, _5, "__construct", NULL, 2, _7);
	zephir_check_call_status();
	zephir_throw_exception_debug(_5, "yii/base/Component.zep", 287 TSRMLS_CC);
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
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool checkVars, checkBehaviors, _1, _2;
	zval *name_param = NULL, *checkVars_param = NULL, *checkBehaviors_param = NULL, *behavior = NULL, *_3 = NULL, *_4$$4, **_7$$4, *_8$$5 = NULL, *_9$$5 = NULL;
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
	if (_1) {
		RETURN_MM_BOOL(1);
	} else if (checkBehaviors) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
		zephir_check_call_status();
		_4$$4 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
		zephir_is_iterable(_4$$4, &_6$$4, &_5$$4, 0, 0, "yii/base/Component.zep", 349);
		for (
		  ; zephir_hash_get_current_data_ex(_6$$4, (void**) &_7$$4, &_5$$4) == SUCCESS
		  ; zephir_hash_move_forward_ex(_6$$4, &_5$$4)
		) {
			ZEPHIR_GET_HVALUE(behavior, _7$$4);
			ZEPHIR_INIT_NVAR(_9$$5);
			if (checkVars) {
				ZVAL_BOOL(_9$$5, 1);
			} else {
				ZVAL_BOOL(_9$$5, 0);
			}
			ZEPHIR_CALL_METHOD(&_8$$5, behavior, "cangetproperty", NULL, 0, name, _9$$5);
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
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool checkVars, checkBehaviors, _1, _2;
	zval *name_param = NULL, *checkVars_param = NULL, *checkBehaviors_param = NULL, *behavior = NULL, *_3 = NULL, *_4$$4, **_7$$4, *_8$$5 = NULL, *_9$$5 = NULL;
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
	if (_1) {
		RETURN_MM_BOOL(1);
	} else if (checkBehaviors) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
		zephir_check_call_status();
		_4$$4 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
		zephir_is_iterable(_4$$4, &_6$$4, &_5$$4, 0, 0, "yii/base/Component.zep", 381);
		for (
		  ; zephir_hash_get_current_data_ex(_6$$4, (void**) &_7$$4, &_5$$4) == SUCCESS
		  ; zephir_hash_move_forward_ex(_6$$4, &_5$$4)
		) {
			ZEPHIR_GET_HVALUE(behavior, _7$$4);
			ZEPHIR_INIT_NVAR(_9$$5);
			if (checkVars) {
				ZVAL_BOOL(_9$$5, 1);
			} else {
				ZVAL_BOOL(_9$$5, 0);
			}
			ZEPHIR_CALL_METHOD(&_8$$5, behavior, "cansetproperty", NULL, 0, name, _9$$5);
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
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool checkBehaviors;
	zval *name_param = NULL, *checkBehaviors_param = NULL, *behavior = NULL, *_0$$4, **_3$$4, *_4$$5 = NULL;
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
	} else if (checkBehaviors) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
		zephir_check_call_status();
		_0$$4 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
		zephir_is_iterable(_0$$4, &_2$$4, &_1$$4, 0, 0, "yii/base/Component.zep", 409);
		for (
		  ; zephir_hash_get_current_data_ex(_2$$4, (void**) &_3$$4, &_1$$4) == SUCCESS
		  ; zephir_hash_move_forward_ex(_2$$4, &_1$$4)
		) {
			ZEPHIR_GET_HVALUE(behavior, _3$$4);
			ZEPHIR_CALL_METHOD(&_4$$5, behavior, "hasmethod", NULL, 0, name);
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
 * ```php
 * 'behaviorName' => [
 *     'class' => 'BehaviorClass',
 *     'property1' => 'value1',
 *     'property2' => 'value2',
 * ]
 * ```
 *
 * Note that a behavior class must extend from [[Behavior]]. Behaviors can be attached using a name or anonymously.
 * When a name is used as the array key, using this name, the behavior can later be retrieved using [[getBehavior()]]
 * or be detached using [[detachBehavior()]]. Anonymous behaviors can not be retrieved or detached.
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

	zend_bool _1, _4;
	zephir_fcall_cache_entry *_6 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *_0, *_2, *_3, *_5 = NULL;
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
		ZEPHIR_OBS_VAR(_3);
		zephir_array_fetch(&_3, _2, name, PH_NOISY, "yii/base/Component.zep", 451 TSRMLS_CC);
		_1 = !(ZEPHIR_IS_EMPTY(_3));
	}
	_4 = _1;
	if (!(_4)) {
		ZEPHIR_CALL_CE_STATIC(&_5, yii_base_event_ce, "hashandlers", &_6, 7, this_ptr, name);
		zephir_check_call_status();
		_4 = zephir_is_true(_5);
	}
	RETURN_MM_BOOL(_4);

}

/**
 * Attaches an event handler to an event.
 *
 * The event handler must be a valid PHP callback. The following are
 * some examples:
 *
 * ```
 * function ($event) { ... }         // anonymous function
 * [$object, 'handleClick']          // $object->handleClick()
 * ['Page', 'handleClick']           // Page::handleClick()
 * 'handleClick'                     // global function handleClick()
 * ```
 *
 * The event handler must be defined with the following signature,
 *
 * ```
 * function ($event)
 * ```
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

	zval *_5$$3;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool append, _0, _2;
	zval *name_param = NULL, *handler, *data = NULL, *append_param = NULL, *handlerData = NULL, *_1, *_3, *_4, *_6$$4, *_7$$4;
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
	_0 = append;
	if (!(_0)) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
		_2 = !(zephir_array_isset(_1, name));
		if (!(_2)) {
			_3 = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
			ZEPHIR_OBS_VAR(_4);
			zephir_array_fetch(&_4, _3, name, PH_NOISY, "yii/base/Component.zep", 489 TSRMLS_CC);
			_2 = ZEPHIR_IS_EMPTY(_4);
		}
		_0 = _2;
	}
	if (_0) {
		ZEPHIR_INIT_VAR(_5$$3);
		zephir_create_array(_5$$3, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(_5$$3, handler);
		zephir_array_fast_append(_5$$3, data);
		zephir_update_property_array_multi(this_ptr, SL("_events"), &_5$$3 TSRMLS_CC, SL("za"), 2, name);
	} else {
		ZEPHIR_INIT_VAR(handlerData);
		zephir_create_array(handlerData, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(handlerData, handler);
		zephir_array_fast_append(handlerData, data);
		_6$$4 = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
		zephir_array_fetch(&_7$$4, _6$$4, name, PH_NOISY | PH_READONLY, "yii/base/Component.zep", 493 TSRMLS_CC);
		ZEPHIR_MAKE_REF(_7$$4);
		ZEPHIR_CALL_FUNCTION(NULL, "array_unshift", NULL, 8, _7$$4, handlerData);
		ZEPHIR_UNREF(_7$$4);
		zephir_check_call_status();
	}
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

	HashTable *_8$$5;
	HashPosition _7$$5;
	zend_bool removed = 0, _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *handler = NULL, *i = NULL, *event = NULL, *_0, *_2, *_3, *_4$$4, *_5$$5, *_6$$5, **_9$$5, *_10$$6, *_11$$7, *_12$$7, *_13$$8, *_14$$8, *_15$$8 = NULL;
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
		ZEPHIR_OBS_VAR(_3);
		zephir_array_fetch(&_3, _2, name, PH_NOISY, "yii/base/Component.zep", 511 TSRMLS_CC);
		_1 = ZEPHIR_IS_EMPTY(_3);
	}
	if (_1) {
		RETURN_MM_BOOL(0);
	}
	if (Z_TYPE_P(handler) == IS_NULL) {
		_4$$4 = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
		zephir_array_unset(&_4$$4, name, PH_SEPARATE);
		RETURN_MM_BOOL(1);
	} else {
		removed = 0;
		_5$$5 = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
		zephir_array_fetch(&_6$$5, _5$$5, name, PH_NOISY | PH_READONLY, "yii/base/Component.zep", 520 TSRMLS_CC);
		zephir_is_iterable(_6$$5, &_8$$5, &_7$$5, 0, 0, "yii/base/Component.zep", 527);
		for (
		  ; zephir_hash_get_current_data_ex(_8$$5, (void**) &_9$$5, &_7$$5) == SUCCESS
		  ; zephir_hash_move_forward_ex(_8$$5, &_7$$5)
		) {
			ZEPHIR_GET_HMKEY(i, _8$$5, _7$$5);
			ZEPHIR_GET_HVALUE(event, _9$$5);
			zephir_array_fetch_long(&_10$$6, event, 0, PH_NOISY | PH_READONLY, "yii/base/Component.zep", 521 TSRMLS_CC);
			if (ZEPHIR_IS_IDENTICAL(_10$$6, handler)) {
				_11$$7 = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
				zephir_array_fetch(&_12$$7, _11$$7, name, PH_NOISY | PH_READONLY, "yii/base/Component.zep", 522 TSRMLS_CC);
				zephir_array_unset(&_12$$7, i, PH_SEPARATE);
				removed = 1;
			}
		}
		if (removed) {
			_13$$8 = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
			zephir_array_fetch(&_14$$8, _13$$8, name, PH_NOISY | PH_READONLY, "yii/base/Component.zep", 528 TSRMLS_CC);
			ZEPHIR_CALL_FUNCTION(&_15$$8, "array_values", NULL, 9, _14$$8);
			zephir_check_call_status();
			zephir_update_property_array(this_ptr, SL("_events"), name, _15$$8 TSRMLS_CC);
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
	zend_bool _1;
	zephir_fcall_cache_entry *_12 = NULL, *_14 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *event = NULL, *handler = NULL, *_0, *_2, *_3, *_4$$3, *_5$$3, *_6$$3, **_9$$3, *_10$$6, *_11$$6, *_13$$6 = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name_param, &event);

	zephir_get_strval(name, name_param);
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
		ZEPHIR_OBS_VAR(_3);
		zephir_array_fetch(&_3, _2, name, PH_NOISY, "yii/base/Component.zep", 546 TSRMLS_CC);
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
		zephir_array_fetch(&_6$$3, _5$$3, name, PH_NOISY | PH_READONLY, "yii/base/Component.zep", 555 TSRMLS_CC);
		zephir_is_iterable(_6$$3, &_8$$3, &_7$$3, 0, 0, "yii/base/Component.zep", 563);
		for (
		  ; zephir_hash_get_current_data_ex(_8$$3, (void**) &_9$$3, &_7$$3) == SUCCESS
		  ; zephir_hash_move_forward_ex(_8$$3, &_7$$3)
		) {
			ZEPHIR_GET_HVALUE(handler, _9$$3);
			zephir_array_fetch_long(&_10$$6, handler, 1, PH_NOISY | PH_READONLY, "yii/base/Component.zep", 556 TSRMLS_CC);
			zephir_update_property_zval(event, SL("data"), _10$$6 TSRMLS_CC);
			zephir_array_fetch_long(&_11$$6, handler, 0, PH_NOISY | PH_READONLY, "yii/base/Component.zep", 557 TSRMLS_CC);
			ZEPHIR_CALL_FUNCTION(NULL, "call_user_func", &_12, 11, _11$$6, event);
			zephir_check_call_status();
			ZEPHIR_OBS_NVAR(_13$$6);
			zephir_read_property(&_13$$6, event, SL("handled"), PH_NOISY_CC);
			if (zephir_is_true(_13$$6)) {
				RETURN_MM_NULL();
			}
		}
	}
	ZEPHIR_CALL_CE_STATIC(NULL, yii_base_event_ce, "trigger", &_14, 12, this_ptr, name, event);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns the named behavior object.
 * @param string $name the behavior name
 * @return null|Behavior the behavior object, or null if the behavior does not exist
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
		zephir_array_fetch(&_0, _2, name, PH_NOISY, "yii/base/Component.zep", 576 TSRMLS_CC);
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
 *  - an object configuration array that will be passed to [[BaseYii::createObject()]] to create the behavior object.
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
	zval *behaviors_param = NULL, *name = NULL, *behavior = NULL, **_2;
	zval *behaviors = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &behaviors_param);

	zephir_get_arrval(behaviors, behaviors_param);


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(behaviors, &_1, &_0, 0, 0, "yii/base/Component.zep", 625);
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
 * @return null|Behavior the detached behavior. Null if the behavior does not exist.
 */
PHP_METHOD(yii_base_Component, detachBehavior) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, *behavior = NULL, *_0, *_1$$3, *_2$$3;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(name, name_param);


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
	zephir_check_call_status();
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
	if (zephir_array_isset(_0, name)) {
		_1$$3 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
		ZEPHIR_OBS_VAR(behavior);
		zephir_array_fetch(&behavior, _1$$3, name, PH_NOISY, "yii/base/Component.zep", 639 TSRMLS_CC);
		_2$$3 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
		zephir_array_unset(&_2$$3, name, PH_SEPARATE);
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

	HashTable *_2;
	HashPosition _1;
	zval *name = NULL, *behavior = NULL, *_0, **_3;
	zephir_fcall_cache_entry *_4 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(NULL, this_ptr, "ensurebehaviors", NULL, 0);
	zephir_check_call_status();
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
	zephir_is_iterable(_0, &_2, &_1, 0, 0, "yii/base/Component.zep", 660);
	for (
	  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HMKEY(name, _2, _1);
		ZEPHIR_GET_HVALUE(behavior, _3);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "detachbehavior", &_4, 0, name);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Makes sure that the behaviors declared in [[behaviors()]] are attached to this component.
 */
PHP_METHOD(yii_base_Component, ensureBehaviors) {

	HashTable *_4$$3;
	HashPosition _3$$3;
	zval *name = NULL, *behavior = NULL, *_0, *_1$$3, *_2$$3 = NULL, **_5$$3;
	zephir_fcall_cache_entry *_6 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_behaviors"), PH_NOISY_CC);
	if (Z_TYPE_P(_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(_1$$3);
		array_init(_1$$3);
		zephir_update_property_this(this_ptr, SL("_behaviors"), _1$$3 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "behaviors", NULL, 0);
		zephir_check_call_status();
		zephir_is_iterable(_2$$3, &_4$$3, &_3$$3, 0, 0, "yii/base/Component.zep", 674);
		for (
		  ; zephir_hash_get_current_data_ex(_4$$3, (void**) &_5$$3, &_3$$3) == SUCCESS
		  ; zephir_hash_move_forward_ex(_4$$3, &_3$$3)
		) {
			ZEPHIR_GET_HMKEY(name, _4$$3, _3$$3);
			ZEPHIR_GET_HVALUE(behavior, _5$$3);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "attachbehaviorinternal", &_6, 0, name, behavior);
			zephir_check_call_status();
		}
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Attaches a behavior to this component.
 * @param string|integer $name the name of the behavior. If this is an integer, it means the behavior
 * is an anonymous one. Otherwise, the behavior is a named one and any existing behavior with the same name
 * will be detached first.
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
			zephir_array_fetch(&_4$$6, _3$$6, name, PH_NOISY | PH_READONLY, "yii/base/Component.zep", 695 TSRMLS_CC);
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

