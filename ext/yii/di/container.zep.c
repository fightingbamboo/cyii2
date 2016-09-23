
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
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "kernel/hash.h"


/**
 * @link http://www.yiiframework.com/
 * @copyright Copyright (c) 2008 Yii Software LLC
 * @license http://www.yiiframework.com/license/
 */
/**
 * Container implements a [dependency injection](http://en.wikipedia.org/wiki/Dependency_injection) container.
 *
 * A dependency injection (DI) container is an object that knows how to instantiate and configure objects and
 * all their dependent objects. For more information about DI, please refer to
 * [Martin Fowler's article](http://martinfowler.com/articles/injection.html).
 *
 * Container supports constructor injection as well as property injection.
 *
 * To use Container, you first need to set up the class dependencies by calling [[set()]].
 * You then call [[get()]] to create a new class object. Container will automatically instantiate
 * dependent objects, inject them into the object being created, configure and finally return the newly created object.
 *
 * By default, [[\Yii::$container]] refers to a Container instance which is used by [[\Yii::createObject()]]
 * to create new object instances. You may use this method to replace the `new` operator
 * when creating a new object, which gives you the benefit of automatic dependency resolution and default
 * property configuration.
 *
 * Below is an example of using Container:
 *
 * ```php
 * namespace app\models;
 *
 * use yii\base\Object;
 * use yii\db\Connection;
 * use yii\di\Container;
 *
 * interface UserFinderInterface
 * {
 *     function findUser();
 * }
 *
 * class UserFinder extends Object implements UserFinderInterface
 * {
 *     public $db;
 *
 *     public function __construct(Connection $db, $config = [])
 *     {
 *         $this->db = $db;
 *         parent::__construct($config);
 *     }
 *
 *     public function findUser()
 *     {
 *     }
 * }
 *
 * class UserLister extends Object
 * {
 *     public $finder;
 *
 *     public function __construct(UserFinderInterface $finder, $config = [])
 *     {
 *         $this->finder = $finder;
 *         parent::__construct($config);
 *     }
 * }
 *
 * $container = new Container;
 * $container->set('yii\db\Connection', [
 *     'dsn' => '...',
 * ]);
 * $container->set('app\models\UserFinderInterface', [
 *     'class' => 'app\models\UserFinder',
 * ]);
 * $container->set('userLister', 'app\models\UserLister');
 *
 * $lister = $container->get('userLister');
 *
 * // which is equivalent to:
 *
 * $db = new \yii\db\Connection(['dsn' => '...']);
 * $finder = new UserFinder($db);
 * $lister = new UserLister($finder);
 * ```
 *
 * @property array $definitions The list of the object definitions or the loaded shared objects (type or ID =>
 * definition or instance). This property is read-only.
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
ZEPHIR_INIT_CLASS(yii_di_Container) {

	ZEPHIR_REGISTER_CLASS_EX(yii\\di, Container, yii, di_container, yii_base_component_ce, yii_di_container_method_entry, 0);

	/**
	 * @var array singleton objects indexed by their types
	 */
	zend_declare_property_null(yii_di_container_ce, SL("_singletons"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var array object definitions indexed by their types
	 */
	zend_declare_property_null(yii_di_container_ce, SL("_definitions"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var array constructor parameters indexed by object types
	 */
	zend_declare_property_null(yii_di_container_ce, SL("_params"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var array cached ReflectionClass objects indexed by class/interface names
	 */
	zend_declare_property_null(yii_di_container_ce, SL("_reflections"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var array cached dependencies indexed by class/interface names. Each class name
	 * is associated with a list of constructor parameter types or default values.
	 */
	zend_declare_property_null(yii_di_container_ce, SL("_dependencies"), ZEND_ACC_PROTECTED TSRMLS_CC);

	yii_di_container_ce->create_object = zephir_init_properties_yii_di_Container;
	return SUCCESS;

}

/**
 * Returns an instance of the requested class.
 *
 * You may provide constructor parameters (`$params`) and object configurations (`$config`)
 * that will be used during the creation of the instance.
 *
 * Note that if the class is declared to be singleton by calling [[setSingleton()]],
 * the same instance of the class will be returned each time this method is called.
 * In this case, the constructor parameters and object configurations will be used
 * only if the class is instantiated the first time.
 *
 * @param string $class the class name or an alias name (e.g. `foo`) that was previously registered via [[set()]]
 * or [[setSingleton()]].
 * @param array $params a list of constructor parameter values. The parameters should be provided in the order
 * they appear in the constructor declaration. If you want to skip some parameters, you should index the remaining
 * ones with the integers that represent their positions in the constructor parameter list.
 * @param array $config a list of name-value pairs that will be used to initialize the object properties.
 * @return object an instance of the requested class.
 * @throws InvalidConfigException if the class cannot be recognized or correspond to an invalid definition
 */
PHP_METHOD(yii_di_Container, get) {

	zephir_fcall_cache_entry *_4 = NULL, *_9 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *class_param = NULL, *params = NULL, *config = NULL, *singletons = NULL, *singleton = NULL, *definitions = NULL, *_2, *definition = NULL, *object = NULL, *_5, *_6, *_7 = NULL, *_15, *_0$$3, *_1$$4, *_3$$6, *_8$$8 = NULL, *concrete$$10 = NULL, *_10$$10, *_11$$10 = NULL, *_12$$15, *_13$$15, *_14$$15;
	zval *class = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &class_param, &params, &config);

	zephir_get_strval(class, class_param);
	if (!params) {
		ZEPHIR_INIT_VAR(params);
		array_init(params);
	} else {
		ZEPHIR_SEPARATE_PARAM(params);
	}
	if (!config) {
		ZEPHIR_INIT_VAR(config);
		array_init(config);
	} else {
		ZEPHIR_SEPARATE_PARAM(config);
	}


	ZEPHIR_OBS_VAR(singletons);
	zephir_read_property_this(&singletons, this_ptr, SL("_singletons"), PH_NOISY_CC);
	if (Z_TYPE_P(singletons) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(_0$$3);
		array_init(_0$$3);
		zephir_update_property_this(this_ptr, SL("_singletons"), _0$$3 TSRMLS_CC);
	}
	ZEPHIR_OBS_VAR(definitions);
	zephir_read_property_this(&definitions, this_ptr, SL("_definitions"), PH_NOISY_CC);
	if (Z_TYPE_P(definitions) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(_1$$4);
		array_init(_1$$4);
		zephir_update_property_this(this_ptr, SL("_definitions"), _1$$4 TSRMLS_CC);
	}
	ZEPHIR_OBS_VAR(singleton);
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("_singletons"), PH_NOISY_CC);
	if (zephir_array_isset_fetch(&singleton, _2, class, 0 TSRMLS_CC)) {
		RETURN_CCTOR(singleton);
	} else {
		_3$$6 = zephir_fetch_nproperty_this(this_ptr, SL("_definitions"), PH_NOISY_CC);
		if (!(zephir_array_isset(_3$$6, class))) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "build", &_4, 0, class, params, config);
			zephir_check_call_status();
			RETURN_MM();
		}
	}
	_5 = zephir_fetch_nproperty_this(this_ptr, SL("_definitions"), PH_NOISY_CC);
	ZEPHIR_OBS_VAR(definition);
	zephir_array_fetch(&definition, _5, class, PH_NOISY, "yii/di/Container.zep", 164 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_6);
	ZVAL_BOOL(_6, 1);
	ZEPHIR_CALL_FUNCTION(&_7, "is_callable", NULL, 19, definition, _6);
	zephir_check_call_status();
	if (zephir_is_true(_7)) {
		ZEPHIR_CALL_METHOD(&_8$$8, this_ptr, "mergeparams", &_9, 0, class, params);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(params, _8$$8);
		ZEPHIR_CALL_METHOD(&_8$$8, this_ptr, "resolvedependencies", NULL, 0, params);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(params, _8$$8);
		ZEPHIR_CALL_FUNCTION(&object, "call_user_func", NULL, 11, definition, this_ptr, params, config);
		zephir_check_call_status();
	} else {
		if (Z_TYPE_P(definition) == IS_ARRAY) {
			ZEPHIR_OBS_VAR(concrete$$10);
			zephir_array_fetch_string(&concrete$$10, definition, SL("class"), PH_NOISY, "yii/di/Container.zep", 174 TSRMLS_CC);
			zephir_array_unset_string(&definition, SS("class"), PH_SEPARATE);
			ZEPHIR_INIT_VAR(_10$$10);
			zephir_fast_array_merge(_10$$10, &(definition), &(config) TSRMLS_CC);
			ZEPHIR_CPY_WRT(config, _10$$10);
			ZEPHIR_CALL_METHOD(&_11$$10, this_ptr, "mergeparams", &_9, 0, class, params);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(params, _11$$10);
			if (ZEPHIR_IS_IDENTICAL(concrete$$10, class)) {
				ZEPHIR_CALL_METHOD(&object, this_ptr, "build", &_4, 0, class, params, config);
				zephir_check_call_status();
			} else {
				ZEPHIR_CALL_METHOD(&object, this_ptr, "get", NULL, 22, concrete$$10, params, config);
				zephir_check_call_status();
			}
		} else {
			if (Z_TYPE_P(definition) == IS_OBJECT) {
				zephir_update_property_array(this_ptr, SL("_singletons"), class, definition TSRMLS_CC);
				RETURN_CCTOR(definition);
			} else {
				ZEPHIR_INIT_VAR(_12$$15);
				object_init_ex(_12$$15, yii_base_invalidconfigexception_ce);
				ZEPHIR_INIT_VAR(_13$$15);
				zephir_gettype(_13$$15, definition TSRMLS_CC);
				ZEPHIR_INIT_VAR(_14$$15);
				ZEPHIR_CONCAT_SV(_14$$15, "Unexpected object definition type: ", _13$$15);
				ZEPHIR_CALL_METHOD(NULL, _12$$15, "__construct", NULL, 3, _14$$15);
				zephir_check_call_status();
				zephir_throw_exception_debug(_12$$15, "yii/di/Container.zep", 192 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	_15 = zephir_fetch_nproperty_this(this_ptr, SL("_singletons"), PH_NOISY_CC);
	if (zephir_array_key_exists(_15, class TSRMLS_CC)) {
		zephir_update_property_array(this_ptr, SL("_singletons"), class, object TSRMLS_CC);
	}
	RETURN_CCTOR(object);

}

/**
 * Registers a class definition with this container.
 *
 * For example,
 *
 * ```php
 * // register a class name as is. This can be skipped.
 * $container->set('yii\db\Connection');
 *
 * // register an interface
 * // When a class depends on the interface, the corresponding class
 * // will be instantiated as the dependent object
 * $container->set('yii\mail\MailInterface', 'yii\swiftmailer\Mailer');
 *
 * // register an alias name. You can use $container->get('foo')
 * // to create an instance of Connection
 * $container->set('foo', 'yii\db\Connection');
 *
 * // register a class with configuration. The configuration
 * // will be applied when the class is instantiated by get()
 * $container->set('yii\db\Connection', [
 *     'dsn' => 'mysql:host=127.0.0.1;dbname=demo',
 *     'username' => 'root',
 *     'password' => '',
 *     'charset' => 'utf8',
 * ]);
 *
 * // register an alias name with class configuration
 * // In this case, a "class" element is required to specify the class
 * $container->set('db', [
 *     'class' => 'yii\db\Connection',
 *     'dsn' => 'mysql:host=127.0.0.1;dbname=demo',
 *     'username' => 'root',
 *     'password' => '',
 *     'charset' => 'utf8',
 * ]);
 *
 * // register a PHP callable
 * // The callable will be executed when $container->get('db') is called
 * $container->set('db', function ($container, $params, $config) {
 *     return new \yii\db\Connection($config);
 * });
 * ```
 *
 * If a class definition with the same name already exists, it will be overwritten with the new one.
 * You may use [[has()]] to check if a class definition already exists.
 *
 * @param string $class class name, interface name or alias name
 * @param mixed $definition the definition associated with `$class`. It can be one of the followings:
 *
 * - a PHP callable: The callable will be executed when [[get()]] is invoked. The signature of the callable
 *   should be `function ($container, $params, $config)`, where `$params` stands for the list of constructor
 *   parameters, `$config` the object configuration, and `$container` the container object. The return value
 *   of the callable will be returned by [[get()]] as the object instance requested.
 * - a configuration array: the array contains name-value pairs that will be used to initialize the property
 *   values of the newly created object when [[get()]] is called. The `class` element stands for the
 *   the class of the object to be created. If `class` is not specified, `$class` will be used as the class name.
 * - a string: a class name, an interface name or an alias name.
 * @param array $params the list of constructor parameters. The parameters will be passed to the class
 * constructor when [[get()]] is called.
 * @return static the container itself
 */
PHP_METHOD(yii_di_Container, set) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *params = NULL;
	zval *class_param = NULL, *definition = NULL, *params_param = NULL, *_0 = NULL, *_1;
	zval *class = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &class_param, &definition, &params_param);

	zephir_get_strval(class, class_param);
	if (!definition) {
		ZEPHIR_INIT_VAR(definition);
		array_init(definition);
	}
	if (!params_param) {
		ZEPHIR_INIT_VAR(params);
		array_init(params);
	} else {
		zephir_get_arrval(params, params_param);
	}


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "normalizedefinition", NULL, 0, class, definition);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("_definitions"), class, _0 TSRMLS_CC);
	zephir_update_property_array(this_ptr, SL("_params"), class, params TSRMLS_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_singletons"), PH_NOISY_CC);
	zephir_array_unset(&_1, class, PH_SEPARATE);
	RETURN_THIS();

}

/**
 * Registers a class definition with this container and marks the class as a singleton class.
 *
 * This method is similar to [[set()]] except that classes registered via this method will only have one
 * instance. Each time [[get()]] is called, the same instance of the specified class will be returned.
 *
 * @param string $class class name, interface name or alias name
 * @param mixed $definition the definition associated with `$class`. See [[set()]] for more details.
 * @param array $params the list of constructor parameters. The parameters will be passed to the class
 * constructor when [[get()]] is called.
 * @return static the container itself
 * @see set()
 */
PHP_METHOD(yii_di_Container, setSingleton) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *params = NULL;
	zval *class_param = NULL, *definition = NULL, *params_param = NULL, *_0 = NULL;
	zval *class = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &class_param, &definition, &params_param);

	zephir_get_strval(class, class_param);
	if (!definition) {
		ZEPHIR_INIT_VAR(definition);
		array_init(definition);
	}
	if (!params_param) {
		ZEPHIR_INIT_VAR(params);
		array_init(params);
	} else {
		zephir_get_arrval(params, params_param);
	}


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "normalizedefinition", NULL, 0, class, definition);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("_definitions"), class, _0 TSRMLS_CC);
	zephir_update_property_array(this_ptr, SL("_params"), class, params TSRMLS_CC);
	zephir_update_property_array(this_ptr, SL("_singletons"), class, ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Returns a value indicating whether the container has the definition of the specified name.
 * @param string $class class name, interface name or alias name
 * @return boolean whether the container has the definition of the specified name..
 * @see set()
 */
PHP_METHOD(yii_di_Container, has) {

	zval *class_param = NULL, *_0;
	zval *class = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &class_param);

	zephir_get_strval(class, class_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_definitions"), PH_NOISY_CC);
	RETURN_MM_BOOL(zephir_array_isset(_0, class));

}

/**
 * Returns a value indicating whether the given name corresponds to a registered singleton.
 * @param string $class class name, interface name or alias name
 * @param boolean $checkInstance whether to check if the singleton has been instantiated.
 * @return boolean whether the given name corresponds to a registered singleton. If `$checkInstance` is true,
 * the method should return a value indicating whether the singleton has been instantiated.
 */
PHP_METHOD(yii_di_Container, hasSingleton) {

	zend_bool checkInstance;
	zval *class_param = NULL, *checkInstance_param = NULL, *_0, *_1, *_2;
	zval *class = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &class_param, &checkInstance_param);

	zephir_get_strval(class, class_param);
	if (!checkInstance_param) {
		checkInstance = 0;
	} else {
		checkInstance = zephir_get_boolval(checkInstance_param);
	}


	ZEPHIR_INIT_VAR(_0);
	if (checkInstance) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("_singletons"), PH_NOISY_CC);
		ZVAL_BOOL(_0, zephir_array_isset(_1, class));
	} else {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("_singletons"), PH_NOISY_CC);
		ZVAL_BOOL(_0, zephir_array_key_exists(_2, class TSRMLS_CC));
	}
	RETURN_CCTOR(_0);

}

/**
 * Removes the definition for the specified name.
 * @param string $class class name, interface name or alias name
 */
PHP_METHOD(yii_di_Container, clear) {

	zval *class_param = NULL, *_0, *_1;
	zval *class = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &class_param);

	zephir_get_strval(class, class_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_definitions"), PH_NOISY_CC);
	zephir_array_unset(&_0, class, PH_SEPARATE);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_singletons"), PH_NOISY_CC);
	zephir_array_unset(&_1, class, PH_SEPARATE);
	ZEPHIR_MM_RESTORE();

}

/**
 * Normalizes the class definition.
 * @param string $class class name
 * @param string|array|callable $definition the class definition
 * @return array the normalized class definition
 * @throws InvalidConfigException if the definition is invalid.
 */
PHP_METHOD(yii_di_Container, normalizeDefinition) {

	zend_bool _2$$6;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *class_param = NULL, *definition, *_0$$6, *_1$$6 = NULL, _3$$10, *_4$$10, *_5$$12, *_7$$13, *_8$$13, *_9$$13;
	zval *class = NULL, *text$$12, *_6$$12;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &class_param, &definition);

	zephir_get_strval(class, class_param);
	ZEPHIR_SEPARATE_PARAM(definition);


	if (ZEPHIR_IS_EMPTY(definition)) {
		zephir_create_array(return_value, 1, 0 TSRMLS_CC);
		zephir_array_update_string(&return_value, SL("class"), &class, PH_COPY | PH_SEPARATE);
		RETURN_MM();
	} else {
		if (Z_TYPE_P(definition) == IS_STRING) {
			zephir_create_array(return_value, 1, 0 TSRMLS_CC);
			zephir_array_update_string(&return_value, SL("class"), &definition, PH_COPY | PH_SEPARATE);
			RETURN_MM();
		} else {
			ZEPHIR_INIT_VAR(_0$$6);
			ZVAL_BOOL(_0$$6, 1);
			ZEPHIR_CALL_FUNCTION(&_1$$6, "is_callable", NULL, 19, definition, _0$$6);
			zephir_check_call_status();
			_2$$6 = zephir_is_true(_1$$6);
			if (!(_2$$6)) {
				_2$$6 = Z_TYPE_P(definition) == IS_OBJECT;
			}
			if (_2$$6) {
				RETVAL_ZVAL(definition, 1, 0);
				RETURN_MM();
			} else {
				if (Z_TYPE_P(definition) == IS_ARRAY) {
					if (!(zephir_array_isset_string(definition, SS("class")))) {
						ZEPHIR_SINIT_VAR(_3$$10);
						ZVAL_STRING(&_3$$10, "\\", 0);
						ZEPHIR_INIT_VAR(_4$$10);
						zephir_fast_strpos(_4$$10, class, &_3$$10, 0 );
						if (!ZEPHIR_IS_FALSE_IDENTICAL(_4$$10)) {
							zephir_array_update_string(&definition, SL("class"), &class, PH_COPY | PH_SEPARATE);
						} else {
							ZEPHIR_INIT_VAR(text$$12);
							ZVAL_STRING(text$$12, "class", 1);
							ZEPHIR_INIT_VAR(_5$$12);
							object_init_ex(_5$$12, yii_base_invalidconfigexception_ce);
							ZEPHIR_INIT_VAR(_6$$12);
							ZEPHIR_CONCAT_SVS(_6$$12, "A class definition requires a \"", text$$12, "\" member.");
							ZEPHIR_CALL_METHOD(NULL, _5$$12, "__construct", NULL, 3, _6$$12);
							zephir_check_call_status();
							zephir_throw_exception_debug(_5$$12, "yii/di/Container.zep", 356 TSRMLS_CC);
							ZEPHIR_MM_RESTORE();
							return;
						}
					}
					RETVAL_ZVAL(definition, 1, 0);
					RETURN_MM();
				} else {
					ZEPHIR_INIT_VAR(_7$$13);
					object_init_ex(_7$$13, yii_base_invalidconfigexception_ce);
					ZEPHIR_INIT_VAR(_8$$13);
					zephir_gettype(_8$$13, definition TSRMLS_CC);
					ZEPHIR_INIT_VAR(_9$$13);
					ZEPHIR_CONCAT_SVSV(_9$$13, "Unsupported definition type for \"", class, "\": ", _8$$13);
					ZEPHIR_CALL_METHOD(NULL, _7$$13, "__construct", NULL, 3, _9$$13);
					zephir_check_call_status();
					zephir_throw_exception_debug(_7$$13, "yii/di/Container.zep", 361 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
			}
		}
	}

}

/**
 * Returns the list of the object definitions or the loaded shared objects.
 * @return array the list of the object definitions or the loaded shared objects (type or ID => definition or instance).
 */
PHP_METHOD(yii_di_Container, getDefinitions) {

	

	RETURN_MEMBER(this_ptr, "_definitions");

}

/**
 * Creates an instance of the specified class.
 * This method will resolve dependencies of the specified class, instantiate them, and inject
 * them into the new instance of the specified class.
 * @param string $class the class name
 * @param array $params constructor parameters
 * @param array $config configurations to be applied to the new instance
 * @return object the newly created instance of the specified class
 */
PHP_METHOD(yii_di_Container, build) {

	zend_bool _6;
	HashTable *_1, *_10$$7;
	HashPosition _0, _9$$7;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *class, *params, *config, *elements = NULL, *reflection = NULL, *dependencies = NULL, *index = NULL, *param = NULL, **_2, *_3 = NULL, *_7 = NULL, *_8, *_4$$4, *_5$$4, *object$$7 = NULL, *name$$7 = NULL, *value$$7 = NULL, **_11$$7;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &class, &params, &config);



	ZEPHIR_INIT_VAR(elements);
	array_init(elements);
	ZEPHIR_CALL_METHOD(&elements, this_ptr, "getdependencies", NULL, 0, class);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(reflection);
	zephir_array_fetch_long(&reflection, elements, 0, PH_NOISY, "yii/di/Container.zep", 393 TSRMLS_CC);
	ZEPHIR_OBS_VAR(dependencies);
	zephir_array_fetch_long(&dependencies, elements, 1, PH_NOISY, "yii/di/Container.zep", 394 TSRMLS_CC);
	zephir_is_iterable(params, &_1, &_0, 0, 0, "yii/di/Container.zep", 401);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HMKEY(index, _1, _0);
		ZEPHIR_GET_HVALUE(param, _2);
		zephir_array_update_zval(&dependencies, index, &param, PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "resolvedependencies", NULL, 0, dependencies, reflection);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(dependencies, _3);
	ZEPHIR_CALL_METHOD(&_3, reflection, "isinstantiable", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(_3)) {
		ZEPHIR_INIT_VAR(_4$$4);
		object_init_ex(_4$$4, yii_di_notinstantiableexception_ce);
		ZEPHIR_OBS_VAR(_5$$4);
		zephir_read_property(&_5$$4, reflection, SL("name"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, _4$$4, "__construct", NULL, 23, _5$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(_4$$4, "yii/di/Container.zep", 403 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (ZEPHIR_IS_EMPTY(config)) {
		ZEPHIR_RETURN_CALL_METHOD(reflection, "newinstanceargs", NULL, 0, dependencies);
		zephir_check_call_status();
		RETURN_MM();
	}
	_6 = !(ZEPHIR_IS_EMPTY(dependencies));
	if (_6) {
		ZEPHIR_INIT_VAR(_8);
		ZVAL_STRING(_8, "yii\\base\\Configurable", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&_7, reflection, "implementsinterface", NULL, 0, _8);
		zephir_check_temp_parameter(_8);
		zephir_check_call_status();
		_6 = zephir_is_true(_7);
	}
	if (_6) {
		zephir_array_update_long(&dependencies, (zephir_fast_count_int(dependencies TSRMLS_CC) - 1), &config, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
		ZEPHIR_RETURN_CALL_METHOD(reflection, "newinstanceargs", NULL, 0, dependencies);
		zephir_check_call_status();
		RETURN_MM();
	} else {
		ZEPHIR_CALL_METHOD(&object$$7, reflection, "newinstanceargs", NULL, 0, dependencies);
		zephir_check_call_status();
		zephir_is_iterable(config, &_10$$7, &_9$$7, 0, 0, "yii/di/Container.zep", 421);
		for (
		  ; zephir_hash_get_current_data_ex(_10$$7, (void**) &_11$$7, &_9$$7) == SUCCESS
		  ; zephir_hash_move_forward_ex(_10$$7, &_9$$7)
		) {
			ZEPHIR_GET_HMKEY(name$$7, _10$$7, _9$$7);
			ZEPHIR_GET_HVALUE(value$$7, _11$$7);
			zephir_update_property_zval_zval(object$$7, name$$7, value$$7 TSRMLS_CC);
		}
		RETURN_CCTOR(object$$7);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Merges the user-specified constructor parameters with the ones registered via [[set()]].
 * @param string $class class name, interface name or alias name
 * @param array $params the constructor parameters
 * @return array the merged parameters
 */
PHP_METHOD(yii_di_Container, mergeParams) {

	HashTable *_6$$5;
	HashPosition _5$$5;
	zval *class_param = NULL, *params, *_0, *_1, *_2$$4, *_3$$4, *ps$$5 = NULL, *index$$5 = NULL, *value$$5 = NULL, *_4$$5, **_7$$5;
	zval *class = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &class_param, &params);

	zephir_get_strval(class, class_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_params"), PH_NOISY_CC);
	zephir_array_fetch(&_1, _0, class, PH_NOISY | PH_READONLY, "yii/di/Container.zep", 433 TSRMLS_CC);
	if (ZEPHIR_IS_EMPTY(_1)) {
		RETVAL_ZVAL(params, 1, 0);
		RETURN_MM();
	}
	if (ZEPHIR_IS_EMPTY(params)) {
		_2$$4 = zephir_fetch_nproperty_this(this_ptr, SL("_params"), PH_NOISY_CC);
		zephir_array_fetch(&_3$$4, _2$$4, class, PH_NOISY | PH_READONLY, "yii/di/Container.zep", 438 TSRMLS_CC);
		RETURN_CTOR(_3$$4);
	} else {
		_4$$5 = zephir_fetch_nproperty_this(this_ptr, SL("_params"), PH_NOISY_CC);
		ZEPHIR_OBS_VAR(ps$$5);
		zephir_array_fetch(&ps$$5, _4$$5, class, PH_NOISY, "yii/di/Container.zep", 441 TSRMLS_CC);
		zephir_is_iterable(params, &_6$$5, &_5$$5, 0, 0, "yii/di/Container.zep", 445);
		for (
		  ; zephir_hash_get_current_data_ex(_6$$5, (void**) &_7$$5, &_5$$5) == SUCCESS
		  ; zephir_hash_move_forward_ex(_6$$5, &_5$$5)
		) {
			ZEPHIR_GET_HMKEY(index$$5, _6$$5, _5$$5);
			ZEPHIR_GET_HVALUE(value$$5, _7$$5);
			zephir_array_update_zval(&ps$$5, index$$5, &value$$5, PH_COPY | PH_SEPARATE);
		}
		RETURN_CCTOR(ps$$5);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns the dependencies of the specified class.
 * @param string $class class name, interface name or alias name
 * @return array the dependencies of the specified class.
 */
PHP_METHOD(yii_di_Container, getDependencies) {

	HashTable *_5$$4;
	HashPosition _4$$4;
	zephir_fcall_cache_entry *_8 = NULL, *_10 = NULL, *_11 = NULL, *_13 = NULL, *_16 = NULL, *_20 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *class_param = NULL, *r = NULL, *_0, *dependencies = NULL, *reflection = NULL, *constructor = NULL, *_1$$3, *_2$$3, *param$$4 = NULL, *_3$$4 = NULL, **_6$$4, *_7$$5 = NULL, *_9$$6 = NULL, *c$$7 = NULL, *_12$$7 = NULL, *_14$$8 = NULL, *_15$$10 = NULL, *_17$$10 = NULL, *_18$$11 = NULL, *_19$$11 = NULL;
	zval *class = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &class_param);

	zephir_get_strval(class, class_param);


	ZEPHIR_OBS_VAR(r);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_reflections"), PH_NOISY_CC);
	if (zephir_array_isset_fetch(&r, _0, class, 0 TSRMLS_CC)) {
		zephir_create_array(return_value, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(return_value, r);
		_1$$3 = zephir_fetch_nproperty_this(this_ptr, SL("_dependencies"), PH_NOISY_CC);
		ZEPHIR_OBS_VAR(_2$$3);
		zephir_array_fetch(&_2$$3, _1$$3, class, PH_NOISY, "yii/di/Container.zep", 458 TSRMLS_CC);
		zephir_array_fast_append(return_value, _2$$3);
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(dependencies);
	array_init(dependencies);
	ZEPHIR_INIT_VAR(reflection);
	object_init_ex(reflection, zephir_get_internal_ce(SS("reflectionclass") TSRMLS_CC));
	ZEPHIR_CALL_METHOD(NULL, reflection, "__construct", NULL, 24, class);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&constructor, reflection, "getconstructor", NULL, 25);
	zephir_check_call_status();
	if (Z_TYPE_P(constructor) != IS_NULL) {
		ZEPHIR_CALL_METHOD(&_3$$4, constructor, "getparameters", NULL, 0);
		zephir_check_call_status();
		zephir_is_iterable(_3$$4, &_5$$4, &_4$$4, 0, 0, "yii/di/Container.zep", 486);
		for (
		  ; zephir_hash_get_current_data_ex(_5$$4, (void**) &_6$$4, &_4$$4) == SUCCESS
		  ; zephir_hash_move_forward_ex(_5$$4, &_4$$4)
		) {
			ZEPHIR_GET_HVALUE(param$$4, _6$$4);
			ZEPHIR_CALL_METHOD(&_7$$5, param$$4, "isdefaultvalueavailable", &_8, 0);
			zephir_check_call_status();
			if (zephir_is_true(_7$$5)) {
				ZEPHIR_CALL_METHOD(&_9$$6, param$$4, "getdefaultvalue", &_10, 0);
				zephir_check_call_status();
				zephir_array_append(&dependencies, _9$$6, PH_SEPARATE, "yii/di/Container.zep", 469);
			} else {
				ZEPHIR_CALL_METHOD(&c$$7, param$$4, "getclass", &_11, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_12$$7, param$$4, "getname", &_13, 0);
				zephir_check_call_status();
				if (ZEPHIR_IS_STRING(_12$$7, "config")) {
					ZEPHIR_INIT_NVAR(_14$$8);
					array_init(_14$$8);
					zephir_array_append(&dependencies, _14$$8, PH_SEPARATE, "yii/di/Container.zep", 474);
				} else {
					if (Z_TYPE_P(c$$7) == IS_NULL) {
						ZEPHIR_INIT_NVAR(_17$$10);
						ZVAL_NULL(_17$$10);
						ZEPHIR_CALL_CE_STATIC(&_15$$10, yii_di_instance_ce, "of", &_16, 0, _17$$10);
						zephir_check_call_status();
						zephir_array_append(&dependencies, _15$$10, PH_SEPARATE, "yii/di/Container.zep", 478);
					} else {
						ZEPHIR_CALL_METHOD(&_19$$11, c$$7, "getname", &_20, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_CE_STATIC(&_18$$11, yii_di_instance_ce, "of", &_16, 0, _19$$11);
						zephir_check_call_status();
						zephir_array_append(&dependencies, _18$$11, PH_SEPARATE, "yii/di/Container.zep", 480);
					}
				}
			}
		}
	}
	zephir_update_property_array(this_ptr, SL("_reflections"), class, reflection TSRMLS_CC);
	zephir_update_property_array(this_ptr, SL("_dependencies"), class, dependencies TSRMLS_CC);
	zephir_create_array(return_value, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(return_value, reflection);
	zephir_array_fast_append(return_value, dependencies);
	RETURN_MM();

}

/**
 * Resolves dependencies by replacing them with the actual object instances.
 * @param array $dependencies the dependencies
 * @param ReflectionClass $reflection the class reflection associated with the dependencies
 * @return array the resolved dependencies
 * @throws InvalidConfigException if a dependency cannot be resolved or if a dependency cannot be fulfilled.
 */
PHP_METHOD(yii_di_Container, resolveDependencies) {

	zend_bool _3$$3;
	HashTable *_1;
	HashPosition _0;
	zephir_fcall_cache_entry *_7 = NULL, *_9 = NULL, *_12 = NULL, *_15 = NULL, *_18 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *dependencies, *reflection = NULL, *index = NULL, *dependency = NULL, **_2, *_4$$4 = NULL, *_5$$5 = NULL, *_6$$5 = NULL, *name$$6 = NULL, *class$$6 = NULL, *_8$$6 = NULL, *_10$$6 = NULL, *_16$$6 = NULL, *_17$$6 = NULL, *_11$$7 = NULL, *_13$$7 = NULL, *_14$$7;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &dependencies, &reflection);

	ZEPHIR_SEPARATE_PARAM(dependencies);
	if (!reflection) {
		reflection = ZEPHIR_GLOBAL(global_null);
	}


	zephir_is_iterable(dependencies, &_1, &_0, 1, 0, "yii/di/Container.zep", 519);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HMKEY(index, _1, _0);
		ZEPHIR_GET_HVALUE(dependency, _2);
		_3$$3 = Z_TYPE_P(dependency) == IS_OBJECT;
		if (_3$$3) {
			_3$$3 = (zephir_instance_of_ev(dependency, yii_di_instance_ce TSRMLS_CC));
		}
		if (_3$$3) {
			ZEPHIR_OBS_NVAR(_4$$4);
			zephir_read_property(&_4$$4, dependency, SL("id"), PH_NOISY_CC);
			if (Z_TYPE_P(_4$$4) != IS_NULL) {
				ZEPHIR_OBS_NVAR(_6$$5);
				zephir_read_property(&_6$$5, dependency, SL("id"), PH_NOISY_CC);
				ZEPHIR_CALL_METHOD(&_5$$5, this_ptr, "get", &_7, 0, _6$$5);
				zephir_check_call_status();
				zephir_array_update_zval(&dependencies, index, &_5$$5, PH_COPY | PH_SEPARATE);
			} else if (Z_TYPE_P(reflection) != IS_NULL) {
				ZEPHIR_CALL_METHOD(&_8$$6, reflection, "getconstructor", &_9, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_10$$6, _8$$6, "getparameters", NULL, 0);
				zephir_check_call_status();
				if (zephir_array_isset(_10$$6, index)) {
					ZEPHIR_CALL_METHOD(&_11$$7, reflection, "getconstructor", &_12, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_13$$7, _11$$7, "getparameters", NULL, 0);
					zephir_check_call_status();
					zephir_array_fetch(&_14$$7, _13$$7, index, PH_NOISY | PH_READONLY, "yii/di/Container.zep", 512 TSRMLS_CC);
					ZEPHIR_CALL_METHOD(&name$$6, _14$$7, "getname", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&class$$6, reflection, "getname", &_15, 0);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(_16$$6);
				object_init_ex(_16$$6, yii_base_invalidconfigexception_ce);
				ZEPHIR_INIT_LNVAR(_17$$6);
				ZEPHIR_CONCAT_SVSVS(_17$$6, "Missing required parameter \"", name$$6, "\" when instantiating \"", class$$6, "\".");
				ZEPHIR_CALL_METHOD(NULL, _16$$6, "__construct", &_18, 3, _17$$6);
				zephir_check_call_status();
				zephir_throw_exception_debug(_16$$6, "yii/di/Container.zep", 515 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	zend_hash_destroy(_1);
	FREE_HASHTABLE(_1);
	RETVAL_ZVAL(dependencies, 1, 0);
	RETURN_MM();

}

/**
 * Invoke a callback with resolving dependencies in parameters.
 *
 * This methods allows invoking a callback and let type hinted parameter names to be
 * resolved as objects of the Container. It additionally allow calling function using named parameters.
 *
 * For example, the following callback may be invoked using the Container to resolve the formatter dependency:
 *
 * ```php
 * $formatString = function($string, \yii\i18n\Formatter $formatter) {
 *    // ...
 * }
 * Yii::$container->invoke($formatString, ['string' => 'Hello World!']);
 * ```
 *
 * This will pass the string `'Hello World!'` as the first param, and a formatter instance created
 * by the DI container as the second param to the callable.
 *
 * @param callable $callback callable to be invoked.
 * @param array $params The array of parameters for the function.
 * This can be either a list of parameters, or an associative array representing named function parameters.
 * @return mixed the callback return value.
 * @throws InvalidConfigException if a dependency cannot be resolved or if a dependency cannot be fulfilled.
 * @throws NotInstantiableException If resolved to an abstract class or an interface (since 2.0.9)
 * @since 2.0.7
 */
PHP_METHOD(yii_di_Container, invoke) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *callback, *params = NULL, *_0$$3 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &callback, &params);

	if (!params) {
		ZEPHIR_INIT_VAR(params);
		array_init(params);
	}


	if (zephir_is_callable(callback TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(&_0$$3, this_ptr, "resolvecallabledependencies", NULL, 0, callback, params);
		zephir_check_call_status();
		ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, callback, _0$$3);
		zephir_check_call_status();
		RETURN_MM();
	} else {
		ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, callback, params);
		zephir_check_call_status();
		RETURN_MM();
	}

}

PHP_METHOD(yii_di_Container, isAssociative) {

	HashTable *_1$$5, *_4$$8;
	HashPosition _0$$5, _3$$8;
	zend_bool allStrings;
	zval *array, *allStrings_param = NULL, *key = NULL, *value = NULL, **_2$$5, **_5$$8;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &array, &allStrings_param);

	if (!allStrings_param) {
		allStrings = 1;
	} else {
		allStrings = zephir_get_boolval(allStrings_param);
	}


	if (Z_TYPE_P(array) != IS_ARRAY) {
		RETURN_MM_BOOL(0);
	}
	if (zephir_fast_count_int(array TSRMLS_CC) == 0) {
		RETURN_MM_BOOL(0);
	}
	if (allStrings == 1) {
		zephir_is_iterable(array, &_1$$5, &_0$$5, 0, 0, "yii/di/Container.zep", 574);
		for (
		  ; zephir_hash_get_current_data_ex(_1$$5, (void**) &_2$$5, &_0$$5) == SUCCESS
		  ; zephir_hash_move_forward_ex(_1$$5, &_0$$5)
		) {
			ZEPHIR_GET_HMKEY(key, _1$$5, _0$$5);
			ZEPHIR_GET_HVALUE(value, _2$$5);
			if (Z_TYPE_P(key) != IS_STRING) {
				RETURN_MM_BOOL(0);
			}
		}
		RETURN_MM_BOOL(1);
	} else {
		zephir_is_iterable(array, &_4$$8, &_3$$8, 0, 0, "yii/di/Container.zep", 581);
		for (
		  ; zephir_hash_get_current_data_ex(_4$$8, (void**) &_5$$8, &_3$$8) == SUCCESS
		  ; zephir_hash_move_forward_ex(_4$$8, &_3$$8)
		) {
			ZEPHIR_GET_HMKEY(key, _4$$8, _3$$8);
			ZEPHIR_GET_HVALUE(value, _5$$8);
			if (Z_TYPE_P(key) == IS_STRING) {
				RETURN_MM_BOOL(1);
			}
		}
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Resolve dependencies for a function.
 *
 * This method can be used to implement similar functionality as provided by [[invoke()]] in other
 * components.
 *
 * @param callable $callback callable to be invoked.
 * @param array $params The array of parameters for the function, can be either numeric or associative.
 * @return array The resolved dependencies.
 * @throws InvalidConfigException if a dependency cannot be resolved or if a dependency cannot be fulfilled.
 * @throws NotInstantiableException If resolved to an abstract class or an interface (since 2.0.9)
 * @since 2.0.7
 */
PHP_METHOD(yii_di_Container, resolveCallableDependencies) {

	zend_bool _7$$5, _11$$5, _12$$5, _15$$7, _17$$7, _19$$7, _21$$7, _23$$7, _24$$7;
	HashTable *_5, *_45;
	HashPosition _4, _44;
	zephir_fcall_cache_entry *_9 = NULL, *_10 = NULL, *_27 = NULL, *_29 = NULL, *_35 = NULL, *_40 = NULL, *_43 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *callback, *params = NULL, *app = NULL, *reflection = NULL, *args = NULL, *associative = NULL, *_0, *name = NULL, *class = NULL, *className = NULL, *param = NULL, *_3 = NULL, **_6, *value = NULL, **_46, *_1$$3, *_2$$3, *obj$$5 = NULL, *_8$$5 = NULL, *_13$$5 = NULL, *_14$$5 = NULL, *obj$$6 = NULL, *_16$$7 = NULL, *_18$$7 = NULL, *_20$$7 = NULL, *_22$$7 = NULL, *_25$$8, *_26$$9 = NULL, *_28$$12 = NULL, *_30$$11 = NULL, *_31$$13 = NULL, *_32$$14 = NULL, *_33$$16 = NULL, *_34$$17 = NULL, *_36$$18, *_37$$19 = NULL, *_38$$20 = NULL, *_39$$21 = NULL, *funcName$$22 = NULL, *_41$$22 = NULL, *_42$$22 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &callback, &params);

	if (!params) {
		ZEPHIR_INIT_VAR(params);
		array_init(params);
	} else {
		ZEPHIR_SEPARATE_PARAM(params);
	}


	ZEPHIR_OBS_VAR(_0);
	zephir_read_static_property_ce(&_0, yii_baseyii_ce, SL("app") TSRMLS_CC);
	ZEPHIR_CPY_WRT(app, _0);
	ZEPHIR_INIT_VAR(reflection);
	if (Z_TYPE_P(callback) == IS_ARRAY) {
		object_init_ex(reflection, zephir_get_internal_ce(SS("reflectionmethod") TSRMLS_CC));
		zephir_array_fetch_long(&_1$$3, callback, 0, PH_NOISY | PH_READONLY, "yii/di/Container.zep", 604 TSRMLS_CC);
		zephir_array_fetch_long(&_2$$3, callback, 1, PH_NOISY | PH_READONLY, "yii/di/Container.zep", 604 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, reflection, "__construct", NULL, 26, _1$$3, _2$$3);
		zephir_check_call_status();
	} else {
		object_init_ex(reflection, zephir_get_internal_ce(SS("reflectionfunction") TSRMLS_CC));
		ZEPHIR_CALL_METHOD(NULL, reflection, "__construct", NULL, 27, callback);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(args);
	array_init(args);
	ZEPHIR_CALL_STATIC(&associative, "isassociative", NULL, 0, params);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_3, reflection, "getparameters", NULL, 28);
	zephir_check_call_status();
	zephir_is_iterable(_3, &_5, &_4, 0, 0, "yii/di/Container.zep", 668);
	for (
	  ; zephir_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
	  ; zephir_hash_move_forward_ex(_5, &_4)
	) {
		ZEPHIR_GET_HVALUE(param, _6);
		ZEPHIR_INIT_NVAR(class);
		ZVAL_NULL(class);
		ZEPHIR_CALL_METHOD(&name, param, "getname", NULL, 0);
		zephir_check_call_status();
		_7$$5 = (0 == 0);
		if (_7$$5) {
			ZEPHIR_CALL_METHOD(&_8$$5, app, "has", &_9, 0, name);
			zephir_check_call_status();
			_7$$5 = zephir_is_true(_8$$5);
		}
		if (_7$$5) {
			ZEPHIR_CALL_METHOD(&obj$$6, app, "get", &_10, 0, name);
			zephir_check_call_status();
		}
		ZEPHIR_CALL_METHOD(&class, param, "getclass", NULL, 0);
		zephir_check_call_status();
		_11$$5 = zephir_is_true(associative);
		if (_11$$5) {
			_11$$5 = zephir_array_isset(params, name);
		}
		_12$$5 = !zephir_is_true(associative);
		if (_12$$5) {
			_12$$5 = ((zephir_fast_count_int(params TSRMLS_CC)) ? 1 : 0);
		}
		ZEPHIR_CALL_METHOD(&_13$$5, param, "isdefaultvalueavailable", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_14$$5, param, "isoptional", NULL, 0);
		zephir_check_call_status();
		if (Z_TYPE_P(class) != IS_NULL) {
			ZEPHIR_CALL_METHOD(&className, class, "getname", NULL, 0);
			zephir_check_call_status();
			_15$$7 = zephir_is_true(associative);
			if (_15$$7) {
				ZEPHIR_OBS_NVAR(_16$$7);
				zephir_array_fetch(&_16$$7, params, name, PH_NOISY, "yii/di/Container.zep", 627 TSRMLS_CC);
				_15$$7 = Z_TYPE_P(_16$$7) == IS_OBJECT;
			}
			_17$$7 = _15$$7;
			if (_17$$7) {
				ZEPHIR_OBS_NVAR(_18$$7);
				zephir_array_fetch(&_18$$7, params, name, PH_NOISY, "yii/di/Container.zep", 627 TSRMLS_CC);
				_17$$7 = zephir_is_instance_of(_18$$7, Z_STRVAL_P(className), Z_STRLEN_P(className) TSRMLS_CC);
			}
			_19$$7 = !zephir_is_true(associative);
			if (_19$$7) {
				ZEPHIR_OBS_NVAR(_20$$7);
				zephir_array_fetch_long(&_20$$7, params, 0, PH_NOISY, "yii/di/Container.zep", 630 TSRMLS_CC);
				_19$$7 = Z_TYPE_P(_20$$7) == IS_OBJECT;
			}
			_21$$7 = _19$$7;
			if (_21$$7) {
				ZEPHIR_OBS_NVAR(_22$$7);
				zephir_array_fetch_long(&_22$$7, params, 0, PH_NOISY, "yii/di/Container.zep", 630 TSRMLS_CC);
				_21$$7 = zephir_is_instance_of(_22$$7, Z_STRVAL_P(className), Z_STRLEN_P(className) TSRMLS_CC);
			}
			_23$$7 = (0 == 0);
			if (_23$$7) {
				_23$$7 = Z_TYPE_P(obj$$5) == IS_OBJECT;
			}
			_24$$7 = _23$$7;
			if (_24$$7) {
				_24$$7 = (zephir_is_instance_of(obj$$5, Z_STRVAL_P(className), Z_STRLEN_P(className) TSRMLS_CC));
			}
			if (_17$$7) {
				zephir_array_fetch(&_25$$8, params, name, PH_NOISY | PH_READONLY, "yii/di/Container.zep", 628 TSRMLS_CC);
				zephir_array_append(&args, _25$$8, PH_SEPARATE, "yii/di/Container.zep", 628);
				zephir_array_unset(&params, name, PH_SEPARATE);
			} else if (_21$$7) {
				ZEPHIR_MAKE_REF(params);
				ZEPHIR_CALL_FUNCTION(&_26$$9, "array_shift", &_27, 29, params);
				ZEPHIR_UNREF(params);
				zephir_check_call_status();
				zephir_array_append(&args, _26$$9, PH_SEPARATE, "yii/di/Container.zep", 631);
			} else if (_24$$7) {
				zephir_array_append(&args, obj$$5, PH_SEPARATE, "yii/di/Container.zep", 633);
			} else {

				/* try_start_1: */

					ZEPHIR_CALL_METHOD(&_28$$12, this_ptr, "get", &_29, 0, className);
					zephir_check_call_status_or_jump(try_end_1);
					zephir_array_append(&args, _28$$12, PH_SEPARATE, "yii/di/Container.zep", 637);

				try_end_1:

				if (EG(exception)) {
					ZEPHIR_INIT_NVAR(_30$$11);
					ZEPHIR_CPY_WRT(_30$$11, EG(exception));
					if (zephir_instance_of_ev(_30$$11, yii_di_notinstantiableexception_ce TSRMLS_CC)) {
						zend_clear_exception(TSRMLS_C);
						ZEPHIR_CALL_METHOD(&_31$$13, param, "isdefaultvalueavailable", NULL, 0);
						zephir_check_call_status();
						if (zephir_is_true(_31$$13)) {
							ZEPHIR_CALL_METHOD(&_32$$14, param, "getdefaultvalue", NULL, 0);
							zephir_check_call_status();
							zephir_array_append(&args, _32$$14, PH_SEPARATE, "yii/di/Container.zep", 640);
						} else {
							if (ZEPHIR_IS_STRING(name, "config")) {
								ZEPHIR_INIT_NVAR(_33$$16);
								array_init(_33$$16);
								zephir_array_append(&args, _33$$16, PH_SEPARATE, "yii/di/Container.zep", 643);
							} else {
								ZEPHIR_INIT_NVAR(_34$$17);
								object_init_ex(_34$$17, yii_di_notinstantiableexception_ce);
								ZEPHIR_CALL_METHOD(NULL, _34$$17, "__construct", &_35, 23, className);
								zephir_check_call_status();
								zephir_throw_exception_debug(_34$$17, "yii/di/Container.zep", 645 TSRMLS_CC);
								ZEPHIR_MM_RESTORE();
								return;
							}
						}
					}
				}
			}
		} else if (_11$$5) {
			zephir_array_fetch(&_36$$18, params, name, PH_NOISY | PH_READONLY, "yii/di/Container.zep", 653 TSRMLS_CC);
			zephir_array_append(&args, _36$$18, PH_SEPARATE, "yii/di/Container.zep", 653);
			zephir_array_unset(&params, name, PH_SEPARATE);
		} else if (_12$$5) {
			ZEPHIR_MAKE_REF(params);
			ZEPHIR_CALL_FUNCTION(&_37$$19, "array_shift", &_27, 29, params);
			ZEPHIR_UNREF(params);
			zephir_check_call_status();
			zephir_array_append(&args, _37$$19, PH_SEPARATE, "yii/di/Container.zep", 656);
		} else if (zephir_is_true(_13$$5)) {
			ZEPHIR_CALL_METHOD(&_38$$20, param, "getdefaultvalue", NULL, 0);
			zephir_check_call_status();
			zephir_array_append(&args, _38$$20, PH_SEPARATE, "yii/di/Container.zep", 658);
		} else if (ZEPHIR_IS_STRING(name, "config")) {
			ZEPHIR_INIT_NVAR(_39$$21);
			array_init(_39$$21);
			zephir_array_append(&args, _39$$21, PH_SEPARATE, "yii/di/Container.zep", 660);
		} else if (!(zephir_is_true(_14$$5))) {
			ZEPHIR_CALL_METHOD(&funcName$$22, reflection, "getname", &_40, 30);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(_41$$22);
			object_init_ex(_41$$22, yii_base_invalidconfigexception_ce);
			ZEPHIR_INIT_LNVAR(_42$$22);
			ZEPHIR_CONCAT_SVSVS(_42$$22, "Missing required parameter \"", name, "\" when calling \"", funcName$$22, "\".");
			ZEPHIR_CALL_METHOD(NULL, _41$$22, "__construct", &_43, 3, _42$$22);
			zephir_check_call_status();
			zephir_throw_exception_debug(_41$$22, "yii/di/Container.zep", 664 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	zephir_is_iterable(params, &_45, &_44, 0, 0, "yii/di/Container.zep", 672);
	for (
	  ; zephir_hash_get_current_data_ex(_45, (void**) &_46, &_44) == SUCCESS
	  ; zephir_hash_move_forward_ex(_45, &_44)
	) {
		ZEPHIR_GET_HVALUE(value, _46);
		zephir_array_append(&args, value, PH_SEPARATE, "yii/di/Container.zep", 670);
	}
	RETURN_CCTOR(args);

}

zend_object_value zephir_init_properties_yii_di_Container(zend_class_entry *class_type TSRMLS_DC) {

		zval *_0, *_2, *_4, *_6, *_8, *_10, *_1$$3, *_3$$4, *_5$$5, *_7$$6, *_9$$7, *_11$$8;

		ZEPHIR_MM_GROW();
	
	{
		zval *this_ptr = NULL;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dependencies"), PH_NOISY_CC);
		if (Z_TYPE_P(_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(_1$$3);
			array_init(_1$$3);
			zephir_update_property_this(this_ptr, SL("_dependencies"), _1$$3 TSRMLS_CC);
		}
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("_reflections"), PH_NOISY_CC);
		if (Z_TYPE_P(_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(_3$$4);
			array_init(_3$$4);
			zephir_update_property_this(this_ptr, SL("_reflections"), _3$$4 TSRMLS_CC);
		}
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("_params"), PH_NOISY_CC);
		if (Z_TYPE_P(_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(_5$$5);
			array_init(_5$$5);
			zephir_update_property_this(this_ptr, SL("_params"), _5$$5 TSRMLS_CC);
		}
		_6 = zephir_fetch_nproperty_this(this_ptr, SL("_definitions"), PH_NOISY_CC);
		if (Z_TYPE_P(_6) == IS_NULL) {
			ZEPHIR_INIT_VAR(_7$$6);
			array_init(_7$$6);
			zephir_update_property_this(this_ptr, SL("_definitions"), _7$$6 TSRMLS_CC);
		}
		_8 = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
		if (Z_TYPE_P(_8) == IS_NULL) {
			ZEPHIR_INIT_VAR(_9$$7);
			array_init(_9$$7);
			zephir_update_property_this(this_ptr, SL("_events"), _9$$7 TSRMLS_CC);
		}
		_10 = zephir_fetch_nproperty_this(this_ptr, SL("_singletons"), PH_NOISY_CC);
		if (Z_TYPE_P(_10) == IS_NULL) {
			ZEPHIR_INIT_VAR(_11$$8);
			array_init(_11$$8);
			zephir_update_property_this(this_ptr, SL("_singletons"), _11$$8 TSRMLS_CC);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJVAL_P(this_ptr);
	}

}

