
extern zend_class_entry *yii_base_exitexception_ce;

ZEPHIR_INIT_CLASS(yii_base_ExitException);

PHP_METHOD(yii_base_ExitException, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_exitexception___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, status)
	ZEND_ARG_INFO(0, message)
	ZEND_ARG_INFO(0, code)
	ZEND_ARG_OBJ_INFO(0, previous, yii\\base\\Exception, 1)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yii_base_exitexception_method_entry) {
	PHP_ME(yii_base_ExitException, __construct, arginfo_yii_base_exitexception___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_FE_END
};
