
extern zend_class_entry *yii_di_container_ce;

ZEPHIR_INIT_CLASS(yii_di_Container);

PHP_METHOD(yii_di_Container, get);
PHP_METHOD(yii_di_Container, set);
PHP_METHOD(yii_di_Container, setSingleton);
PHP_METHOD(yii_di_Container, has);
PHP_METHOD(yii_di_Container, hasSingleton);
PHP_METHOD(yii_di_Container, clear);
PHP_METHOD(yii_di_Container, normalizeDefinition);
PHP_METHOD(yii_di_Container, getDefinitions);
PHP_METHOD(yii_di_Container, build);
PHP_METHOD(yii_di_Container, mergeParams);
PHP_METHOD(yii_di_Container, getDependencies);
PHP_METHOD(yii_di_Container, resolveDependencies);
PHP_METHOD(yii_di_Container, invoke);
PHP_METHOD(yii_di_Container, isAssociative);
PHP_METHOD(yii_di_Container, resolveCallableDependencies);
zend_object_value zephir_init_properties_yii_di_Container(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_container_get, 0, 0, 1)
	ZEND_ARG_INFO(0, class)
	ZEND_ARG_INFO(0, params)
	ZEND_ARG_INFO(0, config)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_container_set, 0, 0, 1)
	ZEND_ARG_INFO(0, class)
	ZEND_ARG_INFO(0, definition)
	ZEND_ARG_ARRAY_INFO(0, params, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_container_setsingleton, 0, 0, 1)
	ZEND_ARG_INFO(0, class)
	ZEND_ARG_INFO(0, definition)
	ZEND_ARG_ARRAY_INFO(0, params, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_container_has, 0, 0, 1)
	ZEND_ARG_INFO(0, class)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_container_hassingleton, 0, 0, 1)
	ZEND_ARG_INFO(0, class)
	ZEND_ARG_INFO(0, checkInstance)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_container_clear, 0, 0, 1)
	ZEND_ARG_INFO(0, class)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_container_normalizedefinition, 0, 0, 2)
	ZEND_ARG_INFO(0, class)
	ZEND_ARG_INFO(0, definition)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_container_build, 0, 0, 3)
	ZEND_ARG_INFO(0, class)
	ZEND_ARG_INFO(0, params)
	ZEND_ARG_INFO(0, config)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_container_mergeparams, 0, 0, 2)
	ZEND_ARG_INFO(0, class)
	ZEND_ARG_INFO(0, params)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_container_getdependencies, 0, 0, 1)
	ZEND_ARG_INFO(0, class)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_container_resolvedependencies, 0, 0, 1)
	ZEND_ARG_INFO(0, dependencies)
	ZEND_ARG_INFO(0, reflection)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_container_invoke, 0, 0, 1)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(0, params)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_container_isassociative, 0, 0, 1)
	ZEND_ARG_INFO(0, array)
	ZEND_ARG_INFO(0, allStrings)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_container_resolvecallabledependencies, 0, 0, 1)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(0, params)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yii_di_container_method_entry) {
	PHP_ME(yii_di_Container, get, arginfo_yii_di_container_get, ZEND_ACC_PUBLIC)
	PHP_ME(yii_di_Container, set, arginfo_yii_di_container_set, ZEND_ACC_PUBLIC)
	PHP_ME(yii_di_Container, setSingleton, arginfo_yii_di_container_setsingleton, ZEND_ACC_PUBLIC)
	PHP_ME(yii_di_Container, has, arginfo_yii_di_container_has, ZEND_ACC_PUBLIC)
	PHP_ME(yii_di_Container, hasSingleton, arginfo_yii_di_container_hassingleton, ZEND_ACC_PUBLIC)
	PHP_ME(yii_di_Container, clear, arginfo_yii_di_container_clear, ZEND_ACC_PUBLIC)
	PHP_ME(yii_di_Container, normalizeDefinition, arginfo_yii_di_container_normalizedefinition, ZEND_ACC_PROTECTED)
	PHP_ME(yii_di_Container, getDefinitions, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(yii_di_Container, build, arginfo_yii_di_container_build, ZEND_ACC_PROTECTED)
	PHP_ME(yii_di_Container, mergeParams, arginfo_yii_di_container_mergeparams, ZEND_ACC_PROTECTED)
	PHP_ME(yii_di_Container, getDependencies, arginfo_yii_di_container_getdependencies, ZEND_ACC_PROTECTED)
	PHP_ME(yii_di_Container, resolveDependencies, arginfo_yii_di_container_resolvedependencies, ZEND_ACC_PROTECTED)
	PHP_ME(yii_di_Container, invoke, arginfo_yii_di_container_invoke, ZEND_ACC_PUBLIC)
	PHP_ME(yii_di_Container, isAssociative, arginfo_yii_di_container_isassociative, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_di_Container, resolveCallableDependencies, arginfo_yii_di_container_resolvecallabledependencies, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
