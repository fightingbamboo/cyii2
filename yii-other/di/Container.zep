/**
 * @link http://www.yiiframework.com/
 * @copyright Copyright (c) 2008 Yii Software LLC
 * @license http://www.yiiframework.com/license/
 */
namespace yii\di;

use yii\BaseYii;
use ReflectionClass;
use yii\base\Component;
use yii\base\InvalidConfigException;
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
 * By default, [[\BaseYii::$container]] refers to a Container instance which is used by [[\BaseYii::createObject()]]
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
class Container extends Component
{
    /**
     * @var array singleton objects indexed by their types
     */
    protected _singletons = [];
    /**
     * @var array object definitions indexed by their types
     */
    protected _definitions = [];
    /**
     * @var array constructor parameters indexed by object types
     */
    protected _params = [];
    /**
     * @var array cached ReflectionClass objects indexed by class/interface names
     */
    protected _reflections = [];
    /**
     * @var array cached dependencies indexed by class/interface names. Each class name
     * is associated with a list of constructor parameter types or default values.
     */
    protected _dependencies = [];
    /**
     * Returns an instance of the requested class.
     *
     * You may provide constructor parameters (`$params`) and object configurations (`$config`)
     * that will be used during the creation of the instance.
     *
     * If the class implements [[\yii\base\Configurable]], the `$config` parameter will be passed as the last
     * parameter to the class constructor; Otherwise, the configuration will be applied *after* the object is
     * instantiated.
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
     * @throws NotInstantiableException If resolved to an abstract class or an interface (since 2.0.9)
     */
    public function get(string classs, array params = [], array config = [])
    {
        var definition, $object, concrete;

        if isset this->_singletons[classs] {
            // singleton
            return this->_singletons[classs];
        } elseif !(isset this->_definitions[classs]) {
            return this->build(classs, params, config);
        }
        let definition = this->_definitions[classs];
        if is_callable(definition, true) {
            var mergeParams = [];
            let mergeParams = this->mergeParams(classs, params);
            let params =  (array)this->resolveDependencies( mergeParams );
            let $object =  call_user_func(definition, this, params, config);
        } elseif is_array(definition) {
            let concrete = definition["class"];
            unset definition["class"];

            let config =  array_merge(definition, config);
            let params =  this->mergeParams(classs, params);
            if concrete === classs {
                let $object =  this->build(classs, params, config);
            } else {
                let $object =  this->get(concrete, params, config);
            }
        } elseif is_object(definition) {
            let this->_singletons[classs] = definition;
            return this->_singletons[classs];
        } else {
            throw new InvalidConfigException("Unexpected object definition type: " . gettype(definition));
        }
        if array_key_exists(classs, this->_singletons) {
            // singleton
            let this->_singletons[classs] = $object;
        }
        return $object;
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
     * @param mixed $definition the definition associated with `$class`. It can be one of the following:
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
     * @return $this the container itself
     */
    public function set(string classs, definition = [], array params = [])
    {
        let this->_definitions[classs] =  this->normalizeDefinition(classs, definition);
        let this->_params[classs] = params;
        unset this->_singletons[classs];

        return this;
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
     * @return $this the container itself
     * @see set()
     */
    public function setSingleton(string classs, definition = [], array params = [])
    {
        let this->_definitions[classs] =  this->normalizeDefinition(classs, definition);
        let this->_params[classs] = params;
        let this->_singletons[classs] = null;
        return this;
    }

    /**
     * Returns a value indicating whether the container has the definition of the specified name.
     * @param string $class class name, interface name or alias name
     * @return boolean whether the container has the definition of the specified name..
     * @see set()
     */
    public function has(string classs) -> boolean
    {
        return isset this->_definitions[classs];
    }

    /**
     * Returns a value indicating whether the given name corresponds to a registered singleton.
     * @param string $class class name, interface name or alias name
     * @param boolean $checkInstance whether to check if the singleton has been instantiated.
     * @return boolean whether the given name corresponds to a registered singleton. If `$checkInstance` is true,
     * the method should return a value indicating whether the singleton has been instantiated.
     */
    public function hasSingleton(string classs, boolean checkInstance = false) -> boolean
    {
        return  checkInstance ? isset this->_singletons[classs]  : array_key_exists(classs, this->_singletons);
    }

    /**
     * Removes the definition for the specified name.
     * @param string $class class name, interface name or alias name
     */
    public function clear(string classs) -> void
    {
        unset this->_definitions[classs];
        unset this->_singletons[classs];

    }

    /**
     * Normalizes the class definition.
     * @param string $class class name
     * @param string|array|callable $definition the class definition
     * @return array the normalized class definition
     * @throws InvalidConfigException if the definition is invalid.
     */
    protected function normalizeDefinition(string classs, definition) -> array
    {
        var params;

        if empty(definition) {
            let params = ["class" : classs];
            return params;
        } elseif is_string(definition) {
            let params = ["class" : definition];
            return params;
        } elseif is_callable(definition, true) || is_object(definition) {
            return definition;
        } elseif is_array(definition) {
            if !(isset definition["class"]) {
                if strpos(classs, "\\") !== false {
                    let definition["class"] = classs;
                } else {
                    throw new InvalidConfigException("A class definition requires a \"class\" member.");
                }
            }
            return definition;
        } else {
            throw new InvalidConfigException("Unsupported definition type for \"".classs."\": " . gettype(definition));
        }
    }

    /**
     * Returns the list of the object definitions or the loaded shared objects.
     * @return array the list of the object definitions or the loaded shared objects (type or ID => definition or instance).
     */
    public function getDefinitions() -> array
    {
        return this->_definitions;
    }

    /**
     * Creates an instance of the specified class.
     * This method will resolve dependencies of the specified class, instantiate them, and inject
     * them into the new instance of the specified class.
     * @param string $class the class name
     * @param array $params constructor parameters
     * @param array $config configurations to be applied to the new instance
     * @return object the newly created instance of the specified class
     * @throws NotInstantiableException If resolved to an abstract class or an interface (since 2.0.9)
     */
    protected function build(string classs, array params, array config)
    {
        var reflection, dependencies, tmpListReflectionDependencies, index, param, $object, name, value;

        /* @var $reflection ReflectionClass */
        let tmpListReflectionDependencies = this->getDependencies(classs);
        let reflection = tmpListReflectionDependencies[0];
        let dependencies = tmpListReflectionDependencies[1];
        for index, param in params {
            let dependencies[index] = param;
        }
        let dependencies =  this->resolveDependencies(dependencies, reflection);
        if !(reflection->isInstantiable()) {
            throw new NotInstantiableException(reflection->name);
        }
        if empty(config) {
            return reflection->newInstanceArgs(dependencies);
        }
        if !(empty(dependencies)) && reflection->implementsInterface("yii\\base\\Configurable") {
            // set $config as the last parameter (existing one will be overwritten)
            let dependencies[count(dependencies) - 1] = config;
            return reflection->newInstanceArgs(dependencies);
        } else {
            let $object =  reflection->newInstanceArgs(dependencies);
            for name, value in config {
                let $object->{name} = value;
            }
            return $object;
        }
    }

    /**
     * Merges the user-specified constructor parameters with the ones registered via [[set()]].
     * @param string $class class name, interface name or alias name
     * @param array $params the constructor parameters
     * @return array the merged parameters
     */
    protected function mergeParams(string classs, params)
    {
        var ps, index, value;

        if empty(this->_params[classs]) {
            return params;
        } elseif empty(params) {
            return this->_params[classs];
        } else {
            let ps = this->_params[classs];
            for index, value in params {
                let ps[index] = value;
            }
            return ps;
        }
    }

    /**
     * Returns the dependencies of the specified class.
     * @param string $class class name, interface name or alias name
     * @return array the dependencies of the specified class.
     */
    protected function getDependencies(string classs) -> array
    {
        var dependencies, reflection, constructor, param, c;

        if isset this->_reflections[classs] {
            return [this->_reflections[classs], this->_dependencies[classs]];
        }
        let dependencies =  [];
        let reflection =  new ReflectionClass(classs);
        let constructor =  reflection->getConstructor();
        if constructor !== null {
            for param in constructor->getParameters() {
                if param->isDefaultValueAvailable() {
                    let dependencies[] =  param->getDefaultValue();
                } elseif param->getName() == "config" {
                    let dependencies[] =  [];
                } else {
                    let c =  param->getClass();
                    let dependencies[] = Instance::of( c === null ? null  : c->getName());
                }
            }
        }
        let this->_reflections[classs] = reflection;
        let this->_dependencies[classs] = dependencies;
        return [reflection, dependencies];
    }

    /**
     * Resolves dependencies by replacing them with the actual object instances.
     * @param array $dependencies the dependencies
     * @param ReflectionClass $reflection the class reflection associated with the dependencies
     * @return array the resolved dependencies
     * @throws InvalidConfigException if a dependency cannot be resolved or if a dependency cannot be fulfilled.
     */
    protected function resolveDependencies(array dependencies, reflection = null) -> array
    {
        var index, dependency, name, classs;

        for index, dependency in dependencies {
            if typeof dependency == "object" && dependency instanceof Instance {
                if dependency->id !== null {
                    let dependencies[index] =  this->get(dependency->id);
                } elseif reflection !== null {
                    let name =  reflection->getConstructor()->getParameters()[index]->getName();
                    let classs =  reflection->getName();
                    throw new InvalidConfigException("Missing required parameter \"".name."\" when instantiating \"".classs."\".");
                }
            }
        }
        return dependencies;
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
     * BaseYii::$container->invoke($formatString, ['string' => 'Hello World!']);
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
    public function invoke(callback, array params = [])
    {
        if is_callable(callback) {
            return call_user_func_array(callback, this->resolveCallableDependencies(callback, params));
        } else {
            return call_user_func_array(callback, params);
        }
    }

    /**
     * Returns a value indicating whether the given array is an associative array.
     *
     * An array is associative if all its keys are strings. If `$allStrings` is false,
     * then an array will be treated as associative if at least one of its keys is a string.
     *
     * Note that an empty array will NOT be considered associative.
     *
     * @param array $array the array being checked
     * @param boolean $allStrings whether the array keys must be all strings in order for
     * the array to be treated as associative.
     * @return boolean whether the array is associative
     */
    public static function isAssociative(array myArray, boolean allStrings = true)
    {
        var key, value;

        if !(is_array(myArray)) || empty(myArray) {
            return false;
        }
        if allStrings {
            for key, value in myArray {
                if !(is_string(key)) {
                    return false;
                }
            }
            return true;
        } else {
            for key, value in myArray {
                if is_string(key) {
                    return true;
                }
            }
            return false;
        }
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
    public function resolveCallableDependencies(callback, array params = []) -> array
    {
        var reflection, args, associative, param, name, classs, className, obj, e, funcName, value;
        var app = BaseYii::app;
        if is_array(callback) {
            let reflection =  new \ReflectionMethod(callback[0], callback[1]);
        } else {
            let reflection =  new \ReflectionFunction(callback);
        }
        let args =  [];
        let associative =  static::isAssociative(params);
        for param in reflection->getParameters() {
            let name =  param->getName();
            let classs =  param->getClass();
            if classs !== null {
                let className =  classs->getName();
                if associative && isset params[name] && (typeof params[name] == "object") && params[name] instanceof className {
                    let args[] = params[name];
                    unset params[name];

                } elseif !(associative) && isset params[0] && (typeof params[0] == "object") && params[0] instanceof className {
                    let args[] =  array_shift(params);
                } else {
                let obj =  app->get(name);
                if app->has(name) && (typeof obj == "object") && obj instanceof className {
                    let args[] = obj;
                }
                 else {
                    // If the argument is optional we catch not instantiable exceptions
                    try {
                        let args[] =  this->get(className);
                    } catch NotInstantiableException, e {
                        if param->isDefaultValueAvailable() {
                            let args[] =  param->getDefaultValue();
                        } elseif param->getName() == "config" {
                            let args[] =  [];
                        } else {
                            throw e;
                        }
                    }
                }}
            } elseif associative && isset params[name] {
                let args[] = params[name];
                unset params[name];

            } elseif !(associative) && count(params) {
                let args[] =  array_shift(params);
            } elseif param->isDefaultValueAvailable() {
                let args[] =  param->getDefaultValue();
            } elseif name == "config" {
                let args[] =  [];
            } elseif !(param->isOptional()) {
                let funcName =  reflection->getName();
                throw new InvalidConfigException("Missing required parameter \"".name."\" when calling \"".funcName."\".");
            }
        }
        for value in params {
            let args[] = value;
        }
        return args;
    }

}