
extern zend_class_entry *yii_base_invalidvalueexception_ce;

ZEPHIR_INIT_CLASS(yii_base_InvalidValueException);

PHP_METHOD(yii_base_InvalidValueException, getName);

ZEPHIR_INIT_FUNCS(yii_base_invalidvalueexception_method_entry) {
	PHP_ME(yii_base_InvalidValueException, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
