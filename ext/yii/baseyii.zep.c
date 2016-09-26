
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/string.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/hash.h"
#include "kernel/exception.h"
#include "kernel/require.h"


/**
 * @link http://www.yiiframework.com/
 * @copyright Copyright (c) 2008 Yii Software LLC
 * @license http://www.yiiframework.com/license/
 */
/**
 * BaseYii is the core helper class for the Yii framework.
 *
 * Do not use BaseYii directly. Instead, use its child class [[\Yii]] which you can replace to
 * customize methods of BaseYii.
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
ZEPHIR_INIT_CLASS(yii_BaseYii) {

	ZEPHIR_REGISTER_CLASS(yii, BaseYii, yii, baseyii, yii_baseyii_method_entry, 0);

	/**
	 * @var array class map used by the Yii autoloading mechanism.
	 * The array keys are the class names (without leading backslashes), and the array values
	 * are the corresponding class file paths (or path aliases). This property mainly affects
	 * how [[autoload()]] works.
	 * @see autoload()
	 */
	zend_declare_property_null(yii_baseyii_ce, SL("classMap"), ZEND_ACC_PUBLIC|ZEND_ACC_STATIC TSRMLS_CC);

	/**
	 * @var \yii\console\Application|\yii\web\Application the application instance
	 */
	zend_declare_property_null(yii_baseyii_ce, SL("app"), ZEND_ACC_PUBLIC|ZEND_ACC_STATIC TSRMLS_CC);

	/**
	 * @var array registered path aliases
	 * @see getAlias()
	 * @see setAlias()
	 */
	zend_declare_property_null(yii_baseyii_ce, SL("aliases"), ZEND_ACC_PUBLIC|ZEND_ACC_STATIC TSRMLS_CC);

	/**
	 * @var Container the dependency injection (DI) container used by [[createObject()]].
	 * You may use [[Container::set()]] to set up the needed dependencies of classes and
	 * their initial property values.
	 * @see createObject()
	 * @see Container
	 */
	zend_declare_property_null(yii_baseyii_ce, SL("container"), ZEND_ACC_PUBLIC|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_null(yii_baseyii_ce, SL("_logger"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	return SUCCESS;

}

/**
 * Returns a string representing the current version of the Yii framework.
 * @return string the version of Yii framework
 */
PHP_METHOD(yii_BaseYii, getVersion) {

	

	RETURN_STRING("cyii 2.0.10-dev", 1);

}

/**
 * Translates a path alias into an actual path.
 *
 * The translation is done according to the following procedure:
 *
 * 1. If the given alias does not start with '@', it is returned back without change;
 * 2. Otherwise, look for the longest registered alias that matches the beginning part
 *    of the given alias. If it exists, replace the matching part of the given alias with
 *    the corresponding registered path.
 * 3. Throw an exception or return false, depending on the `$throwException` parameter.
 *
 * For example, by default '@yii' is registered as the alias to the Yii framework directory,
 * say '/path/to/yii'. The alias '@yii/web' would then be translated into '/path/to/yii/web'.
 *
 * If you have registered two aliases '@foo' and '@foo/bar'. Then translating '@foo/bar/config'
 * would replace the part '@foo/bar' (instead of '@foo') with the corresponding registered path.
 * This is because the longest alias takes precedence.
 *
 * However, if the alias to be translated is '@foo/barbar/config', then '@foo' will be replaced
 * instead of '@foo/bar', because '/' serves as the boundary character.
 *
 * Note, this method does not check if the returned path exists or not.
 *
 * @param string $alias the alias to be translated.
 * @param boolean $throwException whether to throw an exception if the given alias is invalid.
 * If this is false and an invalid alias is given, false will be returned by this method.
 * @return string|boolean the path corresponding to the alias, false if the root alias is not previously registered.
 * @throws InvalidParamException if the alias is invalid while $throwException is true.
 * @see setAlias()
 */
PHP_METHOD(yii_BaseYii, getAlias) {

	HashTable *_10$$10;
	HashPosition _9$$10;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool throwException, _14$$11;
	zval *alias_param = NULL, *throwException_param = NULL, *aliases = NULL, *root_alias = NULL, *_0, _1 = zval_used_for_init, _2, *_3 = NULL, *pos = NULL, *root = NULL, _4$$5, *_5$$8, *_6$$9, *_7$$9, *name$$10 = NULL, *path$$10 = NULL, *new_pos$$10 = NULL, *_8$$10, **_11$$10, *_13$$11 = NULL, _15$$12 = zval_used_for_init, *_16$$12 = NULL, *_17$$13;
	zval *alias = NULL, *_12$$11 = NULL, *_18$$13;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &alias_param, &throwException_param);

	zephir_get_strval(alias, alias_param);
	if (!throwException_param) {
		throwException = 1;
	} else {
		throwException = zephir_get_boolval(throwException_param);
	}


	ZEPHIR_OBS_VAR(_0);
	zephir_read_static_property_ce(&_0, yii_baseyii_ce, SL("aliases") TSRMLS_CC);
	ZEPHIR_CPY_WRT(aliases, _0);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "@", 0);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_LONG(&_2, 1);
	ZEPHIR_CALL_FUNCTION(&_3, "strncmp", NULL, 12, alias, &_1, &_2);
	zephir_check_call_status();
	if (zephir_is_true(_3)) {
		RETURN_CTOR(alias);
	}
	ZEPHIR_SINIT_NVAR(_1);
	ZVAL_STRING(&_1, "/", 0);
	ZEPHIR_INIT_VAR(pos);
	zephir_fast_strpos(pos, alias, &_1, 0 );
	if (Z_TYPE_P(pos) == IS_BOOL) {
		ZEPHIR_CPY_WRT(root, alias);
	} else {
		ZEPHIR_SINIT_VAR(_4$$5);
		ZVAL_LONG(&_4$$5, 0);
		ZEPHIR_INIT_NVAR(root);
		zephir_substr(root, alias, 0 , zephir_get_intval(pos), 0);
	}
	ZEPHIR_OBS_VAR(root_alias);
	if (zephir_array_isset_fetch(&root_alias, aliases, root, 0 TSRMLS_CC)) {
		if (Z_TYPE_P(root_alias) == IS_STRING) {
			if (Z_TYPE_P(pos) == IS_BOOL) {
				zephir_array_fetch(&_5$$8, aliases, root, PH_NOISY | PH_READONLY, "yii/BaseYii.zep", 115 TSRMLS_CC);
				RETURN_CTOR(_5$$8);
			} else {
				zephir_array_fetch(&_6$$9, aliases, root, PH_NOISY | PH_READONLY, "yii/BaseYii.zep", 118 TSRMLS_CC);
				ZEPHIR_INIT_VAR(_7$$9);
				zephir_substr(_7$$9, alias, zephir_get_intval(pos), 0, ZEPHIR_SUBSTR_NO_LENGTH);
				ZEPHIR_CONCAT_VV(return_value, _6$$9, _7$$9);
				RETURN_MM();
			}
		} else {
			zephir_array_fetch(&_8$$10, aliases, root, PH_NOISY | PH_READONLY, "yii/BaseYii.zep", 122 TSRMLS_CC);
			zephir_is_iterable(_8$$10, &_10$$10, &_9$$10, 0, 0, "yii/BaseYii.zep", 128);
			for (
			  ; zephir_hash_get_current_data_ex(_10$$10, (void**) &_11$$10, &_9$$10) == SUCCESS
			  ; zephir_hash_move_forward_ex(_10$$10, &_9$$10)
			) {
				ZEPHIR_GET_HMKEY(name$$10, _10$$10, _9$$10);
				ZEPHIR_GET_HVALUE(path$$10, _11$$10);
				ZEPHIR_INIT_LNVAR(_12$$11);
				ZEPHIR_CONCAT_VS(_12$$11, alias, "/");
				ZEPHIR_INIT_LNVAR(_13$$11);
				ZEPHIR_CONCAT_VS(_13$$11, name$$10, "/");
				ZEPHIR_INIT_NVAR(new_pos$$10);
				zephir_fast_strpos(new_pos$$10, _12$$11, _13$$11, 0 );
				_14$$11 = Z_TYPE_P(new_pos$$10) != IS_BOOL;
				if (_14$$11) {
					_14$$11 = ZEPHIR_IS_LONG(new_pos$$10, 0);
				}
				if (_14$$11) {
					ZEPHIR_SINIT_NVAR(_15$$12);
					ZVAL_LONG(&_15$$12, zephir_fast_strlen_ev(name$$10));
					ZEPHIR_INIT_NVAR(_16$$12);
					zephir_substr(_16$$12, alias, zephir_get_intval(&_15$$12), 0, ZEPHIR_SUBSTR_NO_LENGTH);
					ZEPHIR_CONCAT_VV(return_value, path$$10, _16$$12);
					RETURN_MM();
				}
			}
		}
	}
	if (throwException) {
		ZEPHIR_INIT_VAR(_17$$13);
		object_init_ex(_17$$13, yii_base_invalidparamexception_ce);
		ZEPHIR_INIT_VAR(_18$$13);
		ZEPHIR_CONCAT_SV(_18$$13, "Invalid path alias: ", alias);
		ZEPHIR_CALL_METHOD(NULL, _17$$13, "__construct", NULL, 2, _18$$13);
		zephir_check_call_status();
		zephir_throw_exception_debug(_17$$13, "yii/BaseYii.zep", 132 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} else {
		RETURN_MM_BOOL(0);
	}

}

/**
 * Returns the root alias part of a given alias.
 * A root alias is an alias that has been registered via [[setAlias()]] previously.
 * If a given alias matches multiple root aliases, the longest one will be returned.
 * @param string $alias the alias
 * @return string|boolean the root alias, or false if no root alias is found
 */
PHP_METHOD(yii_BaseYii, getRootAlias) {

	zend_bool _12$$8;
	HashTable *_8$$7;
	HashPosition _7$$7;
	zval *alias_param = NULL, *pos = NULL, *root = NULL, _0, *_2, _1$$4, *_3$$5, *_4$$5, *name$$7 = NULL, *path$$7 = NULL, *new_pos$$7 = NULL, *_5$$7, *_6$$7, **_9$$7, *_11$$8 = NULL;
	zval *alias = NULL, *_10$$8 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &alias_param);

	zephir_get_strval(alias, alias_param);


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_STRING(&_0, "/", 0);
	ZEPHIR_INIT_VAR(pos);
	zephir_fast_strpos(pos, alias, &_0, 0 );
	if (Z_TYPE_P(pos) == IS_BOOL) {
		ZEPHIR_CPY_WRT(root, alias);
	} else {
		ZEPHIR_SINIT_VAR(_1$$4);
		ZVAL_LONG(&_1$$4, 0);
		ZEPHIR_INIT_NVAR(root);
		zephir_substr(root, alias, 0 , zephir_get_intval(pos), 0);
	}
	_2 = zephir_fetch_static_property_ce(yii_baseyii_ce, SL("aliases") TSRMLS_CC);
	if (zephir_array_isset(_2, root)) {
		_3$$5 = zephir_fetch_static_property_ce(yii_baseyii_ce, SL("aliases") TSRMLS_CC);
		zephir_array_fetch(&_4$$5, _3$$5, root, PH_NOISY | PH_READONLY, "yii/BaseYii.zep", 158 TSRMLS_CC);
		if (Z_TYPE_P(_4$$5) == IS_STRING) {
			RETURN_CCTOR(root);
		} else {
			_5$$7 = zephir_fetch_static_property_ce(yii_baseyii_ce, SL("aliases") TSRMLS_CC);
			zephir_array_fetch(&_6$$7, _5$$7, root, PH_NOISY | PH_READONLY, "yii/BaseYii.zep", 162 TSRMLS_CC);
			zephir_is_iterable(_6$$7, &_8$$7, &_7$$7, 0, 0, "yii/BaseYii.zep", 168);
			for (
			  ; zephir_hash_get_current_data_ex(_8$$7, (void**) &_9$$7, &_7$$7) == SUCCESS
			  ; zephir_hash_move_forward_ex(_8$$7, &_7$$7)
			) {
				ZEPHIR_GET_HMKEY(name$$7, _8$$7, _7$$7);
				ZEPHIR_GET_HVALUE(path$$7, _9$$7);
				ZEPHIR_INIT_LNVAR(_10$$8);
				ZEPHIR_CONCAT_VS(_10$$8, alias, "/");
				ZEPHIR_INIT_LNVAR(_11$$8);
				ZEPHIR_CONCAT_VS(_11$$8, name$$7, "/");
				ZEPHIR_INIT_NVAR(new_pos$$7);
				zephir_fast_strpos(new_pos$$7, _10$$8, _11$$8, 0 );
				_12$$8 = Z_TYPE_P(new_pos$$7) != IS_BOOL;
				if (_12$$8) {
					_12$$8 = ZEPHIR_IS_LONG(new_pos$$7, 0);
				}
				if (_12$$8) {
					RETURN_CCTOR(name$$7);
				}
			}
		}
	}
	RETURN_MM_BOOL(0);

}

/**
 * Registers a path alias.
 *
 * A path alias is a short name representing a long path (a file path, a URL, etc.)
 * For example, we use '@yii' as the alias of the path to the Yii framework directory.
 *
 * A path alias must start with the character '@' so that it can be easily differentiated
 * from non-alias paths.
 *
 * Note that this method does not check if the given path exists or not. All it does is
 * to associate the alias with the path.
 *
 * Any trailing '/' and '\' characters in the given path will be trimmed.
 *
 * @param string $alias the alias name (e.g. "@yii"). It must start with a '@' character.
 * It may contain the forward slash '/' which serves as boundary character when performing
 * alias translation by [[getAlias()]].
 * @param string $path the path corresponding to the alias. Trailing '/' and '\' characters
 * will be trimmed. This can be
 *
 * - a directory or a file path (e.g. `/tmp`, `/tmp/main.txt`)
 * - a URL (e.g. `http://www.yiiframework.com`)
 * - a path alias (e.g. `@yii/base`). In this case, the path alias will be converted into the
 *   actual path first by calling [[getAlias()]].
 *
 * @throws InvalidParamException if $path is an invalid alias.
 * @see getAlias()
 */
PHP_METHOD(yii_BaseYii, setAlias) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_4 = NULL;
	zval *alias_param = NULL, *path, *aliases = NULL, *root_alias = NULL, *_0, _1 = zval_used_for_init, _2, *_3 = NULL, *pos = NULL, *root = NULL, _6$$6, *path_ext$$7 = NULL, _7$$7, _8$$7, *_9$$7 = NULL, *elements$$7 = NULL, _10$$8, *_11$$13, *_12$$16;
	zval *alias = NULL, *_5$$4;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &alias_param, &path);

	zephir_get_strval(alias, alias_param);


	ZEPHIR_OBS_VAR(_0);
	zephir_read_static_property_ce(&_0, yii_baseyii_ce, SL("aliases") TSRMLS_CC);
	ZEPHIR_CPY_WRT(aliases, _0);
	if (Z_TYPE_P(aliases) != IS_ARRAY) {
		ZEPHIR_INIT_NVAR(aliases);
		array_init(aliases);
	}
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "@", 0);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_LONG(&_2, 1);
	ZEPHIR_CALL_FUNCTION(&_3, "strncmp", &_4, 12, alias, &_1, &_2);
	zephir_check_call_status();
	if (zephir_is_true(_3)) {
		ZEPHIR_INIT_VAR(_5$$4);
		ZEPHIR_CONCAT_SV(_5$$4, "@", alias);
		ZEPHIR_CPY_WRT(alias, _5$$4);
	}
	ZEPHIR_SINIT_NVAR(_1);
	ZVAL_STRING(&_1, "/", 0);
	ZEPHIR_INIT_VAR(pos);
	zephir_fast_strpos(pos, alias, &_1, 0 );
	if (Z_TYPE_P(pos) == IS_BOOL) {
		ZEPHIR_CPY_WRT(root, alias);
	} else {
		ZEPHIR_SINIT_VAR(_6$$6);
		ZVAL_LONG(&_6$$6, 0);
		ZEPHIR_INIT_NVAR(root);
		zephir_substr(root, alias, 0 , zephir_get_intval(pos), 0);
	}
	if (Z_TYPE_P(path) == IS_STRING) {
		ZEPHIR_SINIT_VAR(_7$$7);
		ZVAL_STRING(&_7$$7, "@", 0);
		ZEPHIR_SINIT_VAR(_8$$7);
		ZVAL_LONG(&_8$$7, 1);
		ZEPHIR_CALL_FUNCTION(&_9$$7, "strncmp", &_4, 12, path, &_7$$7, &_8$$7);
		zephir_check_call_status();
		if (zephir_is_true(_9$$7)) {
			ZEPHIR_SINIT_VAR(_10$$8);
			ZVAL_STRING(&_10$$8, "\\/", 0);
			ZEPHIR_INIT_VAR(path_ext$$7);
			zephir_fast_trim(path_ext$$7, path, &_10$$8, ZEPHIR_TRIM_RIGHT TSRMLS_CC);
		} else {
			ZEPHIR_CALL_STATIC(&path_ext$$7, "getalias", NULL, 0, path);
			zephir_check_call_status();
		}
		ZEPHIR_INIT_VAR(elements$$7);
		array_init(elements$$7);
		if (!(zephir_array_isset(aliases, root))) {
			if (Z_TYPE_P(pos) == IS_BOOL) {
				zephir_array_update_zval(&aliases, root, &path_ext$$7, PH_COPY | PH_SEPARATE);
			} else {
				zephir_array_update_zval(&elements$$7, alias, &path_ext$$7, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&aliases, root, &elements$$7, PH_COPY | PH_SEPARATE);
			}
		} else {
			ZEPHIR_OBS_VAR(_11$$13);
			zephir_array_fetch(&_11$$13, aliases, root, PH_NOISY, "yii/BaseYii.zep", 244 TSRMLS_CC);
			if (Z_TYPE_P(_11$$13) == IS_STRING) {
				if (Z_TYPE_P(pos) == IS_BOOL) {
					zephir_array_update_zval(&aliases, root, &path_ext$$7, PH_COPY | PH_SEPARATE);
				} else {
					zephir_array_update_zval(&elements$$7, alias, &path_ext$$7, PH_COPY | PH_SEPARATE);
					zephir_array_fetch(&_12$$16, aliases, root, PH_NOISY | PH_READONLY, "yii/BaseYii.zep", 249 TSRMLS_CC);
					zephir_array_update_zval(&elements$$7, root, &_12$$16, PH_COPY | PH_SEPARATE);
					zephir_array_update_zval(&aliases, root, &elements$$7, PH_COPY | PH_SEPARATE);
				}
			} else {
				ZEPHIR_OBS_VAR(root_alias);
				zephir_array_fetch(&root_alias, aliases, root, PH_NOISY, "yii/BaseYii.zep", 253 TSRMLS_CC);
				zephir_array_update_zval(&root_alias, alias, &path_ext$$7, PH_COPY | PH_SEPARATE);
				ZEPHIR_MAKE_REF(root_alias);
				ZEPHIR_CALL_FUNCTION(NULL, "krsort", NULL, 16, root_alias);
				ZEPHIR_UNREF(root_alias);
				zephir_check_call_status();
				zephir_array_update_zval(&aliases, root, &root_alias, PH_COPY | PH_SEPARATE);
			}
		}
	} else {
		ZEPHIR_OBS_NVAR(root_alias);
		if (zephir_array_isset_fetch(&root_alias, aliases, root, 0 TSRMLS_CC)) {
			if (Z_TYPE_P(root_alias) == IS_ARRAY) {
				zephir_array_unset(&root_alias, alias, PH_SEPARATE);
				zephir_array_update_zval(&aliases, root, &root_alias, PH_COPY | PH_SEPARATE);
			} else {
				if (Z_TYPE_P(pos) == IS_BOOL) {
					zephir_array_unset(&aliases, root, PH_SEPARATE);
				}
			}
		}
	}
	zephir_update_static_property_ce(yii_baseyii_ce, SL("aliases"), &aliases TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Class autoload loader.
 * This method is invoked automatically when PHP sees an unknown class.
 * The method will attempt to include the class file according to the following procedure:
 *
 * 1. Search in [[classMap]];
 * 2. If the class is namespaced (e.g. `yii\base\Component`), it will attempt
 *    to include the file associated with the corresponding path alias
 *    (e.g. `@yii/base/Component.php`);
 *
 * This autoloader allows loading classes that follow the [PSR-4 standard](http://www.php-fig.org/psr/psr-4/)
 * and have its top-level namespace or sub-namespaces defined as path aliases.
 *
 * Example: When aliases `@yii` and `@yii/bootstrap` are defined, classes in the `yii\bootstrap` namespace
 * will be loaded using the `@yii/bootstrap` alias which points to the directory where bootstrap extension
 * files are installed and all classes from other `yii` namespaces will be loaded from the yii framework directory.
 *
 * @param string $className the fully qualified class name without a leading backslash "\"
 * @throws UnknownClassException if the class does not exist in the class file
 */
PHP_METHOD(yii_BaseYii, autoload) {

	zend_bool _14, _15, _16, _11$$5;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *className_param = NULL, *classFile = NULL, *_0, *pos = NULL, _5, *_13, *_17 = NULL, _1$$3, _2$$3, *_3$$3, *_4$$4 = NULL, *_6$$5, _7$$5, _8$$5, *_9$$5, *_10$$5, *_12$$5 = NULL, *_18$$8, *_19$$8;
	zval *className = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &className_param);

	zephir_get_strval(className, className_param);


	ZEPHIR_OBS_VAR(classFile);
	_0 = zephir_fetch_static_property_ce(yii_baseyii_ce, SL("classMap") TSRMLS_CC);
	if (zephir_array_isset_fetch(&classFile, _0, className, 0 TSRMLS_CC)) {
		ZEPHIR_SINIT_VAR(_1$$3);
		ZVAL_LONG(&_1$$3, 0);
		ZEPHIR_SINIT_VAR(_2$$3);
		ZVAL_LONG(&_2$$3, 1);
		ZEPHIR_INIT_VAR(_3$$3);
		zephir_substr(_3$$3, classFile, 0 , 1 , 0);
		if (ZEPHIR_IS_STRING(_3$$3, "@")) {
			ZEPHIR_CALL_STATIC(&_4$$4, "getalias", NULL, 0, classFile);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(classFile, _4$$4);
		}
	}
	ZEPHIR_SINIT_VAR(_5);
	ZVAL_STRING(&_5, "\\", 0);
	ZEPHIR_INIT_VAR(pos);
	zephir_fast_strpos(pos, className, &_5, 0 );
	if (!ZEPHIR_IS_FALSE_IDENTICAL(pos)) {
		ZEPHIR_INIT_VAR(_6$$5);
		ZEPHIR_SINIT_VAR(_7$$5);
		ZVAL_STRING(&_7$$5, "\\", 0);
		ZEPHIR_SINIT_VAR(_8$$5);
		ZVAL_STRING(&_8$$5, "/", 0);
		zephir_fast_str_replace(&_6$$5, &_7$$5, &_8$$5, className TSRMLS_CC);
		ZEPHIR_INIT_VAR(_9$$5);
		ZEPHIR_CONCAT_SVS(_9$$5, "@", _6$$5, ".php");
		ZEPHIR_INIT_VAR(_10$$5);
		ZVAL_BOOL(_10$$5, 0);
		ZEPHIR_CALL_STATIC(&classFile, "getalias", NULL, 0, _9$$5, _10$$5);
		zephir_check_call_status();
		_11$$5 = ZEPHIR_IS_FALSE(classFile);
		if (!(_11$$5)) {
			ZEPHIR_CALL_FUNCTION(&_12$$5, "is_file", NULL, 17, classFile);
			zephir_check_call_status();
			_11$$5 = !zephir_is_true(_12$$5);
		}
		if (_11$$5) {
			RETURN_MM_NULL();
		}
	} else {
		RETURN_MM_NULL();
	}
	if (zephir_require_zval(classFile TSRMLS_CC) == FAILURE) {
		RETURN_MM_NULL();
	}
	ZEPHIR_INIT_VAR(_13);
	ZEPHIR_GET_CONSTANT(_13, "YII_DEBUG");
	_14 = zephir_is_true(_13);
	if (_14) {
		_14 = !(zephir_class_exists(className, zephir_is_true(ZEPHIR_GLOBAL(global_false))  TSRMLS_CC));
	}
	_15 = _14;
	if (_15) {
		_15 = !(zephir_interface_exists(className, false  TSRMLS_CC));
	}
	_16 = _15;
	if (_16) {
		ZEPHIR_CALL_FUNCTION(&_17, "trait_exists", NULL, 18, className, ZEPHIR_GLOBAL(global_false));
		zephir_check_call_status();
		_16 = !zephir_is_true(_17);
	}
	if (_16) {
		ZEPHIR_INIT_VAR(_18$$8);
		object_init_ex(_18$$8, yii_base_unknownclassexception_ce);
		ZEPHIR_INIT_VAR(_19$$8);
		ZEPHIR_CONCAT_SVSVS(_19$$8, "Unable to find \\'", className, "\\' in file: ", classFile, " Namespace missing?");
		ZEPHIR_CALL_METHOD(NULL, _18$$8, "__construct", NULL, 3, _19$$8);
		zephir_check_call_status();
		zephir_throw_exception_debug(_18$$8, "yii/BaseYii.zep", 318 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Creates a new object using the given configuration.
 *
 * You may view this method as an enhanced version of the `new` operator.
 * The method supports creating an object based on a class name, a configuration array or
 * an anonymous function.
 *
 * Below are some usage examples:
 *
 * ```php
 * // create an object using a class name
 * $object = Yii::createObject('yii\db\Connection');
 *
 * // create an object using a configuration array
 * $object = Yii::createObject([
 *     'class' => 'yii\db\Connection',
 *     'dsn' => 'mysql:host=127.0.0.1;dbname=demo',
 *     'username' => 'root',
 *     'password' => '',
 *     'charset' => 'utf8',
 * ]);
 *
 * // create an object with two constructor parameters
 * $object = \Yii::createObject('MyClass', [$param1, $param2]);
 * ```
 *
 * Using [[\yii\di\Container|dependency injection container]], this method can also identify
 * dependent objects, instantiate them and inject them into the newly created object.
 *
 * @param string|array|callable $type the object type. This can be specified in one of the following forms:
 *
 * - a string: representing the class name of the object to be created
 * - a configuration array: the array must contain a `class` element which is treated as the object class,
 *   and the rest of the name-value pairs will be used to initialize the corresponding object properties
 * - a PHP callable: either an anonymous function or an array representing a class method (`[$class or $object, $method]`).
 *   The callable should return a new instance of the object being created.
 *
 * @param array $params the constructor parameters
 * @return object the created object
 * @throws InvalidConfigException if the configuration is invalid.
 * @see \yii\di\Container
 */
PHP_METHOD(yii_BaseYii, createObject) {

	zend_bool _0;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *params = NULL;
	zval *type, *params_param = NULL, *_1, *_2 = NULL, *_3$$3, *class_name$$4 = NULL, *_4$$4, *_5$$5, *text$$6 = NULL, *_6$$6, *_7$$6, *_8$$7, *_9$$7, *_10$$7;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &type, &params_param);

	if (!params_param) {
		ZEPHIR_INIT_VAR(params);
		array_init(params);
	} else {
		zephir_get_arrval(params, params_param);
	}


	_0 = Z_TYPE_P(type) == IS_ARRAY;
	if (_0) {
		_0 = zephir_array_isset_string(type, SS("class"));
	}
	ZEPHIR_INIT_VAR(_1);
	ZVAL_BOOL(_1, 1);
	ZEPHIR_CALL_FUNCTION(&_2, "is_callable", NULL, 19, type, _1);
	zephir_check_call_status();
	if (Z_TYPE_P(type) == IS_STRING) {
		_3$$3 = zephir_fetch_static_property_ce(yii_baseyii_ce, SL("container") TSRMLS_CC);
		ZEPHIR_RETURN_CALL_METHOD(_3$$3, "get", NULL, 0, type, params);
		zephir_check_call_status();
		RETURN_MM();
	} else if (_0) {
		ZEPHIR_OBS_VAR(class_name$$4);
		zephir_array_fetch_string(&class_name$$4, type, SL("class"), PH_NOISY, "yii/BaseYii.zep", 370 TSRMLS_CC);
		zephir_array_unset_string(&type, SS("class"), PH_SEPARATE);
		_4$$4 = zephir_fetch_static_property_ce(yii_baseyii_ce, SL("container") TSRMLS_CC);
		ZEPHIR_RETURN_CALL_METHOD(_4$$4, "get", NULL, 0, class_name$$4, params, type);
		zephir_check_call_status();
		RETURN_MM();
	} else if (zephir_is_true(_2)) {
		_5$$5 = zephir_fetch_static_property_ce(yii_baseyii_ce, SL("container") TSRMLS_CC);
		ZEPHIR_RETURN_CALL_METHOD(_5$$5, "invoke", NULL, 0, type, params);
		zephir_check_call_status();
		RETURN_MM();
	} else if (Z_TYPE_P(type) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(text$$6);
		ZVAL_STRING(text$$6, "class", 1);
		ZEPHIR_INIT_VAR(_6$$6);
		object_init_ex(_6$$6, yii_base_invalidconfigexception_ce);
		ZEPHIR_INIT_VAR(_7$$6);
		ZEPHIR_CONCAT_SVS(_7$$6, "Object configuration must be an array containing a \"", text$$6, "\" element.");
		ZEPHIR_CALL_METHOD(NULL, _6$$6, "__construct", NULL, 3, _7$$6);
		zephir_check_call_status();
		zephir_throw_exception_debug(_6$$6, "yii/BaseYii.zep", 377 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} else {
		ZEPHIR_INIT_VAR(_8$$7);
		object_init_ex(_8$$7, yii_base_invalidconfigexception_ce);
		ZEPHIR_INIT_VAR(_9$$7);
		zephir_gettype(_9$$7, type TSRMLS_CC);
		ZEPHIR_INIT_VAR(_10$$7);
		ZEPHIR_CONCAT_SV(_10$$7, "Unsupported configuration type: ", _9$$7);
		ZEPHIR_CALL_METHOD(NULL, _8$$7, "__construct", NULL, 3, _10$$7);
		zephir_check_call_status();
		zephir_throw_exception_debug(_8$$7, "yii/BaseYii.zep", 379 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}

}

/**
 * @return Logger message logger
 */
PHP_METHOD(yii_BaseYii, getLogger) {

	zval *_0, *_1$$3, *_2$$4 = NULL, *_3$$4, *_4$$4;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_static_property_ce(yii_baseyii_ce, SL("_logger") TSRMLS_CC);
	if (Z_TYPE_P(_0) != IS_NULL) {
		_1$$3 = zephir_fetch_static_property_ce(yii_baseyii_ce, SL("_logger") TSRMLS_CC);
		RETURN_CTOR(_1$$3);
	} else {
		ZEPHIR_INIT_VAR(_3$$4);
		ZVAL_STRING(_3$$4, "yii\\log\\Logger", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_STATIC(&_2$$4, "createobject", NULL, 0, _3$$4);
		zephir_check_temp_parameter(_3$$4);
		zephir_check_call_status();
		zephir_update_static_property_ce(yii_baseyii_ce, SL("_logger"), &_2$$4 TSRMLS_CC);
		_4$$4 = zephir_fetch_static_property_ce(yii_baseyii_ce, SL("_logger") TSRMLS_CC);
		RETURN_CTOR(_4$$4);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Sets the logger object.
 * @param Logger $logger the logger object.
 */
PHP_METHOD(yii_BaseYii, setLogger) {

	zval *logger;

	zephir_fetch_params(0, 1, 0, &logger);



	zephir_update_static_property_ce(yii_baseyii_ce, SL("_logger"), &logger TSRMLS_CC);

}

/**
 * Logs a trace message.
 * Trace messages are logged mainly for development purpose to see
 * the execution work flow of some code.
 * @param string $message the message to be logged.
 * @param string $category the category of the message.
 */
PHP_METHOD(yii_BaseYii, trace) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *message_param = NULL, *category_param = NULL, *_0, *_1$$3 = NULL, *_2$$3;
	zval *message = NULL, *category = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &message_param, &category_param);

	zephir_get_strval(message, message_param);
	if (!category_param) {
		ZEPHIR_INIT_VAR(category);
		ZVAL_STRING(category, "application", 1);
	} else {
		zephir_get_strval(category, category_param);
	}


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_GET_CONSTANT(_0, "YII_DEBUG");
	if (zephir_is_true(_0)) {
		ZEPHIR_CALL_STATIC(&_1$$3, "getlogger", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_2$$3);
		ZVAL_LONG(_2$$3, 0x08);
		ZEPHIR_CALL_METHOD(NULL, _1$$3, "log", NULL, 0, message, _2$$3, category);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Logs an error message.
 * An error message is typically logged when an unrecoverable error occurs
 * during the execution of an application.
 * @param string $message the message to be logged.
 * @param string $category the category of the message.
 */
PHP_METHOD(yii_BaseYii, error) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *message_param = NULL, *category_param = NULL, *_0 = NULL, *_1;
	zval *message = NULL, *category = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &message_param, &category_param);

	zephir_get_strval(message, message_param);
	if (!category_param) {
		ZEPHIR_INIT_VAR(category);
		ZVAL_STRING(category, "application", 1);
	} else {
		zephir_get_strval(category, category_param);
	}


	ZEPHIR_CALL_STATIC(&_0, "getlogger", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 0x01);
	ZEPHIR_CALL_METHOD(NULL, _0, "log", NULL, 0, message, _1, category);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Logs a warning message.
 * A warning message is typically logged when an error occurs while the execution
 * can still continue.
 * @param string $message the message to be logged.
 * @param string $category the category of the message.
 */
PHP_METHOD(yii_BaseYii, warning) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *message_param = NULL, *category_param = NULL, *_0 = NULL, *_1;
	zval *message = NULL, *category = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &message_param, &category_param);

	zephir_get_strval(message, message_param);
	if (!category_param) {
		ZEPHIR_INIT_VAR(category);
		ZVAL_STRING(category, "application", 1);
	} else {
		zephir_get_strval(category, category_param);
	}


	ZEPHIR_CALL_STATIC(&_0, "getlogger", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 0x02);
	ZEPHIR_CALL_METHOD(NULL, _0, "log", NULL, 0, message, _1, category);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Logs an informative message.
 * An informative message is typically logged by an application to keep record of
 * something important (e.g. an administrator logs in).
 * @param string $message the message to be logged.
 * @param string $category the category of the message.
 */
PHP_METHOD(yii_BaseYii, info) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *message_param = NULL, *category_param = NULL, *_0 = NULL, *_1;
	zval *message = NULL, *category = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &message_param, &category_param);

	zephir_get_strval(message, message_param);
	if (!category_param) {
		ZEPHIR_INIT_VAR(category);
		ZVAL_STRING(category, "application", 1);
	} else {
		zephir_get_strval(category, category_param);
	}


	ZEPHIR_CALL_STATIC(&_0, "getlogger", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 0x04);
	ZEPHIR_CALL_METHOD(NULL, _0, "log", NULL, 0, message, _1, category);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Marks the beginning of a code block for profiling.
 * This has to be matched with a call to [[endProfile]] with the same category name.
 * The begin- and end- calls must also be properly nested. For example,
 *
 * ~~~
 * \Yii::beginProfile('block1');
 * // some code to be profiled
 *     \Yii::beginProfile('block2');
 *     // some other code to be profiled
 *     \Yii::endProfile('block2');
 * \Yii::endProfile('block1');
 * ~~~
 * @param string $token token for the code block
 * @param string $category the category of this log message
 * @see endProfile()
 */
PHP_METHOD(yii_BaseYii, beginProfile) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *token_param = NULL, *category_param = NULL, *_0 = NULL, *_1;
	zval *token = NULL, *category = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &token_param, &category_param);

	zephir_get_strval(token, token_param);
	if (!category_param) {
		ZEPHIR_INIT_VAR(category);
		ZVAL_STRING(category, "application", 1);
	} else {
		zephir_get_strval(category, category_param);
	}


	ZEPHIR_CALL_STATIC(&_0, "getlogger", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 0x50);
	ZEPHIR_CALL_METHOD(NULL, _0, "log", NULL, 0, token, _1, category);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Marks the end of a code block for profiling.
 * This has to be matched with a previous call to [[beginProfile]] with the same category name.
 * @param string $token token for the code block
 * @param string $category the category of this log message
 * @see beginProfile()
 */
PHP_METHOD(yii_BaseYii, endProfile) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *token_param = NULL, *category_param = NULL, *_0 = NULL, *_1;
	zval *token = NULL, *category = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &token_param, &category_param);

	zephir_get_strval(token, token_param);
	if (!category_param) {
		ZEPHIR_INIT_VAR(category);
		ZVAL_STRING(category, "application", 1);
	} else {
		zephir_get_strval(category, category_param);
	}


	ZEPHIR_CALL_STATIC(&_0, "getlogger", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 0x60);
	ZEPHIR_CALL_METHOD(NULL, _0, "log", NULL, 0, token, _1, category);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns an HTML hyperlink that can be displayed on your Web page showing "Powered by Yii Framework" information.
 * @return string an HTML hyperlink that can be displayed on your Web page showing "Powered by Yii Framework" information
 */
PHP_METHOD(yii_BaseYii, powered) {

	

	RETURN_STRING("Powered by <a href=\"http://www.yiiframework.com/\" rel=\"external\">Yii Framework</a>", 1);

}

/**
 * Translates a message to the specified language.
 *
 * This is a shortcut method of [[\yii\i18n\I18N::translate()]].
 *
 * The translation will be conducted according to the message category and the target language will be used.
 *
 * You can add parameters to a translation message that will be substituted with the corresponding value after
 * translation. The format for this is to use curly brackets around the parameter name as you can see in the following example:
 *
 * ```php
 * $username = 'Alexander';
 * echo \Yii::t('app', 'Hello, {username}!', ['username' => $username]);
 * ```
 *
 * Further formatting of message parameters is supported using the [PHP intl extensions](http://www.php.net/manual/en/intro.intl.php)
 * message formatter. See [[\yii\i18n\I18N::translate()]] for more details.
 *
 * @param string $category the message category.
 * @param string $message the message to be translated.
 * @param array $params the parameters that will be used to replace the corresponding placeholders in the message.
 * @param string $language the language code (e.g. `en-US`, `en`). If this is null, the current
 * [[\yii\base\Application::language|application language]] will be used.
 * @return string the translated message.
 */
PHP_METHOD(yii_BaseYii, t) {

	HashTable *_6$$4;
	HashPosition _5$$4;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *category_param = NULL, *message_param = NULL, *params = NULL, *language = NULL, *_0, *_1$$3, *_2$$3 = NULL, *_3$$3 = NULL, *_4$$3, *p$$4 = NULL, *name$$4 = NULL, *value$$4 = NULL, **_7$$4, *emptyArr$$4 = NULL, *_9$$4 = NULL, *_8$$5 = NULL;
	zval *category = NULL, *message = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 2, &category_param, &message_param, &params, &language);

	zephir_get_strval(category, category_param);
	zephir_get_strval(message, message_param);
	if (!params) {
		ZEPHIR_INIT_VAR(params);
		array_init(params);
	}
	if (!language) {
		language = ZEPHIR_GLOBAL(global_null);
	}


	_0 = zephir_fetch_static_property_ce(yii_baseyii_ce, SL("app") TSRMLS_CC);
	if (Z_TYPE_P(_0) != IS_NULL) {
		_1$$3 = zephir_fetch_static_property_ce(yii_baseyii_ce, SL("app") TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_2$$3, _1$$3, "geti18n", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_3$$3);
		if (zephir_is_true(language)) {
			ZEPHIR_CPY_WRT(_3$$3, language);
		} else {
			_4$$3 = zephir_fetch_static_property_ce(yii_baseyii_ce, SL("app") TSRMLS_CC);
			ZEPHIR_OBS_NVAR(_3$$3);
			zephir_read_property(&_3$$3, _4$$3, SL("language"), PH_NOISY_CC);
		}
		ZEPHIR_RETURN_CALL_METHOD(_2$$3, "translate", NULL, 0, category, message, params, _3$$3);
		zephir_check_call_status();
		RETURN_MM();
	} else {
		ZEPHIR_INIT_VAR(p$$4);
		array_init(p$$4);
		zephir_is_iterable(params, &_6$$4, &_5$$4, 0, 0, "yii/BaseYii.zep", 532);
		for (
		  ; zephir_hash_get_current_data_ex(_6$$4, (void**) &_7$$4, &_5$$4) == SUCCESS
		  ; zephir_hash_move_forward_ex(_6$$4, &_5$$4)
		) {
			ZEPHIR_GET_HMKEY(name$$4, _6$$4, _5$$4);
			ZEPHIR_GET_HVALUE(value$$4, _7$$4);
			ZEPHIR_INIT_LNVAR(_8$$5);
			ZEPHIR_CONCAT_SVS(_8$$5, "{", name$$4, "}");
			zephir_array_update_zval(&p$$4, _8$$5, &value$$4, PH_COPY | PH_SEPARATE);
		}
		ZEPHIR_INIT_VAR(emptyArr$$4);
		array_init(emptyArr$$4);
		ZEPHIR_INIT_VAR(_9$$4);
		if (ZEPHIR_IS_IDENTICAL(p$$4, emptyArr$$4)) {
			ZEPHIR_CPY_WRT(_9$$4, message);
		} else {
			ZEPHIR_CALL_FUNCTION(&_9$$4, "strtr", NULL, 20, message, p$$4);
			zephir_check_call_status();
		}
		RETURN_CCTOR(_9$$4);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Configures an object with the initial property values.
 * @param object $object the object to be configured
 * @param array $properties the property initial values given in terms of name-value pairs.
 * @return object the object itself
 */
PHP_METHOD(yii_BaseYii, configure) {

	HashTable *_2$$3;
	HashPosition _1$$3;
	zend_bool _0;
	zval *object, *properties, *name$$3 = NULL, *value$$3 = NULL, **_3$$3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &object, &properties);

	ZEPHIR_SEPARATE_PARAM(object);


	_0 = Z_TYPE_P(object) == IS_OBJECT;
	if (_0) {
		_0 = Z_TYPE_P(properties) == IS_ARRAY;
	}
	if (_0) {
		zephir_is_iterable(properties, &_2$$3, &_1$$3, 0, 0, "yii/BaseYii.zep", 551);
		for (
		  ; zephir_hash_get_current_data_ex(_2$$3, (void**) &_3$$3, &_1$$3) == SUCCESS
		  ; zephir_hash_move_forward_ex(_2$$3, &_1$$3)
		) {
			ZEPHIR_GET_HMKEY(name$$3, _2$$3, _1$$3);
			ZEPHIR_GET_HVALUE(value$$3, _3$$3);
			zephir_update_property_zval_zval(object, name$$3, value$$3 TSRMLS_CC);
		}
	}
	RETVAL_ZVAL(object, 1, 0);
	RETURN_MM();

}

/**
 * Returns the public member variables of an object.
 * This method is provided such that we can get the public member variables of an object.
 * It is different from "get_object_vars()" because the latter will return private
 * and protected variables if it is called within the object itself.
 * @param object $object the object to be handled
 * @return array the public member variables of the object
 */
PHP_METHOD(yii_BaseYii, getObjectVars) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *object;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &object);



	ZEPHIR_RETURN_CALL_FUNCTION("get_object_vars", NULL, 21, object);
	zephir_check_call_status();
	RETURN_MM();

}

void zephir_init_static_properties_yii_BaseYii(TSRMLS_D) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_static_property_ce(yii_baseyii_ce, SL("classMap"), &_0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

