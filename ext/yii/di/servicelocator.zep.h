
extern zend_class_entry *yii_di_servicelocator_ce;

ZEPHIR_INIT_CLASS(yii_di_ServiceLocator);

PHP_METHOD(yii_di_ServiceLocator, __get);
PHP_METHOD(yii_di_ServiceLocator, __isset);
PHP_METHOD(yii_di_ServiceLocator, has);
PHP_METHOD(yii_di_ServiceLocator, get);
PHP_METHOD(yii_di_ServiceLocator, set);
PHP_METHOD(yii_di_ServiceLocator, clear);
PHP_METHOD(yii_di_ServiceLocator, getComponents);
PHP_METHOD(yii_di_ServiceLocator, setComponents);
zend_object_value zephir_init_properties_yii_di_ServiceLocator(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_servicelocator___get, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_servicelocator___isset, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_servicelocator_has, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, checkInstance)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_servicelocator_get, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, throwException)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_servicelocator_set, 0, 0, 2)
	ZEND_ARG_INFO(0, id)
	ZEND_ARG_INFO(0, definition)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_servicelocator_clear, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_servicelocator_getcomponents, 0, 0, 0)
	ZEND_ARG_INFO(0, returnDefinitions)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_servicelocator_setcomponents, 0, 0, 1)
	ZEND_ARG_INFO(0, components)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yii_di_servicelocator_method_entry) {
	PHP_ME(yii_di_ServiceLocator, __get, arginfo_yii_di_servicelocator___get, ZEND_ACC_PUBLIC)
	PHP_ME(yii_di_ServiceLocator, __isset, arginfo_yii_di_servicelocator___isset, ZEND_ACC_PUBLIC)
	PHP_ME(yii_di_ServiceLocator, has, arginfo_yii_di_servicelocator_has, ZEND_ACC_PUBLIC)
	PHP_ME(yii_di_ServiceLocator, get, arginfo_yii_di_servicelocator_get, ZEND_ACC_PUBLIC)
	PHP_ME(yii_di_ServiceLocator, set, arginfo_yii_di_servicelocator_set, ZEND_ACC_PUBLIC)
	PHP_ME(yii_di_ServiceLocator, clear, arginfo_yii_di_servicelocator_clear, ZEND_ACC_PUBLIC)
	PHP_ME(yii_di_ServiceLocator, getComponents, arginfo_yii_di_servicelocator_getcomponents, ZEND_ACC_PUBLIC)
	PHP_ME(yii_di_ServiceLocator, setComponents, arginfo_yii_di_servicelocator_setcomponents, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
