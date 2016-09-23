
extern zend_class_entry *yii_di_notinstantiableexception_ce;

ZEPHIR_INIT_CLASS(yii_di_NotInstantiableException);

PHP_METHOD(yii_di_NotInstantiableException, __construct);
PHP_METHOD(yii_di_NotInstantiableException, getName);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_di_notinstantiableexception___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, class)
	ZEND_ARG_INFO(0, message)
	ZEND_ARG_INFO(0, code)
	ZEND_ARG_OBJ_INFO(0, previous, Exception, 1)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yii_di_notinstantiableexception_method_entry) {
	PHP_ME(yii_di_NotInstantiableException, __construct, arginfo_yii_di_notinstantiableexception___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(yii_di_NotInstantiableException, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
