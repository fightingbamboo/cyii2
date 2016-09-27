
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
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/object.h"
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
 * If an event handler sets [[handled]] to be `true`, the rest of the
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
	 * set as the object whose `trigger()` method is called.
	 * This property may also be a `null` when this event is a
	 * class-level event which is triggered in a static context.
	 */
	zend_declare_property_null(yii_base_event_ce, SL("sender"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * @var boolean whether the event is handled. Defaults to `false`.
	 * When a handler sets this to be `true`, the event processing will stop and
	 * ignore the rest of the uninvoked event handlers.
	 */
	zend_declare_property_bool(yii_base_event_ce, SL("handled"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * @var mixed the data that is passed to [[Component::on()]] when attaching an event handler.
	 * Note that this varies according to which event handler is currently executing.
	 */
	zend_declare_property_null(yii_base_event_ce, SL("data"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * @var array contains all globally registered event handlers.
	 */
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
 * ```php
 * Event::on(ActiveRecord::className(), ActiveRecord::EVENT_AFTER_INSERT, function ($event) {
 *     Yii::trace(get_class($event->sender) . ' is inserted.');
 * });
 * ```
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
 * @param boolean $append whether to append new event handler to the end of the existing
 * handler list. If `false`, the new handler will be inserted at the beginning of the existing
 * handler list.
 * @see off()
 */
PHP_METHOD(yii_base_Event, on) {

	zval *_11$$3;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool append, _2, _4, _7;
	zval *classs_param = NULL, *name_param = NULL, *handler, *data = NULL, *append_param = NULL, *tmpArray3b96bb5d49aa4e738ab1b36c1e0a9125 = NULL, *_0, _1, *_3, *_5, *_6, *_8, *_9, *_10, *_12$$4, *_13$$4, *_14$$4;
	zval *classs = NULL, *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 2, &classs_param, &name_param, &handler, &data, &append_param);

	zephir_get_strval(classs, classs_param);
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
	zephir_fast_trim(_0, classs, &_1, ZEPHIR_TRIM_LEFT TSRMLS_CC);
	zephir_get_strval(classs, _0);
	_2 = append;
	if (!(_2)) {
		_3 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
		_4 = !(zephir_array_isset(_3, name));
		if (!(_4)) {
			_5 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
			zephir_array_fetch(&_6, _5, name, PH_READONLY, "yii/base/Event.zep", 86 TSRMLS_CC);
			_4 = !(zephir_array_isset(_6, classs));
		}
		_7 = _4;
		if (!(_7)) {
			_8 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
			zephir_array_fetch(&_9, _8, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 86 TSRMLS_CC);
			ZEPHIR_OBS_VAR(_10);
			zephir_array_fetch(&_10, _9, classs, PH_NOISY, "yii/base/Event.zep", 86 TSRMLS_CC);
			_7 = ZEPHIR_IS_EMPTY(_10);
		}
		_2 = _7;
	}
	if (_2) {
		ZEPHIR_INIT_VAR(_11$$3);
		zephir_create_array(_11$$3, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(_11$$3, handler);
		zephir_array_fast_append(_11$$3, data);
		zephir_update_static_property_array_multi_ce(yii_base_event_ce, SL("_events"), &_11$$3 TSRMLS_CC, SL("zza"), 3, name, classs);
	} else {
		ZEPHIR_INIT_VAR(tmpArray3b96bb5d49aa4e738ab1b36c1e0a9125);
		zephir_create_array(tmpArray3b96bb5d49aa4e738ab1b36c1e0a9125, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(tmpArray3b96bb5d49aa4e738ab1b36c1e0a9125, handler);
		zephir_array_fast_append(tmpArray3b96bb5d49aa4e738ab1b36c1e0a9125, data);
		_12$$4 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
		zephir_array_fetch(&_13$$4, _12$$4, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 90 TSRMLS_CC);
		zephir_array_fetch(&_14$$4, _13$$4, classs, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 90 TSRMLS_CC);
		ZEPHIR_MAKE_REF(_14$$4);
		ZEPHIR_CALL_FUNCTION(NULL, "array_unshift", NULL, 8, _14$$4, tmpArray3b96bb5d49aa4e738ab1b36c1e0a9125);
		ZEPHIR_UNREF(_14$$4);
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
 * If it is `null`, all handlers attached to the named event will be removed.
 * @return boolean whether a handler is found and detached.
 * @see on()
 */
PHP_METHOD(yii_base_Event, off) {

	HashTable *_16$$5;
	HashPosition _15$$5;
	zend_bool removed = 0, _3, _6;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *classs_param = NULL, *name_param = NULL, *handler = NULL, *i = NULL, *event = NULL, *_0, _1, *_2, *_4, *_5, *_7, *_8, *_9, *_10$$4, *_11$$4, *_12$$5, *_13$$5, *_14$$5, **_17$$5, *_18$$6, *_19$$7, *_20$$7, *_21$$7, *_22$$8, *_23$$8, *_24$$8, *_25$$8 = NULL;
	zval *classs = NULL, *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &classs_param, &name_param, &handler);

	zephir_get_strval(classs, classs_param);
	zephir_get_strval(name, name_param);
	if (!handler) {
		handler = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "\\", 0);
	zephir_fast_trim(_0, classs, &_1, ZEPHIR_TRIM_LEFT TSRMLS_CC);
	zephir_get_strval(classs, _0);
	_2 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
	_3 = !(zephir_array_isset(_2, name));
	if (!(_3)) {
		_4 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
		zephir_array_fetch(&_5, _4, name, PH_READONLY, "yii/base/Event.zep", 111 TSRMLS_CC);
		_3 = !(zephir_array_isset(_5, classs));
	}
	_6 = _3;
	if (!(_6)) {
		_7 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
		zephir_array_fetch(&_8, _7, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 111 TSRMLS_CC);
		ZEPHIR_OBS_VAR(_9);
		zephir_array_fetch(&_9, _8, classs, PH_NOISY, "yii/base/Event.zep", 111 TSRMLS_CC);
		_6 = ZEPHIR_IS_EMPTY(_9);
	}
	if (_6) {
		RETURN_MM_BOOL(0);
	}
	if (Z_TYPE_P(handler) == IS_NULL) {
		_10$$4 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
		zephir_array_fetch(&_11$$4, _10$$4, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 115 TSRMLS_CC);
		zephir_array_unset(&_11$$4, classs, PH_SEPARATE);
		RETURN_MM_BOOL(1);
	} else {
		removed = 0;
		_12$$5 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
		zephir_array_fetch(&_13$$5, _12$$5, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 120 TSRMLS_CC);
		zephir_array_fetch(&_14$$5, _13$$5, classs, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 120 TSRMLS_CC);
		zephir_is_iterable(_14$$5, &_16$$5, &_15$$5, 0, 0, "yii/base/Event.zep", 127);
		for (
		  ; zephir_hash_get_current_data_ex(_16$$5, (void**) &_17$$5, &_15$$5) == SUCCESS
		  ; zephir_hash_move_forward_ex(_16$$5, &_15$$5)
		) {
			ZEPHIR_GET_HMKEY(i, _16$$5, _15$$5);
			ZEPHIR_GET_HVALUE(event, _17$$5);
			zephir_array_fetch_long(&_18$$6, event, 0, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 121 TSRMLS_CC);
			if (ZEPHIR_IS_IDENTICAL(_18$$6, handler)) {
				_19$$7 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
				zephir_array_fetch(&_20$$7, _19$$7, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 122 TSRMLS_CC);
				zephir_array_fetch(&_21$$7, _20$$7, classs, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 122 TSRMLS_CC);
				zephir_array_unset(&_21$$7, i, PH_SEPARATE);
				removed = 1;
			}
		}
		if (removed) {
			_22$$8 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
			zephir_array_fetch(&_23$$8, _22$$8, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 128 TSRMLS_CC);
			zephir_array_fetch(&_24$$8, _23$$8, classs, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 128 TSRMLS_CC);
			ZEPHIR_CALL_FUNCTION(&_25$$8, "array_values", NULL, 9, _24$$8);
			zephir_check_call_status();
			zephir_update_static_property_array_multi_ce(yii_base_event_ce, SL("_events"), &_25$$8 TSRMLS_CC, SL("zz"), 2, name, classs);
		}
		RETURN_MM_BOOL(removed);
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

	HashTable *_10;
	HashPosition _9;
	zend_bool _1, _14$$6;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name = NULL;
	zval *classs = NULL, *name_param = NULL, *classes = NULL, *tmpArray9613f42f8264d80e17bfc80cc7a471fb = NULL, *_0, *_2, *_3, *_7 = NULL, *_8 = NULL, **_11, *_4$$4, *_5$$5, _6$$5, *_12$$6, *_13$$6, *_15$$6, *_16$$6, *_17$$6 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &classs, &name_param);

	ZEPHIR_SEPARATE_PARAM(classs);
	zephir_get_strval(name, name_param);


	_0 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
	_1 = !(zephir_array_isset(_0, name));
	if (!(_1)) {
		_2 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
		ZEPHIR_OBS_VAR(_3);
		zephir_array_fetch(&_3, _2, name, PH_NOISY, "yii/base/Event.zep", 157 TSRMLS_CC);
		_1 = ZEPHIR_IS_EMPTY(_3);
	}
	if (_1) {
		RETURN_MM_BOOL(0);
	}
	if (Z_TYPE_P(classs) == IS_OBJECT) {
		ZEPHIR_INIT_VAR(_4$$4);
		zephir_get_class(_4$$4, classs, 0 TSRMLS_CC);
		ZEPHIR_CPY_WRT(classs, _4$$4);
	} else {
		ZEPHIR_INIT_VAR(_5$$5);
		ZEPHIR_SINIT_VAR(_6$$5);
		ZVAL_STRING(&_6$$5, "\\", 0);
		zephir_fast_trim(_5$$5, classs, &_6$$5, ZEPHIR_TRIM_LEFT TSRMLS_CC);
		ZEPHIR_CPY_WRT(classs, _5$$5);
	}
	ZEPHIR_INIT_VAR(tmpArray9613f42f8264d80e17bfc80cc7a471fb);
	zephir_create_array(tmpArray9613f42f8264d80e17bfc80cc7a471fb, 1, 0 TSRMLS_CC);
	zephir_array_fast_append(tmpArray9613f42f8264d80e17bfc80cc7a471fb, classs);
	ZEPHIR_CALL_FUNCTION(&_7, "class_parents", NULL, 13, classs, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_8, "class_implements", NULL, 14, classs, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&classes, "array_merge", NULL, 15, tmpArray9613f42f8264d80e17bfc80cc7a471fb, _7, _8);
	zephir_check_call_status();
	zephir_is_iterable(classes, &_10, &_9, 0, 0, "yii/base/Event.zep", 172);
	for (
	  ; zephir_hash_get_current_data_ex(_10, (void**) &_11, &_9) == SUCCESS
	  ; zephir_hash_move_forward_ex(_10, &_9)
	) {
		ZEPHIR_GET_HVALUE(classs, _11);
		_12$$6 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
		zephir_array_fetch(&_13$$6, _12$$6, name, PH_READONLY, "yii/base/Event.zep", 168 TSRMLS_CC);
		_14$$6 = zephir_array_isset(_13$$6, classs);
		if (_14$$6) {
			_15$$6 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
			zephir_array_fetch(&_16$$6, _15$$6, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 168 TSRMLS_CC);
			ZEPHIR_OBS_NVAR(_17$$6);
			zephir_array_fetch(&_17$$6, _16$$6, classs, PH_NOISY, "yii/base/Event.zep", 168 TSRMLS_CC);
			_14$$6 = !(ZEPHIR_IS_EMPTY(_17$$6));
		}
		if (_14$$6) {
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

	HashTable *_11, *_23$$9;
	HashPosition _10, _22$$9;
	zend_bool _1, _15$$8;
	zephir_fcall_cache_entry *_27 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *name = NULL;
	zval *classs = NULL, *name_param = NULL, *event = NULL, *classes = NULL, *tmpArray94fd3581f8118e54e2778c97fdb99a2e = NULL, *handler = NULL, *_0, *_2, *_3, *_8 = NULL, *_9 = NULL, **_12, *_4$$5, *_5$$5, *_6$$7, _7$$7, *_13$$8, *_14$$8, *_16$$8, *_17$$8, *_18$$8 = NULL, *_19$$9, *_20$$9, *_21$$9, **_24$$9, *_25$$10, *_26$$10, *_28$$10;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &classs, &name_param, &event);

	ZEPHIR_SEPARATE_PARAM(classs);
	zephir_get_strval(name, name_param);
	if (!event) {
		ZEPHIR_CPY_WRT(event, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(event);
	}


	_0 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
	_1 = !(zephir_array_isset(_0, name));
	if (!(_1)) {
		_2 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
		ZEPHIR_OBS_VAR(_3);
		zephir_array_fetch(&_3, _2, name, PH_NOISY, "yii/base/Event.zep", 187 TSRMLS_CC);
		_1 = ZEPHIR_IS_EMPTY(_3);
	}
	if (_1) {
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
	if (Z_TYPE_P(classs) == IS_OBJECT) {
		_4$$5 = zephir_fetch_nproperty_this(event, SL("sender"), PH_NOISY_CC);
		if (Z_TYPE_P(_4$$5) == IS_NULL) {
			zephir_update_property_zval(event, SL("sender"), classs TSRMLS_CC);
		}
		ZEPHIR_INIT_VAR(_5$$5);
		zephir_get_class(_5$$5, classs, 0 TSRMLS_CC);
		ZEPHIR_CPY_WRT(classs, _5$$5);
	} else {
		ZEPHIR_INIT_VAR(_6$$7);
		ZEPHIR_SINIT_VAR(_7$$7);
		ZVAL_STRING(&_7$$7, "\\", 0);
		zephir_fast_trim(_6$$7, classs, &_7$$7, ZEPHIR_TRIM_LEFT TSRMLS_CC);
		ZEPHIR_CPY_WRT(classs, _6$$7);
	}
	ZEPHIR_INIT_VAR(tmpArray94fd3581f8118e54e2778c97fdb99a2e);
	zephir_create_array(tmpArray94fd3581f8118e54e2778c97fdb99a2e, 1, 0 TSRMLS_CC);
	zephir_array_fast_append(tmpArray94fd3581f8118e54e2778c97fdb99a2e, classs);
	ZEPHIR_CALL_FUNCTION(&_8, "class_parents", NULL, 13, classs, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_9, "class_implements", NULL, 14, classs, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&classes, "array_merge", NULL, 15, tmpArray94fd3581f8118e54e2778c97fdb99a2e, _8, _9);
	zephir_check_call_status();
	zephir_is_iterable(classes, &_11, &_10, 0, 0, "yii/base/Event.zep", 216);
	for (
	  ; zephir_hash_get_current_data_ex(_11, (void**) &_12, &_10) == SUCCESS
	  ; zephir_hash_move_forward_ex(_11, &_10)
	) {
		ZEPHIR_GET_HVALUE(classs, _12);
		_13$$8 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
		zephir_array_fetch(&_14$$8, _13$$8, name, PH_READONLY, "yii/base/Event.zep", 206 TSRMLS_CC);
		_15$$8 = zephir_array_isset(_14$$8, classs);
		if (_15$$8) {
			_16$$8 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
			zephir_array_fetch(&_17$$8, _16$$8, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 206 TSRMLS_CC);
			ZEPHIR_OBS_NVAR(_18$$8);
			zephir_array_fetch(&_18$$8, _17$$8, classs, PH_NOISY, "yii/base/Event.zep", 206 TSRMLS_CC);
			_15$$8 = !(ZEPHIR_IS_EMPTY(_18$$8));
		}
		if (_15$$8) {
			_19$$9 = zephir_fetch_static_property_ce(yii_base_event_ce, SL("_events") TSRMLS_CC);
			zephir_array_fetch(&_20$$9, _19$$9, name, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 207 TSRMLS_CC);
			zephir_array_fetch(&_21$$9, _20$$9, classs, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 207 TSRMLS_CC);
			zephir_is_iterable(_21$$9, &_23$$9, &_22$$9, 0, 0, "yii/base/Event.zep", 214);
			for (
			  ; zephir_hash_get_current_data_ex(_23$$9, (void**) &_24$$9, &_22$$9) == SUCCESS
			  ; zephir_hash_move_forward_ex(_23$$9, &_22$$9)
			) {
				ZEPHIR_GET_HVALUE(handler, _24$$9);
				zephir_array_fetch_long(&_25$$10, handler, 1, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 208 TSRMLS_CC);
				zephir_update_property_zval(event, SL("data"), _25$$10 TSRMLS_CC);
				zephir_array_fetch_long(&_26$$10, handler, 0, PH_NOISY | PH_READONLY, "yii/base/Event.zep", 209 TSRMLS_CC);
				ZEPHIR_CALL_FUNCTION(NULL, "call_user_func", &_27, 11, _26$$10, event);
				zephir_check_call_status();
				_28$$10 = zephir_fetch_nproperty_this(event, SL("handled"), PH_NOISY_CC);
				if (zephir_is_true(_28$$10)) {
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

