
extern zend_class_entry *yii_di_instance_ce;

ZEPHIR_INIT_CLASS(yii_di_Instance);

PHP_METHOD(yii_di_Instance, __construct);
PHP_METHOD(yii_di_Instance, of);
PHP_METHOD(yii_di_Instance, ensure);
PHP_METHOD(yii_di_Instance, get);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_instance___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_instance_of, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_instance_ensure, 0, 0, 1)
	ZEND_ARG_INFO(0, reference)
	ZEND_ARG_INFO(0, type)
	ZEND_ARG_INFO(0, container)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_instance_get, 0, 0, 0)
	ZEND_ARG_INFO(0, container)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yii_di_instance_method_entry) {
	PHP_ME(yii_di_Instance, __construct, arginfo_yii_di_instance___construct, ZEND_ACC_PROTECTED|ZEND_ACC_CTOR)
	PHP_ME(yii_di_Instance, of, arginfo_yii_di_instance_of, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_di_Instance, ensure, arginfo_yii_di_instance_ensure, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_di_Instance, get, arginfo_yii_di_instance_get, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
