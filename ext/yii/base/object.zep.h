
extern zend_class_entry *yii_base_object_ce;

ZEPHIR_INIT_CLASS(yii_base_Object);

PHP_METHOD(yii_base_Object, className);
PHP_METHOD(yii_base_Object, __construct);
PHP_METHOD(yii_base_Object, init);
PHP_METHOD(yii_base_Object, __get);
PHP_METHOD(yii_base_Object, __set);
PHP_METHOD(yii_base_Object, __isset);
PHP_METHOD(yii_base_Object, __unset);
PHP_METHOD(yii_base_Object, __call);
PHP_METHOD(yii_base_Object, hasProperty);
PHP_METHOD(yii_base_Object, canGetProperty);
PHP_METHOD(yii_base_Object, canSetProperty);
PHP_METHOD(yii_base_Object, hasMethod);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_object___construct, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, config, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_object___get, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_object___set, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_object___isset, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_object___unset, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_object___call, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, params)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_object_hasproperty, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, checkVars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_object_cangetproperty, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, checkVars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_object_cansetproperty, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, checkVars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_object_hasmethod, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yii_base_object_method_entry) {
	PHP_ME(yii_base_Object, className, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_base_Object, __construct, arginfo_yii_base_object___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(yii_base_Object, init, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Object, __get, arginfo_yii_base_object___get, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Object, __set, arginfo_yii_base_object___set, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Object, __isset, arginfo_yii_base_object___isset, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Object, __unset, arginfo_yii_base_object___unset, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Object, __call, arginfo_yii_base_object___call, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Object, hasProperty, arginfo_yii_base_object_hasproperty, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Object, canGetProperty, arginfo_yii_base_object_cangetproperty, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Object, canSetProperty, arginfo_yii_base_object_cansetproperty, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Object, hasMethod, arginfo_yii_base_object_hasmethod, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
