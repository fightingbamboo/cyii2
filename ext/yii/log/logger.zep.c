
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
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/array.h"
#include "kernel/time.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/hash.h"
#include "kernel/string.h"


/**
 * @link http://www.yiiframework.com/
 * @copyright Copyright (c) 2008 Yii Software LLC
 * @license http://www.yiiframework.com/license/
 */
/**
 * Logger records logged messages in memory and sends them to different targets if [[dispatcher]] is set.
 *
 * Logger can be accessed via `Yii::getLogger()`. You can call the method [[log()]] to record a single log message.
 * For convenience, a set of shortcut methods are provided for logging messages of various severity levels
 * via the [[Yii]] class:
 *
 * - [[Yii::trace()]]
 * - [[Yii::error()]]
 * - [[Yii::warning()]]
 * - [[Yii::info()]]
 * - [[Yii::beginProfile()]]
 * - [[Yii::endProfile()]]
 *
 * When the application ends or [[flushInterval]] is reached, Logger will call [[flush()]]
 * to send logged messages to different log targets, such as file, email, Web, with the help of [[dispatcher]].
 *
 * @property array $dbProfiling The first element indicates the number of SQL statements executed, and the
 * second element the total time spent in SQL execution. This property is read-only.
 * @property float $elapsedTime The total elapsed time in seconds for current request. This property is
 * read-only.
 * @property array $profiling The profiling results. Each element is an array consisting of these elements:
 * `info`, `category`, `timestamp`, `trace`, `level`, `duration`. This property is read-only.
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
ZEPHIR_INIT_CLASS(yii_log_Logger) {

	ZEPHIR_REGISTER_CLASS_EX(yii\\log, Logger, yii, log_logger, yii_base_component_ce, yii_log_logger_method_entry, 0);

	/**
	 * @var array logged messages. This property is managed by [[log()]] and [[flush()]].
	 * Each log message is of the following structure:
	 *
	 * ~~~
	 * [
	 *   [0] => message (mixed, can be a string or some complex data, such as an exception object)
	 *   [1] => level (integer)
	 *   [2] => category (string)
	 *   [3] => timestamp (float, obtained by microtime(true))
	 *   [4] => traces (array, debug backtrace, contains the application code call stacks)
	 * ]
	 * ~~~
	 */
	zend_declare_property_null(yii_log_logger_ce, SL("messages"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * @var integer how many messages should be logged before they are flushed from memory and sent to targets.
	 * Defaults to 1000, meaning the [[flush]] method will be invoked once every 1000 messages logged.
	 * Set this property to be 0 if you don't want to flush messages until the application terminates.
	 * This property mainly affects how much memory will be taken by the logged messages.
	 * A smaller value means less memory, but will increase the execution time due to the overhead of [[flush()]].
	 */
	zend_declare_property_long(yii_log_logger_ce, SL("flushInterval"), 1000, ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * @var integer how much call stack information (file name and line number) should be logged for each message.
	 * If it is greater than 0, at most that number of call stacks will be logged. Note that only application
	 * call stacks are counted.
	 */
	zend_declare_property_long(yii_log_logger_ce, SL("traceLevel"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * @var Dispatcher the message dispatcher
	 */
	zend_declare_property_null(yii_log_logger_ce, SL("dispatcher"), ZEND_ACC_PUBLIC TSRMLS_CC);

	yii_log_logger_ce->create_object = zephir_init_properties_yii_log_Logger;
	/**
	 * Error message level. An error message is one that indicates the abnormal termination of the
	 * application and may require developer's handling.
	 */
	zend_declare_class_constant_long(yii_log_logger_ce, SL("LEVEL_ERROR"), 0x01 TSRMLS_CC);

	/**
	 * Warning message level. A warning message is one that indicates some abnormal happens but
	 * the application is able to continue to run. Developers should pay attention to this message.
	 */
	zend_declare_class_constant_long(yii_log_logger_ce, SL("LEVEL_WARNING"), 0x02 TSRMLS_CC);

	/**
	 * Informational message level. An informational message is one that includes certain information
	 * for developers to review.
	 */
	zend_declare_class_constant_long(yii_log_logger_ce, SL("LEVEL_INFO"), 0x04 TSRMLS_CC);

	/**
	 * Tracing message level. An tracing message is one that reveals the code execution flow.
	 */
	zend_declare_class_constant_long(yii_log_logger_ce, SL("LEVEL_TRACE"), 0x08 TSRMLS_CC);

	/**
	 * Profiling message level. This indicates the message is for profiling purpose.
	 */
	zend_declare_class_constant_long(yii_log_logger_ce, SL("LEVEL_PROFILE"), 0x40 TSRMLS_CC);

	/**
	 * Profiling message level. This indicates the message is for profiling purpose. It marks the
	 * beginning of a profiling block.
	 */
	zend_declare_class_constant_long(yii_log_logger_ce, SL("LEVEL_PROFILE_BEGIN"), 0x50 TSRMLS_CC);

	/**
	 * Profiling message level. This indicates the message is for profiling purpose. It marks the
	 * end of a profiling block.
	 */
	zend_declare_class_constant_long(yii_log_logger_ce, SL("LEVEL_PROFILE_END"), 0x60 TSRMLS_CC);

	return SUCCESS;

}

/**
 * Initializes the logger by registering [[flush()]] as a shutdown function.
 */
PHP_METHOD(yii_log_Logger, init) {

	zval *_2;
	zval *_1;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_PARENT(NULL, yii_log_logger_ce, this_ptr, "init", &_0, 22);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_1);
	zephir_create_array(_1, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(_1, this_ptr);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "flush", 1);
	zephir_array_fast_append(_1, _2);
	ZEPHIR_CALL_FUNCTION(NULL, "register_shutdown_function", NULL, 23, _1, ZEPHIR_GLOBAL(global_true));
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Logs a message with the given type and category.
 * If [[traceLevel]] is greater than 0, additional call stack information about
 * the application code will be logged as well.
 * @param string $message the message to be logged.
 * @param integer $level the level of the message. This must be one of the following:
 * `Logger::LEVEL_ERROR`, `Logger::LEVEL_WARNING`, `Logger::LEVEL_INFO`, `Logger::LEVEL_TRACE`,
 * `Logger::LEVEL_PROFILE_BEGIN`, `Logger::LEVEL_PROFILE_END`.
 * @param string $category the category of the message.
 */
PHP_METHOD(yii_log_Logger, log) {

	HashTable *_2$$3;
	HashPosition _1$$3;
	zend_bool _8, _4$$4;
	zval *_6;
	int ZEPHIR_LAST_CALL_STATUS, count = 0;
	zval *message, *level, *category = NULL, *time = NULL, *traces = NULL, *ts = NULL, *_0, *_7, *_9, *_10, *trace$$3 = NULL, **_3$$3, *_5$$5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &message, &level, &category);

	if (!category) {
		ZEPHIR_INIT_VAR(category);
		ZVAL_STRING(category, "application", 1);
	}


	ZEPHIR_INIT_VAR(traces);
	array_init(traces);
	ZEPHIR_INIT_VAR(time);
	zephir_microtime(time, ZEPHIR_GLOBAL(global_true) TSRMLS_CC);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("traceLevel"), PH_NOISY_CC);
	if (ZEPHIR_GT_LONG(_0, 0)) {
		count = 0;
		ZEPHIR_CALL_FUNCTION(&ts, "debug_backtrace", NULL, 24);
		zephir_check_call_status();
		ZEPHIR_MAKE_REF(ts);
		ZEPHIR_CALL_FUNCTION(NULL, "array_pop", NULL, 25, ts);
		ZEPHIR_UNREF(ts);
		zephir_check_call_status();
		zephir_is_iterable(ts, &_2$$3, &_1$$3, 0, 0, "yii/log/Logger.zep", 164);
		for (
		  ; zephir_hash_get_current_data_ex(_2$$3, (void**) &_3$$3, &_1$$3) == SUCCESS
		  ; zephir_hash_move_forward_ex(_2$$3, &_1$$3)
		) {
			ZEPHIR_GET_HVALUE(trace$$3, _3$$3);
			_4$$4 = zephir_array_isset_string(trace$$3, SS("file"));
			if (_4$$4) {
				_4$$4 = zephir_array_isset_string(trace$$3, SS("line"));
			}
			if (_4$$4) {
				zephir_array_unset_string(&trace$$3, SS("object"), PH_SEPARATE);
				zephir_array_unset_string(&trace$$3, SS("args"), PH_SEPARATE);
				zephir_array_append(&traces, trace$$3, PH_SEPARATE, "yii/log/Logger.zep", 155);
				_5$$5 = zephir_fetch_nproperty_this(this_ptr, SL("traceLevel"), PH_NOISY_CC);
				if (ZEPHIR_LE_LONG(_5$$5, count)) {
					count += 1;
					break;
				} else {
					count += 1;
				}
			}
		}
	}
	ZEPHIR_INIT_VAR(_6);
	zephir_create_array(_6, 5, 0 TSRMLS_CC);
	zephir_array_fast_append(_6, message);
	zephir_array_fast_append(_6, level);
	zephir_array_fast_append(_6, category);
	zephir_array_fast_append(_6, time);
	zephir_array_fast_append(_6, traces);
	zephir_update_property_array_append(this_ptr, SL("messages"), _6 TSRMLS_CC);
	_7 = zephir_fetch_nproperty_this(this_ptr, SL("flushInterval"), PH_NOISY_CC);
	_8 = ZEPHIR_GT_LONG(_7, 0);
	if (_8) {
		_9 = zephir_fetch_nproperty_this(this_ptr, SL("messages"), PH_NOISY_CC);
		_10 = zephir_fetch_nproperty_this(this_ptr, SL("flushInterval"), PH_NOISY_CC);
		_8 = ZEPHIR_LE_LONG(_10, zephir_fast_count_int(_9 TSRMLS_CC));
	}
	if (_8) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "flush", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Flushes log messages from memory to targets.
 * @param boolean $final whether this is a final call during a request.
 */
PHP_METHOD(yii_log_Logger, flush) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *isFinal = NULL, *messages = NULL, *_0, *_1, *_2, *_3$$3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &isFinal);

	if (!isFinal) {
		isFinal = ZEPHIR_GLOBAL(global_false);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("messages"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(messages, _0);
	ZEPHIR_INIT_VAR(_1);
	array_init(_1);
	zephir_update_property_this(this_ptr, SL("messages"), _1 TSRMLS_CC);
	ZEPHIR_OBS_VAR(_2);
	zephir_read_property_this(&_2, this_ptr, SL("dispatcher"), PH_NOISY_CC);
	if (zephir_is_instance_of(_2, SL("yii\\log\\Dispatcher") TSRMLS_CC)) {
		_3$$3 = zephir_fetch_nproperty_this(this_ptr, SL("dispatcher"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, _3$$3, "dispatch", NULL, 0, messages, isFinal);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns the total elapsed time since the start of the current request.
 * This method calculates the difference between now and the timestamp
 * defined by constant `YII_BEGIN_TIME` which is evaluated at the beginning
 * of [[\yii\BaseYii]] class file.
 * @return float the total elapsed time in seconds for current request.
 */
PHP_METHOD(yii_log_Logger, getElapsedTime) {

	zval *_0, *_1;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	zephir_microtime(_0, ZEPHIR_GLOBAL(global_true) TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	ZEPHIR_GET_CONSTANT(_1, "YII_BEGIN_TIME");
	zephir_sub_function(return_value, _0, _1);
	RETURN_MM();

}

/**
 * Returns the profiling results.
 *
 * By default, all profiling results will be returned. You may provide
 * `$categories` and `$excludeCategories` as parameters to retrieve the
 * results that you are interested in.
 *
 * @param array $categories list of categories that you are interested in.
 * You can use an asterisk at the end of a category to do a prefix match.
 * For example, 'yii\db\*' will match categories starting with 'yii\db\',
 * such as 'yii\db\Connection'.
 * @param array $excludeCategories list of categories that you want to exclude
 * @return array the profiling results. Each element is an array consisting of these elements:
 * `info`, `category`, `timestamp`, `trace`, `level`, `duration`.
 */
PHP_METHOD(yii_log_Logger, getProfiling) {

	HashTable *_3, *_6$$4, *_15$$7, *_19$$8;
	HashPosition _2, _5$$4, _14$$7, _18$$8;
	zend_bool _1, matched$$4 = 0, _11$$5, _13$$5, _23$$9, _25$$9;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *categories = NULL, *excludeCategories = NULL, *timings = NULL, *_0, *i = NULL, *timing = NULL, *prefix = NULL, **_4, *category$$4 = NULL, **_7$$4, _8$$5 = zval_used_for_init, *_9$$5, *_10$$5 = NULL, *_12$$5, **_16$$7, _17$$8 = zval_used_for_init, **_20$$8, *_21$$9, *_22$$9 = NULL, *_24$$9;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &categories, &excludeCategories);

	if (!categories) {
		ZEPHIR_INIT_VAR(categories);
		array_init(categories);
	}
	if (!excludeCategories) {
		ZEPHIR_INIT_VAR(excludeCategories);
		array_init(excludeCategories);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("messages"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&timings, this_ptr, "calculatetimings", NULL, 0, _0);
	zephir_check_call_status();
	_1 = ZEPHIR_IS_EMPTY(categories);
	if (_1) {
		_1 = ZEPHIR_IS_EMPTY(excludeCategories);
	}
	if (_1) {
		RETURN_CCTOR(timings);
	}
	zephir_is_iterable(timings, &_3, &_2, 1, 0, "yii/log/Logger.zep", 251);
	for (
	  ; zephir_hash_get_current_data_ex(_3, (void**) &_4, &_2) == SUCCESS
	  ; zephir_hash_move_forward_ex(_3, &_2)
	) {
		ZEPHIR_GET_HMKEY(i, _3, _2);
		ZEPHIR_GET_HVALUE(timing, _4);
		matched$$4 = ZEPHIR_IS_EMPTY(categories);
		zephir_is_iterable(categories, &_6$$4, &_5$$4, 0, 0, "yii/log/Logger.zep", 234);
		for (
		  ; zephir_hash_get_current_data_ex(_6$$4, (void**) &_7$$4, &_5$$4) == SUCCESS
		  ; zephir_hash_move_forward_ex(_6$$4, &_5$$4)
		) {
			ZEPHIR_GET_HVALUE(category$$4, _7$$4);
			ZEPHIR_SINIT_NVAR(_8$$5);
			ZVAL_STRING(&_8$$5, "*", 0);
			ZEPHIR_INIT_NVAR(prefix);
			zephir_fast_trim(prefix, category$$4, &_8$$5, ZEPHIR_TRIM_RIGHT TSRMLS_CC);
			zephir_array_fetch_string(&_9$$5, timing, SL("category"), PH_NOISY | PH_READONLY, "yii/log/Logger.zep", 228 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&_10$$5, _9$$5, "index", NULL, 0, prefix);
			zephir_check_call_status();
			_11$$5 = ZEPHIR_IS_LONG_IDENTICAL(_10$$5, 0);
			if (_11$$5) {
				zephir_array_fetch_string(&_12$$5, timing, SL("category"), PH_NOISY | PH_READONLY, "yii/log/Logger.zep", 228 TSRMLS_CC);
				_13$$5 = ZEPHIR_IS_IDENTICAL(_12$$5, category$$4);
				if (!(_13$$5)) {
					_13$$5 = !ZEPHIR_IS_IDENTICAL(prefix, category$$4);
				}
				_11$$5 = _13$$5;
			}
			if (_11$$5) {
				matched$$4 = 1;
				break;
			}
		}
		if (matched$$4) {
			zephir_is_iterable(excludeCategories, &_15$$7, &_14$$7, 0, 0, "yii/log/Logger.zep", 244);
			for (
			  ; zephir_hash_get_current_data_ex(_15$$7, (void**) &_16$$7, &_14$$7) == SUCCESS
			  ; zephir_hash_move_forward_ex(_15$$7, &_14$$7)
			) {
				ZEPHIR_GET_HVALUE(category$$4, _16$$7);
				ZEPHIR_SINIT_NVAR(_17$$8);
				ZVAL_STRING(&_17$$8, "*", 0);
				ZEPHIR_INIT_NVAR(prefix);
				zephir_fast_trim(prefix, category$$4, &_17$$8, ZEPHIR_TRIM_RIGHT TSRMLS_CC);
				zephir_is_iterable(timings, &_19$$8, &_18$$8, 0, 0, "yii/log/Logger.zep", 243);
				for (
				  ; zephir_hash_get_current_data_ex(_19$$8, (void**) &_20$$8, &_18$$8) == SUCCESS
				  ; zephir_hash_move_forward_ex(_19$$8, &_18$$8)
				) {
					ZEPHIR_GET_HVALUE(timing, _20$$8);
					zephir_array_fetch_string(&_21$$9, timing, SL("category"), PH_NOISY | PH_READONLY, "yii/log/Logger.zep", 238 TSRMLS_CC);
					ZEPHIR_CALL_METHOD(&_22$$9, _21$$9, "index", NULL, 0, prefix);
					zephir_check_call_status();
					_23$$9 = ZEPHIR_IS_LONG_IDENTICAL(_22$$9, 0);
					if (_23$$9) {
						zephir_array_fetch_string(&_24$$9, timing, SL("category"), PH_NOISY | PH_READONLY, "yii/log/Logger.zep", 238 TSRMLS_CC);
						_25$$9 = ZEPHIR_IS_IDENTICAL(_24$$9, category$$4);
						if (!(_25$$9)) {
							_25$$9 = !ZEPHIR_IS_IDENTICAL(prefix, category$$4);
						}
						_23$$9 = _25$$9;
					}
					if (_23$$9) {
						matched$$4 = 0;
						break;
					}
				}
			}
		}
		if (!(matched$$4)) {
			zephir_array_unset(&timings, i, PH_SEPARATE);
		}
	}
	zend_hash_destroy(_3);
	FREE_HASHTABLE(_3);
	ZEPHIR_RETURN_CALL_FUNCTION("array_values", NULL, 6, timings);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Returns the statistical results of DB queries.
 * The results returned include the number of SQL statements executed and
 * the total time spent.
 * @return array the first element indicates the number of SQL statements executed,
 * and the second element the total time spent in SQL execution.
 */
PHP_METHOD(yii_log_Logger, getDbProfiling) {

	HashTable *_3;
	HashPosition _2;
	zval *_0;
	zval *count = NULL, *timings = NULL, *_1 = NULL, *timing = NULL, **_4, *_5$$3 = NULL;
	int ZEPHIR_LAST_CALL_STATUS, time = 0;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	zephir_create_array(_0, 2, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "yii\\db\\Command::query", 1);
	zephir_array_fast_append(_0, _1);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "yii\\db\\Command::execute", 1);
	zephir_array_fast_append(_0, _1);
	ZEPHIR_CALL_METHOD(&timings, this_ptr, "getprofiling", NULL, 0, _0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(count);
	ZVAL_LONG(count, zephir_fast_count_int(timings TSRMLS_CC));
	time = 0;
	zephir_is_iterable(timings, &_3, &_2, 0, 0, "yii/log/Logger.zep", 274);
	for (
	  ; zephir_hash_get_current_data_ex(_3, (void**) &_4, &_2) == SUCCESS
	  ; zephir_hash_move_forward_ex(_3, &_2)
	) {
		ZEPHIR_GET_HVALUE(timing, _4);
		ZEPHIR_OBS_NVAR(_5$$3);
		zephir_array_fetch_string(&_5$$3, timing, SL("duration"), PH_NOISY, "yii/log/Logger.zep", 271 TSRMLS_CC);
		time += zephir_get_intval(_5$$3);
	}
	zephir_create_array(return_value, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(return_value, count);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_LONG(_1, time);
	zephir_array_fast_append(return_value, _1);
	RETURN_MM();

}

/**
 * Calculates the elapsed time for the given log messages.
 * @param array $messages the log messages obtained from profiling
 * @return array timings. Each element is an array consisting of these elements:
 * `info`, `category`, `timestamp`, `trace`, `level`, `duration`.
 */
PHP_METHOD(yii_log_Logger, calculateTimings) {

	zend_bool _4$$5;
	HashTable *_1;
	HashPosition _0;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_3 = NULL;
	zval *messages, *timings = NULL, *stack = NULL, *i = NULL, *log = NULL, **_2, *token$$3 = NULL, *level$$3 = NULL, *category$$3 = NULL, *timestamp$$3 = NULL, *traces$$3 = NULL, *timings_last$$3 = NULL, *last$$5 = NULL, *last_5$$5 = NULL, *_5$$5, *_6$$7 = NULL, *_7$$6, *_8$$6, *_9$$6, *_10$$6, *_11$$6 = NULL, *_12$$6, *_13$$6 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &messages);



	ZEPHIR_INIT_VAR(timings);
	array_init(timings);
	ZEPHIR_INIT_VAR(stack);
	array_init(stack);
	zephir_is_iterable(messages, &_1, &_0, 0, 0, "yii/log/Logger.zep", 322);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HMKEY(i, _1, _0);
		ZEPHIR_GET_HVALUE(log, _2);
		ZEPHIR_OBS_NVAR(token$$3);
		zephir_array_fetch_long(&token$$3, log, 0, PH_NOISY, "yii/log/Logger.zep", 291 TSRMLS_CC);
		ZEPHIR_OBS_NVAR(level$$3);
		zephir_array_fetch_long(&level$$3, log, 1, PH_NOISY, "yii/log/Logger.zep", 292 TSRMLS_CC);
		ZEPHIR_OBS_NVAR(category$$3);
		zephir_array_fetch_long(&category$$3, log, 2, PH_NOISY, "yii/log/Logger.zep", 293 TSRMLS_CC);
		ZEPHIR_OBS_NVAR(timestamp$$3);
		zephir_array_fetch_long(&timestamp$$3, log, 3, PH_NOISY, "yii/log/Logger.zep", 294 TSRMLS_CC);
		ZEPHIR_OBS_NVAR(traces$$3);
		zephir_array_fetch_long(&traces$$3, log, 4, PH_NOISY, "yii/log/Logger.zep", 295 TSRMLS_CC);
		zephir_array_update_long(&log, 5, &i, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
		if (ZEPHIR_IS_LONG(level$$3, 0x50)) {
			zephir_array_append(&stack, log, PH_SEPARATE, "yii/log/Logger.zep", 299);
		}
		if (ZEPHIR_IS_LONG(level$$3, 0x60)) {
			ZEPHIR_MAKE_REF(stack);
			ZEPHIR_CALL_FUNCTION(&last$$5, "array_pop", &_3, 25, stack);
			ZEPHIR_UNREF(stack);
			zephir_check_call_status();
			_4$$5 = Z_TYPE_P(last$$5) != IS_NULL;
			if (_4$$5) {
				zephir_array_fetch_long(&_5$$5, last$$5, 0, PH_NOISY | PH_READONLY, "yii/log/Logger.zep", 304 TSRMLS_CC);
				_4$$5 = ZEPHIR_IS_IDENTICAL(_5$$5, token$$3);
			}
			if (_4$$5) {
				ZEPHIR_OBS_NVAR(last_5$$5);
				zephir_array_fetch_long(&last_5$$5, last$$5, 5, PH_NOISY, "yii/log/Logger.zep", 305 TSRMLS_CC);
				if (!(zephir_array_isset(timings, last_5$$5))) {
					ZEPHIR_INIT_NVAR(_6$$7);
					array_init(_6$$7);
					zephir_array_update_zval(&timings, last_5$$5, &_6$$7, PH_COPY | PH_SEPARATE);
				}
				ZEPHIR_OBS_NVAR(timings_last$$3);
				zephir_array_fetch(&timings_last$$3, timings, last_5$$5, PH_NOISY, "yii/log/Logger.zep", 310 TSRMLS_CC);
				zephir_array_fetch_long(&_7$$6, last$$5, 0, PH_NOISY | PH_READONLY, "yii/log/Logger.zep", 311 TSRMLS_CC);
				zephir_array_update_string(&timings_last$$3, SL("info"), &_7$$6, PH_COPY | PH_SEPARATE);
				zephir_array_fetch_long(&_8$$6, last$$5, 2, PH_NOISY | PH_READONLY, "yii/log/Logger.zep", 312 TSRMLS_CC);
				zephir_array_update_string(&timings_last$$3, SL("category"), &_8$$6, PH_COPY | PH_SEPARATE);
				zephir_array_fetch_long(&_9$$6, last$$5, 3, PH_NOISY | PH_READONLY, "yii/log/Logger.zep", 313 TSRMLS_CC);
				zephir_array_update_string(&timings_last$$3, SL("timestamp"), &_9$$6, PH_COPY | PH_SEPARATE);
				zephir_array_fetch_long(&_10$$6, last$$5, 4, PH_NOISY | PH_READONLY, "yii/log/Logger.zep", 314 TSRMLS_CC);
				zephir_array_update_string(&timings_last$$3, SL("trace"), &_10$$6, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(_11$$6);
				ZVAL_LONG(_11$$6, zephir_fast_count_int(stack TSRMLS_CC));
				zephir_array_update_string(&timings_last$$3, SL("level"), &_11$$6, PH_COPY | PH_SEPARATE);
				zephir_array_fetch_long(&_12$$6, last$$5, 3, PH_NOISY | PH_READONLY, "yii/log/Logger.zep", 316 TSRMLS_CC);
				ZEPHIR_INIT_LNVAR(_13$$6);
				zephir_sub_function(_13$$6, timestamp$$3, _12$$6);
				zephir_array_update_string(&timings_last$$3, SL("duration"), &_13$$6, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&timings, last_5$$5, &timings_last$$3, PH_COPY | PH_SEPARATE);
			}
		}
	}
	ZEPHIR_MAKE_REF(timings);
	ZEPHIR_CALL_FUNCTION(NULL, "ksort", NULL, 26, timings);
	ZEPHIR_UNREF(timings);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_FUNCTION("array_values", NULL, 6, timings);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Returns the text display of the specified level.
 * @param integer $level the message level, e.g. [[LEVEL_ERROR]], [[LEVEL_WARNING]].
 * @return string the text display of the level
 */
PHP_METHOD(yii_log_Logger, getLevelName) {

	zval *level, *levels = NULL, *_0, *_1, *_2, *_3, *_4, *_5, *_6;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &level);



	ZEPHIR_INIT_VAR(levels);
	array_init(levels);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "error", 1);
	zephir_array_update_long(&levels, 0x01, &_0, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "warning", 1);
	zephir_array_update_long(&levels, 0x02, &_1, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "info", 1);
	zephir_array_update_long(&levels, 0x04, &_2, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_STRING(_3, "trace", 1);
	zephir_array_update_long(&levels, 0x08, &_3, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_VAR(_4);
	ZVAL_STRING(_4, "profile begin", 1);
	zephir_array_update_long(&levels, 0x50, &_4, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_VAR(_5);
	ZVAL_STRING(_5, "profile end", 1);
	zephir_array_update_long(&levels, 0x60, &_5, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_VAR(_6);
	if (zephir_array_isset(levels, level)) {
		zephir_array_fetch(&_6, levels, level, PH_NOISY, "yii/log/Logger.zep", 342 TSRMLS_CC);
	} else {
		ZVAL_STRING(_6, "unknown", 1);
	}
	RETURN_CCTOR(_6);

}

zend_object_value zephir_init_properties_yii_log_Logger(zend_class_entry *class_type TSRMLS_DC) {

		zval *_0, *_2, *_1$$3, *_3$$4;

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
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("messages"), PH_NOISY_CC);
		if (Z_TYPE_P(_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(_3$$4);
			array_init(_3$$4);
			zephir_update_property_this(this_ptr, SL("messages"), _3$$4 TSRMLS_CC);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJVAL_P(this_ptr);
	}

}

