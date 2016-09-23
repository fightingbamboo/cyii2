
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
#include "kernel/string.h"
#include "kernel/array.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/hash.h"


/**
 * @link http://www.yiiframework.com/
 * @copyright Copyright (c) 2008 Yii Software LLC
 * @license http://www.yiiframework.com/license/
 */
/**
 * Event is the base class for all event classes.
 *
 * It encapsulates the parameters associated with an event.
 * The [[sender]] property describes who raises the event.
 * And the [[handled]] property indicates if the event is handled.
 * If an event handler sets [[handled]] to be true, the rest of the
 * uninvoked handlers will no longer be called to handle the event.
 *
 * Additionally, when attaching an event handler, extra data may be passed
 * and be available via the [[data]] property when the event handler is invoked.
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
ZEPHIR_INIT_CLASS(yii_base_Event) {

	ZEPHIR_REGISTER_CLASS_EX(yii\\base, Event, yii, base_event, yii_base_object_ce, yii_base_event_method_entry, 0);

	/**
	 * @var string the event name. This property is set by [[Component::trigger()]] and [[trigger()]].
	 * Event handlers may use this property to check what event it is handling.
	 */
	zend_declare_property_null(yii_base_event_ce, SL("name"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * @var object the sender of this event. If not set, this property will be
	 * set as the object whose "trigger()" method is called.
	 * This property may also be a `null` when this event is a
	 * class-level event which is triggered in a static context.
	 */
	zend_declare_property_null(yii_base_event_ce, SL("sender"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * @var boolean whether the event is handled. Defaults to false.
	 * When a handler sets this to be true, the event processing will stop and
	 * ignore the rest of the uninvoked event handlers.
	 */
	zend_declare_property_bool(yii_base_event_ce, SL("handled"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * @var mixed the data that is passed to [[Component::on()]] when attaching an event handler.
	 * Note that this varies according to which event handler is currently executing.
	 */
	zend_declare_property_null(yii_base_event_ce, SL("data"), ZEND_ACC_PUBLIC TSRMLS_CC);

	zend_declare_property_null(yii_base_event_ce, SL("_events"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	return SUCCESS;

}

/**
 * Attaches an event handler to a class-level event.
 *
 * When a class-level event is triggered, event handlers attached
 * to that class and all parent classes will be invoked.
 *
 * For example, the following code attaches an event handler to `ActiveRecord`'s
 * `afterInsert` event:
 *
 * ~~~
 * Event::on(ActiveRecord::className(), ActiveRecord::EVENT_AFTER_INSERT, function ($event) {
 *     Yii::trace(get_class($event->sender) . ' is inserted.');
 * });
 * ~~~
 *
 * The handler will be invoked for EVERY successful ActiveRecord insertion.
 *
 * For more details about how to declare an event handler, please refer to [[Component::on()]].
 *
 * @param string $class the fully qualified class name to which the event handler needs to attach.
 * @param string $name the event name.
 * @param callable $handler the event handler.
 * @param mixed $data the data to be passed to the event handler when the event is triggered.
 * When the event handler is invoked, this data can be accessed via [[Event::data]].
 * @see off()
 */
PHP_METHOD(yii_base_Event, on) {

	zval *_14$$5, *_18$$6;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool append, _7, _10;
	zval *name = NULL;
	zval *class = NULL, *name_param = NULL, *handler, *data = NULL, *append_param = NULL, *_0, _1, *_2, *_4, *_5, *_8, *_9, *_11, *_12, *_13, *_3$$3, *_6$$4, *_15$$6, *_16$$6, *_17$$6;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 2, &class, &name_param, &handler, &data, &append_param);

	ZEPHIR_SEPARATE_PARAM(class);
	zephir_get_strval(name, name_param);
	if (!data) {
		data = ZEPHIR_GLOBAL(global_null);
	}
	if (!append_param) {
		append = 1;
	} else {
		append = zephir_get_boolval(append_param);
	}


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "\\", 0);
	zephir_fast_trim(_0, class, &_1, ZEPHIR_TRIM_LEFT TSRMLS_CC);
	ZEPHIR_CPY_WRT(class, _0);
	_2 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
	if (!(zephir_array_isset(_2, name))) {
		ZEPHIR_INIT_VAR(_3$$3);
		array_init(_3$$3);
		zephir_update_static_property_array_multi_ce(yii_base_event_ce, SL("_events"), &_3$$3 TSRMLS_CC, SL("z"), 1, name);
	}
	_4 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
	zephir_array_fetch(&_5, _4, name, PH_READONLY, "yii/base/Event.zep", 85 TSRMLS_CC);
	if (!(zephir_array_isset(_5, class))) {
		ZEPHIR_INIT_VAR(_6$$4);
		array_init(_6$$4);
		zephir_update_static_property_array_multi_ce(yii_base_event_ce, SL("_events"), &_6$$4 TSRMLS_CC, SL("zz"), 2, name, class);
	}
	_7 = append;
	if (!(_7)) {
		_8 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
		zephir_array_fetch(&_9, _8, name, PH_READONLY, "yii/base/Event.zep", 89 TSRMLS_CC);
		_10 = !(zephir_array_isset(_9, class));
		if (!(_10)) {
			_11 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
			zephir_array_fetch(&_12, _11, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 89 TSRMLS_CC);
			zephir_array_fetch(&_13, _12, class, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 89 TSRMLS_CC);
			_10 = ZEPHIR_IS_EMPTY(_13);
		}
		_7 = _10;
	}
	if (_7) {
		ZEPHIR_INIT_VAR(_14$$5);
		zephir_create_array(_14$$5, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(_14$$5, handler);
		zephir_array_fast_append(_14$$5, data);
		zephir_update_static_property_array_multi_ce(yii_base_event_ce, SL("_events"), &_14$$5 TSRMLS_CC, SL("zza"), 3, name, class);
	} else {
		_15$$6 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
		zephir_array_fetch(&_16$$6, _15$$6, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 92 TSRMLS_CC);
		zephir_array_fetch(&_17$$6, _16$$6, class, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 92 TSRMLS_CC);
		ZEPHIR_INIT_VAR(_18$$6);
		zephir_create_array(_18$$6, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(_18$$6, handler);
		zephir_array_fast_append(_18$$6, data);
		ZEPHIR_MAKE_REF(_17$$6);
		ZEPHIR_CALL_FUNCTION(NULL, "array_unshift", NULL, 8, _17$$6, _18$$6);
		ZEPHIR_UNREF(_17$$6);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Detaches an event handler from a class-level event.
 *
 * This method is the opposite of [[on()]].
 *
 * @param string $class the fully qualified class name from which the event handler needs to be detached.
 * @param string $name the event name.
 * @param callable $handler the event handler to be removed.
 * If it is null, all handlers attached to the named event will be removed.
 * @return boolean whether a handler is found and detached.
 * @see on()
 */
PHP_METHOD(yii_base_Event, off) {

	HashTable *_17$$6;
	HashPosition _16$$6;
	zend_bool _4, removed$$5 = 0, _19$$7;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name = NULL;
	zval *class = NULL, *name_param = NULL, *handler = NULL, *_0, _1, *_2, *_3, *_5, *_6, *_7, *_8$$4, *_9$$4, *i$$5 = NULL, *temp_event$$5 = NULL, *_10$$5, *_11$$5, *_12$$5, *_13$$6, *_14$$6, *_15$$6, **_18$$6, *_20$$7, *_21$$8, *_22$$8, *_23$$8, *_24$$9, *_25$$9, *_26$$9, *_27$$9 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &class, &name_param, &handler);

	ZEPHIR_SEPARATE_PARAM(class);
	zephir_get_strval(name, name_param);
	if (!handler) {
		handler = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "\\", 0);
	zephir_fast_trim(_0, class, &_1, ZEPHIR_TRIM_LEFT TSRMLS_CC);
	ZEPHIR_CPY_WRT(class, _0);
	_2 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
	zephir_array_fetch(&_3, _2, name, PH_READONLY, "yii/base/Event.zep", 111 TSRMLS_CC);
	_4 = !(zephir_array_isset(_3, class));
	if (!(_4)) {
		_5 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
		zephir_array_fetch(&_6, _5, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 111 TSRMLS_CC);
		zephir_array_fetch(&_7, _6, class, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 111 TSRMLS_CC);
		_4 = ZEPHIR_IS_EMPTY(_7);
	}
	if (_4) {
		RETURN_MM_BOOL(0);
	}
	if (Z_TYPE_P(handler) == IS_NULL) {
		_8$$4 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
		zephir_array_fetch(&_9$$4, _8$$4, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 115 TSRMLS_CC);
		zephir_array_unset(&_9$$4, class, PH_SEPARATE);
		RETURN_MM_BOOL(1);
	} else {
		removed$$5 = 0;
		_10$$5 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
		zephir_array_fetch(&_11$$5, _10$$5, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 120 TSRMLS_CC);
		ZEPHIR_OBS_VAR(_12$$5);
		zephir_array_fetch(&_12$$5, _11$$5, class, PH_NOISY, "yii/base/Event.zep", 120 TSRMLS_CC);
		if (Z_TYPE_P(_12$$5) == IS_ARRAY) {
			_13$$6 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
			zephir_array_fetch(&_14$$6, _13$$6, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 121 TSRMLS_CC);
			zephir_array_fetch(&_15$$6, _14$$6, class, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 121 TSRMLS_CC);
			zephir_is_iterable(_15$$6, &_17$$6, &_16$$6, 0, 0, "yii/base/Event.zep", 127);
			for (
			  ; zephir_hash_get_current_data_ex(_17$$6, (void**) &_18$$6, &_16$$6) == SUCCESS
			  ; zephir_hash_move_forward_ex(_17$$6, &_16$$6)
			) {
				ZEPHIR_GET_HMKEY(i$$5, _17$$6, _16$$6);
				ZEPHIR_GET_HVALUE(temp_event$$5, _18$$6);
				_19$$7 = Z_TYPE_P(temp_event$$5) == IS_ARRAY;
				if (_19$$7) {
					zephir_array_fetch_long(&_20$$7, temp_event$$5, 0, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 122 TSRMLS_CC);
					_19$$7 = ZEPHIR_IS_EQUAL(_20$$7, handler);
				}
				if (_19$$7) {
					_21$$8 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
					zephir_array_fetch(&_22$$8, _21$$8, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 123 TSRMLS_CC);
					zephir_array_fetch(&_23$$8, _22$$8, class, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 123 TSRMLS_CC);
					zephir_array_unset(&_23$$8, i$$5, PH_SEPARATE);
					removed$$5 = 1;
				}
			}
		}
		if (removed$$5) {
			_24$$9 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
			zephir_array_fetch(&_25$$9, _24$$9, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 129 TSRMLS_CC);
			zephir_array_fetch(&_26$$9, _25$$9, class, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 129 TSRMLS_CC);
			ZEPHIR_CALL_FUNCTION(&_27$$9, "array_values", NULL, 9, _26$$9);
			zephir_check_call_status();
			zephir_update_static_property_array_multi_ce(yii_base_event_ce, SL("_events"), &_27$$9 TSRMLS_CC, SL("zz"), 2, name, class);
		}
		RETURN_MM_BOOL(removed$$5);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Detaches all registered class-level event handlers.
 * @see on()
 * @see off()
 * @since 2.0.10
 */
PHP_METHOD(yii_base_Event, offAll) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_static_property_ce(yii_base_event_ce, SL("_events"), &_0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns a value indicating whether there is any handler attached to the specified class-level event.
 * Note that this method will also check all parent classes to see if there is any handler attached
 * to the named event.
 * @param string|object $class the object or the fully qualified class name specifying the class-level event.
 * @param string $name the event name.
 * @return boolean whether there is any handler attached to the event.
 */
PHP_METHOD(yii_base_Event, hasHandlers) {

	HashTable *_11;
	HashPosition _10;
	zval *_7;
	zend_bool _1, _15$$6;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name = NULL;
	zval *class = NULL, *name_param = NULL, *_0, *_2, *_3, *classes = NULL, *_8 = NULL, *_9 = NULL, **_12, *_4$$4, *_5$$5, _6$$5, *_13$$6, *_14$$6, *_16$$6, *_17$$6, *_18$$6;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &class, &name_param);

	ZEPHIR_SEPARATE_PARAM(class);
	zephir_get_strval(name, name_param);


	_0 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
	_1 = !(zephir_array_isset(_0, name));
	if (!(_1)) {
		_2 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
		zephir_array_fetch(&_3, _2, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 157 TSRMLS_CC);
		_1 = ZEPHIR_IS_EMPTY(_3);
	}
	if (_1) {
		RETURN_MM_BOOL(0);
	}
	if (Z_TYPE_P(class) == IS_OBJECT) {
		ZEPHIR_INIT_VAR(_4$$4);
		zephir_get_class(_4$$4, class, 0 TSRMLS_CC);
		ZEPHIR_CPY_WRT(class, _4$$4);
	} else {
		ZEPHIR_INIT_VAR(_5$$5);
		ZEPHIR_SINIT_VAR(_6$$5);
		ZVAL_STRING(&_6$$5, "\\", 0);
		zephir_fast_trim(_5$$5, class, &_6$$5, ZEPHIR_TRIM_LEFT TSRMLS_CC);
		ZEPHIR_CPY_WRT(class, _5$$5);
	}
	ZEPHIR_INIT_VAR(_7);
	zephir_create_array(_7, 1, 0 TSRMLS_CC);
	zephir_array_fast_append(_7, class);
	ZEPHIR_CALL_FUNCTION(&_8, "class_parents", NULL, 13, class, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_9, "class_implements", NULL, 14, class, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&classes, "array_merge", NULL, 15, _7, _8, _9);
	zephir_check_call_status();
	zephir_is_iterable(classes, &_11, &_10, 0, 0, "yii/base/Event.zep", 178);
	for (
	  ; zephir_hash_get_current_data_ex(_11, (void**) &_12, &_10) == SUCCESS
	  ; zephir_hash_move_forward_ex(_11, &_10)
	) {
		ZEPHIR_GET_HVALUE(class, _12);
		_13$$6 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
		zephir_array_fetch(&_14$$6, _13$$6, name, PH_READONLY, "yii/base/Event.zep", 174 TSRMLS_CC);
		_15$$6 = zephir_array_isset(_14$$6, class);
		if (_15$$6) {
			_16$$6 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
			zephir_array_fetch(&_17$$6, _16$$6, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 174 TSRMLS_CC);
			zephir_array_fetch(&_18$$6, _17$$6, class, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 174 TSRMLS_CC);
			_15$$6 = !(ZEPHIR_IS_EMPTY(_18$$6));
		}
		if (_15$$6) {
			RETURN_MM_BOOL(1);
		}
	}
	RETURN_MM_BOOL(0);

}

/**
 * Triggers a class-level event.
 * This method will cause invocation of event handlers that are attached to the named event
 * for the specified class and all its parent classes.
 * @param string|object $class the object or the fully qualified class name specifying the class-level event.
 * @param string $name the event name.
 * @param Event $event the event parameter. If not set, a default [[Event]] object will be created.
 */
PHP_METHOD(yii_base_Event, trigger) {

	HashTable *_10, *_22$$9;
	HashPosition _9, _21$$9;
	zval *_6;
	zend_bool _0, _14$$8;
	zephir_fcall_cache_entry *_26 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name = NULL;
	zval *class = NULL, *name_param = NULL, *event = NULL, *events = NULL, *_1, *classes = NULL, *_7 = NULL, *_8 = NULL, **_11, *_2$$5, *_3$$5, *_4$$7, _5$$7, *_12$$8, *_13$$8, *_15$$8, *_16$$8, *_17$$8, *handler$$9 = NULL, *_18$$9, *_19$$9, *_20$$9, **_23$$9, *_24$$10, *_25$$10, *_27$$10;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &class, &name_param, &event);

	ZEPHIR_SEPARATE_PARAM(class);
	zephir_get_strval(name, name_param);
	if (!event) {
		ZEPHIR_CPY_WRT(event, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(event);
	}


	ZEPHIR_OBS_VAR(events);
	zephir_read_static_property_ce(&events, yii_base_event_ce, SL("_events") TSRMLS_CC);
	_0 = !(zephir_array_isset(events, name));
	if (!(_0)) {
		zephir_array_fetch(&_1, events, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 194 TSRMLS_CC);
		_0 = ZEPHIR_IS_EMPTY(_1);
	}
	if (_0) {
		RETURN_MM_NULL();
	}
	if (Z_TYPE_P(event) == IS_NULL) {
		ZEPHIR_INIT_NVAR(event);
		object_init_ex(event, yii_base_event_ce);
		ZEPHIR_CALL_METHOD(NULL, event, "__construct", NULL, 10);
		zephir_check_call_status();
	}
	if (0) {
		zephir_update_property_zval(event, SL("handled"), ZEPHIR_GLOBAL(global_true) TSRMLS_CC);
	} else {
		zephir_update_property_zval(event, SL("handled"), ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	}
	zephir_update_property_zval(event, SL("name"), name TSRMLS_CC);
	if (Z_TYPE_P(class) == IS_OBJECT) {
		ZEPHIR_OBS_VAR(_2$$5);
		zephir_read_property_this(&_2$$5, event, SL("sender"), PH_NOISY_CC);
		if (Z_TYPE_P(_2$$5) == IS_NULL) {
			zephir_update_property_zval(event, SL("sender"), class TSRMLS_CC);
		}
		ZEPHIR_INIT_VAR(_3$$5);
		zephir_get_class(_3$$5, class, 0 TSRMLS_CC);
		ZEPHIR_CPY_WRT(class, _3$$5);
	} else {
		ZEPHIR_INIT_VAR(_4$$7);
		ZEPHIR_SINIT_VAR(_5$$7);
		ZVAL_STRING(&_5$$7, "\\", 0);
		zephir_fast_trim(_4$$7, class, &_5$$7, ZEPHIR_TRIM_LEFT TSRMLS_CC);
		ZEPHIR_CPY_WRT(class, _4$$7);
	}
	ZEPHIR_INIT_VAR(_6);
	zephir_create_array(_6, 1, 0 TSRMLS_CC);
	zephir_array_fast_append(_6, class);
	ZEPHIR_CALL_FUNCTION(&_7, "class_parents", NULL, 13, class, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_8, "class_implements", NULL, 14, class, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&classes, "array_merge", NULL, 15, _6, _7, _8);
	zephir_check_call_status();
	zephir_is_iterable(classes, &_10, &_9, 0, 0, "yii/base/Event.zep", 233);
	for (
	  ; zephir_hash_get_current_data_ex(_10, (void**) &_11, &_9) == SUCCESS
	  ; zephir_hash_move_forward_ex(_10, &_9)
	) {
		ZEPHIR_GET_HVALUE(class, _11);
		_12$$8 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
		zephir_array_fetch(&_13$$8, _12$$8, name, PH_READONLY, "yii/base/Event.zep", 222 TSRMLS_CC);
		_14$$8 = zephir_array_isset(_13$$8, class);
		if (_14$$8) {
			_15$$8 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
			zephir_array_fetch(&_16$$8, _15$$8, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 222 TSRMLS_CC);
			zephir_array_fetch(&_17$$8, _16$$8, class, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 222 TSRMLS_CC);
			_14$$8 = !(ZEPHIR_IS_EMPTY(_17$$8));
		}
		if (_14$$8) {
			_18$$9 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
			zephir_array_fetch(&_19$$9, _18$$9, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 224 TSRMLS_CC);
			zephir_array_fetch(&_20$$9, _19$$9, class, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 224 TSRMLS_CC);
			zephir_is_iterable(_20$$9, &_22$$9, &_21$$9, 0, 0, "yii/base/Event.zep", 231);
			for (
			  ; zephir_hash_get_current_data_ex(_22$$9, (void**) &_23$$9, &_21$$9) == SUCCESS
			  ; zephir_hash_move_forward_ex(_22$$9, &_21$$9)
			) {
				ZEPHIR_GET_HVALUE(handler$$9, _23$$9);
				zephir_array_fetch_long(&_24$$10, handler$$9, 1, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 225 TSRMLS_CC);
				zephir_update_property_zval(event, SL("data"), _24$$10 TSRMLS_CC);
				zephir_array_fetch_long(&_25$$10, handler$$9, 0, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 226 TSRMLS_CC);
				ZEPHIR_CALL_FUNCTION(NULL, "call_user_func", &_26, 11, _25$$10, event);
				zephir_check_call_status();
				_27$$10 = zephir_fetch_nproperty_this(event, SL("handled"), PH_NOISY_CC);
				if (zephir_is_true(_27$$10)) {
					RETURN_MM_NULL();
				}
			}
		}
	}
	ZEPHIR_MM_RESTORE();

}

void zephir_init_static_properties_yii_base_Event(TSRMLS_D) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_static_property_ce(yii_base_event_ce, SL("_events"), &_0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

